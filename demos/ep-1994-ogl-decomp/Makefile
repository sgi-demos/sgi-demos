APPNAME=ep-1994-ogl-decomp
# ep.c is Brendan Shanks's modern C decompilation (needs C99+, not the
# default -std=c90); -DOPENGL10 selects the immediate-mode draw path that
# gl_wrap.h maps onto IRIS GL.  -I. finds gl_wrap.h / ep.h / ep_gluperspective.h.
DEMO_CFLAGS=-I. -std=gnu11 -DOPENGL10 -Wno-int-conversion
include ../../makefiles/make_demo.mk
