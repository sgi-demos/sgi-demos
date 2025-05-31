UNAME:=$(shell uname -s)
ifeq ($(UNAME),Darwin)
    SDL_INC=-F/Library/Frameworks
    SDL_LIBS=-framework SDL2
else ifeq ($(UNAME),Linux)
    SDL_INC=`sdl2-config --cflags`
    SDL_LIBS=`sdl2-config --libs`
else ifneq ($(findstring MINGW64_NT,$(UNAME)),)
    SDL_INC=`sdl2-config --cflags`
    SDL_LIBS=`sdl2-config --libs`
	SHIM_INC=-I../gl/shim
endif

EM_SDL_LIBS =-s USE_SDL=2

GL_LIB = ../libgl/bin/libgl.a
EM_GL_LIB = ../libgl/web/libgl.a
LIBGL_INC = -I../ -I../gl

DEMO_LIB = ../libdemo/bin/libdemo.a
EM_DEMO_LIB = ../libdemo/web/libdemo.a
LIBDEMO_INC = -I../demo_include

SRC_DIR = .
BIN_DIR = ./bin
WEB_DIR = ./web
OPT_ZERO = -O0 -g
OPT_TWO = -DNDEBUG -O2
OPT = $(OPT_ZERO)
EM_OPT = $(OPT_TWO)
EXTRA_DEBUG = -fsanitize=undefined
EM_EXTRA_DEBUG = $(EXTRA_DEBUG) -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2

AR = ar rvsc
EMAR = emar rvsc
CC = cc $(EXTRA_DEBUG)
EMCC = emcc -s WASM=1 -s PRECISE_F32=1
OLD_CODE_CC = $(CC) -std=c90
OLD_CODE_EMCC = $(EMCC) -std=c90
OLD_CODE_WARN_OFF = -Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value -Wno-return-type -Wno-parentheses -Wno-gcc-compat -Wno-pointer-sign -Wno-int-conversion -Wno-out-of-scope-function -Wno-format-extra-args -Wno-unused-command-line-argument -Wno-comment -Wno-deprecated-non-prototype $(OLD_CODE_WARN_OFF_EXTRA)
EM_OLD_CODE_WARN_OFF = $(OLD_CODE_WARN_OFF)