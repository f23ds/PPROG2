CC=gcc
LDFLAGS=-L./
LDLIBS=-lqueue

all: p3_e1

p3_e1: p3_e1.o point.o sorted_queue.o 
	$(CC) p3_e1.o point.o sorted_queue.o  $(LDFLAGS) $(LDLIBS) -lm -g -o p3_e1

point.o: point.c point.h types.h
	$(CC) -ansi -pedantic -Wall -g -c point.c
	
map.o: map.c map.h types.h 
	$(CC) -ansi -pedantic -Wall -g -c map.c

p3_e1.o: p3_e1.c point.h types.h
	$(CC) -ansi -pedantic -Wall -g -c p3_e1.c

sorted_queue.o: sorted_queue.c types.h
	$(CC) -ansi -pedantic -Wall -g -c sorted_queue.c