# 
# This makefile creates the fight demos and installs it into /usr/demos
#
include	$(ROOT)/usr/include/make/commondefs

AREA = applications

IDBTAG = 	-idb "std.sw.demos mach(GFXBOARD=CLOVER1 GFXBOARD=ECLIPSE)"
SALESIDB = 	-idb "demos.sw.${AREA} mach(GFXBOARD=CLOVER1 GFXBOARD=ECLIPSE)"

TARGETS =	flight dog shadow
#TARGETS =	flight dog radar shadow dogscore
SRCS =		main.c comm.c uflight.c land1.c land2.c meters.c density.c \
		c150.c b747.c f15.c f16.c f18.c flight.c \
		radar.c shadow.c p38.c f16w.c p38w.c mat.c \
		udpbrdcst.c udpcomm.c
LIBOBJS =	uflight.o land1.o land2.o c150.o b747.o f15.o f16.o f18.o \
		p38.o f16w.o p38w.o savecolors.o mat.o
OBJS =		$(LIBOBJS) main.o meters.o density.o xasin.o xatable.o
DOGOBJS =	dog.o udpbrdcst.o udpcomm.o $(OBJS)
SHADOWOBJS =	shadow.o udpbrdcst.o udpcomm.o $(LIBOBJS)

# compiler switches
#LCOPTS =	-D_4D -float -O -DDEBUG
LCOPTS =	-D_4D -float -O -Olimit 1000
# loader switches
LLDLIBS =	-lgl_s -lcps -lm -lsun -lbsd

default: $(TARGETS)

install: default
	${INSTALL} -F /usr/demos/bin -m 555 -u demos -g demos \
		${IDBTAG}  ${TARGETS}
	${INSTALL} -F /usr/demos -m 644 -u demos -g demos \
		${IDBTAG} -src m_flight .m_${AREA}_flight
	${INSTALL} -F /usr/demos -m 644 -u demos -g demos \
		${IDBTAG} -src m_flying .m_flight_flying
#	${INSTALL} -dir -m 755 -u demos -g demos \
#		${IDBTAG} /usr/demos/data/flight
#	${INSTALL} -F /usr/demos/data/flight -m 644 -u demos -g demos \
#		${SALESIDB} airshow
#	${INSTALL} -F /usr/demos -m 644 -u demos -g demos \
#		${SALESIDB} -src m_airshow .m_flight_airshow
# When there is a good airshow again, put the previous two installs
#  back in.

sales: install

flight:	flight.o $(OBJS)
	$(CC) -o $@ $@.o $(OBJS) $(LDFLAGS) 
	@echo "Make done"

flight.o shadow.o: iconize.h

iconize.h: iconize.cps
	$(TOOLROOT)/usr/sbin/cps $?

dog.o:	flight.c iconize.h
	$(CC) $(CFLAGS) -c flight.c -o $@ -DDOGFIGHT
dog:	$(DOGOBJS)
	$(CC) -o $@ $(DOGOBJS) $(LDFLAGS)
	@echo "Make done"

shadow:	$(SHADOWOBJS)
	$(CC) -o $@ $(SHADOWOBJS) $(LDFLAGS)
	@echo "Make done"

radar:	radar.o comm.o savecolors.o
	$(CC) -o $@ $@.o comm.o savecolors.o $(LDFLAGS)
	@echo "Make done"

dogscore: dogscore.o comm.o savecolors.o
	$(CC) -o $@ $@.o comm.o savecolors.o $(LDFLAGS)
	@echo "Make done"

clean:
	rm -f *CKP *BAK *.o $(PROGRAMS) .emacs* iconize.h

clobber: clean
	rm -f $(PROGRAMS)


# the following needed to be compile with -G0

p38w.o:
	$(CC) -G 0 $(CFLAGS) -c p38w.c

p38.o:
	$(CC) -G 0 $(CFLAGS) -c p38.c

f16w.o:
	$(CC) -G 0 $(CFLAGS) -c f16w.c

f16.o:
	$(CC) -G 0 $(CFLAGS) -c f16.c
