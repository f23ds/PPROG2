LDFLAGS=-L./
LDLIBS=-lstack_fDoble

all: p2_e1a p2_e1b p2_e1c

p2_e1a: p2_e1a.o point.o
	gcc p2_e1a.o point.o -lm -g -o p2_e1a

p2_e1b: p2_e1b.o point.o
	gcc p2_e1b.o point.o $(LDFLAGS) $(LDLIBS) -lm -g -o p2_e1b

p2_e1c: p2_e1c.o point.o
	gcc p2_e1c.o point.o $(LDFLAGS) $(LDLIBS) -lm -g -o p2_e1c

point.o: point.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c point.c
	
map.o: map.c map.h types.h 
	gcc -ansi -pedantic -Wall -g -c map.c

p2_e1b.o: p2_e1b.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c p2_e1b.c

p2_e1c.o: p2_e1c.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c p2_e1c.c

	