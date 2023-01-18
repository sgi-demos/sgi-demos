.PHONY: clean run

include ../platform.mk

APP=ideas
SRC= a.c b.c d.c draw_holder.c draw_lamp.c draw_logo.c draw_logo_line.c draw_logo_shadow.c e.c f.c h.c i.c m.c n.c o.c p.c r.c s.c t.c track.c w.c
LIBGL_SRC=../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)

$(APP): $(SRC) $(LIBGL_SRC)
	cc -DNDEBUG -O2 -g -I../sys_include -I../demo_include \
		-Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value \
		-Wno-return-type \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	./$(APP)

clean:
	rm -f $(APP)
