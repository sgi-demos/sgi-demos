APPNAME=arena
APP_DEFS=-DNETWORKING=1
# arena's layout is calibrated to the 1024x768 IRIS screens (its own hud.c
# says so): HUD bars/meters cluster around x=512, ortho2 is 0..1023/0..767.
# Build it for that screen; prefposition(0,XMAXSCREEN,0,YMAXSCREEN) then
# gets it a 1024x768 framebuffer instead of the 1280x1024 default.
DEMO_CFLAGS=-DXMAXSCREEN=1023 -DYMAXSCREEN=767
include ../../makefiles/make_demo.mk
include ../../makefiles/run_networked.mk
