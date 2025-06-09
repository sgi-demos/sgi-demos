PROGRAMS =	flight dog shadow
#PROGRAMS =	flight dog radar shadow dogscore
SRCS =		main.c comm.c uflight.c land1.c land2.c meters.c density.c \
		c150.c b747.c f15.c f16.c f18.c flight.c \
		radar.c shadow.c p38.c f16w.c p38w.c
LIBOBJS =	uflight.o land1.o land2.o c150.o b747.o f15.o f16.o f18.o \
		p38.o f16w.o p38w.o savecolors.o
OBJS =		$(LIBOBJS) main.o meters.o density.o xasin.o xatable.o
DOGOBJS =	dog.o udpcomm.o udpbrdcst.o $(OBJS)
DSOBJS =	dogscore.o udpbrdcst.o udpcomm.o savecolors.o

# compiler switches
CC	=	cc
CFLAGS =	-O
# loader switches
LDFLAGS =	-Zg
SYSLIBS =	-lsun -lbsd -ldbm
SALES	=	/usr/people/sales
BOOT	=	/usr/people/demos

all: $(PROGRAMS)

sales:  all
	cp flight dog radar shadow airshow $(SALES)/demo
	cp radar shadow airshow $(SALES)/wmandemo

install: all
	cp $(PROGRAMS) $(BOOT)
	@echo "Install done"

flight:	flight.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $@.o $(OBJS) $(SYSLIBS)
	@echo "Make done"

dog.o:	flight.c
	$(CC) $(CFLAGS) -c flight.c -o $@ -DDOGFIGHT
dog:	$(DOGOBJS)
	$(CC) $(LDFLAGS) -o $@ $(DOGOBJS) $(SYSLIBS)
	@echo "Make done"

shadow:	shadow.o udpcomm.o udpbrdcst.o $(LIBOBJS)
	$(CC) $(LDFLAGS) -o $@ $@.o udpcomm.o udpbrdcst.o $(LIBOBJS) $(SYSLIBS)
	@echo "Make done"

radar:	radar.o comm.o savecolors.o
	$(CC) $(LDFLAGS) -o $@ $@.o comm.o savecolors.o $(SYSLIBS)
	@echo "Make done"

dogscore: $(DSOBJS)
	$(CC) $(LDFLAGS) -o $@ $(DSOBJS) $(SYSLIBS)
	@echo "Make done"

clean:
	rm -f *CKP *BAK *.o $(PROGRAMS) .emacs*

