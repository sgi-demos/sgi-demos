# Electropaint (1988)

The **earliest** known Electropaint, from **Panel Library v7**, which David Tristram posted to `comp.sys.sgi` on 18 August 1988 while at NASA Ames. Source recovered from that Usenet posting — see [../ep-1989/versions/](../ep-1989/versions/README.md) for provenance and the full v7 distribution.

This is a companion to the [ep-1989](../ep-1989) demo (the later igl 0.1.8 version). Run both side by side to see how the demo changed.

## How it differs from the later version

- **No self-animating sliders.** v7 predates the Panel Library's Modslider actuator. Its sliders (`pnl_dvslider`) are plain values read directly (`speedslider->val`); there's no built-in wander and no default script. So attract mode here drives the plain sliders with **external sinusoidal oscillators** (`attractmode()` in [ep.c](ep.c)) — one slow LFO per slider — rather than leaning on panel-library animation.
- **Simpler geometry.** `drawit()` draws four mirrored copies of the triangle stream; the mirror-fold ribbon geometry the later version adds isn't here, so the motion reads as a looser, more scattered swarm.
- **944-line `ep.c`** vs 1925 in the later version; no color-panel / HLS-lighting (`IRIS_GT`) path in use.

## How the port works

Same approach as the sibling demo: [panelstub.c](panelstub.c) is a **headless** stand-in for the Panel Library — actuators are allocated and linked as data, nothing is drawn, no panel window opens. It targets v7's older API (unprefixed `mkpanel`/`mkact`/`dopanel`…, the `pnl_dvslider` actuator, v7's simpler `Actuator` struct). Colormap (color-index) mode with the spectrum map.

Keyboard toggles work via actuator key registration: `O` outline, `I` fat lines, `U` fill, `R` ribbons, `M` smooth, `Q` smear, `W` fade, `S` stop, `F` full screen; `ESC` exits.

## Source modifications

The v7 source needed two fixes for a modern (token-based) C preprocessor, both marked `sgi-demos:` in [ep.c](ep.c):
- The `MK_EP_SLIDER` macro pasted tokens with the K&R empty-comment idiom (`Mname`+empty comment+`slider`); rewritten with `##`.
- One slider bound used `NPNTS.0-1.0`, which relied on character-level macro expansion to mean `128.0-1.0`; spelled out.
