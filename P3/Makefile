CC=gcc
LDFLAGS=-L./
LDLIBS=-lqueue

all: p3_e1 p3_e2

p3_e1: p3_e1.o point.o queue.o sorted_queue.o list.o
	$(CC) p3_e1.o point.o queue.o sorted_queue.o list.o $(LDFLAGS) $(LDLIBS) -lm -g -o p3_e1

p3_e2: p3_e2.o point.o queue.o list.o map.o
	$(CC) p3_e2.o point.o queue.o list.o map.o $(LDFLAGS) $(LDLIBS) -lm -g -o p3_e2

point.o: point.c point.h types.h
	$(CC) -ansi -Wall -g -c point.c
	
map.o: map.c map.h types.h point.h
	$(CC) -ansi -Wall -g -c map.c

p3_e1.o: p3_e1.c point.h types.h queue.h sorted_queue.h list.h
	$(CC) -ansi -Wall -g -c p3_e1.c

p3_e2.o: p3_e2.c point.h types.h map.h
	$(CC) -ansi -Wall -g -c p3_e2.c

sorted_queue.o: sorted_queue.c types.h queue.h
	$(CC) -ansi -Wall -g -c sorted_queue.c

list.o: list.c types.h 
	$(CC) -ansi -Wall -g -c list.c

queue.o: queue.c types.h 
	$(CC) -ansi -Wall -g -c queue.c

clean:
	rm -f *.o
