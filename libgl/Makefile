.PHONY: clean run

include ../platform.mk

APP=$(BIN_DIR)/sdl_framebuffer
EMAPP=$(APP).html
SRC=sdl_framebuffer.c sdl_events.c

all: $(APP) $(EMAPP)

$(APP): $(SRC) 
	$(CC) $(OPT_LEVEL) $(SRC) -F/Library/Frameworks -framework SDL2 -o $(APP)

$(EMAPP): $(SRC)
	$(EMCC) $(SRC) -s USE_SDL=2 -o $(EMAPP)

run: $(APP) $(EMAPP)
	$(APP) && emrun $(EMAPP)

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM
	rm -f $(EMAPP)
	rm -f $(APP).js
	rm -f $(APP).wasm
