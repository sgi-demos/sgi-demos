# Adding a demo

From original source to a demo on exhibit. `<name>` is the demo's directory name, lower case, with a year suffix when versions differ (`ep-1988`).

## 1. Bring in the source

- Copy the original files into `demos/<name>/` byte-identical to the archive they came from, including SGI's own Makefile (renamed `Makefile.orig`), data files, and `.info` slides. Keep every copyright and license notice.
- Write `demos/<name>/README.md`: one paragraph on what the demo is and who wrote it, then a Provenance section naming the archive and the basis for using the source (see any other demo's README).
- Add the demo to [COPYRIGHT.md](COPYRIGHT.md): a row in the section 4 inventory, and the archive with its SHA-256 in the section 8 source archives table if it is new.

## 2. Makefile

`demos/<name>/Makefile` names the demo and includes the shared rules:

```makefile
APPNAME=<name>
include ../../makefiles/make_demo.mk
```

Before the include, as needed:

- `DEMO_CFLAGS`: extra compiler flags (defines, `-std=`, `-w` for vintage warnings). Comment each one.
- `USE_SHIM_HEADER=yes`: force-include `include/shim/demo_shim.h` (common workarounds for 1980s C).
- `EM_PRELOAD=--preload-file <file> ...`: data files the web build needs.
- `DEMO_EXTRA_SRC` / `DEMO_EXCLUDE_SRC`: sources beyond the directory's `*.c`, or ones SGI's Makefile didn't link.

## 3. Placard

`demos/<name>/placard.json` is the demo's record: the corner card on its web page, the terminal print of a native build, and its entry in the gallery. The fields are listed in [scripts/placard.py](../scripts/placard.py). Start with `"draft": true`, which keeps the demo out of the full build, the smoke tests, and the gallery until it runs, then fill in the detected inputs:

```bash
python3 scripts/placard.py update demos/<name>
```

## 4. Build and port

```bash
make -C demos/<name>
```

This builds `bin/<name>` natively and `web/` for the browser (`<name>.js`, `<name>.wasm`, and `index.html`, generated from the placard). Fix what breaks with the least change to the original, in this order:

1. The emulator (`libs/libgl`), when the demo uses IRIS GL that isn't implemented or isn't faithful. Every demo benefits.
2. Build flags and shims: `DEMO_CFLAGS`, `include/shim/`.
3. A per-demo quirk in `apply_demo_quirks` (libs/libgl/gl.c), only when the demo depends on hardware behavior no other demo shares.
4. The demo source itself, as a last resort: the smallest fix, commented in place, and listed in its README.

Run it both ways, and in both rasterizers:

```bash
cd demos/<name> && ./bin/<name>
IRISGL_RAST=ref ./bin/<name>
```

```bash
python3 -m http.server 8000
```

then open http://localhost:8000/demos/<name>/web/ and http://localhost:8000/demos/<name>/web/?rast=ref. A demo that takes a data file on its command line gets it from `web_arg` (and `web_flags` for switches) in the placard.

## 5. Test

Remove `"draft": true` from the placard, then run the smoke test for the demo:

```bash
make smoke
```

`node tests/smoke/smoke.mjs --only <name>` runs just this one while you work, but it leaves only that demo in `tests/smoke/results`, so run the full `make smoke` before committing. A sparse demo that fails the non-blank check gets its own `minContent` in `tests/smoke/demos.json`.

## 6. Thumbnail and gallery

```bash
node scripts/thumbs.mjs --only <name>
make gallery
```

The first writes `media/<name>.png`; a demo that needs keys or clicks to get past a splash screen gets a recipe in `scripts/thumbs.json`. The second adds the demo to `demos/gallery.json` (the site's browse page) and the README's Working demos grid.

## 7. Buttonfly (optional)

To launch it from buttonfly, add an entry to one of the menus in `demos/buttonfly/menus/`, copying the others (the command is the native path, `../<name>/bin/<name>`). The menus are packed into buttonfly's web build, which doesn't notice the edit, so rebuild it:

```bash
make -B browser -C demos/buttonfly
```

## 8. Timeline

In the [sgi-demos.github.io](https://github.com/sgi-demos/sgi-demos.github.io) repository, add the demo to `timeline/data.js` with `status: "exhibit"`. Its [README](https://github.com/sgi-demos/sgi-demos.github.io/blob/main/timeline/README.md) has the fields and the evidence rules.

## 9. Commit

Commit the demo directory, including `web/` (GitHub Pages serves the committed build), `media/<name>.png`, `demos/gallery.json`, `README.md`, `docs/COPYRIGHT.md`, and any buttonfly, smoke, or thumbnail changes. Push sgi-demos before the timeline change, so the demo is live when the timeline links to it.
