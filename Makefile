.PHONY: all clean

all:
	make -C insect
	make -C arena
	make -C logo
	make -C bounce
	make -C jello
	make -C buttonfly
	make -C ideas
	make -C flight
	make -C colortest
	make -C gltest
	make -C bench
	make -C sunflower
	make -C newave

clean:
	make clean -C insect
	make clean -C arena
	make clean -C logo
	make clean -C bounce
	make clean -C jello
	make clean -C buttonfly
	make clean -C ideas
	make clean -C flight
	make clean -C colortest
	make clean -C gltest
	make clean -C bench
	make clean -C sunflower
	make clean -C newave
