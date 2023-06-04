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

$(GL_LIB) $(EM_GL_LIB):
	make -C ../libgl

$(DEMO_LIB) $(EM_DEMO_LIB):
	make -C ../libdemo

$(PATCH_DIR):
	mkdir -p $@
	echo *.[ch] > $@/.gitignore

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
	echo *.dSYM >> $@/.gitignore

$(WEB_DIR):
	mkdir -p $@
	echo *.o > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: $(PATCH_DIR)/%.c | $(BIN_DIR) $(PATCH_SRC) $(PATCH_HDRS)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $(APPDEFS) $< -c -o $@

$(APP): $(GL_LIB) $(DEMO_LIB) $(OBJS)
	$(CC) $(OPT) $(LIBGL_INC) $(OBJS) -D EM_CHILD_APP $(DEMO_LIB) $(GL_LIB) $(SDL_LIB) -lm -o $@
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: $(PATCH_DIR)/%.c | $(WEB_DIR) $(PATCH_SRC) $(PATCH_HDRS)
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $(APPDEFS) $< -c -o $@

$(EMAPP): $(EM_GL_LIB) $(EM_DEMO_LIB) $(EMOBJS) 
	$(EMCC) $(EM_OPT) $(LIBGL_INC) $(EMOBJS) -D EM_CHILD_APP $(EM_DEMO_LIB) $(EM_GL_LIB) $(EM_SDL_LIB) $(EMLNKR) -lm -o $@
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
	rm -f $(PATCH_DIR)/*