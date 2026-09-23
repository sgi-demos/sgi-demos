# SGI demos from long ago, running in your browser [today](https://sgi-demos.org).
_It's a UNIX system. I know this!_

This is the original SGI demo source code, compiled for the web using Emscripten and SDL2.  Rendering is done via an IRIS GL-to-GLES2/3 rasterizer or a reference software rasterizer forked from the [Alice 4 project](https://lkesteloot.github.io/alice/alice4/libgl.html).  Event handling is done by SDL2, with events translated into GL's event system.

Each demo is a separate web page, with its own Javascript + WASM compiled by Emscripten from the original C/C++ source.  Native Linux, Mac, and Windows builds are also available. Minimal modifications have been made to the original source, only what is necessary to build them 30+ years later for modern hardware and the browser.

See the [copyright doc](https://github.com/sgi-demos/sgi-demos/blob/main/docs/COPYRIGHT.md) for thorough copyright considerations, the [architecture doc](https://github.com/sgi-demos/sgi-demos/blob/main/docs/ARCHITECTURE.md) for implementation details, and the latest [smoke test](https://sgi-demos.org/sgi-demos/tests/smoke/report/index.html) for build status.

## [Working demos](https://sgi-demos.org/browse/)

<!-- demos:start -->
<table>
<tr><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/arena/web/"><img src="https://sgi-demos.org/sgi-demos/media/arena.png" width="110" alt="Arena"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/bounce/web/"><img src="https://sgi-demos.org/sgi-demos/media/bounce.png" width="110" alt="Bounce"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/buttonfly/web/"><img src="https://sgi-demos.org/sgi-demos/media/buttonfly.png" width="110" alt="Buttonfly"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/cedit/web/"><img src="https://sgi-demos.org/sgi-demos/media/cedit.png" width="110" alt="Cedit"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/ep-1988/web/"><img src="https://sgi-demos.org/sgi-demos/media/ep-1988.png" width="110" alt="Electropaint 1988"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/ep-1989/web/"><img src="https://sgi-demos.org/sgi-demos/media/ep-1989.png" width="110" alt="Electropaint 1989"></a></td></tr>
<tr><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/arena/web/"><b>Arena</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/bounce/web/"><b>Bounce</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/buttonfly/web/"><b>Buttonfly</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/cedit/web/"><b>Cedit</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/ep-1988/web/"><b>Electropaint 1988</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/ep-1989/web/"><b>Electropaint 1989</b></a></td></tr>
</table>

<table>
<tr><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/ep-1994/web/"><img src="https://sgi-demos.org/sgi-demos/media/ep-1994.png" width="110" alt="Electropaint 1994"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/flight-1988/web/"><img src="https://sgi-demos.org/sgi-demos/media/flight-1988.png" width="110" alt="Flight"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/flight-1994/web/"><img src="https://sgi-demos.org/sgi-demos/media/flight-1994.png" width="110" alt="Flight 3.4"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/gview/web/"><img src="https://sgi-demos.org/sgi-demos/media/gview.png" width="110" alt="Gview: the Barcelona Pavilion"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/ideas/web/"><img src="https://sgi-demos.org/sgi-demos/media/ideas.png" width="110" alt="Ideas in Motion"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/insect/web/"><img src="https://sgi-demos.org/sgi-demos/media/insect.png" width="110" alt="Insect"></a></td></tr>
<tr><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/ep-1994/web/"><b>Electropaint 1994</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/flight-1988/web/"><b>Flight</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/flight-1994/web/"><b>Flight 3.4</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/gview/web/"><b>Gview: the Barcelona Pavilion</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/ideas/web/"><b>Ideas in Motion</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/insect/web/"><b>Insect</b></a></td></tr>
</table>

<table>
<tr><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/jello/web/"><img src="https://sgi-demos.org/sgi-demos/media/jello.png" width="110" alt="Jello"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/logo/web/"><img src="https://sgi-demos.org/sgi-demos/media/logo.png" width="110" alt="Logo"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/newave/web/"><img src="https://sgi-demos.org/sgi-demos/media/newave.png" width="110" alt="Newave"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-performer/web/apps/webfly/web/"><img src="https://sgi-demos.org/sgi-performer/media/webfly.png" width="110" alt="Performer Town"></a></td><td align="center"><a href="https://sgi-demos.org/sgi-demos/demos/twilight/web/"><img src="https://sgi-demos.org/sgi-demos/media/twilight.png" width="110" alt="Twilight"></a></td></tr>
<tr><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/jello/web/"><b>Jello</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/logo/web/"><b>Logo</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/newave/web/"><b>Newave</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-performer/web/apps/webfly/web/"><b>Performer Town</b></a></td><td align="center" valign="top"><a href="https://sgi-demos.org/sgi-demos/demos/twilight/web/"><b>Twilight</b></a></td></tr>
</table>
<!-- demos:end -->

## Demos coming next
- More IRIS GL demos
- Aux/Tk OpenGL demos
- GLUT OpenGL demos
- Inventor Slotcars, Maze
- Performer Matterhorn, Yosemite


## Build

Every platform needs a C compiler, SDL2, Emscripten, bison (buttonfly's menu parser), and Python 3. `make` then builds every demo twice: natively into `demos/<name>/bin/`, and for the web into `demos/<name>/web/`. `make native` or `make browser` builds just one of the two, `make libs` just the libraries (a quick compile check while editing one), and `make list` prints the demos. To add a demo, see [docs/ADD_A_DEMO.md](docs/ADD_A_DEMO.md).

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

### Linux

1. Install the compiler, SDL2, bison, and Python (Debian and Ubuntu package names):
```bash
sudo apt install build-essential libsdl2-dev bison python3
```

2. Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) with emsdk, following its directions, and add `source /path/to/emsdk/emsdk_env.sh` to your `~/.bashrc`.

3. Build:
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
setx PATH "%PATH%;C:\msys64\clang64\bin"
```

3. Install clang toolchain, SDL2, bison, and Python in MSYS2 CLANG64 shell:
```bash
pacman -Syu
pacman -S base-devel mingw-w64-clang-x86_64-toolchain
pacman -S mingw-w64-clang-x86_64-SDL2
pacman -S bison mingw-w64-clang-x86_64-python
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

## Run

A native build runs from its demo's directory, where it finds its data files:
```bash
cd demos/jello && ./bin/jello
```

The web build runs from any local web server at the repository root; `make run-browser -C demos/jello` starts one with emrun and opens the demo. Otherwise:
```bash
python3 -m http.server 8000
```
then open http://localhost:8000/demos/jello/web/.

Runtime switches, such as `IRISGL_RAST=ref` (`?rast=ref` on the web) for the CPU reference rasterizer, are listed in the [architecture doc](docs/ARCHITECTURE.md#runtime-switches). `make smoke` runs the headless-browser smoke tests of every web build (see [tests/smoke](tests/smoke/README.md)).

## To do
- Fix logged [issues](https://github.com/sgi-demos/sgi-demos/issues)
- Link each demo's man page from its placard
- Add 'inspect demo' mode to pause, orbit, zoom, pan, fly through demo scene (as a hidden override to the demo's own controls)
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
- [drvink](https://github.com/drvink/electroportis) for the custom MIPS decompiler and ElectroPortis, the Electropaint decompilation, and [Brendan Shanks](https://github.com/bslabs) for its clean cross-platform fork
- [Claude Fable 5](https://claude.ai) for gobbling up the to do list at incredible speed.
- [Emscripten](https://emscripten.org) and [SDL](https://www.libsdl.org) teams, for making a web port possible.
- [Internet Archive](https://archive.org/search?query=sgi&and%5B%5D=mediatype%3A%22software%22), [Bitsavers](https://bitsavers.org/bits/SGI/mips/cd/), [WinWorld](https://winworldpc.com/search?q=irix), [IRIXNet](https://irixnet.org/files.html), [fsck.technology](https://fsck.technology/software/Silicon%20Graphics/IRIX%20Install%20Media/), [jrra.zone](https://jrra.zone/sgi/), and others, for saving the history.
