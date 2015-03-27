IDIR =/home/pi/
CC=g++
CFLAGS=-I$(IDIR) -Wall -g

LDIR =

LIBS=-lboost_thread -lboost_system  -lboost_filesystem -lcxxtools -lcxxtools-json  -lrt -lm  -pthread 

DEPS = eventNotifier.h

OBJ = notifyEvent.o eventNotifier.o

%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $< 

%.o: %.cpp $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $< 


notifyEvent: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean all

clean:
	rm -f $(OBJ) 

all: notifyEvent
