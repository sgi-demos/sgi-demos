/*****************************************************************
    sgi-demos: headless stand-in for the SGI Panel Library.

    Electropaint was written against David Tristram's Panel Library
    (libpanel), which draws its slider/button control panels in GL
    windows of its own.  The sgi-demos IRIS GL emulator is a single
    window system, so instead of porting libpanel's ~11k lines of
    windowing and drawing code, this file implements the panel API as
    pure data: actuators are allocated and linked exactly as libpanel
    does, but nothing is ever drawn.  ep.c compiles against the real
    panel.h unmodified, reads and animates the same actuator structs,
    and drives everything visible from its own drawit().

    Keyboard equivalents still work: pnl_addact() registers each
    actuator's key with qdevice() just like the real library, and
    pnl_dopanel() drains the GL event queue, toggling the matching
    actuator when its key is pressed (e.g. O outline, U fill, Q smear,
    W fade, E background, S stop).  ESC exits.
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

void *
pnl_alloc(int size)
{
  void *p = calloc(1, size);

  if (!p) {
    fprintf(stderr, "panelstub: out of memory\n");
    exit(1);
  }
  return p;
}

/* ------------------------------------------------------------------ */
/* actuator types: each init function just sets default geometry and  */
/* allocates the type-specific data struct that PNL_ACCESS() reads    */
/* ------------------------------------------------------------------ */

void
pnl_label(Actuator *a)
{
  a->selectable = FALSE;
}

void
pnl_wide_button(Actuator *a)
{
  a->w = PNL_WIDE_BUTTON_WIDTH;
  a->h = PNL_WIDE_BUTTON_HEIGHT;
}

void
pnl_toggle_button(Actuator *a)
{
  a->w = PNL_BUTTON_EDGE;
  a->h = PNL_BUTTON_EDGE;
}

void
pnl_hslider(Actuator *a)
{
  Slider *ad;

  a->w = PNL_SLIDER_HEIGHT;
  a->h = PNL_SLIDER_WIDTH;
  a->data = pnl_alloc(sizeof(Slider));
  ad = (Slider *)a->data;
  ad->bh = PNL_SLIDER_BAR_HEIGHT / 2.0;
}

void
pnl_multislider(Actuator *a)
{
  Multislider *ad;

  a->w = PNL_SLIDER_WIDTH;
  a->h = PNL_SLIDER_HEIGHT;
  a->data = pnl_alloc(sizeof(Multislider));
  ad = (Multislider *)a->data;
  ad->bh = PNL_SLIDER_BAR_HEIGHT / 2.0;
  ad->acttype = pnl_multislider_bar;
}

void
pnl_multislider_bar(Actuator *a)
{
}

void
pnl_multislider_open_bar(Actuator *a)
{
}

void
pnl_floating_puck(Actuator *a)
{
  a->w = PNL_FLOATING_PUCK_EDGE;
  a->h = PNL_FLOATING_PUCK_EDGE;
  a->data = pnl_alloc(sizeof(Puck));
}

/* ------------------------------------------------------------------ */
/* construction: same bookkeeping as libpanel's panel.c               */
/* ------------------------------------------------------------------ */

Panel *
pnl_mkpanel(void)
{
  Panel *p = (Panel *)pnl_alloc(sizeof(Panel));

  p->active = TRUE;
  p->selectable = TRUE;
  p->visible = TRUE;
  p->ppu = PNL_PIXELS_PER_UNIT;
  p->next = pnl_pl;
  pnl_pl = p;
  return p;
}

Actuator *
pnl_mkact(void (*initfunc)())
{
  Actuator *a = (Actuator *)pnl_alloc(sizeof(Actuator));

  a->key = NULLDEV;
  a->labeltype = PNL_LABEL_BOTTOM;
  a->initfunc = initfunc;
  a->group = a;
  a->selectable = TRUE;
  a->visible = TRUE;
  a->beveled = TRUE;
  a->minval = 0.0;
  a->maxval = 1.0;
  a->val = 0.0;
  a->scalefactor = 1.0;

  if (initfunc) (*initfunc)(a);
  return a;
}

Actuator *
mkact(void (*initfunc)())
{
  return pnl_mkact(initfunc);
}

Actuator *
_mkuseract(int size, void (*initfunc)())
{
  Actuator *useract = (Actuator *)pnl_alloc(size);
  Actuator *temp = pnl_mkact(initfunc);

  *useract = *temp;             /* structure copy, as in libpanel */
  useract->group = useract;
  free(temp);
  return useract;
}

Actuator *
pnl_mkuseract(int size, void (*initfunc)())
{
  return _mkuseract(size, initfunc);
}

void
pnl_addact(Actuator *a, Panel *p)
{
  a->p = p;
  a->pa = NULL;
  a->next = p->al;
  p->al = a;
  a->initval = a->val;

  if (a->key != NULLDEV) {
    Alist *e = (Alist *)pnl_alloc(sizeof(Alist));

    e->a = a;
    e->next = pnl_kl;
    pnl_kl = e;
    qdevice(a->key);
  }
}

void
addact(Actuator *a, Panel *p)
{
  pnl_addact(a, p);
}

void
pnl_addsubact(Actuator *sa, Actuator *a)
{
  sa->p = a->p;
  sa->pa = a;
  sa->next = a->al;
  a->al = sa;
  a->na++;
  sa->initval = sa->val;
}

/* ------------------------------------------------------------------ */
/* no-op drawing and fixup                                            */
/* ------------------------------------------------------------------ */

void pnl_fixact(Actuator *a) {}
void fixact(Actuator *a) { pnl_fixact(a); }
void pnl_fixpanel(Panel *p) {}
void pnl_drawpanel(void) {}
void _drawwidebutton(Actuator *a, Panel *p) {}

/* These three are undeclared in panel.h, so ep.c's call sites use the
   implicit int return type; the definitions must match or the calls
   trap on WebAssembly (wasm-ld checks signatures). */
int pnl_drawbevel(Actuator *a, Panel *p) { return 0; }
int pnl_drawlabel(Actuator *a, Panel *p) { return 0; }
int initscriptpanel(void) { return 0; }

/* ------------------------------------------------------------------ */
/* event handling                                                     */
/* ------------------------------------------------------------------ */

void
pnl_needredraw(void)
{
  qdevice(REDRAW);
  qdevice(ESCKEY);
}

short
pnl_userredraw(void)
{
  short r = userredraw_seen;

  userredraw_seen = 0;
  return r;
}

/* Press of an actuator's keyboard equivalent, standing in for a mouse
   click on it: toggle the value and run the down/up callbacks. */
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
pnl_dopanel(void)
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
