IDIR =/home/pi/
CC=g++
CFLAGS=-I$(IDIR) -Wall -g -fPIC

INSTALLEXEDIR=/usr/local/bin
INSTALLLIBDIR=/usr/local/lib
INSTALLINCDIR=/usr/local/include

LIBBARENAME=ds_notify_event
LIBNAME=lib$(LIBBARENAME).so
EXENAME=notifyEvent

LDIR =
LIBS=-lboost_thread -lboost_system  -lboost_filesystem -lcxxtools -lcxxtools-http -lcxxtools-json  -lrt -lm  -pthread 
LIBHEADER=eventNotifier.h
DEPS=$(LIBHEADER)

LIBOBJS=eventNotifier.o
EXEOBJS=notifyEvent.o

%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $< 

%.o: %.cpp $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $< 

$(LIBNAME): $(LIBOBJS)
	$(CXX) -shared -Wl,-soname,$@ -o $@ $(LIBOBJS) $(LIBS)

$(EXENAME): $(EXEOBJS) $(LIBNAME)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) -L. -l$(LIBBARENAME)

.PHONY: clean clobber all install

clean:
	rm -f $(LIBOBJS) 

clobber:
	rm -f $(LIBOBJS) $(EXEOBJS) $(LIBNAME) $(EXENAME)

# sudo make install
install:
	cp -f $(EXENAME) $(INSTALLEXEDIR)
	cp -f $(LIBNAME) $(INSTALLLIBDIR)
	cp -f $(LIBHEADER) $(INSTALLINCDIR)
	
all: $(EXENAME) $(LIBNAME)
