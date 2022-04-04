/* Bibliotecas públicas */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Bibliotecas privadas */
#include "sorted_queue.h"
#include "queue.h"
#include "point.h"
#include "types.h"
#include "map.h"



int main(int argc, char **argv)
{
  Map *map;
  Point *output=NULL;
  FILE *pf;

  /* Comprobamos que hay el número correcto de argumentos en la command line */
  if (argc != 2)
  {
    printf("Error en la ejecución. Debe ser del tipo: './p3_e2 laberinto_1.txt'\n");
    return -1;
  }

  /* Abrimos el archivo cuyo nombre es el segundo argumentos de la command line */
  pf = fopen(argv[1], "r");

  if (!pf)
    return -1;

  /* Inserta en el Map el laberinto del enunciado punto a punto*/
  map = map_readFromFile(pf);

  /* Imprimimos el mapa*/
  printf("Maze:\n");
  map_print(stdout, map);
  
  fprintf(stdout, "\nBFS:\n");
  
  output = map_bfs (stdout, map);
  
  if(output == NULL){
    printf("Error en la ejecución del algoritmo.\n");
    map_free(map);
    return -1;
  }

  printf("\n");
  
  fclose(pf);
  map_free(map);
  return 0;
}
