include ../build/platform.mk

LIB=$(BIN_DIR)/$(LIBNAME).a
EMLIBNAME=$(WEB_DIR)/$(LIBNAME)
EMLIB=$(EMLIBNAME).a
SRC = $(wildcard *.c)
HDRS = $(wildcard *.h)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EMOBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

ifeq ($(IS_OLD_CODE),yes)
LIB_CC = $(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF)
LIB_EMCC = $(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF)
else
LIB_CC = $(CC) $(OPT)
LIB_EMCC = $(EMCC) $(EM_OPT) -Wno-unused-command-line-argument
endif

all: $(LIB) $(EMLIB)

$(BIN_DIR):
	mkdir -p $@
	echo "*.[oach]" > $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo "*.[oach]" > $@/.gitignore

$(PATCH_SRC): $(BIN_DIR)/%.c: ./%.c | $(BIN_DIR)
	cp -p $< $@
$(PATCH_HDRS): $(BIN_DIR)/%.h: ./%.h | $(BIN_DIR)
	cp -p $< $@

$(EMPATCH_SRC): $(WEB_DIR)/%.c: ./%.c | $(WEB_DIR)
	cp -p $< $@
$(EMPATCH_HDRS): $(WEB_DIR)/%.h: ./%.h | $(WEB_DIR)
	cp -p $< $@
	
$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR) $(PATCH_SRC) $(PATCH_HDRS)
	$(LIB_CC) $(LIBGL_INC) $(LIBDEMO_INC) -D EM_CHILD_APP $(SDL_INC) $< -c -o $@
$(LIB): $(OBJS)
	$(AR) $@ $(OBJS)
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: $(SRC_DIR)/%.c | $(WEB_DIR) $(EMPATCH_SRC) $(EMPATCH_HDRS)
	$(LIB_EMCC) $(LIBGL_INC) $(LIBDEMO_INC) -D EM_CHILD_APP $(EM_SDL_LIB) $< -c -o $@
$(EMLIB): $(EMOBJS)
	$(EMAR) $@ $(EMOBJS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: clean

clean:
	rm -f $(LIB) $(OBJS) $(PATCH_SRC) $(PATCH_HDRS)
	rm -f $(EMLIB) $(EMOBJS) $(EMPATCH_SRC) $(EMPATCH_HDRS)
