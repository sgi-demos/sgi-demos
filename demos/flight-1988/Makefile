# SGI Flight Simulator, the 1988-89 original (see Makefile.orig, SGI's own).
# Sources are byte-identical to the archive tree except a handful of
# unavoidable modern-C fixes (see README.md); everything else is handled here
# and in include/shim/{psio.h,iconize.h}.
APPNAME=flight-1988
# SGI's Makefile links the flight binary WITHOUT these: comm.c/udpcomm.c/
# udpbrdcst.c belong to the separate dog target (flight.c has local stubs),
# and shadow.c is its own program.
DEMO_EXCLUDE_SRC=comm.c udpcomm.c udpbrdcst.c shadow.c
# -D_4D: SGI's own LCOPTS (Makefile.orig) — selects the 4D-era float-tps
#   physics and CLOCKRATE=HZ; without it the IRIS-3000 fallback assumes a
#   60Hz times() clock and the sim runs ~40% slow ("planes too slow")
# -DHZ=100: IRIX <sys/param.h> ticks/sec; matches times() on macOS/Linux and
#   Emscripten's musl
# -Dregister=: IRIX cc allowed things modern C90 register vars can't do
# -Drandom=flight_random: uflight.c defines its own random(range), which
#   collides with libc's random(void); the define renames the definition and
#   every caller uniformly (no flight TU includes <stdlib.h>)
# -w: silence warnings on this frozen vintage source. All are verified-benign
#   K&R-isms (extra printf args, their DELAY/XXX macro shadowing, float[60] as
#   float(*)[3], #endif DEBUG tokens), and the "too many arguments in call"
#   K&R diagnostic has no -Wno-<name> flag (same story as ep-1988).
DEMO_CFLAGS=-D_4D -DHZ=100 -Dregister= -Drandom=flight_random -w
include ../../makefiles/make_demo.mk
include ../../makefiles/run_networked.mk
