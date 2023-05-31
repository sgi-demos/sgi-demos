include ../build/platform.mk

APP=$(BIN_DIR)/$(APPNAME)
EMAPP_NAME=$(WEB_DIR)/$(APPNAME)
EMAPP=$(EMAPP_NAME).html
APP_SRC = $(wildcard *.c)
APP_HDRS = $(wildcard *.h)
APP_OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(APP_SRC))
EMAPP_OBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(APP_SRC))

all: $(APP) $(EMAPP)

$(BIN_DIR):
	mkdir -p $@
	echo *.o > $@/.gitignore
	echo *.dSYM >> $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo *.o > $@/.gitignore

$(APP_OBJS): $(BIN_DIR)/%.o: %.c $(APP_HDRS) | $(BIN_DIR)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(DEMO_INC) $(APP_DEFS) $< -c -o $@

$(APP): $(APP_OBJS) $(LIBGL_SRC) $(LIBAPP_SRC)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(DEMO_INC) $(APP_DEFS) $(LIBAPP_SRC) -c
	mv *.o $(BIN_DIR)
	$(CC) $(OPT) $(LIBGL_INC) $(DEMO_INC) $(BIN_DIR)/*.o $(APP_DEFS) -D EM_CHILD_APP $(LIBGL_SRC) $(SDL_LIB) -lm -o $@
	@echo
	@echo BUILT: $@
	@echo

$(EMAPP_OBJS): $(WEB_DIR)/%.o: %.c $(APP_HDRS) | $(WEB_DIR)
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(DEMO_INC) $(APP_DEFS) $< -c -o $@

$(EMAPP): $(EMAPP_OBJS) $(LIBGL_SRC) $(LIBAPP_SRC)
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(DEMO_INC) $(APP_DEFS) $(LIBAPP_SRC) -c
	mv *.o $(WEB_DIR) 
	$(EMCC) $(EM_OPT) $(LIBGL_INC) $(DEMO_INC) $(APP_DEFS) $(WEB_DIR)/*.o -D EM_CHILD_APP $(LIBGL_SRC) $(EM_SDL_LIB) $(EMLNKR) -lm -o $@
	$(APPCMDS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: run clean

run: $(APP) $(EMAPP)
	$(APP) $(APPARGS) && emrun $(EMAPP)

clean:
	rm -f $(APP) $(APP_OBJS)
	rm -rf $(APP).dSYM
	rm -f $(EMAPP) $(EMAPP_OBJS) $(EMAPP_NAME).js $(EMAPP_NAME).wasm
