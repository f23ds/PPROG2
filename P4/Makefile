CC=gcc
CFLAGS=-Wall -ggdb

LIBS =-lm -pthread

all: bstree

## $@ Nombre del fichero destino de la regla
## $< Nombre de la primera dependencia de la regla
## $^ Equivale a todas las dependencias de la regla

p3_e1: p3_e1.o point.o sorted_queue.o queue.o list.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS) 

p3_e2: p3_e2.o point.o map.o queue.o list.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p3_e1.o: p3_e1.c point.h types.h sorted_queue.h 
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p3_e2.o: p3_e2.c point.h types.h sorted_queue.h 
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

list.o: list.c list.h types.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

queue.o: queue.c queue.h types.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

sorted_queue.o: sorted_queue.c sorted_queue.h types.h 
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

map.o: map.c map.h types.h #Notad que se puede quitar -o y $@
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

point.o: point.c point.h types.h #Notad que se puede quitar -o y $@
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

clean:
	rm -f *.o