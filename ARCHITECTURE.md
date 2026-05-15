# Architecture

This document describes how `sgi-demos` runs original (or nearly so) 1980s-90s Silicon Graphics demo source code on modern web browsers and hardware.

See [README.md](README.md) for user-facing overview and build instructions. This document is for those who want to understand the internals — what lies between the original SGI source and the browser/native rendered pixels — and why it was done that way.

## Goals

1. **Source preservation.** Original SGI demo source should compile unaltered, or as closely as possible to the original. The emulator should adapt to the demo code.
2. **Wide accessibility.** A browser link is the lowest possible barrier to experiencing this software. Anything that requires the user to install something, or for the developer to be running a particular native platform, is disallowed.
3. **Cross-platform parity.** Native (macOS, Linux, Windows) and web (Emscripten) builds share one code path as much as possible.
4. **Faithful behavior, not top performance.** Modern hardware is so much faster than an SGI workstation that performance is not currently the binding constraint. Faithful pacing (30Hz) and visual fidelity are the driving factors.

## Overview

### Data flow
```
┌──────────────────────────────────────────────────────────────────────┐
│   Demo source (e.g. demos/twilight/twilight.c)                       │
│   - Original SGI C code, zero to minimal changes                     │
│   - Calls IRIS GL functions: winopen, qdevice, swapbuffers, ...      │
|     to draw graphics and process user input and OS events            |
└───────────────────────────────────────┬──────────────────────────────┘
               ▲                        │  IRIS GL draw calls
               │ IRIS GL events         ▼
┌──────────────┴───────────────────────────────────────────────────────┐
│   libs/libgl  — IRIS GL emulator                                     │
│                                                                      │
│   gl.c            implements IRIS GL drawing and event handling on   |
|                   top of a reference rasterizer + an SDL-backed      |
|                   event/window layer                                 │
│                                                                      │
│   rasterizer.h    complete rasterizer interface                      │
│   reference_      software implementation of rasterizer interface,   │
│     rasterizer.c  from the Alice 4 project                           │
|   ogl_            TBD: future OpenGLES implementation of rasterizer  |
|     rasterizer.c  interface                                          |
│                                                                      │
│   events.h        GL event queue interface: winopen, qdevice/qread/  |
|                   qtest, valuator/button state, tie, frame yield     │
│   sdl_events.c    translates SDL events → GL events; implements the  │
│                   frame and event yielding.                          │
│                                                                      │
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

### Directory layout

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

## Initialization

The demo's real `main()` is now the program entry point on both native and web. SDL initialization is lazy: the initial IRIS GL `winopen()` call does the full SDL initialization — `sdlInitWindow` window setup, `sdlInitFramebufferTexture` framebuffer allocation, and  `atexit(sdlFreeFramebufferTexture)` exit handler for cleanup.

This matches the original IRIS GL convention: demos call `prefsize()` and `prefposition()` to declare what they want, then `winopen()` to actually create the window. Note however that framebuffer size and position is currently fixed regardless of what the demo specifies - this is a future todo when dynamic framebuffer resizing is implemented.

## Rasterization

The IRIS GL implementation uses a software rasterizer forked from the [Alice 4](https://lkesteloot.github.io/alice/alice4/) project. It writes
into a CPU-side framebuffer, which `sdl_framebuffer.c` then uploads as an OpenGLES2 texture and draws onto a quad in the SDL window each frame. An alternate SDL texture rendering path is also available for reference/debugging against the OGLES2 path.

The long-term rasterization goal however, is to provide a true OpenGLES rasterizer (drawing directly to the GPU), which would unlock arbitrary window
sizes and performant texture mapping. The framebuffer-texture path is a stepping stone as it isolates the rest of the system from how rasterization happens, so a future rasterizer swap touches one file.

## Event handling

### Two queues

Two separate event queues are maintained, one SDL and the other IRIS GL:

```
SDL events ──► sdl_input_queue ──► (drained on demand) ──► input_queue ──► demo
               (libgl/sdl_events.c)                        (libgl/gl.c)
```

The SDL-side queue (`sdl_input_queue` in `sdl_events.c`) buffers translated SDL events. The GL-side queue (`input_queue` in `gl.c`) is what `qtest` /
`qread` read from. When the GL queue is empty, `qtest` calls `events_qread_start` / `events_qread_continue` to drain whatever is in the SDL queue. This split keeps the IRIS GL semantics — including filtering by `qdevice` / `unqdevice` and ordering of tied valuators — entirely inside `gl.c`, where it matches the original API.

### REDRAW synthesis

IRIS GL demos that handle window events expect the window system to inject `REDRAW` events when the window needs repainting. On SGI workstations these came from the X server / 4Sight. In our environment there is no external window system poking the demo, so the SDL layer synthesizes them when the demo has subscribed to `REDRAW` via `qdevice(REDRAW)`:

1. On SDL window expose, shown, restored, focus-gained, or size-changed events.
2. Periodically (once per frame interval).  This keeps demos like `twilight`, which only repaint in response to `REDRAW`, alive in an environment that would otherwise never tell them to repaint.
   
## Browser yielding

An architectural problem with this project was that IRIS GL demos were written to own the event loop: `main()` calls `winopen()`, then enters a `while(1)` loop and never returns. That works fine on native, but on the web it cannot work — the browser's main thread must yield regularly or the page hangs.

Three solutions were tried/considered:

1. **Restructure the demo's loop into callbacks** This was the project's original approach, allowing the host (browser) to drive the demo, but it was messy, fragile, and cost some original source fidelity (preprocessor macro trickery that split the demo loop).
2. **Run the demo on its own thread** (Web Worker via pthreads). This would introduce all the cross-thread synchronization complexity of any threaded codebase. It would require `SharedArrayBuffer`, which requires COOP/COEP HTTP headers, which requires service-worker workarounds to run on GitHub Pages or else a self-hosted domain.
4. **Compile-time stack saving** via Emscripten's Asyncify. This is single thread the same as solution 1, but with a twist: the demo's `while(1)` runs to a yield point, Asyncify saves the WebAssembly stack, control returns to the browser event loop, and on the next browser tick the stack is restored and execution resumes exactly where it left off. From the demo's perspective nothing happened. On native, we simply SDL_Delay() as necessary to run no faster than target FPS.

The architecture had been option 1.  Option 2 was then considered, but added complexity.  Option 3 was adopted as the new solution.  Now the original source runs more closely as-is, no special preprocessor nor web tricks are needed (COOP/COEP), native and web share generally share one code path, and the runtime cost of asyncify should be negligible with SGI-era code running on modern devices.

### Central yield point

This function in the IRIS GL emulator is the central yield point:

```c
void events_frame_complete(void);
```

Defined in `libs/libgl/sdl_events.c`, it:
1. Pumps SDL events into the GL event queue (`sdlProcessEvents`).
2. Presents whatever framebuffer was last set via `events_set_framebuffer` (uploads the rasterizer's front buffer as a GL texture and draws it).
3. Yields. On Emscripten this is `emscripten_sleep(remaining_ms_in_budget)` (or `emscripten_sleep(0)` if the demo ran over budget — the page still must yield once per frame). On native it is `SDL_Delay(remaining_ms_in_budget)`.

The 30Hz cadence (`DEMO_FPS = 30`) is intentional. Many SGI demos depend on <= 30Hz pacing for animation timing and physics integrators, and 60Hz
makes some of them (e.g. `ideas`) run too fast. The pacing is enforced identically on native and web.

### Where do demos yield?

These call sites all route through `events_frame_complete()`:

| Call site | When demos hit it |
|---|---|
| `swapbuffers()` | Double-buffered demos call this at the end of every frame. After the rasterizer pointer flip, the SDL-side framebuffer pointer is updated (the only place this is needed). |
| `gflush()` | Single-buffered demos call this at the end of every frame. |
| `qtest()` / `qread()` / `getbutton()` / `getvaluator()` | Throttled safety net (`yieldByEventQuery` in `sdl_events.c`). Demos like `twilight` don't call `swapbuffers` or `gflush` — they only poll input waiting for REDRAW events. To keep these demos from hanging the browser, every event-poll function yields when at least one frame budget has elapsed since the last yield. |
| `dopup()` | Pop-up menu modal loop. Calls `events_frame_complete` directly, with no rasterizer swap, so the menu composited onto the front buffer is preserved across iterations. Currently disabled for web, pending testing and mouse pointer integration. |

### Build considerations

The Emscripten flags to enable demos to yield to the browser:

```makefile
EM_ASYNCIFY = -sASYNCIFY -sASYNCIFY_STACK_SIZE=65536
```

`-sASYNCIFY` instruments the call chain so `emscripten_sleep` can pause and resume the WebAssembly stack. `ASYNCIFY_STACK_SIZE=65536` allocates 64KB to hold the saved stack during a yield — probably generous enough for the demos, but can be expanded further if necessary. Asyncify increases WASM code size, but for 1980s-90s code running on 2026 hardware, this cost should be negligible.

## Build system

Each demo has a short `Makefile`, specifying the APPNAME and any demo-specific build flags, e.g.:

```makefile
APPNAME=bounce
EM_PRELOAD=--preload-file canstick.bin --preload-file doughnut.bin --preload-file logo.bin --preload-file martini.bin --preload-file vw.bin --preload-file x29.bin
include ../../makefiles/make_demo.mk
```

`makefiles/make_demo.mk` builds both a native binary (`bin-$(OS)-$(HW)/$(APPNAME)`) and an Emscripten target (`web/$(APPNAME).html` + `.js` + `.wasm`). The shared logic, including platform detection, SDL/GLES paths, and the Asyncify flags, lives in `makefiles/platform.mk`.

## Source modifications

Per the preservation goal, demo source modifications are kept minimal. In practice the only common modification is to add this header at the top of the main demo file:

```c
#include "EM_SYSTEM.h"
```

…which provides shims for 1980s and old UNIX system calls, and browser-compatible replacements for `buttonfly`'s `system()` and `popen()` calls.

Some demos require additional small fixes — usually for C90 strictness, for `-fcommon` LLVM compiler workarounds (insect's globals), or for network play in `arena` and `flight`. These are noted in the demos' own subdirectories and represent the irreducible delta between old SGI hardware and modern browsers and devices.

## Future directions

This project now has a relatively clean foundation for building out further in these main directions:

- **OpenGLES implementation of IRIS GL rendering** - Add a new `ogl_rasterizer.c` implementation of `rasterizer.h`, supplanting `reference_rasterizer.c` once it is fully working.  Use [IGL](https://github.com/sgi-demos/igl) as a starting point for this implementation.

- **Complete the IrisGL demo set** - Highlights here include the last IrisGL version of `flight`, `electropaint`, and `gview` (which is making progress in the reversing process - see `demos\gview`).

- **Add OpenGL demos** - This will require reworking some project structure since the project is currently IrisGL centric.  Use [GL4ES](https://github.com/sgi-demos/gl4es) and/or something similar, to translate old immediate-mode OpenGL calls to modern retained-mode OpenGL(ES2).

- **Add GLUT demos** - GLUT does its own event handling, and Emscripten has a GLUT implementation already. However, it might be interesting to see if a more robust approach would be to provide an OpenGLES2/SDL2-based port of [FreeGLUT](https://github.com/freeglut/freeglut) and lean on Emscripten's SDL2 implementation and OpenGLES2-to-WebGL transpiling.

- **Add Performer and Inventor demos** - [Inventor](https://github.com/sgi-demos/sgi-inventor) already has many open source ports, and [Performer](https://github.com/sgi-demos/sgi-performer) could potentially be reversed via Ghidra and AI tools (Performer file format loader code is already open source). These scene-graph APIs sit on top of OpenGL; so the OpenGL rendering layer could be reused.
