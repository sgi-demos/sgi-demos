.PHONY: clean run

include ../platform.mk

APP=sdl_framebuffer
EMAPP=$(APP).html
SRC=sdl_framebuffer.c sdl_events.c camera2D.c

$(EMAPP): $(SRC)
	emcc $(SRC) \
		-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s FULL_ES2=1 -DTEST_OGLES_FRAMEBUFFER=1 -o $(EMAPP)

run: $(EMAPP)
	emrun $(EMAPP)

clean:
	rm -f $(EMAPP)
	rm -f $(APP).js
	rm -f $(APP).wasm
