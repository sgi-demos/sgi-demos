.PHONY: clean run

include ../platform.mk

APPNAME=sdl_framebuffer
SRC=sdl_framebuffer.c sdl_events.c

APP=$(BIN_DIR)/$(APPNAME)
EMAPPNAME=$(WEB_DIR)/$(APPNAME)
EMAPP=$(EMAPPNAME).html

all: $(APP) $(EMAPP)

$(APP): $(SRC) 
	$(CC) $(OPT_LEVEL) $(LIBGL_INC) $(SRC) -F/Library/Frameworks -framework SDL2 -o $(APP)

$(EMAPP): $(SRC)
	$(EMCC) $(OPT_LEVEL) $(LIBGL_INC) $(SRC) -s USE_SDL=2 -o $(EMAPP)

run: $(APP) $(EMAPP)
	$(APP) && emrun $(EMAPP)

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM
	rm -f $(EMAPP) $(EMAPPNAME).js $(EMAPPNAME).wasm
