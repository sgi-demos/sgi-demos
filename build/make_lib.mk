include ../build/platform.mk

LIB=$(BIN_DIR)/$(LIBNAME).a
EMLIBNAME=$(WEB_DIR)/$(LIBNAME)
EMLIB=$(EMLIBNAME).a
SRC = $(wildcard *.c)
HDRS = $(wildcard *.h)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EMOBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

all: $(LIB) $(EMLIB)

ifeq ($(IS_OLD_CODE),yes)
PATCH_SRC = $(patsubst %.c,$(PATCH_DIR)/%.c,$(SRC))
PATCH_HDRS = $(patsubst %.h,$(PATCH_DIR)/%.h,$(HDRS))
SRC_DIR = $(PATCH_DIR)
LIB_CC = $(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF)
LIB_EMCC = $(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) -Wno-unused-command-line-argument
else
PATCH_SRC =
PATCH_HDRS =
SRC_DIR = .
LIB_CC = $(CC) $(OPT)
LIB_EMCC = $(EMCC) $(EM_OPT) -Wno-unused-command-line-argument
endif

$(PATCH_DIR):
	mkdir -p $@

$(PATCH_HDRS): $(PATCH_DIR)/%.h: ./%.h | $(PATCH_DIR)
	cp -p $< $@
	#cproto
	#cocci

$(PATCH_SRC): $(PATCH_DIR)/%.c: ./%.c | $(PATCH_DIR)
	cp -p $< $@
	#cproto
	#cocci

$(BIN_DIR):
	mkdir -p $@
	echo *.[oa] > $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo *.[oa] > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR) $(PATCH_SRC) $(PATCH_HDRS)
	$(LIB_CC) $(LIBGL_INC) $(LIBDEMO_INC) -D EM_CHILD_APP -F/Library/Frameworks $< -c -o $@

$(LIB): $(OBJS)
	$(AR) $@ $(OBJS)
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: ./%.c | $(WEB_DIR) $(PATCH_SRC) $(PATCH_HDRS)
	$(LIB_EMCC) $(LIBGL_INC) $(LIBDEMO_INC) -D EM_CHILD_APP $(EM_SDL_LIB) $< -c -o $@

$(EMLIB): $(EMOBJS)
	$(EMAR) $@ $(EMOBJS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: clean

clean:
	rm -f $(LIB) $(OBJS)
	rm -f $(EMLIB) $(EMOBJS)
