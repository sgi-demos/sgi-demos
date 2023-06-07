include ../build/platform.mk

APP=$(BIN_DIR)/$(APPNAME)
EMAPPNAME=$(WEB_DIR)/$(APPNAME)
EMAPP=$(EMAPPNAME).html
PATCH_MAIN_TO_CHILD=../build/transform/main_to_child/main_to_child.cocci
HDRS = $(wildcard *.h)
SRC = $(wildcard *.c)
PATCH_HDRS = $(patsubst %.h,$(BIN_DIR)/%.h,$(HDRS))
PATCH_SRC = $(patsubst %.c,$(BIN_DIR)/%.c,$(SRC))
EMPATCH_HDRS = $(patsubst %.h,$(WEB_DIR)/%.h,$(HDRS))
EMPATCH_SRC = $(patsubst %.c,$(WEB_DIR)/%.c,$(SRC))
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

$(PATCH_HDRS): $(BIN_DIR)/%.h: ./%.h | $(BIN_DIR)
	cp -p $< $@

$(PATCH_SRC): $(BIN_DIR)/%.c: ./%.c | $(BIN_DIR) $(PATCH_HDRS)
	# make source file copy for patching
	cp -p $< $@
	# convert k&r to ansi (-a) (but don't promote types (-p)) as prereq for spatch
	cproto -a -p -I ../gl -I .. $@
	# run preprocessor (-E) to expand all macros as prereq for spatch
	#$(OLD_CODE_CC) -E $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $@ -o $@
	# patch:
	#spatch --sp-file $(PATCH_MAIN_TO_CHILD) $@ -o $@

$(EMPATCH_HDRS): $(WEB_DIR)/%.h: ./%.h | $(WEB_DIR)
	cp -p $< $@

$(EMPATCH_SRC): $(WEB_DIR)/%.c: ./%.c | $(WEB_DIR) $(EMPATCH_HDRS)
	# make source file copy for patching
	cp -p $< $@
	# convert k&r to ansi (-a) (but don't promote types (-p)) as prereq for spatch
	cproto -a -p -I ../gl -I .. $@
	# run preprocessor (-E) to expand all macros as prereq for spatch
	#$(OLD_CODE_EMCC) -E $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $@ -o $@
	# patch:
	#spatch --sp-file $(PATCH_MAIN_TO_CHILD) $@ -o $@

$(OBJS): $(BIN_DIR)/%.o: $(BIN_DIR)/%.c | $(BIN_DIR) $(PATCH_SRC) $(PATCH_HDRS)
	$(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@
$(APP): $(GL_LIB) $(DEMO_LIB) $(OBJS)
	$(CC) $(OPT) $(LIBGL_INC) $(OBJS) -D EM_CHILD_APP $(DEMO_LIB) $(GL_LIB) $(SDL_LIB) -lm -o $@
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: $(WEB_DIR)/%.c | $(WEB_DIR) $(EMPATCH_SRC) $(EMPATCH_HDRS)
	$(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@
$(EMAPP): $(EM_GL_LIB) $(EM_DEMO_LIB) $(EMOBJS) 
	$(EMCC) $(EM_OPT) $(LIBGL_INC) $(EMOBJS) -D EM_CHILD_APP $(EM_DEMO_LIB) $(EM_GL_LIB) $(EM_SDL_LIB) $(EMPRELOAD) -lm -o $@
	$(APPCMDS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: run clean

run: $(APP) $(EMAPP)
	$(APP) $(APPARGS) && emrun $(EMAPP)

clean:
	rm -f $(APP) $(OBJS) $(PATCH_SRC) $(PATCH_HDRS)
	rm -rf $(APP).dSYM
	rm -f $(EMAPP) $(EMOBJS) $(EMPATCH_SRC) $(EMPATCH_HDRS) $(EMAPPNAME).js $(EMAPPNAME).wasm $(EMAPPNAME).data
