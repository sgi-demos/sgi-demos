/*****************************************************************
    sgi-demos: Electropaint animation-script engine.

    A faithful reimplementation of the sequence engine from the OpenGL
    IRIX Electropaint (recovered by the ElectroPortis decompilation), and
    the vehicle for Dave Tristram's actual default "mello script" that
    drove the famous screensaver.  The engine and script are decoupled
    from the renderer: it parses the script text into per-actuator
    sequences and, each frame, writes animated values into a public
    actuator table (epscript_act[]).  ep.c reads that table and maps the
    actuator ids onto its own sliders (see epscript_apply() there).

    Script model (from ElectroPortis src/ep.c):
      actset:  id, v     set actuator id to a constant v
      seqname: k         begin defining sequence k
      seqdo:   k         activate sequence k
      duration: N        frames for the NEXT oscillation (one full cycle)
      actlim1: id, v     low endpoint of the next oscillation
      actlim2: id, v     high endpoint; emits the oscillation step
      randdelay: N       hold for an exponential-random ~N frames
      seqloop:           (sequences loop their step list regardless)

    Each oscillation drives its actuator with the ORIGINAL trapezoidal
    wave (value__GfN21 in ep.c): over a 360-degree phase spanning one
    `duration`, ramp lim1->lim2 (0-60 deg), hold lim2 (60-180), ramp
    lim2->lim1 (180-240), hold lim1 (240-360).
*****************************************************************/
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define EPS_MAXSEQ   16
#define EPS_MAXSTEP  16
#define EPS_NACT     140

enum { EPS_OSC, EPS_DELAY };

typedef struct {
  int   kind;             /* EPS_OSC or EPS_DELAY */
  int   actid;            /* target actuator id (EPS_OSC) */
  int   duration;         /* frames: oscillation period, or delay base */
  float lim1, lim2;       /* oscillation endpoints (EPS_OSC) */
} EpsStep;

typedef struct {
  EpsStep step[EPS_MAXSTEP];
  int nstep;
  int active;
  int cur;                /* current step index */
  int timer;              /* frames elapsed within the current step */
  int dlen;               /* resolved length of the current delay step */
} EpsSeq;

static EpsSeq eps_seq[EPS_MAXSEQ];

/* public: actuator table, indexed by the script's numeric actuator ids */
float epscript_act[EPS_NACT];

/* Dave Tristram's default "mello script", verbatim from ElectroPortis
   (src/ep.c defaultScript); also kept as versions/mello.script. */
static char *eps_default_script =
"# created by mkmaster \n"
"#\n"
"# mello script\n"
"#\n"
"#\tDave Tristram\n"
"#\n"
"#\tthis script moves gently on the screen, and uses wheel to maintain\n"
"#\ta 3D look.\n"
"#\n"
"#\n"
"# constants\n"
"#\n"
"actset: 29, 1.0\t\t# \"full\"\n"
"actset: 17, 0.0\t\t# \"auto\"\n"
"actset: 18, 1.0\t\t# \"outline\"\n"
"# actset: 73, 0.107258\t# \"whl\"\n"
"actset: 31, 0.06\t# \"zoom\"\n"
"actset: 38, 60.0\t# \"twst\"\n"
"#actset: 80, 0.23\t# \"spn\" slow\n"
"actset: 108, 1.2\t# \"size\"\n"
"actset: 52, 40.0\t# \"n\"\n"
"#\n"
"seqdo: 1\t# wrist\n"
"seqdo: 2\t# color\n"
"seqdo: 3\t# wheel\n"
"seqdo: 4\t# spin\n"
"seqdo: 5\t# flip\n"
"seqdo: 6\t# arm\n"
"seqdo: 7\t# twist\n"
"seqdo: 8\t# outline\n"
"#\n"
"# wrst anim: gentle radius modulation\n"
"seqname: 1\n"
"duration: 160\n"
"actlim1: 101, -1.5\t\t# wrst\n"
"actlim2: 101,  1.5\t\t# wrst\n"
"#\n"
"# color anim: hue and lightness motion\n"
"seqname: 2\n"
"duration: 60\n"
"actset: 127, 0.0\t\t# hue rate chan 0\n"
"actlim1: 123, 0.544053\t\t# hue chan 0 (just near cyan)\n"
"actlim2: 123, 1.295\t\t# hue chan 0 (deep green)\n"
"duration: 80\n"
"actlim1: 130, 0.0\t\t# lightness chan 0 (black)\n"
"actlim2: 130, 1.0\t\t# lightness chan 0 (white)\n"
"#\n"
"# wheel anim: very slow, gentle rocking\n"
"seqname: 3\n"
"duration: 120\n"
"actlim1: 73, 0.137\t\t# wheel, real slow\n"
"actlim2: 73, -0.137\t\t# wheel, real slow\n"
"#\n"
"# spin anim: somewhat fast occasionally\n"
"seqname: 4\n"
"duration: 100\n"
"actlim1: 80,  0.23\t\t# spn slow\n"
"actlim2: 80, -0.23\t\t# spn slow\n"
"randdelay: 1000\n"
"duration: 40\n"
"actlim1: 80,  5.23\t\t# spn fast\n"
"actlim2: 80, -5.23\t\t# spn fast\n"
"randdelay: 200\n"
"seqloop:\n"
"#\n"
"# flip anim: somewhat fast occasionally\n"
"seqname: 5\n"
"duration: 50\n"
"actlim1: 87,  2.0\t\t# flip slow\n"
"actlim2: 87, -2.0\t\t# flip slow\n"
"randdelay: 1200\n"
"actlim1: 87,  10.0\t\t# flip fast\n"
"actlim2: 87, -10.0\t\t# flip fast\n"
"randdelay: 220\n"
"seqloop:\n"
"#\n"
"# arm anim: gentle radius modulation\n"
"seqname: 6\n"
"duration: 90\n"
"actlim1: 94, -2.0\t\t# arm\n"
"actlim2: 94,  2.0\t\t# arm\n"
"#\n"
"# twist anim:\n"
"seqname: 7\n"
"duration: 2250\n"
"actlim1: 38, 200.0\t\t# twst\n"
"actlim2: 38, -200.0\t\t# twst\n"
"#\n"
"# outline anim: on and off infrequently, mostly on\n"
"seqname: 8\n"
"duration: 5000\n"
"actlim1: 18, 0.2\t\t# outline\n"
"actlim2: 18, 1.0\t\t# outline\n"
"# end of generated script";

/* ORIGINAL trapezoidal oscillator (value__GfN21). phase in degrees. */
static float
eps_trapezoid(float lim1, float lim2, float phase)
{
  phase = fmod(phase, 360.0);
  if (phase < 0.0) phase += 360.0;
  if (phase <  60.0) return lim1 + (lim2 - lim1) * (phase / 60.0);
  if (phase < 180.0) return lim2;
  if (phase < 240.0) return lim1 + (lim2 - lim1) * ((240.0 - phase) / 60.0);
  return lim1;
}

/* exponential random hold with mean n frames (exprand__Gf) */
static int
eps_exprand(int n)
{
  double u = (rand() + 1.0) / ((double)RAND_MAX + 2.0);
  int d = (int)(-(double)n * log(u));
  if (d < 0) d = 0;
  if (d > 6 * n) d = 6 * n;     /* clamp the exponential tail */
  return d;
}

/* strip an inline '#' comment and trailing whitespace, in place */
static void
eps_decomment(char *s)
{
  char *h = strchr(s, '#');
  char *e;

  if (h) *h = '\0';
  e = s + strlen(s);
  while (e > s && (e[-1] == ' ' || e[-1] == '\t' || e[-1] == '\r' || e[-1] == '\n'))
    *--e = '\0';
}

static void
eps_parse(const char *text)
{
  char *buf = strdup(text);
  char *save = NULL;
  char *line;
  int curseq = -1;        /* sequence being defined by seqname */
  int pend_dur = 60;      /* pending duration for the next oscillation */
  int pend_id = -1;       /* actlim1's actuator id */
  float pend_lim1 = 0.0;

  for (line = strtok_r(buf, "\n", &save); line; line = strtok_r(NULL, "\n", &save)) {
    int id, k;
    float v;

    eps_decomment(line);
    while (*line == ' ' || *line == '\t') line++;
    if (*line == '\0') continue;

    if (sscanf(line, "actset: %d , %f", &id, &v) == 2) {
      if (id >= 0 && id < EPS_NACT) epscript_act[id] = v;
    } else if (sscanf(line, "seqname: %d", &k) == 1) {
      if (k >= 0 && k < EPS_MAXSEQ) { curseq = k; eps_seq[k].nstep = 0; }
    } else if (sscanf(line, "seqdo: %d", &k) == 1) {
      if (k >= 0 && k < EPS_MAXSEQ) eps_seq[k].active = 1;
    } else if (sscanf(line, "duration: %d", &pend_dur) == 1) {
      /* pend_dur set */
    } else if (sscanf(line, "actlim1: %d , %f", &pend_id, &pend_lim1) == 2) {
      /* endpoints held until actlim2 */
    } else if (sscanf(line, "actlim2: %d , %f", &id, &v) == 2) {
      if (curseq >= 0 && eps_seq[curseq].nstep < EPS_MAXSTEP) {
        EpsStep *st = &eps_seq[curseq].step[eps_seq[curseq].nstep++];
        st->kind = EPS_OSC;
        st->actid = id;
        st->lim1 = pend_lim1;
        st->lim2 = v;
        st->duration = pend_dur > 0 ? pend_dur : 1;
      }
    } else if (sscanf(line, "randdelay: %d", &k) == 1) {
      if (curseq >= 0 && eps_seq[curseq].nstep < EPS_MAXSTEP) {
        EpsStep *st = &eps_seq[curseq].step[eps_seq[curseq].nstep++];
        st->kind = EPS_DELAY;
        st->duration = k > 0 ? k : 1;
      }
    }
    /* seqloop: and anything else -> ignored (sequences loop regardless) */
  }
  free(buf);
}

void
epscript_init(void)
{
  int s;

  memset(eps_seq, 0, sizeof(eps_seq));
  memset(epscript_act, 0, sizeof(epscript_act));
  eps_parse(eps_default_script);

  for (s = 0; s < EPS_MAXSEQ; s++) {
    eps_seq[s].cur = 0;
    eps_seq[s].timer = 0;
    if (eps_seq[s].nstep && eps_seq[s].step[0].kind == EPS_DELAY)
      eps_seq[s].dlen = eps_exprand(eps_seq[s].step[0].duration);
  }
}

/* advance every active sequence one frame, updating epscript_act[] */
void
epscript_step(void)
{
  int s;

  for (s = 0; s < EPS_MAXSEQ; s++) {
    EpsSeq *q = &eps_seq[s];
    EpsStep *st;
    int len;

    if (!q->active || q->nstep == 0) continue;
    st = &q->step[q->cur];

    if (st->kind == EPS_OSC) {
      float phase = 360.0 * (float)q->timer / (float)st->duration;
      if (st->actid >= 0 && st->actid < EPS_NACT)
        epscript_act[st->actid] = eps_trapezoid(st->lim1, st->lim2, phase);
      len = st->duration;
    } else {
      len = q->dlen;
    }

    if (++q->timer >= len) {
      q->timer = 0;
      if (++q->cur >= q->nstep) q->cur = 0;
      if (q->step[q->cur].kind == EPS_DELAY)
        q->dlen = eps_exprand(q->step[q->cur].duration);
    }
  }
}
