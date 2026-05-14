# Platform specifics
OS:=$(shell uname -s)
HW:=$(shell uname -m)
ifeq ($(OS),Darwin)
	OS = mac
	DYL_EXT = dylib
else ifeq ($(OS),Linux)
	OS = linux
	DYL_EXT = so
else ifneq ($(findstring MINGW64_NT,$(OS)),)
	OS = win
	DYL_EXT = dll
endif

# Source and executable dirs
SRC_DIR = .
BIN_DIR = ./bin-$(OS)-$(HW)
WEB_DIR = ./web
LIBS_DIR = ../../libs
INCS_DIR = ../../include

# SDL libs and include
SDL_LIBS = `sdl2-config --libs`
EM_SDL_LIBS = -s USE_SDL=2 -s FULL_ES2=1
SDL_INC = `sdl2-config --cflags`

# GLES libs and include
GLES_LIBS_PATH = $(LIBS_DIR)/libgles/lib-$(OS)
GLES_INC = -I$(LIBS_DIR)/libgles/include
GLES_LIBS = -L$(GLES_LIBS_PATH) -l GLESv2 -l EGL
GLES_DYLIBS = libGLESv2.$(DYL_EXT) libEGL.$(DYL_EXT)
ifeq ($(OS),mac)
	GLES_LINK = -Wl,-rpath,$(GLES_LIBS_PATH)
define GLES_INSTALL
	for dylib in $(GLES_DYLIBS); \
		do install_name_tool -change ./$$dylib @rpath/$$dylib $@; \
	done;
endef
else ifeq ($(OS),linux)
	GLES_LINK = -Wl,-rpath,$(GLES_LIBS_PATH)
else ifeq ($(OS),win)
	SHIM_INC = -I$(INCS_DIR)/gl/shim
define GLES_INSTALL
	for dylib in $(GLES_DYLIBS); \
		do cp $(GLES_LIBS_PATH)/$$dylib $(BIN_DIR)/$$dylib; \
	done;
endef	
endif

# Internal libs and includes
GL_LIB = $(LIBS_DIR)/libgl/$(BIN_DIR)/libgl.a
EM_GL_LIB = $(LIBS_DIR)/libgl/$(WEB_DIR)/libgl.a
LIBGL_INC = -I$(INCS_DIR) -I$(INCS_DIR)/gl

DEMO_LIB = $(LIBS_DIR)/libdemo/$(BIN_DIR)/libdemo.a
EM_DEMO_LIB = $(LIBS_DIR)/libdemo/$(WEB_DIR)/libdemo.a
LIBDEMO_INC = -I$(INCS_DIR)/demo_include

# Optimizer options
OPT_ZERO = -O0 -g
OPT_TWO = -DNDEBUG -O2
OPT = $(OPT_ZERO)
EM_OPT = $(OPT_TWO)

# Debug options
EXTRA_DEBUG = -fsanitize=undefined
EM_EXTRA_DEBUG = $(EXTRA_DEBUG) -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2

# Compilers
CC = cc $(EXTRA_DEBUG)
EMCC = emcc -s WASM=1 -s PRECISE_F32=1

# Library archivers
AR = ar rvsc
EMAR = emar rvsc

# Compiler options for ancient SGI code
OLD_CODE_CC = $(CC) -std=c90
OLD_CODE_EMCC = $(EMCC) -std=c90
OLD_CODE_WARN_OFF = -Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value -Wno-return-type -Wno-parentheses -Wno-gcc-compat -Wno-pointer-sign -Wno-int-conversion -Wno-out-of-scope-function -Wno-format-extra-args -Wno-unused-command-line-argument -Wno-comment -Wno-deprecated-non-prototype $(OLD_CODE_WARN_OFF_EXTRA)
EM_OLD_CODE_WARN_OFF = $(OLD_CODE_WARN_OFF)