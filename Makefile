.PHONY: all clean

all:
	make -C insect
	make -C jello
	make -C ideas

clean:
	make clean -C insect
	make clean -C jello
	make clean -C ideas
