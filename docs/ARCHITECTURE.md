# Architecture

This document describes how `sgi-demos` runs original 1980s-90s Silicon Graphics demo source code on modern web browsers and hardware. It is for those who want to understand the internals — what lies between the original SGI source and the browser/native rendered pixels — and why it was done that way.

For the user-facing overview and build instructions, see [README.md](../README.md).

## Goals

1. **Source preservation.** Original SGI demo source should compile unaltered, or as closely as possible to the original. The emulator should adapt to the demo code, not the other way round.
2. **Wide accessibility.** A browser link is the lowest possible barrier to experiencing this software. There is no requirement for the user to install anything, nor for the developer to be working on a particular native platform.
3. **Cross-platform parity.** Native (macOS, Linux, Windows) and web (Emscripten) builds share the same code path as much as possible.
4. **Faithful behavior, not top performance.** Modern hardware is so much faster than an SGI workstation that performance is not currently the binding constraint. Faithful pacing (30Hz) and visual fidelity are the driving factors.

## Overview

### Data flow
```
┌──────────────────────────────────────────────────────────────────────┐
│   Demo source (e.g. demos/twilight/twilight.c)                       │
│   - Original SGI C code, zero to minimal changes                     │
│   - Calls IRIS GL: winopen, qdevice, qread, swapbuffers, ...         │
│     to draw graphics and read user input and window events           │
└──────────────────────────────────────────────────────────────────────┘
     ▲                            │  IRIS GL calls
     │ IRIS GL events             ▼
┌──────────────────────────────────────────────────────────────────────┐
│   libs/libgl — IRIS GL emulator                                      │
│                                                                      │
│   gl.c              the IRIS GL API: state, transforms, lighting,    │
│                     display lists, colormap, fonts, menus, events    │
│                                                                      │
│   rasterizer.h      rasterizer interface; rasterizer.c picks one:    │
│     gles2_rasterizer.c      GPU, OpenGL ES2/3 (default)              │
│     reference_rasterizer.c  CPU, from the Alice 4 project            │
│                                                                      │
│   events.h          GL event queue interface: qdevice, qread, qtest, │
│                     valuator and button state, tie, frame yield      │
│   sdl_events.c      SDL events -> GL events; frame pacing and yield  │
│                                                                      │
│   sdl_framebuffer.c the SDL window and GL context; presents the      │
│                     front buffer as a textured quad in the window    │
└──────────────────────────────────────────────────────────────────────┘
     ▲                            │  GL draw calls, present
     │ SDL events                 ▼
┌──────────────────────────────────────────────────────────────────────┐
│   SDL2 (native) / SDL2 + Emscripten + Asyncify (web)                 │
│                                                                      │
│   - Window, GL context, event pump                                   │
│   - On native: a normal SDL2 app                                     │
│   - On web: SDL2 over WebGL, with emscripten_sleep() letting         │
│     the demo's while(1) loop yield to the browser each frame         │
└──────────────────────────────────────────────────────────────────────┘
```

### Directory layout

```
demos/                One directory per demo: the original source, a short
                      Makefile, placard.json (the demo's record: title,
                      author, year, blurb, inputs), README.md (provenance),
                      and web/, the built web package that GitHub Pages serves
demos/placard.js      The corner card on every demo page, read from placard.json
demos/switches.js     URL switches (?rast=, ?par=) into the environment, per page
demos/gallery.json    The demos on exhibit, for the site's browse page (make gallery)

include/gl/           IRIS GL public headers: gl.h, device.h
include/shim/         Old-to-modern shims: demo_shim.h, sys/termio.h, ...
include/demo_include/ Shared demo utility headers (port.h, slider.h, etc.)

libs/libgl/           The IRIS GL emulator (this is where the architecture
                      lives — see the diagram above)
libs/libdemo/         SGI's demo helper library, built and linked into every demo
libs/portlib/         Paul Haeberli's port library, kept as a source record
                      (not built; libdemo carries the pieces the demos use)
libs/libgles/         OpenGL ES2 and EGL headers, and the ANGLE libraries
                      native builds link against

makefiles/            Shared build rules, and the web page template
scripts/              Placards, the gallery, thumbnails, fonts,
                      frame comparison
tests/smoke/          Headless-browser smoke tests of every web build
tests/native-resize/  Native window-resize harness for the framebuffer fitting
media/                Demo thumbnails (the README grid and the browse page)
```

## Initialization

The demo's `main()` is the program entry point on both native and web. The initial IRIS GL `winopen()` call does the full SDL initialization, including `sdlInitWindow` window and GL context setup, `sdlInitFramebufferTexture` display texture allocation, and the `atexit(sdlFreeFramebufferTexture)` exit handler.

This matches the original IRIS GL convention that demos call `prefposition()` or `keepaspect()` to declare what they want, then `winopen()` to actually create the window. The framebuffer tracks the window: it is resized with the window (keeping the demo's `keepaspect()` ratio if it asked for one) and centered in it. A demo that asks for an exact window with `prefposition()` (the flights and arena, whose layouts are hard-coded to the classic screen) gets a framebuffer of exactly that size instead, scaled to fit the window.

The display also simulates the SGI monitor's pixel shape: SGI framebuffers were 5:4 (1280x1024) shown on 4:3 CRT glass, so each pixel was 16:15 wide. The framebuffer gets 15/16 of the window's columns and the display stretches them back to fill it (`IRISGL_PAR=0` turns this off).

## Rasterization

`libs/libgl/rasterizer.h` is the interface between the IRIS GL implementation in `gl.c` and the code that fills pixels. There are two implementations, chosen once at startup by `rasterizer.c`:

- **gles** (`gles2_rasterizer.c`, the default): IRIS GL primitives batched and drawn by the GPU with OpenGL ES2 (ES3 where available), into two offscreen framebuffer objects that mirror IRIS GL's front and back buffers. The front buffer's texture is handed straight to the display, so no pixels are read back per frame. This is what makes arbitrary window sizes and texture mapping fast, and it ends the irony of a software rasterizer doing the work that SGI did in hardware 40 years ago.
- **ref** (`reference_rasterizer.c`): the CPU scanline rasterizer forked from the [Alice 4](https://lkesteloot.github.io/alice/alice4/) project, kept as the reference to check the GPU path against (`scripts/ppm_compare.py` compares frame dumps from the two). `IRISGL_RAST=ref`, or `?rast=ref` on the web, selects it; any other value, or none, gets gles.

Either way, `sdl_framebuffer.c` presents the front buffer as a textured quad in the SDL window: the gles FBO texture directly, or the ref rasterizer's CPU pixels uploaded to a texture.

### Color-index (colormap) mode and the palette LUT

SGI hardware in colormap mode stored a color *index* per pixel and resolved it through the palette LUT on scan-out, so a `mapcolor()` call recolored already-drawn pixels instantly. Most colormap demos never rely on this (they map their palette once at startup), so the shim normally resolves indices to RGB per vertex and rasterizes plain RGB. For demos that edit the palette live (cedit) or read indices back (`readpixels()`, `getapixel()`), both rasterizers additionally keep a per-pixel color-index buffer, written in parallel with the RGB buffer (`screen_vertex.ci`, flat per primitive): the ref rasterizer on the CPU, the gles rasterizer on the GPU (which needs an ES3 context). At each present, if the colormap changed since the pixels were drawn, the front RGB buffer is re-derived from the CI buffer through the current colormap (`rasterizer_resolve_ci_to_rgb`) — the LUT emulation.

## Browser yielding

An architectural problem with this project was that IRIS GL demos were written to own the event loop: `main()` calls `winopen()`, then enters a `while(1)` loop and never exits. That works fine on native, but on the web it cannot work — the browser's main thread must yield regularly or the page hangs.

Three solutions were tried/considered:

1. **Restructure the demo's loop into callbacks.** This was the project's original approach, allowing the host (browser) to drive the demo. However, due to the preprocessor macro trickery required to split the demo into initialization and event loops, it was messy, fragile, and cost some original source fidelity where macros couldn't help.

2. **Run the demo in its own thread** (Web Worker via pthreads). This would replace #ifdef complexity with the synchronization complexity of a threaded codebase. It would also require `SharedArrayBuffer`, which requires COOP/COEP HTTP headers, which requires service-worker workarounds to run on GitHub Pages or else a self-hosted domain.

3. **Use Emscripten Asyncify (emscripten_sleep).** In this approach, the demo's `while(1)` runs to a yield point, Asyncify saves the WebAssembly stack, control returns to the browser event loop, and on the next browser tick (or after sufficient sleep to not exceed target FPS) the stack is restored and execution resumes exactly where it left off. From the demo's perspective nothing happened. On native, we simply SDL_Delay() as necessary to run no faster than target FPS.

The architecture had been option 1. Option 2 was then considered, but traded one kind of complexity for another. Option 3 was chosen as the best of both: single-threaded like option 1, with none of its macro trickery, and none of option 2's threads or COOP/COEP headers. Now the original source runs more closely as-is, and native and web share one code path. As well, the runtime cost of Asyncify should be negligible with SGI-era code running on modern devices.

### Central yield point

Browser yielding was implemented by defining this function as the central yield location:

```c
void sdl_events_frame_complete(void);
```

Defined in `libs/libgl/sdl_events.c`, it:
1. Pumps SDL events into the GL event queue (`sdlProcessEvents`).
2. Presents whatever framebuffer was last set via `sdl_events_set_framebuffer`.
3. Yields. On Emscripten this is `emscripten_sleep(remaining_ms_in_budget)` (or `emscripten_sleep(0)` if the demo ran over budget — the page still must yield once per frame). On native it simply sleeps with `SDL_Delay(remaining_ms_in_budget)`.

The 30Hz target framerate (`DEMO_FPS = 30`) is intentional. Many SGI demos depend on <= 30Hz pacing for animation timing and physics integrators, and 60Hz makes some of them (e.g. `ideas`) run too fast. The pacing is enforced identically on native and web.

### Where do demos yield?

These call sites all route through `sdl_events_frame_complete()`:

| Call site | When demos hit it |
|---|---|
| `swapbuffers()` | Double-buffered demos call this at the end of every frame. After the rasterizer pointer flip, the SDL-side framebuffer pointer is updated (the only place this is needed). |
| `gflush()` | Single-buffered demos call this at the end of every frame. |
| `qtest()` / `qread()` / `getbutton()` / `getvaluator()` | Throttled safety net (`yieldByEventQuery` in `sdl_events.c`). Demos like `twilight` don't call `swapbuffers` or `gflush` — they only poll input waiting for REDRAW events. To keep these demos from hanging the browser, every event-poll function yields when at least one frame budget has elapsed since the last yield. |
| `dopup()` | Pop-up menu modal loop. Calls `sdl_events_frame_complete` directly, with no rasterizer swap, so the menu composited onto the front buffer is preserved across iterations. |

## Event handling

### Two queues

Two separate event queues are maintained, one SDL and the other IRIS GL:

```
SDL events ──► sdl_input_queue ──► (drained on demand) ──► input_queue_{device,val} ──► demo
               (libgl/sdl_events.c)                        (libgl/gl.c)
```

The SDL-side queue (`sdl_input_queue` in `sdl_events.c`) buffers translated SDL events. The GL-side queue (`input_queue_{device,val}` in `gl.c`) is what `qtest` / `qread` read from. When the GL queue is empty, `qtest` calls `sdl_events_qread_start` / `sdl_events_qread_continue` to drain whatever is in the SDL queue. This split keeps the IRIS GL semantics — including filtering by `qdevice` / `unqdevice` and ordering of tied valuators — entirely inside `gl.c`, where it matches the original API.

ESC quits every demo: `qread` intercepts it (unless a pop-up menu is open) and calls `gl_exit`, which on the web goes back to the previous page, or to the site's home page when there is none.

### REDRAW synthesis

IRIS GL demos that handle window events expect the window system to inject `REDRAW` events when the window needs repainting. On SGI workstations these came from NeWS / 4Sight / X server window managers. In this environment there is no external window system poking the demo, so the SDL layer synthesizes them when the demo has subscribed to `REDRAW` via `qdevice(REDRAW)`. It does this periodically (at most once per frame interval) during GL event queries, and when the window is resized. This enables demos like `twilight` to function, which only repaint in response to `REDRAW` events and don't use swapbuffers() or gflush() to signal the end of a frame.

### Event pump integrity

Some IRIS GL demos depend on atomic event groups in `sdl_input_queue`. For example, `buttonfly` ties `MOUSEX`/`MOUSEY` to `LEFTMOUSE` and expects `qread()` to return that three-event group with no other events interleaved. This implies the following invariant: **any events enqueued during one `sdlProcessEvents` call must appear contiguously in `sdl_input_queue`.**

A reentrant pump (e.g. via a yield from inside an event handler) would violate this by injecting events mid-group. Specifically, yieldByEventQuery() could inject a REDRAW into a group of tied events if not guarded (see REDRAW synthesis above).

To protect against this, a reentrancy flag is set for the duration of `sdlProcessEvents`. Then all yield paths in `sdl_events.c` implement guards by checking this reentrancy flag and early-returning if set. The skipped yield is fulfilled on the next yielding call the demo makes outside sdlProcessEvents. As a further safety measure against future code, a direct reentrant call to `sdlProcessEvents` itself — which the current yield guards may not intercept — is caught by a fatal abort.

## Runtime switches

Each switch is an environment variable. On the web, `demos/switches.js` passes the ones that make sense in a browser in from the URL: `?rast=ref` is `IRISGL_RAST=ref`. The emulator's switches are all `IRISGL_`; `SGI_PLACARD` belongs to the demo's startup placard.

| Variable | URL | Effect |
|---|---|---|
| `IRISGL_RAST=ref` | `?rast=ref` | the ref (CPU) rasterizer instead of gles (GPU) |
| `IRISGL_PAR=0` | `?par=0` | no 16:15 pixel aspect correction |
| `IRISGL_FRAME_PPM=1` | | dump every frame as `frameNNNN.ppm` (native; see `scripts/ppm_compare.py`) |
| `IRISGL_TRACE=1` | | print every IRIS GL call (native debug builds) |
| `IRISGL_SNAP_VERTICES=1` | | snap vertices to whole pixels (ref rasterizer) |
| `SGI_PLACARD=0` | | don't print the placard at startup (native) |

The web page's own switches are read by the page, not the C code: `?placard=off`/`on` (see `demos/placard.js`), and `?arg=` and a demo's `web_flags`, which become its command line (see `makefiles/web_page.html`).

## Build system

Each demo has a short `Makefile`, specifying the APPNAME and any demo-specific build flags, e.g.:

```makefile
APPNAME=bounce
EM_PRELOAD=--preload-file canstick.bin --preload-file doughnut.bin --preload-file logo.bin --preload-file martini.bin --preload-file vw.bin --preload-file x29.bin
include ../../makefiles/make_demo.mk
```

`makefiles/make_demo.mk` builds both a native binary (`bin-$(OS)-$(HW)/$(APPNAME)`) and the web package in `web/`: `$(APPNAME).js` + `$(APPNAME).wasm` (+ `.data` for preloaded files) from Emscripten, and `index.html`, the page that loads them, filled in from `makefiles/web_page.html` and the demo's `placard.json` by `scripts/placard.py page`. The shared build logic, including platform detection, SDL/GLES paths, and the Asyncify flags, lives in `makefiles/platform.mk`.

The root `Makefile` builds every demo: every `demos/<name>/` (or `demos/<name>/<variant>/`, such as `ep-1994/decomp`) with a Makefile, except drafts (`"draft": true` in placard.json). `make list` prints that list, and the smoke tests, thumbnails, and gallery (the README grid and `demos/gallery.json`, which the site's browse page reads) all read it from there.

Emscripten flags to enable demos to yield to the browser:

```makefile
EM_ASYNCIFY = -sASYNCIFY -sASYNCIFY_STACK_SIZE=65536
```

`-sASYNCIFY` instruments the call chain so `emscripten_sleep` can pause and resume the WebAssembly stack. `ASYNCIFY_STACK_SIZE=65536` allocates 64KB to hold the saved stack during a yield — probably generous enough for the demos, but can be expanded further if necessary. Asyncify increases WASM code size, but for 1980s-90s code running on modern hardware, this cost should be negligible.

## Demo source modifications

Per the preservation goal, original demo source compiles unmodified for the most part. Translation between old code and new compilers/headers happens in `platform.mk` (see `DEMO_CODE_*`) and the headers in `include/shim/`, `demo_shim.h` in particular. Each demo's remaining changes are listed in its README, and every one is in the git history.

## Future directions

This project now has a solid foundation for building out further in these main directions:

- **Complete the IRIS GL demo set** - More demos from the demo tapes, IRIX releases, and Developer Toolbox; sunflower is in as a draft. Electropaint runs without its Panel Library control panels (a stub stands in); a fuller port would bring the panels back.

- **Add OpenGL demos** - This will require reworking some project structure since the project is currently IRIS GL centric. Use [GL4ES](https://github.com/sgi-demos/gl4es) and/or something similar, to translate old immediate-mode OpenGL calls to modern retained-mode OpenGL(ES2).

- **Add GLUT demos** - GLUT does its own event handling, and Emscripten has a GLUT implementation already. However, it might be interesting to see if a more robust approach would be to provide an OpenGLES2/SDL2-based port of [FreeGLUT](https://github.com/freeglut/freeglut) and lean on Emscripten's SDL2 implementation and OpenGLES2-to-WebGL cross-compilation.

- **Add Performer and Inventor demos** - [Inventor](https://github.com/sgi-demos/sgi-inventor) already has many open source ports, and [Performer](https://github.com/sgi-demos/sgi-performer) could potentially be reversed via Ghidra and AI tools (Performer file format loader code is already open source). These scene-graph APIs sit on top of OpenGL; so the OpenGL rendering layer could be reused.
