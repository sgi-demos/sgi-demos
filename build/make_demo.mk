include ../build/platform.mk

APP=$(BIN_DIR)/$(APPNAME)
EMAPPNAME=$(WEB_DIR)/$(APPNAME)
EMAPP=$(EMAPPNAME).html
HDRS = $(wildcard *.h)
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EMOBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

all: $(APP) $(EMAPP)

$(GL_LIB) $(EM_GL_LIB):
	make -C ../libgl
$(DEMO_LIB) $(EM_DEMO_LIB):
	make -C ../libdemo

$(BIN_DIR):
	mkdir -p $@
	echo "*.[oach]" > $@/.gitignore
	echo *.dSYM >> $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo "*.[oach]" > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR) $(SRC) $(HDRS)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(SHIM_INC) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@
$(APP): $(GL_LIB) $(DEMO_LIB) $(OBJS)
	$(CC) $(OPT) $(SHIM_INC) $(LIBGL_INC) $(OBJS) -D EM_CHILD_APP $(DEMO_LIB) $(GL_LIB) $(SDL_INC) $(SDL_LIBS) -lm -o $@
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: $(SRC_DIR)/%.c | $(WEB_DIR) $(EM_SRC) $(EM_HDRS)
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@
$(EMAPP): $(EM_GL_LIB) $(EM_DEMO_LIB) $(EMOBJS) 
	$(EMCC) $(EM_OPT) $(LIBGL_INC) $(EMOBJS) -D EM_CHILD_APP $(EM_DEMO_LIB) $(EM_GL_LIB) $(EM_SDL_LIBS) $(EMPRELOAD) -lm -o $@
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
	rm -f $(EMAPP) $(EMOBJS) $(EMAPPNAME).js $(EMAPPNAME).wasm $(EMAPPNAME).data
