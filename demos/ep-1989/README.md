# Electropaint

David Tristram's Electropaint (1986), the legendary SGI screensaver. Source is the Panel Library/Electropaint release as shipped with [IGL](https://github.com/sgi-demos/igl) (`igl_0.1.8/src/panel/D.app`): `ep.c`, `colormod.c`, `fade.c`, and the panel library header `panel.h`, byte-identical to that release (commit recorded in the [source archives table](../../docs/COPYRIGHT.md#8-source-archives)). The files carry Tristram's 1986 copyright and IGL's GPL v2-or-later header; the script engine in epscript.c is built from the 1994 decompilation and is under Tristram's permission for it. See [docs/COPYRIGHT.md](../../docs/COPYRIGHT.md) section 3. This is **Panel Library 9.6** (April 1989) plus IGL's patches — confirmed by diffing against a pristine 9.6 recovered from the GRASS 4.3 source distribution; the only substantive changes are the `lmcolor`→`ep_lmcolor` rename, Win32/X11 event pumping, the "about" button, a 400×400 window, and the GPL header.

## How this port works

The original ep is built on the Panel Library (libpanel), which draws its slider/button control panels in additional GL windows. The sgi-demos IRIS GL emulator is a single-window system, so instead of porting libpanel's ~11k lines, [panelstub.c](panelstub.c) implements the panel API *headlessly*: actuators are real data structures allocated and linked exactly as libpanel does, but nothing is drawn and no panel window opens. `ep.c` compiles against the real `panel.h` and animates the same actuator structs it always did.

Two things replace the panel UI:

- **The authentic default script** ([epscript.c](epscript.c)): this igl release has no built-in script, so instead of hand-waving the motion we run Dave Tristram's *actual* default "mello script" and its sequence engine, recovered from the OpenGL IRIX Electropaint via the [ElectroPortis](https://github.com/drvink/electroportis) decompilation. The engine parses the script text into per-actuator sequences and, each frame, drives each actuator with the original **trapezoidal oscillator** (`value__GfN21`: ramp up over 60°, hold, ramp down, hold, across a 360° phase spanning one `duration`), with exponential random delays and looping. `epscript_apply()` in [ep.c](ep.c) maps the script's actuator ids onto this demo's sliders; the unmodified `drawit()` then samples them into the triangle stream. The script text is embedded verbatim.
- **Keyboard equivalents**: `pnl_addact()` registers each actuator's key with `qdevice()` just like the real library, and `pnl_dopanel()` toggles the matching actuator on key press:
  - `O` outline, `I` fat lines, `U` fill, `M` smooth, `Q` smear, `W` fade, `E` background, `S` stop, `F` full screen, `ESC` exit

### What is and isn't authentic

The **geometry choreography is Tristram's** — the script drives wrist, spin, flip, arm, twist, wheel, zoom, size, `n`, and outline with his exact limits, durations, and random-delay structure (e.g. spin and flip fire fast bursts "occasionally"; twist sweeps very slowly; outline toggles on/off over a 5000-frame cycle). Actuator ids map as: 101→wrist, 80→spin, 87→flip, 94→arm, 38→twist, 73→wheel, 31→zoom, 108→size, 52→`n`, 18→outline.

**Color is not** — the script's color channels (123 hue / 130 lightness) are RGB/HLS, and this demo runs in colormap (color-index) mode with the classic spectrum map (as on 8/12-bitplane IRISes; the `IRIS_GT` RGB/lighting build is unused). So the color id mappings are dropped and the palette is our colormap sweep instead. Stream sampling rate and the color-cycle speed are the only free knobs (`epscript_apply()`); everything shaping the motion comes from the script.
