CC = gcc
CFLAGS = -g -Wall

default: ctop

ctop: ctop.c display.o
	$(CC) $(CFLAGS) -o ctop ctop.c display.o -lncurses

display.o: display.c display.h
	$(CC) $(CFLAGS) -c display.c

clean:
	rm ctop *.o
	rm -r *.dSYM
