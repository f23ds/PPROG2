all: p2_e1a

p2_e1a: p2_e1a.o point.o
	gcc p2_e1a.o point.o -lm -g -o p2_e1a

point.o: point.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c point.c
	
map.o: map.c map.h types.h 
	gcc -ansi -pedantic -Wall -g -c map.c

p2_e1a.o: p2_e1a.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c p2_e1a.c			