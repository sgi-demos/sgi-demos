include ../build/platform.mk

LIB=$(BIN_DIR)/$(LIBNAME).a
EMLIBNAME=$(WEB_DIR)/$(LIBNAME)
EMLIB=$(EMLIBNAME).a
SRC = $(wildcard *.c)
HDRS = $(wildcard *.h)
PATCH_SRC = $(patsubst %.c,$(PATCH_DIR)/%.c,$(SRC)) 
PATCH_HDRS = $(patsubst %.h,$(PATCH_DIR)/%.h,$(HDRS))
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EMOBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

all: $(LIB) $(EMLIB)

$(PATCH_DIR): $(SRC) $(HDRS)
	mkdir -p $@
	cp $(SRC) $(HDRS) $@

$(PATCH_SRC): $(PATCH_DIR)

$(BIN_DIR): $(PATCH_SRC)
	mkdir -p $@
	echo *.o > $@/.gitignore
	echo *.a > $@/.gitignore

$(WEB_DIR): $(PATCH_SRC)
	mkdir -p $@
	echo *.o > $@/.gitignore
	echo *.a > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: $(PATCH_DIR)/%.c | $(BIN_DIR)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $(LIBDEFS) $< -c -o $@

$(LIB): $(OBJS)
	$(AR) $@ $(OBJS)
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: $(PATCH_DIR)/%.c | $(WEB_DIR) 
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@

$(EMLIB): $(EMOBJS)
	$(EMAR) $@ $(EMOBJS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: clean

clean:
	rm -f $(LIB) $(OBJS)
	rm -f $(EMLIB) $(EMOBJS)
	rm -rf $(PATCH_DIR)
