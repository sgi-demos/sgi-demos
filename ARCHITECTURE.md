# Architecture

This document describes how `sgi-demos` runs unmodified (or nearly so) 1980s-90s
Silicon Graphics demo source code on modern web browsers and hardware.

The user-facing overview and build instructions live in [README.md](README.md).
This document is for those who want to understand the internals — what lies
between the original SGI source and the browser/native rendered pixels.

## Goals

1. **Source-level preservation.** Demo `.c` and `.h` files should match the
   original SGI code as closely as possible. The host environment adapts to the
   demo.
2. **Wide accessibility.** A browser link is the lowest possible barrier to
   experiencing this software. Anything that requires the user to install
   something, or for the developer to be running a particular native platform,
   is disallowed.
3. **Cross-platform parity.** Native (macOS, Linux, Windows) and web (Emscripten)
   builds share one code path as much as possible.
4. **Faithful behavior, not top performance.** Modern hardware is so much
   faster than an SGI workstation that performance is not currently the binding
   constraint. Faithful pacing (30Hz) and visual fidelity are the driving
   factors.

## Overview

```
┌──────────────────────────────────────────────────────────────────────┐
│   Demo source (e.g. demos/twilight/twilight.c)                       │
│   - Original SGI C code, zero to minimal changes                     │
│   - Calls IRIS GL functions: winopen, qdevice, swapbuffers, ...      │
|     to draw 3d graphics and process user input and OS events         |
└───────────────────────────────────────┬──────────────────────────────┘
               ▲                        │  IRIS GL draw calls
               │ IRIS GL events         ▼
┌──────────────┴───────────────────────────────────────────────────────┐
│   libs/libgl  — IRIS GL emulator                                     │
│                                                                      │
│   gl.c            implements IRIS GL drawing and event handling on   |
|                   top of a reference rasterizer + an SDL-backed      |
|                   event/window layer                                 │
│   rasterizer.h    complete rasterizer interface                      │
│   reference_      software implementation of rasterizer interface,   │
│     rasterizer.c  from the Alice 4 project                           │
|   ogl_            TBD: future OpenGLES implementation of rasterizer  |
|     rasterizer.c  interface                                          |
│   events.h        GL event queue interface: winopen, qdevice/qread/  |
|                   qtest, valuator/button state, tie, frame yield     │
│   sdl_events.c    translates SDL events → GL events; implements the  │
│                   frame and event yielding.                          │
│   sdl_framebuffer SDL framebuffer management: reference rasterizer's |
|     .{h,c}        color buffer is uploaded as a OGL textured quad or |
|                   SDL texture and drawn to the SDL window each frame │
└───────────────────────────────────────┬──────────────────────────────┘
                ▲                       │  OpenGLES2 or SDL2
                │ SDL2 events           |  framebuffer texture draw
                |                       ▼
┌───────────────┴──────────────────────────────────────────────────────┐
│   SDL2  (native) / SDL2 + Emscripten + Asyncify  (web)               │
│                                                                      │
│   - Window, GL context, event pump, framebuffer texture upload       │
│   - On native: a normal SDL2 app                                     │
│   - On web: SDL2 over WebGL/Canvas, with emscripten_sleep() enabling |
|     the demo's `while(1)` loop to yield to the browser per frame     │
└──────────────────────────────────────────────────────────────────────┘
```

## The yield-point architecture

The architectural problem this project had to solve: IRIS GL demos were written
to own the event loop. Their `main()` calls `winopen()`, enters a `while(1)`
loop, and never returns. That works fine on native; the OS time-slices around
the demo. On the web it cannot work — the browser's main thread must yield
regularly or the page hangs.

There are three solutions to this:

1. **Restructure the demo's loop into callbacks** This was the project's
   original approach, allowing the host (browser) to drive the demo, but it
   was messy, fragile, and cost some original source fidelity
   (`#define main demo_main` plus `em_while(1)` macro that split the loop).
2. **Run the demo on a thread** (Web Worker via pthreads). Introduces all
   the cross-thread synchronization complexity of any threaded codebase.
   Requires `SharedArrayBuffer`, which requires COOP/COEP HTTP headers, which
   GitHub Pages does not allow without service-worker workarounds.
3. **Compile-time stack saving** via Emscripten's Asyncify. Single thread as
   solution 1, but: the demo's `while(1)` runs to a yield point, Asyncify saves
   the WebAssembly stack, control returns to the browser event loop, and on the
   next browser tick the stack is restored and execution resumes exactly where
   it left off. From the demo's perspective nothing happened. On native, simply
   SDL_Delay() as necessary to run no faster than target FPS.

The architecture was option 1.  After considering option 2, option 3 was adopted
as the new architecture.  Now the original source runs more closely as-is, no
special web tricks are needed (COOP/COEP), native and web share generally share
one code path, and the runtime cost (Asyncify instrumentation) should be
invisible with SGI-era frame rendering on modern devices.

### The yield point

A single function in the IRIS GL emulator is the central yield point:

```c
void events_frame_complete(void);
```

Defined in `libs/libgl/sdl_events.c`. It:

1. Pumps SDL events into the GL event queue (`sdlProcessEvents`).
2. Presents whatever framebuffer was last set via `events_set_framebuffer`
   (uploads the rasterizer's front buffer as a GL texture and draws it).
3. Yields. On Emscripten this is `emscripten_sleep(remaining_ms_in_budget)`
   (or `emscripten_sleep(0)` if the demo ran over budget — the page still
   must yield once per frame). On native it is
   `SDL_Delay(remaining_ms_in_budget)`.

The 30Hz cadence (`DEMO_FPS = 30`) is intentional. Many SGI demos depend on
<= 30Hz pacing for animation timing and physics integrators, and 60Hz
makes some of them (e.g. `ideas`) run too fast. The pacing is enforced
identically on native and web.

### Where the demo yields

Four call sites route through `events_frame_complete()`:

| Call site | When demos hit it |
|---|---|
| `swapbuffers()` | Double-buffered demos call this at the end of every frame. After the rasterizer pointer flip, the SDL-side framebuffer pointer is updated (the only place this is needed). |
| `gflush()` | Single-buffered demos call this at the end of every frame. The framebuffer pointer hasn't changed since `winopen`, so no re-pointing is needed. |
| `qtest()` / `qread()` / `getbutton()` / `getvaluator()` | Throttled safety net (`yieldByEventQuery` in `sdl_events.c`). Demos like `twilight` don't call `swapbuffers` or `gflush` — they only poll input waiting for REDRAW events. To keep these demos from hanging the browser, every event-poll function runs a yield iff at least one frame budget has elapsed since the last yield. |
| `dopup()` | Pop-up menu modal loop. Calls `events_frame_complete` directly, with no rasterizer swap, so the menu composited onto the front buffer is preserved across iterations. Currently disabled on Emscripten pending testing and mouse pointer integration. |

### Build considerations

The critical Emscripten flag to enable yielding to the browser:

```makefile
EM_ASYNCIFY = -sASYNCIFY -sASYNCIFY_STACK_SIZE=65536
```

`-sASYNCIFY` instruments the call chain so `emscripten_sleep` can pause and
resume the WebAssembly stack. `ASYNCIFY_STACK_SIZE=65536` allocates 64KB
to hold the saved stack during a yield — probably generous enough for the
demos, but can be expanded further if necessary.

Code-size cost of Asyncify on the wasm side is roughly 30-50%. For 1980s-90s
code running on 2026 hardware this should be invisible.

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
window system poking the demo, so the SDL layer synthesizes them iff the demo
has subscribed to `REDRAW` via `qdevice(REDRAW)`:

1. On SDL window expose, shown, restored, focus-gained, or size-changed events.
2. Periodically (once per frame interval) from `yieldByEventQuery`.

This keeps demos like `twilight` — which only repaint in response to `REDRAW`
— alive in an environment that would otherwise never tell them to repaint.

## SDL initialization lifecycle

There is no longer a host-side `main()`. The demo's real `main()` is the program
entry point on both native and web. SDL initialization is **lazy**: the first call
to `events_winopen()` (which IRIS GL's `winopen()` delegates to) does the full
SDL init — `sdlInitWindow`, `sdlInitFramebufferTexture` — and registers
`atexit(sdlFreeFramebufferTexture)` for cleanup.

This matches the original IRIS GL convention: demos call `prefsize()` and
`prefposition()` to declare what they want, then `winopen()` to actually
create the window. The lazy init pattern lets the demo control its own window
title, framebuffer size, and setup order without the host getting in the way.
Note however that framebuffer size is currently fixed regardless of what the demo
specifies - this is a future todo when dynamic framebuffer resizing is implemented.

## Rasterizer

The IRIS GL implementation uses a software rasterizer adapted from the
[Alice 4](https://lkesteloot.github.io/alice/alice4/) project. It writes
into a CPU-side framebuffer, which `sdl_framebuffer.c` uploads as an
OpenGLES 2 texture and draws as an OpenGL quad onto the SDL window each frame.
An SDL texture rendering path is also available.

The long-term goal is to provide a true OpenGLES rasterizer (drawing directly
to the GPU instead of via a CPU framebuffer), which would unlock arbitrary window
sizes and performant texture mapping. The framebuffer-texture path is a stepping
stone as it isolates the rest of the system from how rasterization happens, so a
future rasterizer swap touches one file.

## Build system

Each demo has a short `Makefile`, specifying the APPNAME and any demo-specific build
flags

```makefile
APPNAME=bounce
EM_PRELOAD=--preload-file canstick.bin --preload-file doughnut.bin --preload-file logo.bin --preload-file martini.bin --preload-file vw.bin --preload-file x29.bin
include ../../makefiles/make_demo.mk
```

`makefiles/make_demo.mk` builds both a native binary (`bin-$(OS)-$(HW)/$(APPNAME)`)
and an Emscripten target (`web/$(APPNAME).html` + `.js` + `.wasm`). The
shared logic, including platform detection, SDL/GLES paths, and the
Asyncify flags, lives in `makefiles/platform.mk`.

## Source modifications

Per the preservation goal, demo source modifications are kept minimal. In
practice the only common modification is:

```c
#include "EM_SYSTEM.h"
```

…which provides shims for 1980s and old UNIX system calls, and browser-compatible
replacements for `buttonfly`'s `system()` and `popen()` calls.

Some demos require additional small fixes — usually for C90 strictness, for
`-fcommon` quirks (insect's globals), or for network play in `arena` and `flight`.
These are noted in the demos' own subdirectories and represent the irreducible
delta between 40 year old SGI hardware and modern browsers and devices.

## Directory layout

```
demos/                One subdirectory per demo, containing original
                      source and a one-line Makefile

include/gl/           IRIS GL public headers: gl.h, device.h
                      Old-to-modern shims: EM_SYSTEM.h

include/demo_include/ Shared demo utilities (port.h, slider.h, etc.)

libs/libgl/           The IRIS GL emulator (this is where the architecture
                      lives — gl.c, sdl_events.c, sdl_framebuffer.c,
                      reference_rasterizer.c)

libs/libdemo/         Original SGI demo utility libraries
libs/portlib/

libs/libgles/         OpenGLES 2 headers + platform libraries

makefiles/            Shared build rules
```

## Future directions

There's now a relatively clean foundation for building out this project in
these major directions:

- **OpenGLES implementation of IRIS GL rendering** Add a new `ogl_rasterizer.c`
implementation of `rasterizer.h`, supplanting `reference_rasterizer.c` once it
is fully working.  Use [IGL](https://github.com/sgi-demos/igl) as a starting
point for this implementation.

- **Complete IrisGL demo set** Complete the full set of IrisGL demo ports.
Highlights here include the last IrisGL version of `flight`, `electropaint`,
and `gview` (which is well along in the reversing process - see `demos\gview`).

- **Add OpenGL demos** Extend the project to run OpenGL SGI demos.  This
will require reworking some project structure since the project is currently
IrisGL centric.  Use [GL4ES](https://github.com/sgi-demos/gl4es) and/or
something similar translate old immediate-mode OpenGL calls
to modern retained-mode OpenGL(ES2).

- **Add GLUT demos** Extend the project to run GLUT SGI demos.  GLUT does
its own event handling, and Emscripten has a GLUT implementation already.
However, it'd be interesting to see if a more robust approach would be to
provide an SDL2-based port of [FreeGLUT](https://github.com/freeglut/freeglut)
 and rely on Emscripten's SDL2 implementation instead.

- **Add Performer and Inventor demos*** Extend the project to run key
SGI Performer and Inventor demos. [Inventor](https://github.com/sgi-demos/sgi-inventor) has many open source ports, and [Performer](https://github.com/sgi-demos/sgi-performer) could potentially be reversed via Ghidra and AI tools.
These scene-graph APIs sit on top of OpenGL; so the OpenGL rendering layer could be reused.
