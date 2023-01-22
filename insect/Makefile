.PHONY: clean run

include ../platform.mk

APP=insect
EMAPP=$(APP).html
SRC=insect.c mat.c parts.c

$(EMAPP): $(SRC) insect.h $(LIBGL_SRC) $(EM_SRC)
	$(EMCC) \
	$(DEMO_WARN_OFF_EM) \
	$(DEMO_INC) $(SRC) $(LIBGL_SRC) $(EM_SRC) \
	-s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s FULL_ES2=1 \
	-o $(EMAPP)

run: $(EMAPP)
	emrun $(EMAPP)

clean:
	rm -f $(EMAPP)
	rm -f $(APP).js
	rm -f $(APP).wasm
