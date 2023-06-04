.PHONY: all clean
DEMOS = libgl libdemo arena bounce buttonfly cedit flight ideas insect jello logo newave twilight

all: $(DEMOS)
	for file in $^ ; do make -C $${file} ; done

clean: $(DEMOS)
	for file in $^ ; do make clean -C $${file} ; done
