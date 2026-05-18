include ../../makefiles/platform.mk

APP = $(BIN_DIR)/$(APPNAME)
EM_APPNAME = $(WEB_DIR)/$(APPNAME)
EM_APP = $(EM_APPNAME).html
HDRS = $(wildcard *.h)
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EM_OBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

all: native em

native: $(APP)

em: $(EM_APP)

$(GL_LIB):
	make native -C $(LIBS_DIR)/libgl

$(EM_GL_LIB):
	make em -C $(LIBS_DIR)/libgl

$(DEMO_LIB):
	make native -C $(LIBS_DIR)/libdemo

$(EM_DEMO_LIB):
	make em -C $(LIBS_DIR)/libdemo

$(BIN_DIR):
	mkdir -p $@
	echo "*.[oach]" > $@/.gitignore
	echo *.dSYM >> $@/.gitignore
	echo *.$(DYL_EXT) >> $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo "*.[oach]" > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR) $(SRC) $(HDRS)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(SHIM_INC) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@

$(APP): $(GL_LIB) $(DEMO_LIB) $(OBJS)
	$(CC) $(OPT) $(SHIM_INC) $(LIBGL_INC) $(OBJS) $(DEMO_LIB) $(GL_LIB) \
		$(SDL_INC) $(SDL_LIBS) $(GLES_INC) $(GLES_LIBS) $(GLES_LINK) -lm $(CONSOLE_FLAGS) -o $@
	$(call GLES_INSTALL)
	ln -sF $(BIN_DIR) ./bin
	@echo
	@echo BUILT: $@
	@echo $(CUR_DIR)

$(EM_OBJS): $(WEB_DIR)/%.o: $(SRC_DIR)/%.c | $(WEB_DIR) $(EM_SRC) $(EM_HDRS)
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@

$(EM_APP): $(EM_GL_LIB) $(EM_DEMO_LIB) $(EM_OBJS)
	$(EMCC) $(EM_OPT) $(LIBGL_INC) $(EM_OBJS) $(EM_DEMO_LIB) $(EM_GL_LIB) \
		$(EM_SDL_LIBS) $(EM_ASYNCIFY) $(EM_PRELOAD) -lm -o $@
	$(APPCMDS)
	@echo
	@echo BUILT: $@
	@echo $(CUR_DIR)

.PHONY: all native em run run-native run-em clean

# Run both applications
run: all
	$(APP) $(APPARGS) && emrun $(EM_APP)

# Run only the native application
run-native: native
	$(APP) $(APPARGS)

# Run only the emscripten application
run-em: em
	emrun $(EM_APP)

clean:
	rm -f $(APP) $(OBJS)
	rm -rf $(APP).dSYM
	rm -f $(EM_APP) $(EM_OBJS) $(EM_APPNAME).js $(EM_APPNAME).wasm $(EM_APPNAME).data
	rm -rf ./bin
