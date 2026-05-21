TARGETS = Make_parser Make_demo

.PHONY: all clean Make_parser Make_demo native web

all: $(TARGETS)

Make_parser:
	make -f Make_parser

Make_demo: Make_parser
	make -f Make_demo

native web: Make_parser
	$(MAKE) $@ -f Make_demo

clean:
	for file in $(TARGETS) ; do $(MAKE) clean -f $${file} ; done
