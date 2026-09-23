APPNAME=arena
# arena's layout is calibrated to the 1024x768 IRIS screens (its own hud.c
# says so): HUD bars/meters cluster around x=512, ortho2 is 0..1023/0..767.
# Build it for that screen; prefposition(0,XMAXSCREEN,0,YMAXSCREEN) then
# gets it a 1024x768 framebuffer instead of the 1280x1024 default.
#
# Network play (-n) is not ported yet. Its UDP code (comm.c, udpbrdcst.c) is
# fenced behind NETWORKING, off by default; it compiles natively with it on:
#   make -B native NETWORKING=-DNETWORKING=1
#   make run_networked HOST=<this machine's address>
# A browser has no UDP, so the web build will need another transport.
NETWORKING=
DEMO_CFLAGS=-DXMAXSCREEN=1023 -DYMAXSCREEN=767 $(NETWORKING)
include ../../makefiles/make_demo.mk

run_networked: $(APP)
	@if [ -z "$(HOST)" ]; then echo "Set HOST to this machine's address: make run_networked HOST=..."; else HOST=$(HOST) $(APP) -n; fi
