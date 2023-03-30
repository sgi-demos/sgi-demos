.PHONY: all clean

all:
	make -C libgl
	make -C arena
	make -C bounce
	make -C buttonfly
	make -C cedit
	make -C flight
	make -C ideas
	make -C insect
	make -C jello
	make -C logo
	make -C newave
	make -C twilight

clean:
	make clean -C libgl
	make clean -C arena
	make clean -C bounce
	make clean -C buttonfly
	make clean -C cedit
	make clean -C flight
	make clean -C ideas
	make clean -C insect
	make clean -C jello
	make clean -C logo
	make clean -C newave
	make clean -C twilight
