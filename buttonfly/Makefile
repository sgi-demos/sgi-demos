parser.tab.c parser.tab.h: parser.y
	bison --defines parser.y

APPNAME=buttonfly
APPARGS=menu_demos
APPLIBS=-lm
include ../make_demo.mk

clean_parser:
	rm -f parser.tab.c parser.tab.h