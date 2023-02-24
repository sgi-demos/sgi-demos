.PHONY: all clean

all:
	make -C insect
	make -C jello
	make -C ideas
	make -C buttonfly

clean:
	make clean -C insect
	make clean -C jello
	make clean -C ideas
	make clean -C buttonfly
