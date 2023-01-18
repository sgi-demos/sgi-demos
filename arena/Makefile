.PHONY: clean run

include ../platform.mk

APP=arena
SRC=arena.c colision.c colors.c comm.c damage.c def.c explode.c hud.c main.c maze.c move.c objects.c shot.c startup.c udpbrdcst.c utils.c
LIBGL_SRC=../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)
$(APP): $(SRC) arena.h udpbrdcst.h $(LIBGL_SRC)
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


