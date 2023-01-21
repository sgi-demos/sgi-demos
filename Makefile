include ./platform.mk

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
	cd ./demo_bin && rm -rf ./* && cd ..