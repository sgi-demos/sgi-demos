.PHONY: clean run

include ../platform.mk

APP=cedit
EMAPP=./web/$(APP).html
SRC=cedit.c

$(EMAPP): $(SRC) $(LIBGL_SRC) $(EM_SRC)
	$(EMCC) \
	$(DEMO_WARN_OFF_EM) \
	$(DEMO_INC) $(SRC) $(LIBGL_SRC) $(EM_SRC) \
	-s WASM=1 -s USE_SDL=2 -s FULL_ES2=1 \
	-o $(EMAPP)

run: $(EMAPP)
	cd web && emrun $(EMAPP)

clean:
	rm -f ./web/$(APP).html
	rm -f ./web/$(APP).js
	rm -f ./web/$(APP).wasm
