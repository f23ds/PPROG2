CC=gcc
LDFLAGS=-L./
LDLIBS=-lstack_fDoble

all: p2_e1a p2_e1b p2_e1c p2_e2

p2_e1a: p2_e1a.o point.o
	$(CC) p2_e1a.o point.o -lm -g -o p2_e1a

p2_e1b: p2_e1b.o point.o stack_fDoble.o 
	$(CC) p2_e1b.o point.o stack_fDoble.o -lm -g -o p2_e1b

p2_e1c: p2_e1c.o point.o stack_fDoble.o
	$(CC) p2_e1c.o point.o stack_fDoble.o -lm -g -o p2_e1c

p2_e2: p2_e2.o point.o map.o stack_fDoble.o
	$(CC) p2_e2.o point.o map.o stack_fDoble.o -lm -g -o p2_e2

point.o: point.c point.h types.h
	$(CC) -ansi -pedantic -Wall -g -c point.c
	
map.o: map.c map.h types.h 
	$(CC) -ansi -pedantic -Wall -g -c map.c

p2_e1a.o: p2_e1a.c point.h types.h
	$(CC) -ansi -pedantic -Wall -g -c p2_e1a.c

p2_e1b.o: p2_e1b.c point.h types.h
	$(CC) -ansi -pedantic -Wall -g -c p2_e1b.c

p2_e1c.o: p2_e1c.c point.h types.h
	$(CC) -ansi -pedantic -Wall -g -c p2_e1c.c

p2_e2.o: p2_e2.c point.h types.h map.h
	$(CC) -ansi -pedantic -Wall -g -c p2_e2.c

stack_fDoble.o: stack_fDoble.c stack_fDoble.h
	$(CC) -ansi -pedantic -Wall -g -c stack_fDoble.c

	