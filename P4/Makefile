CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lqueue #Cambiamos al nombre de la libreria lstack_fp

LIBS =-lm -pthread

all: p4 pruebas

## $@ Nombre del fichero destino de la regla
## $< Nombre de la primera dependencia de la regla
## $^ Equivale a todas las dependencias de la regla

p4: p4.o point.o bstree.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) 

p4.o: p4.c point.h types.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

point.o: point.c point.h types.h #Notad que se puede quitar -o y $@
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

bstree.o: bstree.c bstree.h types.h #Notad que se puede quitar -o y $@
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

pruebas: pruebas.o point.o bstree.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) 

pruebas.o: pruebas.c point.h types.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

clean:
	rm -f *.o