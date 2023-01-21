.PHONY: clean run

include ../platform.mk

APP=$(BIN_DIR)/buttonfly
SRC=buttonfly.c event.c lexer.c parser.tab.c
HEADERS=bartfont.h buttonfly.h data.h event.h parser.tab.h

$(APP): $(SRC) $(HEADERS) $(LIBGL_SRC)
	$(CC) $(OPT_LEVEL) $(DEMO_INC) \
		$(DEMO_WARN_OFF) \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

parser.tab.c parser.tab.h: parser.y
	bison --defines parser.y

run: $(APP)
	$(APP) menu_demos

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM	
	rm -f parser.tab.c parser.tab.h

