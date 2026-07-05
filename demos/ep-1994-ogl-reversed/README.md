# ElectroPortis (readable fork)

A human-readable fork of the [ep-1994-ogl-decomp](../ep-1994-ogl-decomp) demo. Same demo, byte-for-byte the same output — but `ep.c` is refactored from the MIPS decompiler's mangled names into readable ones, so you can actually follow how Electropaint works.

The sibling [ep-1994-ogl-decomp](../ep-1994-ogl-decomp) demo keeps `ep.c` **verbatim** from Brendan Shanks's bslabs decompilation (minimal changes — see its README for the IRIS GL port mechanism, which this fork reuses unchanged: `gl_wrap.h`, `gl_wrap_sgi.c`, `main_sgi.c`). This fork changes **only names**, never logic.

## What was renamed

- **Functions** — the decompiler's C++-mangled names dropped to plain ones: `value__GfN21`→`trapezoid`, `drawit__Gv`→`draw_wings`, `display__Gv`→`ep_display`, `reshape__GiT1`→`ep_reshape`, `hls_to_rgb__GfN21PfN24`→`hls_to_rgb`, `processCommand__GP11animCommand`→`process_command`, `setacttargets__Gv`→`set_act_targets`, `animateacts__Gv`→`animate_acts`, `readAnimation__Gv`→`read_animation`, `twixt__GiPff`→`interp`, `foldtwixt__GiPffT3`→`fold_interp`, `exprand__Gf`→`exp_rand`, and the rest.
- **Actuator ids** — the magic numbers indexing `acttable[]` became named constants, so the animation reads in English: `acttable[52]->flt_g` is now `acttable[ACT_N]->value`, `acttable[101]`→`acttable[ACT_WRIST]`, `acttable[123]`→`acttable[ACT_HUE]`, etc. (full list at the top of `ep.c`).
- **The one certain struct field** — `struct act`'s `flt_g` (the current animated value read by the draw loop) → `value`.

## What was deliberately *not* renamed

`struct act`'s other fields (`flt_c`…`flt_j`) are a stochastic target/smoothing model whose exact roles are genuinely ambiguous — even the bslabs author left them as `flt_*`. Renaming them on a guess would make the code *less* faithful, so they're kept as-is. `struct animSeq`/`animCommand` keep the bslabs names. The decompiler's `/* … no regmap info … */` comments are kept too — they're honest provenance.

## Faithfulness check

Built with `-DTEST` (which seeds `srand48(0)` for a deterministic show), this fork and the verbatim `ep-1994-ogl-decomp` demo produce **byte-identical frames** (`cmp` confirms frames 50/100/150 match exactly). The rename touched names only.
