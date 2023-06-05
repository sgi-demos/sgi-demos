.PHONY: clean run

include ../build/platform.mk

APPNAME=sdl_framebuffer
SRC=sdl_framebuffer.c sdl_gl_events.c

APP=$(BIN_DIR)/$(APPNAME)
EMAPP_NAME=$(WEB_DIR)/$(APPNAME)
EMAPP=$(EMAPP_NAME).html

all: $(APP) $(EMAPP)

$(APP): $(SRC) 
	$(CC) $(OPT) -D MAIN_LOOP_DEBUG $(LIBGL_INC) $(SRC) $(SDL_LIB) -o $(APP)
	@echo
	@echo BUILT: $@
	@echo
	
$(EMAPP): $(SRC)
	$(EMCC) $(EM_OPT) -D MAIN_LOOP_DEBUG $(LIBGL_INC) $(SRC) -s USE_SDL=2 -o $(EMAPP)
	@echo
	@echo BUILT: $@
	@echo

run: $(APP) $(EMAPP)
	$(APP) && emrun $(EMAPP)

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM
	rm -f $(EMAPP) $(EMAPP_NAME).js $(EMAPP_NAME).wasm
