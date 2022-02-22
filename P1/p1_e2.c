/* PRACTICA 1 EJERCICIO 2
  Grupo: 1102
  Número de grupo:4
  Nombres: Fabio Desio Suárez
           Silvia Jiménez Real 
  Fecha entrega: 21/02/2022
  */
  
  
/* Declaración bibliotecas públicas*/


#include <stdio.h>
#include <stdlib.h>

/* Declaración bibliotecas públicas*/

#include "types.h"
#include "point.h"
#include "map.h"


int main()
{
    Map *map;
    Point *aux;
    Position pos;

    
    /* Inserta en el Map el laberinto del enunciado punto a punto*/
    
    map = map_readFromFile (stdin);  
   

   /* Imprimimos el mapa*/
    
    printf("Map:\n");
    map_print(stdout, map);

   /* Devuelve los vecinos en el Map del punto correspondiente al output del laberinto*/
    
    

    printf("\nGet output neighbors:\n");
    
    for(pos=0; pos<4; pos++)
    {
        
    aux = map_getNeighbor(map, map_getOutput(map), pos);
    point_print(stdout, aux);
        
    }

    printf("\n");
    /* Liberar la memoria del mapa */
    map_free(map);
 
    
    return 0;
   
}
