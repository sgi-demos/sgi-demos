.PHONY: clean run

include ../Make/platform.mk

APPNAME=sdl_framebuffer
SRC=sdl_framebuffer.c sdl_gl_events.c

APP=$(BIN_DIR)/$(APPNAME)
EMAPPNAME=$(WEB_DIR)/$(APPNAME)
EMAPP=$(EMAPPNAME).html

all: $(APP) $(EMAPP)

$(APP): $(SRC) 
	$(CC) $(OPT) -D MAIN_LOOP_DEBUG $(LIBGL_INC) $(SRC) $(SDL_LIB) -o $(APP)

$(EMAPP): $(SRC)
	$(EMCC) $(EM_OPT) -D MAIN_LOOP_DEBUG $(LIBGL_INC) $(SRC) -s USE_SDL=2 -o $(EMAPP)

run: $(APP) $(EMAPP)
	$(APP) && emrun $(EMAPP)

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM
	rm -f $(EMAPP) $(EMAPPNAME).js $(EMAPPNAME).wasm
