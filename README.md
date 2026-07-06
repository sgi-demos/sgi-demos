# SGI demos from long ago, running in your browser [today](https://sgi-demos.github.io).
_Old problems require modern solutions._

This is the original SGI demo source code, compiled for the web using Emscripten and SDL2.  Rendering is done using an IRIS GL-to-GLES2 rasterizer with a reference software rasterizer also available from the [Alice 4 project](https://lkesteloot.github.io/alice/alice4/libgl.html).  Event handling is done by SDL2, with events translated into GL's event system.  Each demo is a separate web page, with its own Javascript + WASM compiled by Emscripten from the original C/C++ source.  Native Linux, Mac, and Windows builds are also available. Minimal modifications have been made to the original source, in order to run in the browser and to build with compilers 30+ years later.  For more implementation details, see the [architecture doc](https://github.com/sgi-demos/sgi-demos/blob/main/docs/ARCHITECTURE.md).

## Working demos
- [Buttonfly](https://sgi-demos.github.io/)
- [Bounce](https://sgi-demos.github.io/sgi-demos/demos/bounce/web/bounce_full.html)
- [Cedit](https://sgi-demos.github.io/sgi-demos/demos/cedit/web/cedit_full.html) (Paul Haeberli's 1984 color editor; live palette editing via emulated hardware colormap LUT)
- [Ideas](https://sgi-demos.github.io/sgi-demos/demos/ideas/web/ideas_full.html)
- [Insect](https://sgi-demos.github.io/sgi-demos/demos/insect/web/insect_full.html)
- [Jello](https://sgi-demos.github.io/sgi-demos/demos/jello/web/jello_full.html)
- [Logo](https://sgi-demos.github.io/sgi-demos/demos/logo/web/logo_full.html)
- [Newave](https://sgi-demos.github.io/sgi-demos/demos/newave/web/newave_full.html) (right-click for menus: mesh editing, flat/gouraud shading, depth cueing, top view; the wave starts flat — edit it, then choose 'go')
- [Twilight](https://sgi-demos.github.io/sgi-demos/demos/twilight/web/twilight_full.html)

## Somewhat working demos
- [Flight 1988](https://sgi-demos.github.io/sgi-demos/demos/flight-1988/web/flight-1988_full.html) (the 1988–89 colormap-mode original, now byte-faithful source — 25 diff lines total — at the authentic 1280×1024; splash, plane menu, takeoff, crashes, and stable night mode all work; no network play)
- [Flight 1994](https://sgi-demos.github.io/sgi-demos/demos/flight-1994/web/flight-1994_full.html) (Version 3.4, the definitive IRIX flight — RGB, lighting, 8 planes, full-width 3D horizon and instrument panel; no texture/fog/sound/network yet)
- [Arena](https://sgi-demos.github.io/sgi-demos/demos/arena/web/arena_full.html) (no network play)
- [Gview (Barcelona)](https://sgi-demos.github.io/sgi-demos/demos/gview/web/gview_full.html) (reconstructed from the IRIX 3 binary: fly-through and turntable modes work; no materials, movie loops, or binary model cache)
- [Electropaint 1988](https://sgi-demos.github.io/sgi-demos/demos/ep-1988/web/ep-1988_full.html) (earliest version, Panel Library v7, from the 1988 Usenet posting; plain sliders)
- [Electropaint 1989](https://sgi-demos.github.io/sgi-demos/demos/ep-1989/web/ep-1989_full.html) (Panel Library 9.6; IRIS GL, driven by Tristram's authentic default script; keyboard toggles)
- [Electropaint 1994 (OpenGL, decompiled)](https://sgi-demos.github.io/sgi-demos/demos/ep-1994-ogl-decomp/web/ep-1994-ogl-decomp_full.html) (the real OpenGL IRIX screensaver, decompiled; smooth HLS colour + the famous default script; IRIS-faithful by default — restored 4-fold mirrors + 30° camera — M toggles the shipped 1994 look)
- [Electropaint 1994 (OpenGL, reversed)](https://sgi-demos.github.io/sgi-demos/demos/ep-1994-ogl-reversed/web/ep-1994-ogl-reversed_full.html) (the OpenGL version with ep.c refactored to readable names — byte-identical output)

## Firmly WIP demos
- Sunflower, gltest, colortest

## Build instructions

### Mac

1. Install [Homebrew](https://brew.sh/) if you don't have it, then get SDL2 and Emscripten:
```bash
brew install SDL2
brew install emscripten
```

2. Build:
```bash
git clone https://github.com/sgi-demos/sgi-demos.git
cd sgi-demos
make
```

### Windows

1. Install [Winget](https://learn.microsoft.com/en-us/windows/package-manager/winget/) if you don't have it.

2. Install [MSYS2](https://www.msys2.org/) from cmd.exe, in order to get the clang compiler:
```bash
winget install MSYS2.MSYS2
setx PATH "%PATH%C:\msys64\clang64\bin"
```

3. Install clang toolchain, SDL2, and bison (for buttonfly menu parsing) in MSYS2 CLANG64 shell:
```bash
pacman -Syu
pacman -S base-devel mingw-w64-clang-x86_64-toolchain
pacman -S mingw-w64-clang-x86_64-SDL2
pacman -S bison
```

4. Clone [emscripten](https://emscripten.org/docs/getting_started/downloads.html) from Github.  Cloning seems to work best with MSYS2 rather than using pacman.  Follow the default install directions, not the Windows directions!

5. Add this line to the `~/.bashrc` file in MSYS2 CLANG64 shell:
```bash
source /path/to/emsdk/emsdk_env.sh
```

6. Build:
```bash
git clone https://github.com/sgi-demos/sgi-demos.git
cd sgi-demos
make
```

## To do
- Add more demos, _all the demos_.
  - Barcelona, Cedit, any other IRIS GL demos I can find
  - Then OpenGL, GLUT, Inventor, Performer demos in no particular order
- Fix logged [issues](https://github.com/sgi-demos/sgi-demos/issues)
- Provide context for each demo:
  - Name, author, year (as text in lower corner), code link
  - Brief description/history/context for each demo - can obtain some descriptions from .Info slide files
  - Link to demo man pages
- Add popup/overlay help to show key/mouse input to try
- Provide virtual mouse and keyboard for touch devices:
  - Only display virtual keys and mouse functions used by the demo; use demo's qdevice() calls to determine this
  - Displayed as transparent virtual mouse and key pictures overlaid on demo
  - On always for touch devices
  - On/off for mouse/keyboard devices, as hints

## Credits
- Everyone who worked at [SGI](https://en.wikipedia.org/wiki/Silicon_Graphics), for the eye candy and the baller computers.
- The [Alice 4 folks](https://lkesteloot.github.io/alice/alice4/), for the inspiration and the GL implementation.
- [Emscripten](https://emscripten.org) and [SDL](https://www.libsdl.org) teams, for making a web port possible.
- [Internet Archive](https://archive.org/search?query=sgi&and%5B%5D=mediatype%3A%22software%22), [Bitsavers](https://bitsavers.org/bits/SGI/mips/cd/), [WinWorld](https://winworldpc.com/search?q=irix), [IRIXNet](https://irixnet.org/files.html), [fsck.technology](https://fsck.technology/software/Silicon%20Graphics/IRIX%20Install%20Media/), [jrra.zone](https://jrra.zone/sgi/), and others, for saving the history.
