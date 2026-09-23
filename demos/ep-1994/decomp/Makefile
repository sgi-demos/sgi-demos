APPNAME=ep-1994-decomp
# ep.c is Brendan Shanks's modern C decompilation (needs C99+, not the
# default -std=c90); -DOPENGL10 selects the immediate-mode draw path that
# gl_wrap.h maps onto IRIS GL.
# The harness is the readable build's, in the parent directory: -I.. finds
# gl_wrap.h and stdafx.h, main_sgi.c and gl_wrap_sgi.c here include ../ ones,
# the -D renames point its calls at the decompiled names, and this build
# starts in the shipped-1994 look (M toggles).
DEMO_CFLAGS=-I. -I.. -std=gnu11 -DOPENGL10 -Wno-int-conversion \
	-Dep_reshape=reshape__GiT1 -Dep_display=display__Gv -DEP_SHIPPED_DEFAULT=1
DEMO_EXTRA_HDRS=../main_sgi.c ../gl_wrap_sgi.c ../gl_wrap.h ../stdafx.h
include ../../../makefiles/make_demo.mk
