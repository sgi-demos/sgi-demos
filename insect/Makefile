.PHONY: clean run

include ../platform.mk

APP=$(BIN_DIR)/insect
SRC=insect.c mat.c parts.c
LIBGL_SRC=../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)

$(APP): $(SRC) insect.h $(LIBGL_SRC)
	cc $(OPT_LEVEL) -g -I../sys_include -I../demo_include \
		-Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value \
		-Wno-return-type \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	$(APP)

clean:
	rm -rf $(APP)*
