# Architecture

This document describes how `sgi-demos` runs unmodified (or nearly so) 1980s-90s
Silicon Graphics demos in a modern web browser and on present-day desktops.

The user-facing overview, demo list, and build instructions live in
[README.md](README.md). This document is for contributors who want to understand
the internals — what lies between the original SGI source and the canvas pixels.

## Goals

The project optimizes for, in order:

1. **Source-level preservation.** Demo `.c` files should match the original SGI
   code as closely as possible. The host environment adapts to the demo, never
   the reverse.
2. **Wide accessibility.** A browser link is the lowest possible barrier to
   experiencing this software. Anything that requires the user to install
   tooling, accept warning dialogs, or configure server headers is a regression.
3. **Cross-platform parity.** Native (macOS, Linux, Windows) and web (Emscripten)
   builds share one code path. The only `#ifdef __EMSCRIPTEN__` in the runtime
   is the one that selects between `emscripten_sleep` and `SDL_Delay`.
4. **Faithful behavior, not faithful performance.** Modern hardware is so much
   faster than an IRIS workstation that performance is never the binding
   constraint. Faithful pacing (30Hz) and visual fidelity matter more.

These goals motivate every architectural decision below.

## High-level shape

```
┌─────────────────────────────────────────────────────────────────────┐
│   Demo source (e.g. demos/twilight/twilight.c)                      │
│   - Original SGI C code, lightly touched                            │
│   - Calls IRIS GL functions: winopen, qdevice, swapbuffers, ...     │
└────────────────────────────┬────────────────────────────────────────┘
                             │  IRIS GL API
                             ▼
┌─────────────────────────────────────────────────────────────────────┐
│   libs/libgl  — IRIS GL emulator                                    │
│                                                                     │
│   gl.c            implements IRIS GL on top of a reference          │
│                   rasterizer + an SDL-backed event/window layer     │
│   rasterizer.h    front/back framebuffers in main memory;           │
│   reference_                                                        │
│       rasterizer.c software rasterizer from the Alice 4 project     │
│   events.{h,c}    GL event queue, qdevice/qread/qtest, valuator/    │
│                   button state                                      │
│   sdl_events.c    translates SDL events → GL events; hosts the      │
│                   single platform yield point                       │
│   sdl_framebuffer rasterizer's color buffer is uploaded as a GL     │
│       .{h,c}      texture and drawn to the SDL window each frame    │
└────────────────────────────┬────────────────────────────────────────┘
                             │  SDL2 + OpenGL ES 2
                             ▼
┌─────────────────────────────────────────────────────────────────────┐
│   SDL2  (native) / SDL2 + Emscripten + Asyncify  (web)              │
│                                                                     │
│   - Window, GL context, event pump, framebuffer texture upload      │
│   - On native: a normal SDL2 app                                    │
│   - On web: SDL2 over WebGL2/Canvas, with Asyncify enabling the     │
│     demo's `while(1)` loop to yield to the browser per frame        │
└─────────────────────────────────────────────────────────────────────┘
```

## The yield-point architecture

The architectural problem this project had to solve: IRIS GL demos were written
to own the event loop. Their `main()` calls `winopen()`, enters a `while(1)`
loop, and never returns. That works fine on native; the OS time-slices around
the demo. On the web it cannot work — the browser's main thread must yield
regularly or the page hangs.

There are three families of solutions to this:

1. **Restructure the demo's loop into callbacks** so the host (browser) can
   drive it. Costs source-level fidelity. Was the project's original approach
   (`#define main demo_main` plus `em_while(1)` macro that split the loop).
2. **Run the demo on a thread** (Web Worker via pthreads). Requires
   `SharedArrayBuffer`, which requires COOP/COEP HTTP headers, which GitHub
   Pages does not allow without service-worker workarounds. Also introduces all
   the cross-thread synchronization complexity of any threaded codebase.
3. **Compile-time stack saving** via Emscripten's Asyncify. The demo's
   `while(1)` runs to a yield point, Asyncify saves the WebAssembly stack,
   control returns to the browser event loop, and on the next browser tick the
   stack is restored and execution resumes exactly where it left off. From the
   demo's perspective nothing happened.

The current architecture is option 3. It hits all four project goals: source is
preserved verbatim, no special HTTP headers are needed, native and web share
one code path, and the runtime cost (Asyncify instrumentation) is invisible at
SGI-era frame rates on modern hardware.

### The yield point

A single function in the IRIS GL emulator is the platform touch point:

```c
void events_frame_complete(void);
```

Defined in `libs/libgl/sdl_events.c`. It:

1. Pumps SDL events into the GL event queue (`sdlProcessEvents`).
2. Presents whatever framebuffer was last set via `events_set_framebuffer`
   (uploads the rasterizer's front buffer as a GL texture and draws it).
3. Yields. On Emscripten this is `emscripten_sleep(remaining_ms_in_budget)`
   (or `emscripten_sleep(0)` if the demo ran over budget — the page still
   must yield once per frame). On native it is `SDL_Delay(remaining_ms)`.

The 30Hz cadence (`DEMO_FPS = 30`, `DEMO_TICKS_PER_FRAME_BUDGET = 33ms`) is
intentional. Many SGI demos depend on near-30Hz pacing for animation timing
and physics integrators, and 60Hz makes some of them (e.g. `ideas`) play
visibly too fast. The pacing is enforced identically on native and web.

### Where the demo yields

There are four call sites, each routed through `events_frame_complete()`:

| Call site | When demos hit it |
|---|---|
| `swapbuffers()` | Double-buffered demos call this at the end of every frame. After the rasterizer pointer flip, the SDL-side framebuffer pointer is re-set (the only place that's needed). |
| `gflush()` | Single-buffered demos call this at the end of every frame. The framebuffer pointer hasn't changed since `winopen`, so no re-pointing is needed. |
| `qtest()` / `qread()` / `getbutton()` / `getvaluator()` | Throttled safety net (`yieldByEventQuery` in `sdl_events.c`). Demos like `twilight` don't call `swapbuffers` or `gflush` — they only poll input waiting for REDRAW events. To keep these demos from hanging the browser, every event-poll function runs a yield iff at least one frame budget has elapsed since the last yield. |
| `dopup()` | Pop-up menu modal loop. Calls `events_frame_complete` directly, with no rasterizer swap, so the menu composited onto the front buffer is preserved across iterations. Currently disabled on Emscripten pending UX investigation for touch / small-canvas use. |

The throttle in `yieldByEventQuery` is the key to keeping the cost low. Demos
that poll input in tight inner loops only pay a yield once per 33ms; the rest
of the polls are a single subtraction and branch.

### Why the framebuffer pointer dance is just two lines

The rasterizer maintains two color buffers and a front-buffer pointer that
`rasterizer_swap` flips. The SDL side caches that pointer in
`sdl_framebuffer.c` and uploads it as a GL texture each frame.

Only `rasterizer_swap` changes the pointer. Therefore the SDL side needs to be
re-pointed only where `rasterizer_swap` is called — i.e. inside
`swapbuffers()`. Everywhere else (`gflush`, `dopup`, `yieldByEventQuery`,
`winopen`-time initialization) the pointer is already current.

This keeps `sdl_events.c` free of any rasterizer knowledge:
`events_frame_complete()` takes no arguments and the only reference to
`rasterizer_frontbuffer()` lives in `gl.c`, the layer that owns the rasterizer.

## Event handling

### Two queues

There are two event queues, deliberately kept separate:

```
SDL events ──► sdl_input_queue ──► (drained on demand) ──► input_queue ──► demo
              (libgl/sdl_events.c)                       (libgl/gl.c)
```

The SDL-side queue (`sdl_input_queue` in `sdl_events.c`) buffers translated
SDL events. The GL-side queue (`input_queue` in `gl.c`) is what `qtest` /
`qread` read from. When the GL queue is empty, `qtest` calls
`events_qread_start` / `events_qread_continue` to drain whatever is in the SDL
queue. This split keeps the IRIS GL semantics — including filtering by
`qdevice` / `unqdevice` and ordering of tied valuators — entirely inside
`gl.c`, where it matches the original API.

### REDRAW synthesis

IRIS GL demos that handle window events expect the window system to inject
`REDRAW` events when the window needs repainting. On SGI workstations these
came from the X server / 4Sight. In our environment there is no external
window system poking the demo, so the SDL layer synthesizes them:

1. On SDL window expose, shown, restored, focus-gained, or size-changed events.
2. Periodically (once per frame interval) from `yieldByEventQuery`, *iff* the
   demo has called `qdevice(REDRAW)`. This keeps demos like `twilight` —
   which only repaint in response to `REDRAW` — alive in an environment that
   would otherwise never tell them to repaint.

`gl.c`'s `qdevice(REDRAW)` enqueues one initial REDRAW and also calls
`events_qdevice(REDRAW)` so the SDL side knows to inject future REDRAWs. The
demo's source needs no awareness of this.

## SDL initialization lifecycle

There is no host-side `main()`. The demo's real `main()` is the program entry
point on both native and web. SDL initialization is **lazy**: the first call
to `events_winopen()` (which IRIS GL's `winopen()` delegates to) does the full
SDL init — `sdlInitWindow`, `sdlInitFramebufferTexture` — and registers
`atexit(sdlFreeFramebufferTexture)` for cleanup.

This matches the original IRIS GL convention: demos call `prefsize()` and
`prefposition()` to declare what they want, then `winopen()` to actually
create the window. The lazy init pattern lets the demo control its own window
title, framebuffer size, and setup order without the host getting in the way.

## Rasterizer

The IRIS GL implementation uses a software rasterizer adapted from the
[Alice 4](https://lkesteloot.github.io/alice/alice4/) project. It writes
into a CPU-side framebuffer, which `sdl_framebuffer.c` uploads as an
OpenGL ES 2 texture and draws onto the SDL window each frame.

There is a long-term path toward a true OpenGL ES rasterizer (writing geometry
directly to the GPU instead of via a CPU framebuffer), which would unlock
arbitrary window sizes and proper texture mapping. The framebuffer-texture
path is the stepping stone — it isolates the rest of the system from how
rasterization happens, so a future rasterizer swap touches one file.

## Build system

Each demo has a one-line `Makefile`:

```makefile
APPNAME=twilight
include ../../makefiles/make_demo.mk
```

`makefiles/make_demo.mk` builds both a native binary (`bin-$(OS)-$(HW)/$(APPNAME)`)
and an Emscripten target (`web/$(APPNAME).html` + `.js` + `.wasm`). The
shared logic, including platform detection, SDL/GLES paths, and the
Asyncify flags, lives in `makefiles/platform.mk`.

The critical Emscripten flag is:

```makefile
EM_ASYNCIFY = -sASYNCIFY -sASYNCIFY_STACK_SIZE=65536
```

`-sASYNCIFY` instruments the call chain so `emscripten_sleep` can pause and
resume the WebAssembly stack. `ASYNCIFY_STACK_SIZE=65536` allocates 64KB
to hold the saved stack during a yield — generous enough for the deepest
demo call chains, with room to spare.

Code-size cost of Asyncify on the wasm side is roughly 30-50%. For a
preservation archive running on 2026 hardware this is invisible. Runtime
overhead is sub-millisecond per yield.

## Source modifications

Per the preservation goal, demo source modifications are kept minimal. In
practice the only common modification is:

```c
#include "EM_SYSTEM.h"
```

…which provides browser-compatible replacements for `system()` and `popen()`
when a demo (e.g. `buttonfly`) launches other demos. It's a no-op on native
builds.

Some demos require additional small fixes — usually for C90 strictness, for
`-fcommon` quirks (insect's globals), or for hardware features that no longer
exist (network play in `arena` and `flight`). These are noted in the demos'
own subdirectories and represent the irreducible delta between 1985 SGI
hardware and a 2026 browser.

## Directory layout

```
demos/                One subdirectory per demo, containing original-ish
                      source and a one-line Makefile.

include/gl/           IRIS GL public headers: gl.h, device.h, EM_SYSTEM.h
include/demo_include/ Shared demo utilities (port.h, slider.h, etc.)

libs/libgl/           The IRIS GL emulator (this is where the architecture
                      lives — gl.c, sdl_events.c, sdl_framebuffer.c,
                      reference_rasterizer.c)
libs/libdemo/         Original SGI demo utility library (porting layer)
libs/libgles/         OpenGL ES 2 headers + platform libraries

makefiles/            Shared build rules.
```

## Future directions

The Asyncify-based architecture is a clean foundation for extending the
project beyond IRIS GL. The same yield-point pattern applies to:

- **OpenGL / GLUT demos.** GLUT is already callback-driven (`glutDisplayFunc`,
  `glutIdleFunc`, `glutMainLoop`), so it fits the browser model naturally —
  Asyncify is less of a win there, but the framebuffer / event-translation
  pieces of this project carry over.
- **Performer / Inventor demos.** Scene-graph APIs sitting on top of OpenGL;
  the rendering layer can be the same one this project already has, and the
  scene-graph code is bounded enough to implement incrementally.

Beyond new APIs, near-term improvements tracked in [README.md](README.md)
include OpenGL ES / WebGL rasterization, arbitrary window sizing, per-demo
context/credits overlays, virtual mouse/keyboard hints for touch devices,
and re-enabling `dopup` on Emscripten now that the yield-point architecture
should support it (pending verification).
