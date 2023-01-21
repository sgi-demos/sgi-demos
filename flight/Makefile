.PHONY: clean run

include ../platform.mk

APP=$(BIN_DIR)/flight
SRC =	main.c uflight.c land1.c land2.c meters.c density.c \
		c150.c b747.c f15.c f16.c f18.c flight.c \
		p38.c f16w.c p38w.c mat.c \
		udpbrdcst.c xasin.c xatable.c savecolors.c

$(APP): $(SRC) udpbrdcst.h $(LIBGL_SRC)
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
