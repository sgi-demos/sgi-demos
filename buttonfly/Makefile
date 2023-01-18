.PHONY: clean run

include ../platform.mk

APP=buttonfly
SRC=buttonfly.c event.c lexer.c parser.tab.c
HEADERS=bartfont.h buttonfly.h data.h event.h parser.tab.h
LIBGL_SRC=../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)

$(APP): $(SRC) $(HEADERS) $(LIBGL_SRC)
	cc -DNDEBUG -O2 -g -I../sys_include -I../demo_include \
		-Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value \
		-Wno-return-type \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

parser.tab.c parser.tab.h: parser.y
	bison --defines parser.y

run: $(APP)
	./$(APP) menu_demos

clean:
	rm -f $(APP) parser.tab.c parser.tab.h

