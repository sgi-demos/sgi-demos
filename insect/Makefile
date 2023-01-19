.PHONY: clean run

include ../platform.mk

APP=$(BIN_DIR)/insect
EMAPP=insect.html
SRC=insect.c mat.c parts.c

$(EMAPP): $(SRC) insect.h $(LIBGL_SRC)
	$(EMCC) -std=c90 \
		-Wno-implicit-function-declaration \
		-Wno-unused-value \
		-Wno-return-type \
		-Wno-int-conversion \
		-Wno-gcc-compat \
		-Wno-implicit-int \
		-Wno-deprecated-non-prototype \
		-I../sys_include -I../demo_include \
		$(SRC) $(LIBGL_SRC) -o $(EMAPP)

run: $(EMAPP)
	emrun $(EMAPP)

clean:
	rm -f $(EMAPP)
