TARGETS = Make_parser Make_demo

.PHONY: all clean Make_parser Make_demo

all: $(TARGETS)

Make_parser:
	make -f Make_parser

Make_demo: Make_parser
	make -f Make_demo

clean:
	for file in $(TARGETS) ; do make clean -f $${file} ; done