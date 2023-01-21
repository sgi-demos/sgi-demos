.PHONY: clean run

include ../platform.mk

APP=insect
EMAPP=$(APP).html
SRC=insect.c mat.c parts.c

$(EMAPP): $(SRC) insect.h $(LIBGL_SRC)
	$(EMCC) \
		$(DEMO_WARN_OFF_EM) \
		$(DEMO_INC) $(SRC) $(LIBGL_SRC) \
		-s WASM=0 -o $(EMAPP)

run: $(EMAPP)
	emrun $(EMAPP)

clean:
	rm -f $(EMAPP)
	rm -f $(APP).js
	rm -f $(APP).wasm
