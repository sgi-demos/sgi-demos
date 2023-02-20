.PHONY: clean run

include ../platform.mk

APP=insect
EMAPP=./web/$(APP).html
APPSRC=insect.c mat.c parts.c
APPOBJ=insect.o mat.o parts.o

all: $(APPOBJ) $(EMAPP)

$(APPOBJ): $(APPSRC) insect.h
	$(EMCC) -std=c90 -c $(DEMO_INC) $(APPSRC) \
	$(DEMO_WARN_OFF_EM)

$(EMAPP): $(APPOBJ) $(LIBGL_SRC) $(EM_SRC) 
	$(EMCC) --emrun $(DEMO_INC) $(APPOBJ) $(LIBGL_SRC) $(EM_SRC) \
	-Wno-deprecated-non-prototype \
	-s WASM=1 -s USE_SDL=2 -s FULL_ES2=1 \
	-o $(EMAPP)

run: $(EMAPP)
	emrun $(EMAPP)

clean:
	rm -f ./*.o
	rm -f ./web/$(APP).html
	rm -f ./web/$(APP)*.js
	rm -f ./web/$(APP).wasm
