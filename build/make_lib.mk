include ../../build/platform.mk

LIB = $(BIN_DIR)/$(LIBNAME).a
EM_LIBNAME = $(WEB_DIR)/$(LIBNAME)
EM_LIB = $(EM_LIBNAME).a
HDRS = $(wildcard *.h)
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EM_OBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

ifeq ($(IS_OLD_CODE),yes)
LIB_CC = $(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF)
LIB_EMCC = $(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF)
else
LIB_CC = $(CC) $(OPT)
LIB_EMCC = $(EMCC) $(EM_OPT) -Wno-unused-command-line-argument
endif

all: $(LIB) $(EM_LIB)

$(BIN_DIR):
	mkdir -p $@
	echo "*.[oach]" > $@/.gitignore
	echo *.dSYM >> $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo "*.[oach]" > $@/.gitignore
	
$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(LIB_CC) $(LIBGL_INC) $(LIBDEMO_INC) -D EM_CHILD_APP $(SDL_INC) $(GLES_INC) $< -c -o $@
$(LIB): $(OBJS)
	$(AR) $@ $(OBJS)
	@echo
	@echo BUILT: $@
	@echo

$(EM_OBJS): $(WEB_DIR)/%.o: $(SRC_DIR)/%.c | $(WEB_DIR)
	$(LIB_EMCC) $(LIBGL_INC) $(LIBDEMO_INC) -D EM_CHILD_APP $(EM_SDL_LIBS) $< -c -o $@
$(EM_LIB): $(EM_OBJS)
	$(EMAR) $@ $(EM_OBJS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: clean

clean:
	rm -f $(LIB) $(OBJS)
	rm -f $(EM_LIB) $(EM_OBJS)
