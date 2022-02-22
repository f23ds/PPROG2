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


int main(int argc, char** argv)
{
    Map *map;
    Point *aux, *point;
    Position pos;
    FILE *pf;
    int ncols, nrows; 

    /* Comprobamos que hay el número correcto de argumentos en la command line */
    if (argc != 2) {
      printf("Error en la ejecución. Debe ser del tipo: './p1_e3 laberinto_1.txt'\n");
      return -1;
    }

    pf = fopen(argv[1], "r");

    if (!pf) return -1;

    /* Inserta en el Map el laberinto del enunciado punto a punto*/
    
    map = map_readFromFile (pf);  
   

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
  
    ncols = map_getNcols(map);
    nrows = map_getNrows(map);

    point = point_new(ncols-1, nrows-1, BARRIER);
    
    
    for(pos=0; pos<4; pos++)
    {
        
    aux = map_getNeighbor(map, map_getPoint(map, point), pos);
    point_print(stdout, aux);
      
    }
    
    printf("\n");
    /* Liberar la memoria del mapa */
    map_free(map);
    point_free(point);
    fclose(pf);
    
    return 0;
   
}
