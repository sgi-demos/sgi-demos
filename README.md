# SGI demos from long ago, running in your browser [today](https://sgi-demos.github.io).
_It's a UNIX system. I know this!_

This is the original SGI demo source code, compiled for the web using Emscripten and SDL2.  Rendering is done using an IRIS GL-to-GLES2/3 rasterizer with a reference software rasterizer forked from the [Alice 4 project](https://lkesteloot.github.io/alice/alice4/libgl.html).  Event handling is done by SDL2, with events translated into GL's event system.

Each demo is a separate web page, with its own Javascript + WASM compiled by Emscripten from the original C/C++ source.  Native Linux, Mac, and Windows builds are also available. Minimal modifications have been made to the original source, only what is necessary to build them 30+ years later for modern hardware and the browser.

See the [architecture doc](https://github.com/sgi-demos/sgi-demos/blob/main/docs/ARCHITECTURE.md) for more implementation details, and the latest [smoke test](https://sgi-demos.github.io/sgi-demos/tests/smoke/report/index.html) for build status.

## Working demos
- [Arena](https://sgi-demos.github.io/sgi-demos/demos/arena/web/) - no network play yet
- [Bounce](https://sgi-demos.github.io/sgi-demos/demos/bounce/web/)
- [Buttonfly](https://sgi-demos.github.io/) - Wade Olsen
- [Cedit](https://sgi-demos.github.io/sgi-demos/demos/cedit/web/) - Paul Haeberli, 1984
- [Electropaint 1988](https://sgi-demos.github.io/sgi-demos/demos/ep-1988/web/) - David Tristram, 1988; IRIS GL, earliest version, Panel Library v7 from the 1988 Usenet posting (no sliders yet)
- [Electropaint 1989](https://sgi-demos.github.io/sgi-demos/demos/ep-1989/web/)  - David Tristram, 1989; IRIS GL, Panel Library 9.6; driven by Tristram's authentic default script; keyboard toggles
- [Electropaint 1994 (OpenGL, decompiled)](https://sgi-demos.github.io/sgi-demos/demos/ep-1994-ogl-decomp/web/) - 1994, IRIX screensaver decompiled by drvink; smooth HLS color + the famous default script
- [Electropaint 1994 (OpenGL, reversed)](https://sgi-demos.github.io/sgi-demos/demos/ep-1994-ogl-reversed/web/) 1994, reversed to somewhat-readable code and restored IRIS GL version's 4-fold mirrors + 30° camera  — M toggles the original 1994 look
- [Flight 1988](https://sgi-demos.github.io/sgi-demos/demos/flight-1988/web/) - Gary Tarolli, 1988; colormap-mode original, nearly original source (25 diff lines total) at the authentic 1280×1024; splash, plane menu, takeoff, crashes, and stable night mode all work; no network play
- [Flight 1994](https://sgi-demos.github.io/sgi-demos/demos/flight-1994/web/) Rob Mace, 1994, version 3.4; the definitive IRIX release: RGB, lighting, 8 planes, full-width 3D horizon, instrument panel, HUD, upgraded plane models; no texture/fog/sound/network yet
- [Gview (Barcelona)](https://sgi-demos.github.io/sgi-demos/demos/gview/web/) - Late 1980s; reversed from IRIX 3 binary: fly-through and turntable modes work; no materials, movie loops, or binary model cache; Performer/Inventor pre-cursor perhaps?
- [Ideas](https://sgi-demos.github.io/sgi-demos/demos/ideas/web/)
- [Insect](https://sgi-demos.github.io/sgi-demos/demos/insect/web/) Thant Tessman, mid-1980s; originally for the IRIS 2400
- [Jello](https://sgi-demos.github.io/sgi-demos/demos/jello/web/) Thant Tessman, 1987
- [Logo](https://sgi-demos.github.io/sgi-demos/demos/logo/web/) Thant Tessman, 1987
- [Newave](https://sgi-demos.github.io/sgi-demos/demos/newave/web/) - Late 1980s \, originally for the 4D/70G; note the wave starts flat: right-click, edit, then go
- [Twilight](https://sgi-demos.github.io/sgi-demos/demos/twilight/web/) - Howard Look, 1991
- [Performer Town](https://sgi-demos.github.io/sgi-performer/web/apps/webfly/web/) - WIP; SGI's `perfly` compiled unmodified over an OpenSceneGraph-based Performer shim, from the [sgi-performer](https://github.com/sgi-demos/sgi-performer) repo


## Demos coming next
- More IRIS GL demos
- Aux/Tk OpenGL demos
- GLUT OpenGL demos
- Inventor Slotcars, Maze
- Performer Matterhorn, Yosemite


## Build

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
- [Demos coming next](README.md#demos-coming-next)
- Fix logged [issues](https://github.com/sgi-demos/sgi-demos/issues)
- Provide context for each demo:
  -  Overlay text in lower corner: Name, author, year, code link, provenance (IRIX version, dev toolbox, demo cd, etc.)
  - Brief description/history/context for each demo - Obtain descriptions from .Info slide files
  - Link to demo man page
- Add 'inspect demo' mode to pause, orbit, zoom, pan, fly through demo scene (as a hidden override to the demo's own controls)
- Add popup/overlay help to show available key/mouse inputs
- Provide virtual mouse and keyboard for touch devices:
  - Only display virtual keys and mouse functions used by the demo; use demo's qdevice() calls to determine this
  - Displayed as transparent virtual mouse and key pictures overlaid on demo
  - On always for touch devices
  - On/off for mouse/keyboard devices, as hints

## License

The sgi-demos code (the IRIS GL implementation, rasterizers, SDL layers, shims, build files, tests, and docs) is Apache License 2.0; see [LICENSE](LICENSE) and [NOTICE](NOTICE). The original SGI demos, headers, and data, and Electropaint, are not covered by that license and retain their original authors' terms; several carry SGI's or the author's permissive notice, the rest are used under fair use. Every original notice is preserved. The full provenance and fair-use record for every demo and library is in [docs/COPYRIGHT.md](docs/COPYRIGHT.md). This project is not affiliated with or endorsed by Hewlett Packard Enterprise, Silicon Graphics, or Tristram Visual.

## Credits
- Everyone who worked at [SGI](https://en.wikipedia.org/wiki/Silicon_Graphics), for the eye candy and the baller computers.
- The [Alice 4 folks](https://lkesteloot.github.io/alice/alice4/), for the inspiration and the GL implementation.
- [drvink](https://github.com/drvink/electroportis) for the custom MIPS decompiler and resulting ep decompilation, Electroportis
- [Claude Fable 5](https://claude.ai) for gobbling up the to do list at incredible speed.
- [Emscripten](https://emscripten.org) and [SDL](https://www.libsdl.org) teams, for making a web port possible.
- [Internet Archive](https://archive.org/search?query=sgi&and%5B%5D=mediatype%3A%22software%22), [Bitsavers](https://bitsavers.org/bits/SGI/mips/cd/), [WinWorld](https://winworldpc.com/search?q=irix), [IRIXNet](https://irixnet.org/files.html), [fsck.technology](https://fsck.technology/software/Silicon%20Graphics/IRIX%20Install%20Media/), [jrra.zone](https://jrra.zone/sgi/), and others, for saving the history.
