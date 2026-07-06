# SGI Flight Simulator Version 3.4. SGI's original smake file is
# Makefile.orig (27 CFILES + sibling libgobj.a, -DAUDIO, -laudio).
# -DNO_MS: build without the multisample calls (SGI's documented option
# for pre-4.0.5G IRIX; our libgl has no multisample either).
APPNAME=flight-1994
DEMO_EXTRA_SRC=$(wildcard libgobj/*.c)
DEMO_EXTRA_HDRS=libgobj/gobj.h
# aifflib.c needs IRIX <audio.h>; sound.c is #ifdef AUDIO (off for now)
DEMO_EXCLUDE_SRC=aifflib.c
# -DHZ=100: IRIX <sys/param.h> ticks/sec for times() math (matches
#   _SC_CLK_TCK on macOS/Linux and Emscripten's musl)
# -Dregister=: IRIX cc allowed &register-var; modern C90 doesn't
# -DM_PI: emscripten's strict-c90 math.h hides it
# -D_GNU_SOURCE: emscripten's musl hides struct ip_mreq/caddr_t (udpbrdcst.c) without it
# -include strings.h + vintage_io.h: real prototypes for bzero/bcopy/lseek —
#   the K&R implicit declarations trap wasm's call-signature checking
# -w: silence warnings on this frozen vintage source — all verified-benign
#   (%d-with-long is identical on wasm32 and cosmetic in native dog/radar
#   prints, BSD sockaddr casts, short* I/O buffers, same-struct pointer
#   difference via (int) casts in comm.c, feedback-stub buffer type in
#   libgobj cull(), and SGI's own "&d" printf typo in radar.c's unreached
#   fatal path)
DEMO_CFLAGS=-I. -Ilibgobj -DNO_MS -DHZ=100 -Dregister= -DM_PI=3.14159265358979323846 -D_GNU_SOURCE -include strings.h -include vintage_io.h -w
# mount defs/ at the IRIX default data path so no -D argument is needed
EM_PRELOAD=--preload-file defs@/usr/demos/data/flight
include ../../makefiles/make_demo.mk
