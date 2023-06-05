include ../build/platform.mk

LIB=$(BIN_DIR)/$(LIBNAME).a
EMLIBNAME=$(WEB_DIR)/$(LIBNAME)
EMLIB=$(EMLIBNAME).a
SRC = $(wildcard *.c)
HDRS = $(wildcard *.h)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EMOBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

ifeq ($(IS_OLD_CODE),yes)
PATCH_SRC = $(patsubst %.c,$(BIN_DIR)/%.c,$(SRC))
PATCH_HDRS = $(patsubst %.h,$(BIN_DIR)/%.h,$(HDRS))
EMPATCH_SRC = $(patsubst %.c,$(WEB_DIR)/%.c,$(SRC))
EMPATCH_HDRS = $(patsubst %.h,$(WEB_DIR)/%.h,$(HDRS))
SRC_DIR = $(BIN_DIR)
EMSRC_DIR = $(WEB_DIR)
LIB_CC = $(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF)
LIB_EMCC = $(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) -Wno-unused-command-line-argument
else
PATCH_SRC =
PATCH_HDRS =
EMPATCH_SRC =
EMPATCH_HDRS =
SRC_DIR = .
EMSRC_DIR = .
LIB_CC = $(CC) $(OPT)
LIB_EMCC = $(EMCC) $(EM_OPT) -Wno-unused-command-line-argument
endif

all: $(LIB) $(EMLIB)

$(BIN_DIR):
	mkdir -p $@
	echo *.[oa] > $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo *.[oa] > $@/.gitignore

$(PATCH_SRC): $(BIN_DIR)/%.c: ./%.c | $(BIN_DIR)
	cp -p $< $@
$(PATCH_HDRS): $(BIN_DIR)/%.h: ./%.h | $(BIN_DIR)
	cp -p $< $@

$(EMPATCH_SRC): $(WEB_DIR)/%.c: ./%.c | $(WEB_DIR)
	cp -p $< $@
$(EMPATCH_HDRS): $(WEB_DIR)/%.h: ./%.h | $(WEB_DIR)
	cp -p $< $@
	
$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR) $(PATCH_SRC) $(PATCH_HDRS)
	$(LIB_CC) $(LIBGL_INC) $(LIBDEMO_INC) -D EM_CHILD_APP -F/Library/Frameworks $< -c -o $@
$(LIB): $(OBJS)
	$(AR) $@ $(OBJS)
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: $(EMSRC_DIR)/%.c | $(WEB_DIR) $(EMPATCH_SRC) $(EMPATCH_HDRS)
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
