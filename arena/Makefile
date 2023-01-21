.PHONY: clean run

include ../platform.mk

APP=$(BIN_DIR)/arena
SRC=arena.c colision.c colors.c comm.c damage.c def.c explode.c hud.c main.c maze.c move.c objects.c shot.c startup.c udpbrdcst.c utils.c

$(APP): $(SRC) arena.h udpbrdcst.h $(LIBGL_SRC)
	$(CC) $(OPT_LEVEL) $(DEMO_INC) \
		$(DEMO_WARN_OFF) \
		-DNETWORKING=1 \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	@if [ -z "$(HOST)" ]; then echo 'Set HOST variable first or use run_no_network'; else $(APP) -n; fi

run_no_network: $(APP)
	$(APP)

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM


