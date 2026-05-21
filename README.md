# SGI demos from long ago, running in your browser [today](https://sgi-demos.github.io).
_Old problems require modern solutions._

This is the original SGI demo source code, compiled for the web using Emscripten and SDL2.  Rendering is done using an IRIS GL software rasterizer from the [Alice 4 project](https://lkesteloot.github.io/alice/alice4/libgl.html).  Event handling is done by SDL2, with events translated into GL's event system.  Each demo is a separate web page, with its own Javascript + WASM compiled by Emscripten from the original C/C++ source.  Native Linux, Mac, and Windows builds are also available. Minimal modifications have been made to the original source, in order to run in the browser and to build with compilers 30+ years later.  For more implementation details, see the [architecture doc](https://github.com/sgi-demos/sgi-demos/blob/main/ARCHITECTURE.md).

## Working demos
- [Buttonfly](https://sgi-demos.github.io/)
- [Bounce](https://sgi-demos.github.io/sgi-demos/demos/bounce/web/bounce_full.html)
- [Ideas](https://sgi-demos.github.io/sgi-demos/demos/ideas/web/ideas_full.html)
- [Insect](https://sgi-demos.github.io/sgi-demos/demos/insect/web/insect_full.html)
- [Jello](https://sgi-demos.github.io/sgi-demos/demos/jello/web/jello_full.html)
- [Logo](https://sgi-demos.github.io/sgi-demos/demos/logo/web/logo_full.html)
- [Twilight](https://sgi-demos.github.io/sgi-demos/demos/twilight/web/twilight_full.html)

## Somewhat working demos
- [Flight](https://sgi-demos.github.io/sgi-demos/demos/flight/web/flight_full.html) (cockpit glitches, planes too slow in web version, night mode 'shimmers', no network play)
- [Newave](https://sgi-demos.github.io/sgi-demos/demos/newave/web/newave_full.html) (no mesh editing, no popup menus, only wireframe)
- [Arena](https://sgi-demos.github.io/sgi-demos/demos/arena/web/arena_full.html) (no network play)

## Firmly WIP demos
- [Gview (Barcelona)](https://github.com/sgi-demos/sgi-demos/tree/main/demos/gview)
- [Cedit](https://github.com/sgi-demos/sgi-demos/tree/main/demos/cedit)
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
- Fix logged [issues](https://github.com/sgi-demos/sgi-demos/issues)
- Enable popup menus, including the classic [SGI menu font](https://github.com/sgi-demos/sgi-fonts)
- Upgrade rendering to [OpenGLES/WebGL](https://github.com/sgi-demos/igl) (WIP)
- Enable arbitrary window size
- Provide Rudimentary context for each demo: name, author, year (as text in lower corner), code link
- Add popup/overlay help to show key/mouse input to try
- Add more demos, _all the demos_.
  - Electropaint, Cedit, any other IRIS GL demos I can find
  - Then OpenGL, GLUT, Inventor, Performer demos in no particular order
- Provide virtual mouse and keyboard for touch devices:
  - Only display virtual keys and mouse functions used by the demo; use demo's qdevice() calls to determine this
  - Displayed as transparent virtual mouse and key pictures overlaid on demo
  - On always for touch devices
  - On/off for mouse/keyboard devices, as hints
- Add brief description/history/context for each demo - can obtain some descriptions from .Info slide files
- Add links to man pages

## Credits
- Everyone who worked at [SGI](https://en.wikipedia.org/wiki/Silicon_Graphics), for the eye candy and the baller computers.
- The [Alice 4 folks](https://lkesteloot.github.io/alice/alice4/), for the inspiration and the GL implementation.
- [Emscripten](https://emscripten.org) and [SDL](https://www.libsdl.org) teams, for making a web port possible.
- [Internet Archive](https://archive.org/search?query=sgi&and%5B%5D=mediatype%3A%22software%22), [Bitsavers](https://bitsavers.org/bits/SGI/mips/cd/), [WinWorld](https://winworldpc.com/search?q=irix), [IRIXNet](https://irixnet.org/files.html), and others, for saving the history.
