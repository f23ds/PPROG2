#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "map.h"
#include "map.c"

int main()
{
    Map *map;
    Point p, *aux;
    int i;

    /* Inicializa un Map de 4 columnas y 3 filas*/
    map = map_new(3, 4);

    /* Inserta en el Map el laberinto del enunciado punto a punto*/
    
    map_readFromFile (stdin);  

   /* Imprimimos el mapa*/
    map_print(stdout, map);

   /* Devuelve los vecinos en el Map del punto correspondiente al output del laberinto*/
    
    Point *map_getNeighboor(map, aux, );
    Point * point_new (int x, int y, char symbol);
    void point_free (Point *p);

    /* Liberar la memoria del mapa */
     map_free(map);
   
}
