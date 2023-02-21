RASTERIZER_SRCS = ../libgl/reference_rasterizer.c ../libgl/sdl_framebuffer.c
EVENTS_SRCS = ../libgl/sdl_gl_events.c
LIBGL_SRC = ../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)
LIBGL_INC = -I../sys_include
DEMO_INC = -I../demo_include
BIN_DIR = ./bin
WEB_DIR = ./web
OPT_ZERO = -O0 -g
OPT_TWO = -DNDEBUG -O2 -g
OPT_LEVEL = $(OPT_ZERO)
CC = cc
EMCC = emcc
OLD_CODE_CC = $(CC) -std=c90
OLD_CODE_EMCC = $(EMCC) -std=c90
OLD_CODE_WARN_OFF = -Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value -Wno-return-type -Wno-parentheses -Wno-gcc-compat -Wno-pointer-sign -Wno-int-conversion
OLD_CODE_WARN_OFF_EM = $(OLD_CODE_WARN_OFF) -Wno-deprecated-non-prototype