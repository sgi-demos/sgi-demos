.PHONY: clean run

include ../platform.mk

APP=$(BIN_DIR)/ideas
SRC= a.c b.c d.c draw_holder.c draw_lamp.c draw_logo.c draw_logo_line.c draw_logo_shadow.c e.c f.c h.c i.c m.c n.c o.c p.c r.c s.c t.c track.c w.c

$(APP): $(SRC) $(LIBGL_SRC)
	$(CC) $(OPT_LEVEL) $(DEMO_INC) \
		$(DEMO_WARN_OFF) \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	$(APP)

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM
