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
    Poaition pos;

    /* Inicializa un Map de 4 columnas y 3 filas*/
    
    map = map_new(3, 4);

    /* Inserta en el Map el laberinto del enunciado punto a punto*/
    
    map_readFromFile (stdin);  

   /* Imprimimos el mapa*/
    
    printf("Map:\n");
    map_print(stdout, map);

   /* Devuelve los vecinos en el Map del punto correspondiente al output del laberinto*/
    
    aux = point_new (0, 0, BARRIER);
    
    printf("Get output neighboors:\n");
    
    for(pos=0; pos<5; pos++)
    {
        
    aux = map_getNeighboor(map, map->output, pos);
    point_print(stdout, aux);
        
    }

    /* Liberar la memoria del mapa */
     map_free(map);
    point_free (aux);
    
    return 0;
   
}
