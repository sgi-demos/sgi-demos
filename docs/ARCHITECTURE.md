# Architecture

This document describes how `sgi-demos` runs original 1980s-90s Silicon Graphics demo source code on modern web browsers and hardware. It is for those who want to understand the internals — what lies between the original SGI source and the browser/native rendered pixels — and why it was done that way.

For user-facing overview and build instructions, see [README.md](README.md).

## Goals

1. **Source preservation.** Original SGI demo source should compile unaltered, or as closely as possible to the original. The emulator should adapt to the demo code, not the other way round.
2. **Wide accessibility.** A browser link is the lowest possible barrier to experiencing this software. There is no requirement for the user to install something, or for the developer to be running a particular native platform.
3. **Cross-platform parity.** Native (macOS, Linux, Windows) and web (Emscripten) builds share the same code path as much as possible.
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
                      Old-to-modern shims: demo_shim.h

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

The demo's `main()` is the program entry point on both native and web. The initial IRIS GL `winopen()` call does the full SDL initialization including `sdlInitWindow` window setup, `sdlInitFramebufferTexture` framebuffer allocation, and  `atexit(sdlFreeFramebufferTexture)` exit handler specification.

This matches the original IRIS GL convention that demos call `prefsize()` and `prefposition()` to declare what they want, then `winopen()` to actually create the window. Note however, that framebuffer size and position is currently fixed regardless of what the demo specifies. This is a future TODO when dynamic framebuffer resizing is implemented.

## Rasterization

The IRIS GL implementation uses a software rasterizer forked from the [Alice 4](https://lkesteloot.github.io/alice/alice4/) project. It writes into a CPU-side framebuffer, which `sdl_framebuffer.c` then uploads to an OpenGLES2 (OGLES2) texture applied to quad geometry. An alternate SDL texture rendering path is also available for reference/debugging against the OGLES2 path.

The long-term rasterization goal however is to provide a full OGLES2 rasterizer (IRIS GL calls translated and sent directly to the GPU), which would unlock arbitrary window sizes and performant texture mapping. Not to mention eliminating the current irony of a software rasterizer doing the work that was done by a hardware rasterizer some 40 years ago. The framebuffer-texture path is a stepping stone toward this full OGLES2 rasterizer goal.

### Color-index (colormap) mode and the palette LUT

SGI hardware in colormap mode stored a color *index* per pixel and resolved it through the palette LUT on scan-out, so a `mapcolor()` call recolored already-drawn pixels instantly. Most colormap demos never rely on this (they map their palette once at startup), so the shim normally resolves indices to RGB per vertex and rasterizes plain RGB. For demos that edit the palette live (cedit), the reference rasterizer additionally keeps a per-pixel color-index buffer, written in parallel with the RGB buffer (`screen_vertex.ci`, flat per primitive). At each present, if the colormap changed since the pixels were drawn, the front RGB buffer is re-derived from the CI buffer through the current colormap (`rasterizer_resolve_ci_to_rgb`) — the LUT emulation. `readpixels()`/`getapixel()` also read from this buffer. The GLES2 rasterizer keeps no CI buffer; a per-demo quirk in `gl.c` (`apply_demo_quirks`) selects the reference rasterizer for the demos that need it.

## Browser yielding

An architectural problem with this project was that IRIS GL demos were written to own the event loop: `main()` calls `winopen()`, then enters a `while(1)` loop and never exits. That works fine on native, but on the web it cannot work — the browser's main thread must yield regularly or the page hangs.

Three solutions were tried/considered:

1. **Restructure the demo's loop into callbacks** This was the project's original approach, allowing the host (browser) to drive the demo.  However, due to preprocessor macro trickery required to split the demo into initialization and event loops, it was messy, fragile, and cost some original source fidelity where macros couldn't help.

2. **Run the demo in its own thread** (Web Worker via pthreads). This would replace macro complexity with the synchronization complexity of any threaded codebase. It would also require `SharedArrayBuffer`, which requires COOP/COEP HTTP headers, which requires service-worker workarounds to run on GitHub Pages or else a self-hosted domain.

3. **Use Emscripten Asyncify (emscripten_sleep)**  In this approach, the demo's `while(1)` runs to a yield point, Asyncify saves the WebAssembly stack, control returns to the browser event loop, and on the next browser tick (or after sufficient sleep to not exceed target FPS) the stack is restored and execution resumes exactly where it left off. From the demo's perspective nothing happened. On native, we simply SDL_Delay() as necessary to run no faster than target FPS.

The architecture had been option 1.  Option 2 was then considered, but traded one kind of complexity for another.  Option 3 was chosen as it is the best of options 1 and 2: single threaded simplicity as with option 1, no macro trickery as with option 2.  Now the original source runs more closely as-is, no special preprocessor nor web tricks are needed (COOP/COEP), native and web share generally share one code path, and the runtime cost of asyncify should be negligible with SGI-era code running on modern devices.

### Central yield point

Browser yielding was implemented by defining this function as the central yield location:

```c
void events_frame_complete(void);
```

Defined in `libs/libgl/sdl_events.c`, it:
1. Pumps SDL events into the GL event queue (`sdlProcessEvents`).
2. Presents whatever framebuffer was last set via `events_set_framebuffer` (uploads the rasterizer's front buffer as a GL texture and draws it).
3. Yields. On Emscripten this is `emscripten_sleep(remaining_ms_in_budget)` (or `emscripten_sleep(0)` if the demo ran over budget — the page still must yield once per frame). On native it simply sleeps with `SDL_Delay(remaining_ms_in_budget)`.

The 30Hz target framerate (`DEMO_FPS = 30`) is intentional. Many SGI demos depend on <= 30Hz pacing for animation timing and physics integrators, and 60Hz makes some of them (e.g. `ideas`) run too fast. The pacing is enforced identically on native and web.

### Where do demos yield?

These call sites all route through `events_frame_complete()`:

| Call site | When demos hit it |
|---|---|
| `swapbuffers()` | Double-buffered demos call this at the end of every frame. After the rasterizer pointer flip, the SDL-side framebuffer pointer is updated (the only place this is needed). |
| `gflush()` | Single-buffered demos call this at the end of every frame. |
| `qtest()` / `qread()` / `getbutton()` / `getvaluator()` | Throttled safety net (`yieldByEventQuery` in `sdl_events.c`). Demos like `twilight` don't call `swapbuffers` or `gflush` — they only poll input waiting for REDRAW events. To keep these demos from hanging the browser, every event-poll function yields when at least one frame budget has elapsed since the last yield. |
| `dopup()` | Pop-up menu modal loop. Calls `events_frame_complete` directly, with no rasterizer swap, so the menu composited onto the front buffer is preserved across iterations. Currently disabled for web, pending testing and mouse pointer integration. |

## Event handling

### Two queues

Two separate event queues are maintained, one SDL and the other IRIS GL:

```
SDL events ──► sdl_input_queue ──► (drained on demand) ──► input_queue_{device,val} ──► demo
               (libgl/sdl_events.c)                        (libgl/gl.c)
```

The SDL-side queue (`sdl_input_queue` in `sdl_events.c`) buffers translated SDL events. The GL-side queue (`input_queue_{device,val}` in `gl.c`) is what `qtest` / `qread` read from. When the GL queue is empty, `qtest` calls `events_qread_start` / `events_qread_continue` to drain whatever is in the SDL queue. This split keeps the IRIS GL semantics — including filtering by `qdevice` / `unqdevice` and ordering of tied valuators — entirely inside `gl.c`, where it matches the original API.

### REDRAW synthesis

IRIS GL demos that handle window events expect the window system to inject `REDRAW` events when the window needs repainting. On SGI workstations these came from the X server / 4Sight. In our environment there is no external window system poking the demo, so the SDL layer synthesizes them when the demo has subscribed to `REDRAW` via `qdevice(REDRAW)`. It does this periodically (at most once per frame interval) during GL event queries.  This enables demos like `twilight` to function, which only repaint in response to `REDRAW` events and don't utilize swapbuffers() or gflush() to signal the end of a frame.

### Event pump integrity

Some IRIS GL demos depend on atomic event groups in `sdl_input_queue`. For example, `buttonfly` ties `MOUSEX`/`MOUSEY` to `LEFTMOUSE` and expects `qread()` to return that three-event group with no other events interleaved. This implies the following invariant: **any events enqueued during one `sdlProcessEvents` call must appear contiguously in `sdl_input_queue`.**

A reentrant pump (e.g. via a yield from inside an event handler) would violate this by injecting events mid-group. Specifically, yieldByEventQuery() could inject a REDRAW into a group of tied events if not guarded (see REDRAW synthesis above).

To protect against this, a reentrancy flag is set for the duration of `sdlProcessEvents`.  Then all yield paths in `sdl_events.c` implement guards by checking this reentrancy flag and early-returning if set.  The skipped yield is fulfilled on the next yielding call the demo makes outside sdlProcessEvents. As a further safety measure against future code, a direct reentrant call to `sdlProcessEvents` itself — which the current yield guards may not intercept — is caught by a fatal abort.

## Build system

Each demo has a short `Makefile`, specifying the APPNAME and any demo-specific build flags, e.g.:

```makefile
APPNAME=bounce
EM_PRELOAD=--preload-file canstick.bin --preload-file doughnut.bin --preload-file logo.bin --preload-file martini.bin --preload-file vw.bin --preload-file x29.bin
include ../../makefiles/make_demo.mk
```

`makefiles/make_demo.mk` builds both a native binary (`bin-$(OS)-$(HW)/$(APPNAME)`) and an Emscripten target (`web/$(APPNAME).html` + `.js` + `.wasm`). The shared logic, including platform detection, SDL/GLES paths, and the Asyncify flags, lives in `makefiles/platform.mk`.

Emscripten flags to enable demos to yield to the browser:

```makefile
EM_ASYNCIFY = -sASYNCIFY -sASYNCIFY_STACK_SIZE=65536
```

`-sASYNCIFY` instruments the call chain so `emscripten_sleep` can pause and resume the WebAssembly stack. `ASYNCIFY_STACK_SIZE=65536` allocates 64KB to hold the saved stack during a yield — probably generous enough for the demos, but can be expanded further if necessary. Asyncify increases WASM code size, but for 1980s-90s code running on 2026 hardware, this cost should be negligible.

## Demo source modifications

Per the preservation goal, original demo source compiles unmodified for the most part.  Translation between old code and new compilers/headers happens in `platform.mk`: see `DEMO_CODE_*` and `demo_shim.h` in particular. Some demos require additional small fixes, such as `-fcommon` LLVM compiler workaround (insect's globals), or for network play in `arena` and `flight`.

## Future directions

This project now has a relatively clean foundation for building out further in these main directions:

- **OpenGLES implementation of IRIS GL rendering** - Add a new `ogl_rasterizer.c` implementation of `rasterizer.h`, supplanting `reference_rasterizer.c` once it is fully working.  Use [IGL](https://github.com/sgi-demos/igl) as a starting point for this implementation.

- **Complete the IrisGL demo set** - Highlights here include the last IrisGL version of `flight`, and `gview` (which is making progress in the reversing process - see `demos\gview`). `electropaint` is in, running headless of its panel-library control panels (see `demos/electropaint/README.md`); a fuller port would bring the panels back.

- **Add OpenGL demos** - This will require reworking some project structure since the project is currently IrisGL centric.  Use [GL4ES](https://github.com/sgi-demos/gl4es) and/or something similar, to translate old immediate-mode OpenGL calls to modern retained-mode OpenGL(ES2).

- **Add GLUT demos** - GLUT does its own event handling, and Emscripten has a GLUT implementation already. However, it might be interesting to see if a more robust approach would be to provide an OpenGLES2/SDL2-based port of [FreeGLUT](https://github.com/freeglut/freeglut) and lean on Emscripten's SDL2 implementation and OpenGLES2-to-WebGL transpiling.

- **Add Performer and Inventor demos** - [Inventor](https://github.com/sgi-demos/sgi-inventor) already has many open source ports, and [Performer](https://github.com/sgi-demos/sgi-performer) could potentially be reversed via Ghidra and AI tools (Performer file format loader code is already open source). These scene-graph APIs sit on top of OpenGL; so the OpenGL rendering layer could be reused.
