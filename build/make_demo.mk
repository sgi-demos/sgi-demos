include ../build/platform.mk

APP=$(BIN_DIR)/$(APPNAME)
EMAPPNAME=$(WEB_DIR)/$(APPNAME)
EMAPP=$(EMAPPNAME).html
SRC = $(wildcard *.c)
HDRS = $(wildcard *.h)
PATCH_SRC = $(patsubst %.c,$(PATCH_DIR)/%.c,$(SRC)) 
PATCH_HDRS = $(patsubst %.h,$(PATCH_DIR)/%.h,$(HDRS))
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EMOBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

all: $(APP) $(EMAPP)

$(DEMO_LIB):
	make -C ../libdemo

$(PATCH_DIR): $(SRC) $(HDRS)
	mkdir -p $@
	cp $(SRC) $(HDRS) $@

$(PATCH_SRC): $(PATCH_DIR)

$(BIN_DIR): $(PATCH_SRC)
	mkdir -p $@
	echo *.o > $@/.gitignore
	echo *.dSYM >> $@/.gitignore

$(WEB_DIR): $(PATCH_SRC)
	mkdir -p $@
	echo *.o > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: $(PATCH_DIR)/%.c | $(BIN_DIR)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $(APPDEFS) $< -c -o $@

$(APP): $(OBJS) $(LIBGL_SRC) $(DEMO_LIB)
	$(CC) $(OPT) $(LIBGL_INC) $(OBJS) $(APPDEFS) -D EM_CHILD_APP $(LIBGL_SRC) $(DEMO_LIB) $(SDL_LIB) -lm -o $@
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: $(PATCH_DIR)/%.c | $(WEB_DIR) 
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $(APPDEFS) $< -c -o $@

$(EMAPP): $(EMOBJS) $(LIBGL_SRC) $(DEMO_LIB)
	$(EMCC) $(EM_OPT) $(LIBGL_INC) $(APPDEFS) $(EMOBJS) -D EM_CHILD_APP $(LIBGL_SRC) $(EM_DEMO_LIB) $(EM_SDL_LIB) $(EMLNKR) -lm -o $@
	$(APPCMDS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: run clean

run: $(APP) $(EMAPP)
	$(APP) $(APPARGS) && emrun $(EMAPP)

clean:
	rm -f $(APP) $(OBJS)
	rm -rf $(APP).dSYM
	rm -f $(EMAPP) $(EMOBJS) $(EMAPPNAME).js $(EMAPPNAME).wasm
	rm -rf $(PATCH_DIR)
