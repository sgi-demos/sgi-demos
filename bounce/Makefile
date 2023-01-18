.PHONY: clean run

include ../platform.mk

APP=bounce
SRC=bounce.c 
LIBGL_SRC=../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)

$(APP): $(SRC) $(LIBGL_SRC)
	cc -DNDEBUG -O2 -DNDEBUG -g -I../sys_include -I../demo_include \
		-Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value \
		-Wno-return-type \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	./$(APP) ./logo.bin

clean:
	rm -f $(APP)
