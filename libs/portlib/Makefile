
include ${ROOT}/usr/include/make/commondefs

LCINCS = -I../include -I$(ROOT)/usr/include -I$(ROOT)/usr/include/gl2 
LCOPTS = -O -DUNIX -D$$CPUBOARD
OBJS = turtle.o gamma.o getset.o colormod.o subview.o redraw.o \
	getapixel.o ipc.o percent.o parse.o fontlib.o \
	rectlib.o

all: libport.a

clean:
	rm -f *.o *.a

install: all
	${INSTALL} -idb "std.sw.unix" -F /usr/lib libport.a
	ranlib ${ROOT}/usr/lib/libport.a

libport.a: $(OBJS) 
	ar cr libport.a $(OBJS)
	ranlib libport.a

.c.o:
	$(CCF) -c $<
