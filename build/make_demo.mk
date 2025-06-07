include ../build/platform.mk

APP = $(BIN_DIR)/$(APPNAME)
EM_APPNAME = $(WEB_DIR)/$(APPNAME)
EM_APP = $(EM_APPNAME).html
HDRS = $(wildcard *.h)
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EM_OBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

all: $(APP) $(EM_APP)

$(GL_LIB) $(EM_GL_LIB):
	make -C ../libgl
$(DEMO_LIB) $(EM_DEMO_LIB):
	make -C ../libdemo

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
	$(CC) $(OPT) $(SHIM_INC) $(LIBGL_INC) $(OBJS) -D EM_CHILD_APP $(DEMO_LIB) $(GL_LIB) \
		$(SDL_INC) $(SDL_LIBS) $(GLES_INC) $(GLES_LIBS) $(GLES_LINK) -lm -o $@
	$(call GLES_INSTALL)
	ln -s $(BIN_DIR) ./bin
	@echo
	@echo BUILT: $@
	@echo

$(EM_OBJS): $(WEB_DIR)/%.o: $(SRC_DIR)/%.c | $(WEB_DIR) $(EM_SRC) $(EM_HDRS)
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@

$(EM_APP): $(EM_GL_LIB) $(EM_DEMO_LIB) $(EM_OBJS) 
	$(EMCC) $(EM_OPT) $(LIBGL_INC) $(EM_OBJS) -D EM_CHILD_APP $(EM_DEMO_LIB) $(EM_GL_LIB) \
		$(EM_SDL_LIBS) $(EM_PRELOAD) -lm -o $@
	$(APPCMDS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: run clean

run: $(APP) $(EM_APP)
	$(APP) $(APPARGS) && emrun $(EM_APP)

clean:
	rm -f $(APP) $(OBJS)
	rm -rf $(APP).dSYM
	rm -f $(EM_APP) $(EM_OBJS) $(EM_APPNAME).js $(EM_APPNAME).wasm $(EM_APPNAME).data
	rm -f ./bin