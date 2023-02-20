RASTERIZER_SRCS = ../libgl/reference_rasterizer.c
EVENTS_SRCS = ../libgl/sdl_gl_events.c
LIBGL_SRC = ../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)
EM_SRC = ../libgl/camera2D.c ../libgl/ogles_framebuffer.c
LIBGL_INC = -I../sys_include
DEMO_INC = $(LIBGL_INC) -I../demo_include
DEMO_WARN_OFF = -Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value -Wno-return-type -Wno-parentheses -Wno-gcc-compat -Wno-pointer-sign
DEMO_WARN_OFF_EM = $(DEMO_WARN_OFF) -Wno-int-conversion -Wno-deprecated-non-prototype
BIN_DIR = ../demo_bin
OPT_ZERO = -O0 -g
OPT_TWO = -DNDEBUG -O2 -g
OPT_LEVEL = $(OPT_ZERO)
CC = cc
CC_OLD_CODE = $(CC) -std=c90
EMCC = emcc --emrun
EMCC_OLD_CODE = $(EMCC) -std=c90
