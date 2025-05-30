APPNAME=buttonfly
APPARGS=menu_demos
APPCMDS=cp web/buttonfly.js web/buttonfly.wasm web/buttonfly.data ../../sgi-demos.github.io
EMPRELOAD=--preload-file menus/menu --preload-file menus/m_demos --preload-file menus/m_more_demos --preload-file menus/m_bounce

build_parser := $(shell $(MAKE) -f Make_parser)

include ../build/make_demo.mk

clean_parser:
	$(MAKE) -f Make_parser clean
clean: clean_parser
