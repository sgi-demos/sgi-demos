.PHONY: clean run copy_cmd_to_mmc

include ../platform.mk

APP=logo
SRC=light.c logo.c 
LIBGL_SRC=../libgl/gl.c ../libgl/vector.c $(RASTERIZER_SRCS) $(EVENTS_SRCS)

$(APP): $(SRC) light.h $(LIBGL_SRC)
	cc -DNDEBUG -O2 -g -I../sys_include -I../demo_include \
		-Wno-implicit-function-declaration -Wno-implicit-int -Wno-unused-value \
		-Wno-return-type \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	./$(APP)

clean:
	rm -f $(APP)

# See the ../NOTES file.
cmd.bin: cmd.txt ../tools/convert_command_dump.py
	python ../tools/convert_command_dump.py < cmd.txt > cmd.bin

copy_cmd_to_mmc: cmd.bin
	mkdir -p mmc
	sudo mount /dev/mmcblk0p1 mmc
	sudo cp cmd.bin mmc/logo.bin
	ls -l mmc/logo.bin
	sudo umount mmc
	rmdir mmc
