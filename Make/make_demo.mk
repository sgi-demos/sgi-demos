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

$(WEB_DIR):
	mkdir -p $@

$(OBJS): $(BIN_DIR)/%.o: %.c $(HDRS) | $(BIN_DIR)
	$(OLD_CODE_CC) $(OPT_LEVEL) $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(DEMO_INC) $(APPDEFS) $< -c -o $@

$(APP): $(OBJS) $(LIBGL_SRC)
	$(CC) $(OPT_LEVEL) $(LIBGL_INC) $(OBJS) -D EM_CHILD_MAIN $(LIBGL_SRC) $(APPLIBS) -F/Library/Frameworks -framework SDL2 -o $@
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: %.c $(HDRS) | $(WEB_DIR)
	$(OLD_CODE_EMCC) $(OPT_LEVEL) $(OLD_CODE_WARN_OFF_EM) $(LIBGL_INC) $(DEMO_INC) $(APPDEFS) $< -c -o $@

$(EMAPP): $(EMOBJS) $(LIBGL_SRC)
	$(EMCC) $(OPT_LEVEL) -Wno-deprecated-non-prototype $(LIBGL_INC) $(EMOBJS) -D EM_CHILD_MAIN $(LIBGL_SRC) $(APPLIBS) -s USE_SDL=2 -s WASM=1 -o $@
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
