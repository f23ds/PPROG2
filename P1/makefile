all: p1_e1

p1_e1: p1_e1.o point.o 
	gcc p1_e1.o point.o -g -o p1_e1

point.o: point.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c point.c

p1_e1.o: p1_e1.c point.h types.h
	gcc -ansi -pedantic -Wall -g -c p1_e1.c
	
clean:
	rm -f *.o
