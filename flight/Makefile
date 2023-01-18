.PHONY: clean run

include ../platform.mk

APP=flight
SRC =		main.c uflight.c land1.c land2.c meters.c density.c \
		c150.c b747.c f15.c f16.c f18.c flight.c \
		p38.c f16w.c p38w.c mat.c \
		udpbrdcst.c xasin.c xatable.c savecolors.c
LIBGL_SRC=../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)
$(APP): $(SRC) udpbrdcst.h $(LIBGL_SRC)
	cc -DNDEBUG -O2 -g -I../sys_include -I../demo_include \
		-Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value \
		-Wno-return-type \
		-DNETWORKING=1 \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	@if [ -z "$(HOST)" ]; then echo 'Set HOST variable first or use run_no_network'; else ./$(APP) -n; fi

run_no_network: $(APP)
	./$(APP)

clean:
	rm -f $(APP)



