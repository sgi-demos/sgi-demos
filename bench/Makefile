.PHONY: clean run copy_cmd_to_mmc

include ../platform.mk

APP=$(BIN_DIR)/bench
SRC=bench.c 

$(APP): $(SRC) $(LIBGL_SRC)
	$(CC) $(OPT_LEVEL) $(DEMO_INC) \
		$(DEMO_WARN_OFF) \
		-o $(APP) $(SRC) $(LIBGL_SRC) -lm

run: $(APP)
	$(APP)

clean:
	rm -f $(APP)
	rm -rf $(APP).dSYM

# Make cmd.txt by defining STOP_AFTER_ANIMATION in bench.c and
# DUMP_ALL_COMMANDS in hardware_rasterizer.c, then piping
# the output of bench to cmd.txt. Copy the resulting cmd.bin
# file to the SD card's FAT partition using the copy_cmd_to_mmc target.
cmd.bin: cmd.txt ../tools/convert_command_dump.py
	python ../tools/convert_command_dump.py < cmd.txt > cmd.bin

copy_cmd_to_mmc: cmd.bin
	mkdir -p mmc
	sudo mount /dev/mmcblk0p1 mmc
	sudo cp cmd.bin mmc/bench.bin
	ls -l mmc/bench.bin
	sudo umount mmc
	rmdir mmc
