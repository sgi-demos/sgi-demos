/*****************************************************************
    sgi-demos: headless stand-in for the 1988 SGI Panel Library (v7).

    Same idea as the sibling electropaint demo's panelstub.c, but for the
    older v7 API this 1988 Electropaint was written against: unprefixed
    entry points (mkpanel/mkact/addact/dopanel...), the pnl_dvslider
    actuator instead of the later Modslider, and a simpler Actuator struct
    (no extval). Actuators are allocated and linked as data only; nothing
    is drawn and no panel window opens. ep.c reads/animates the same
    actuator structs it always did.

    Keyboard equivalents work: addact() registers each actuator's key with
    qdevice(), and dopanel() toggles the matching actuator on key press
    (O outline, I fat lines, U fill, R ribbons, M smooth, Q smear, W fade,
    S stop, F full screen). ESC exits.
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <gl.h>
#include <device.h>

/* instantiate panel.h's PNL_EXTERN globals in this translation unit */
#define PNL_EXTERN
#define PNL_INIT(x) = x
#include "panel.h"

static short userredraw_seen = 0;

static void *
stub_alloc(int size)
{
  void *p = calloc(1, size);

  if (!p) {
    fprintf(stderr, "panelstub: out of memory\n");
    exit(1);
  }
  return p;
}

/* ------------------------------------------------------------------ */
/* actuator types                                                     */
/* ------------------------------------------------------------------ */

void pnl_label(Actuator *a)        { a->selectable = FALSE; }
void pnl_wide_button(Actuator *a)  { a->w = PNL_WIDE_BUTTON_WIDTH; a->h = PNL_WIDE_BUTTON_HEIGHT; }
void pnl_toggle_button(Actuator *a){ a->w = PNL_BUTTON_EDGE; a->h = PNL_BUTTON_EDGE; }

void
pnl_dvslider(Actuator *a)
{
  a->w = PNL_SLIDER_WIDTH;
  a->h = PNL_SLIDER_HEIGHT;
  /* ep.c reads/writes a->val directly; no per-actuator data needed */
}

void
pnl_floating_puck(Actuator *a)
{
  a->w = PNL_FLOATING_PUCK_EDGE;
  a->h = PNL_FLOATING_PUCK_EDGE;
  a->data = stub_alloc(sizeof(Puck));   /* PNL_ACCESS(Puck,...) reads this */
}

/* ------------------------------------------------------------------ */
/* construction                                                       */
/* ------------------------------------------------------------------ */

Panel *
mkpanel(void)
{
  Panel *p = (Panel *)stub_alloc(sizeof(Panel));

  p->active = TRUE;
  p->enabled = TRUE;
  p->ppu = PNL_PIXELS_PER_UNIT;
  p->next = pnl_pl;
  pnl_pl = p;
  return p;
}

Actuator *
mkact(void (*initfunc)())
{
  Actuator *a = (Actuator *)stub_alloc(sizeof(Actuator));

  a->key = NULLDEV;
  a->labeltype = PNL_LABEL_BOTTOM;
  a->group = a;
  a->selectable = TRUE;
  a->visible = TRUE;
  a->minval = 0.0;
  a->maxval = 1.0;
  a->val = 0.0;

  if (initfunc) (*initfunc)(a);
  return a;
}

Actuator *
_mkuseract(int size, void (*initfunc)())
{
  Actuator *useract = (Actuator *)stub_alloc(size);
  Actuator *temp = mkact(initfunc);

  *useract = *temp;             /* structure copy, as in libpanel */
  useract->group = useract;
  free(temp);
  return useract;
}

void
addact(Actuator *a, Panel *p)
{
  a->p = p;
  a->next = p->al;
  p->al = a;
  a->initval = a->val;

  if (a->key != NULLDEV) {
    Alist *e = (Alist *)stub_alloc(sizeof(Alist));

    e->a = a;
    e->next = pnl_kl;
    pnl_kl = e;
    qdevice(a->key);
  }
}

/* ------------------------------------------------------------------ */
/* no-op fixup / draw                                                 */
/* ------------------------------------------------------------------ */

void drawpanel(void) {}

/* fixact and initscriptpanel are undeclared in panel.h, so ep.c calls them
   with the implicit-int return type; the definitions must match or the calls
   trap on WebAssembly (wasm-ld checks signatures). */
int fixact(Actuator *a) { return 0; }
int initscriptpanel(void) { return 0; }

/* ------------------------------------------------------------------ */
/* events                                                             */
/* ------------------------------------------------------------------ */

void
needredraw(void)
{
  qdevice(REDRAW);
  qdevice(ESCKEY);
}

short
userredraw(void)
{
  short r = userredraw_seen;

  userredraw_seen = 0;
  return r;
}

/* key press stands in for a mouse click on the actuator */
static void
key_hit(Actuator *a, int pressed)
{
  if (pressed) {
    a->val = (a->val == a->maxval) ? a->minval : a->maxval;
    if (a->downfunc) (*a->downfunc)(a);
  } else {
    if (a->upfunc) (*a->upfunc)(a);
  }
}

Actuator *
dopanel(void)
{
  short val;
  long dev;
  Alist *e;

  while (qtest()) {
    dev = qread(&val);
    if (dev == REDRAW) {
      userredraw_seen = 1;
    } else if (dev == ESCKEY) {
      if (val) exit(0);
    } else {
      for (e = pnl_kl; e; e = e->next)
        if (e->a->key == dev) {
          key_hit(e->a, val != 0);
          break;
        }
    }
  }
  return NULL;                  /* no actuator is ever mouse-active */
}
