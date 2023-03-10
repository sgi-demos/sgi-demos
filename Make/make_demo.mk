include ../Make/platform.mk

APP=$(BIN_DIR)/$(APPNAME)
EMAPPNAME=$(WEB_DIR)/$(APPNAME)
EMAPP=$(EMAPPNAME).html
SRC = $(wildcard *.c)
HDRS = $(wildcard *.h)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EMOBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

all: $(APP) $(EMAPP)

$(BIN_DIR):
	mkdir -p $@
	echo *.o > $@/.gitignore
	echo *.dSYM >> $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo *.o > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: %.c $(HDRS) | $(BIN_DIR)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(DEMO_INC) $(APPDEFS) $< -c -o $@

$(APP): $(OBJS) $(LIBGL_SRC)
	$(CC) $(OPT) $(LIBGL_INC) $(OBJS) $(APPDEFS) -D EM_CHILD_MAIN $(LIBGL_SRC) $(APPLIBS) $(SDL_LIB) -lm -o $@
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: %.c $(HDRS) | $(WEB_DIR)
	$(OLD_CODE_EMCC) $(EM_OPT) $(OLD_CODE_WARN_OFF_EM) $(LIBGL_INC) $(DEMO_INC) $(APPDEFS) $< -c -o $@

$(EMAPP): $(EMOBJS) $(LIBGL_SRC)
	$(EMCC) $(EM_OPT) $(LIBGL_INC) $(APPDEFS) $(EMOBJS) -D EM_CHILD_MAIN $(LIBGL_SRC) $(APPLIBS) $(EM_SDL_LIB) $(EMLNKR) -lm -o $@
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
