.PHONY: clean run

include ../platform.mk

APP=$(BIN_DIR)/logo
SRC=light.c logo.c 

$(APP): $(SRC) light.h $(LIBGL_SRC)
	$(CC) $(OPT_LEVEL) $(DEMO_INC) \
		$(DEMO_WARN_OFF) \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	$(APP)

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM
