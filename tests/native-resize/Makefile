APPNAME=resizetest
include ../../makefiles/make_demo.mk
include ../../makefiles/platform.mk

APP = $(BIN_DIR)/$(APPNAME)
HDRS = $(wildcard $(INCS_DIR)/gl/*.h)
SRC = resizetest.c
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))

native: $(APP)

$(GL_LIB):
	make native -C $(LIBS_DIR)/libgl

$(BIN_DIR):
	mkdir -p $@
	echo "*" > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) | $(BIN_DIR)
	$(MODERN_CODE_CC) $(OPT) $(SHIM_INC) $(LIBGL_INC) $(SDL_INC) $< -c -o $@

$(APP): $(GL_LIB) $(OBJS)
	$(MODERN_CODE_CC) $(OPT) $(SHIM_INC) $(LIBGL_INC) $(OBJS) $(GL_LIB) \
		$(SDL_INC) $(SDL_LIBS) $(GLES_INC) $(GLES_LIBS) $(GLES_LINK) -lm $(CONSOLE_FLAGS) -o $@
	$(call GLES_INSTALL)
	ln -sF $(BIN_DIR) ./bin
