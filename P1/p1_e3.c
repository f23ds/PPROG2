/* PRACTICA 1 EJERCICIO 3
  Grupo: 1102
  Número de grupo:4
  Nombres: Fabio Desio Suárez
           Silvia Jiménez Real 
  Fecha entrega: 28/02/2022
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
    
    map = map_readFromFile ("laberinto1.txt");  
   

   /* Imprimimos el mapa*/
    
    printf("Map:\n");
    map_print(stdout, map);

   /* Devuelve los vecinos en el Map del punto correspondiente al output del laberinto*/
    
    printf("\nGet output neighboors:\n");
    
    for(pos=0; pos<4; pos++)
    {
        
    aux = map_getNeighbor(map, map_getOutput(map), pos);
    point_print(stdout, aux);
        
    }
  
     /* Devuelve los vecinos en el Map del punto correspondiente al output del laberinto*/
    
    printf("\nGet right inferior corner neighboors:\n");
  
  point = point_new(ncols, nrows, BARRIER);
    
    for(pos=0; pos<4; pos++)
    {
        
    aux = map_getNeighbor(map, map_getPoint(map, point), pos);
    point_print(stdout, aux);
        
    }

    /* Liberar la memoria del mapa */
    map_free(map);
 
    
    return 0;
   
}
