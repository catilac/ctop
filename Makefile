CC = gcc
CFLAGS = -g -Wall
LDFLAGS=-lncurses

default: ctop

ctop: ctop.c display.o
	$(CC) $(CFLAGS) -o ctop ctop.c display.o $(LDFLAGS)

display.o: display.c display.h
	$(CC) $(CFLAGS) -c display.c $(LDFLAGS)

clean:
	rm ctop *.o
