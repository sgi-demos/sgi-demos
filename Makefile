.PHONY: demos libs clean

DEMOS_DIR = demos
DEMOS = arena bounce buttonfly cedit flight ideas insect jello logo newave twilight

LIBS_DIR = libs
LIBS = libgl libdemo

all:
	for demo in $(DEMOS) ; do echo "\nBUILDING: $${demo}\n" && make -C $(DEMOS_DIR)/$${demo} ; done

native:
	for demo in $(DEMOS) ; do echo "\nBUILDING: $${demo}\n" && make native -C $(DEMOS_DIR)/$${demo} ; done

browser:
	for demo in $(DEMOS) ; do echo "\nBUILDING: $${demo}\n" && make browser -C $(DEMOS_DIR)/$${demo} ; done

libs:
	for lib in $(LIBS) ; do echo "\nBUILDING: $${lib}\n" && make -C $(LIBS_DIR)/$${lib} ; done

libs-native:
	for lib in $(LIBS) ; do echo "\nBUILDING: $${lib}\n" && make native -C $(LIBS_DIR)/$${lib} ; done

libs-browser:
	for lib in $(LIBS) ; do echo "\nBUILDING: $${lib}\n" && make browser -C $(LIBS_DIR)/$${lib} ; done

clean:
	for demo in $(DEMOS) ; do echo "\nCLEANING: $${demo}\n" && make clean -C $(DEMOS_DIR)/$${demo} ; done
	for lib in $(LIBS) ; do echo "\nCLEANING: $${lib}\n" && make clean -C $(LIBS_DIR)/$${lib} ; done
