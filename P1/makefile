all: p1_e1 p1_e2

p1_e1: p1_e1.o map.o point.o 
	gcc p1_e1.o map.o point.o -g -o p1_e1

p1_e2: p1_e2.o map.o point.o
	gcc p1_e2.o map.o point.o -g -o p1_e2

point.o: point.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c point.c
	
map.o: map.c map.h types.h 
	gcc -ansi -pedantic -Wall -g -c map.c

p1_e1.o: p1_e1.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c p1_e1.c

p1_e2.o: p1_e2.c map.h point.h types.h 
	gcc -ansi -pedantic -Wall -g -c p1_e2.c
	
clean:
	rm -f *.o
