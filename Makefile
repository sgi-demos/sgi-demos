.PHONY: demos libs clean

DEMOS_DIR = demos
DEMOS = arena bounce buttonfly cedit flight ideas insect jello logo newave twilight

LIBS_DIR = libs
LIBS = libgl libdemo

demos:
	for file in $(DEMOS) ; do echo -e "\nBUILDING: $${file}\n" && make -C $(DEMOS_DIR)/$${file} ; done

libs:
	for file in $(LIBS) ; do echo -e "\nBUILDING: $${file}\n" && make -C $(LIBS_DIR)/$${file}  ; done

clean:
	for file in $(LIBS) ; do echo -e "\nCLEANING: $${file}\n" && make clean -C $(LIBS_DIR)/$${file} ; done
	for file in $(DEMOS) ; do echo -e "\nCLEANING: $${file}\n" && make clean -C $(DEMOS_DIR)/$${file} ; done
