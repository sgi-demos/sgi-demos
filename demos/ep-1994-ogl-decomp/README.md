# ElectroPortis

The **real** OpenGL IRIX Electropaint screensaver, running in sgi-demos — decompiled from the original 32-bit MIPS binary, not a reimplementation. This is the version with David Tristram's famous default animation script *and* smooth RGB/HLS colour (the earlier [ep-1989](../ep-1989) demo approximates the same script in colour-index mode, which is why its colours step rather than glide).

## Provenance

Source is [Brendan Shanks's (`bslabs`) cross-platform fork](https://github.com/bslabs) of [drvink's ElectroPortis](https://github.com/drvink/electroportis) — a *clean, properly-typed C* decompilation (drvink's own repo is a raw MIPS register-machine dump). ElectroPortis was produced by running the IRIX OpenGL `ep` binary through [epanos](https://github.com/drvink/epanos), a custom MIPS→C decompiler. `ep.c`, `ep.h`, and `ep_gluperspective.h` are copied **verbatim** from that fork.

## How the port works

ElectroPortis is an OpenGL program; sgi-demos renders IRIS GL. The bridge is `ep.c`'s own GL abstraction: it draws through a tiny set of `wrap_gl*` calls (`wrap_glBegin`/`glVertex2f`/`glEnd`, `wrap_glColor4f`, `wrap_glPush/PopMatrix`, `wrap_glRotatef`/`Translatef`/`Scalef`, `wrap_glClear`), which on most platforms are `#define`d straight to OpenGL. Here they're **retargeted onto IRIS GL** instead:

- [gl_wrap.h](gl_wrap.h) replaces the fork's header: it declares the GL types/enums `ep.c` needs and maps every `wrap_gl*` (and the direct `glViewport`/`glMatrixMode`/`glFrustum`… in reshape) to the IRIS GL primitives sgi-demos implements.
- [gl_wrap_sgi.c](gl_wrap_sgi.c) implements those shims: `glBegin`/`glVertex2f`/`glEnd` buffer vertices and emit them as `bgnpolygon`/`bgnline`; `glRotatef`→`rotate` (tenths of a degree + axis); `glClear`→black `clear()`; and `ep_gluPerspective`→IRIS `perspective()`.
- [main_sgi.c](main_sgi.c) is the harness (replacing the fork's GLUT `main`): a single RGB double-buffered window running `init_ep()` / `reshape__GiT1()` / `display__Gv()`, yielding once per frame via `swapbuffers()`.

Built with `-DOPENGL10` (the immediate-mode draw path, which maps 1:1 to IRIS GL) and `-std=gnu11` (the decompiled C is modern, not the repo's default C90). `ep.c` itself is unmodified.

### The rewrite's two accidents, and the `M` key

The 1994 OpenGL rewrite silently diverged from the IRIS GL ep in two ways (consistent with its author's own "it wasn't quite the same afterwards"):

1. **Lost mirrors.** The display loop never fills the `size[]` history array (the size-actuator wiring went away with the control panels), so the **three mirrored copies of every wing** are drawn under `scale(0, 0, 1)` — collapsed to points. Real OpenGL rasterizes nothing for zero-area/zero-length primitives, so the shipped screensaver showed a single copy per wing, losing the IRIS-era 4-fold symmetry. (Our IRIS GL rasterizers plotted the collapsed copies as single pixels — spurious swirling "particles" — before this was handled.)
2. **Accidental camera.** `ep`'s reshape passes `300` — the IRIS `perspective()` convention, **tenths of a degree** (= 30°) — to `gluPerspective`, which reads *degrees*. The result on real OpenGL is an inverted frustum with an effective **60° FOV** at eye distance 4, instead of the IRIS ep's 30° at polarview distance 10.

The shim handles both (`ep_gl_scalef`/`pushmatrix`/`popmatrix`/`ep_gluPerspective` in [gl_wrap_sgi.c](gl_wrap_sgi.c)), as one mode switch:

- **Default — faithful to the IRIS GL ep**: mirrors restored (the collapsing scale is treated as identity, so mirror copies render at the primary copy's size) and the intended camera (30° FOV, eye at distance 10).
- **Press `M` — the shipped 1994 binary's look**: one visible copy per wing (degenerates discarded exactly as real OpenGL rasterization would, no particles) and the accidental wide flipped camera (60°, distance 4). Verified against the fork's native GLUT/OpenGL build under the same deterministic seed (`-DTEST`): matching composition, zero particles.

## What you get

The wings are **squares** (the OpenGL version's shape), swirling in the classic spiral/mandala under Tristram's "mello script", with **smooth hue and lightness motion through HLS space** and complementary-coloured outlines — the authentic screensaver, GPU (`gles2`) or CPU (`ref`) rasterizer, native and web.
