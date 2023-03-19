.PHONY: all clean

all:
	make -C libgl
	make -C insect
	make -C jello
	make -C ideas
	make -C buttonfly
	make -C bounce
	make -C logo
	make -C newave
	make -C flight

clean:
	make clean -C libgl
	make clean -C insect
	make clean -C jello
	make clean -C ideas
	make clean -C buttonfly
	make clean -C bounce
	make clean -C logo
	make clean -C newave
	make clean -C flight
