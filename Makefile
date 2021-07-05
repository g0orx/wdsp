#
# libwdsp.so Makefile (Linux)
#
PREFIX=/usr/local
LIBDIR=$(DESTDIR)$(PREFIX)/lib
INCLUDEDIR=$(DESTDIR)$(PREFIX)/include
CC=gcc
LINK=gcc
OPTIONS=-g -fPIC -O3 -D _GNU_SOURCE
#OPTIONS=-g -fPIC

#GTK_INCLUDE=GTK
ifeq ($GTK_INCLUDE),GTK)
GTKINCLUDES=`pkg-config --cflags gtk+-3.0`
GTKLIBS=`pkg-config --libs gtk+-3.0`
GTKOPTIONS=-D GTK
endif

LIBS=-lfftw3 -lpthread
JAVA_LIBS=-L. -lwdsp

INCLUDES=-I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux

COMPILE=$(CC) $(INCLUDES) $(GTKINCLUDES)

PROGRAM=libwdsp.so
JAVA_PROGRAM=libwdspj.so

SOURCES= amd.c\
ammod.c\
amsq.c\
analyzer.c\
anf.c\
anr.c\
bandpass.c\
calcc.c\
calculus.c\
cblock.c\
cfcomp.c\
cfir.c\
channel.c\
comm.c\
compress.c\
delay.c\
dexp.c\
div.c\
eer.c\
emnr.c\
emph.c\
eq.c\
fcurve.c\
fir.c\
firmin.c\
fmd.c\
fmmod.c\
fmsq.c\
gain.c\
gen.c\
icfir.c\
iir.c\
iobuffs.c\
iqc.c\
linux_port.c\
lmath.c\
main.c\
meter.c\
meterlog10.c\
nbp.c\
nob.c\
nobII.c\
osctrl.c\
patchpanel.c\
resample.c\
rmatch.c\
RXA.c\
sender.c\
shift.c\
siphon.c\
slew.c\
snb.c\
syncbuffs.c\
TXA.c\
utilities.c\
varsamp.c\
version.c\
wcpAGC.c\
wisdom.c

JAVA_SOURCES= org_g0orx_openhpsdr_wdsp_WDSP.c

HEADERS=amd.h\
ammod.h\
amsq.h\
analyzer.h\
anf.h\
anr.h\
bandpass.h\
calcc.h\
calculus.h\
cblock.h\
cfcomp.h\
cfir.h\
channel.h\
comm.h\
compress.h\
delay.h\
dexp.h\
div.h\
eer.h\
emnr.h\
emph.h\
eq.h\
fastmath.h\
fcurve.h\
fir.h\
firmin.h \
fmd.h\
fmmod.h\
fmsq.h\
gain.h\
gen.h\
icfir.h\
iir.h\
iobuffs.h\
iqc.h\
linux_port.h\
lmath.h\
main.h\
meter.h\
meterlog10.h\
nbp.h\
nob.h\
nobII.h\
osctrl.h\
patchpanel.h\
resample.h\
resource.h\
rmatch.h\
RXA.h\
sender.h\
shift.h\
siphon.h\
slew.h\
snb.h\
syncbuffs.h\
TXA.h\
utilities.h\
wcpAGC.h

JAVA_HEADERS= org_g0orx_openhpsdr_wdsp_WDSP.h

OBJS=linux_port.o\
amd.o\
ammod.o\
amsq.o\
analyzer.o\
anf.o\
anr.o\
bandpass.o\
calcc.o\
calculus.o\
cblock.o\
cfcomp.o\
cfir.o\
channel.o\
comm.o\
compress.o\
delay.o\
dexp.o\
div.o\
eer.o\
emnr.o\
emph.o\
eq.o\
fcurve.o\
fir.o\
firmin.o\
fmd.o\
fmmod.o\
fmsq.o\
gain.o\
gen.o\
icfir.o\
iir.o\
iobuffs.o\
iqc.o\
lmath.o\
main.o\
meter.o\
meterlog10.o\
nbp.o\
nob.o\
nobII.o\
osctrl.o\
patchpanel.o\
resample.o\
rmatch.o\
RXA.o\
sender.o\
shift.o\
siphon.o\
slew.o\
snb.o\
syncbuffs.o\
TXA.o\
utilities.o\
version.o\
varsamp.o\
wcpAGC.o\
wisdom.o

JAVA_OBJS= org_g0orx_openhpsdr_wdsp_WDSP.o

all: $(PROGRAM) $(HEADERS) $(SOURCES)

java: $(JAVA_PROGRAM) $(JAVA_HEADERS) $(JAVA_SOURCES)

$(PROGRAM): $(OBJS)
	$(LINK) -shared -z noexecstack $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LIBS) $(GTKLIBS)

$(JAVA_PROGRAM): $(JAVA_OBJS)
	$(LINK) -shared -z noexecstack $(LDFLAGS) -o $(JAVA_PROGRAM) $(JAVA_OBJS) $(JAVA_LIBS)

.c.o:
	$(COMPILE) $(OPTIONS) $(GTKOPTIONS) $(CFLAGS) -c -o $@ $<

install-dirs:
	mkdir -p $(LIBDIR) $(INCLUDEDIR)

install: $(PROGRAM) install-dirs
	cp -a wdsp.h $(INCLUDEDIR)
	cp -a $(PROGRAM) $(LIBDIR)
	ldconfig || :

install_java: $(JAVA_PROGRAM) install-dirs
	cp -a $(JAVA_PROGRAM) $(LIBDIR)

release: $(PROGRAM)
	cp -a $(PROGRAM) ../pihpsdr.src/release/pihpsdr

clean:
	-rm -f *.o
	-rm -f $(PROGRAM)
	-rm -f $(JAVA_PROGRAM)

