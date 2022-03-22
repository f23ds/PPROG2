#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "stack_fDoble.h"
#include "types.h"
#include "point.h"
#include "map.h"

int main(int argc, char **argv)
{
    FILE *pf;
    Map *map;
    Point *p = NULL;

    /* Comprobamos que hay el número correcto de argumentos en la command line */
    if (argc != 2)
    {
        printf("Error en la ejecución. Debe ser del tipo: './p2_e2 laberinto_1.txt'\n");
        return -1;
    }

    /* Abrimos el archivo cuyo nombre es el segundo argumentos de la command line */
    pf = fopen(argv[1], "r");

    if (!pf)
        return -1;

    /* Inserta en el Map el laberinto del enunciado punto a punto*/
    map = map_readFromFile(pf);

    /* Imprimimos el laberinto */
    printf("Maze:\n");
    map_print(stdout, map);

    fprintf(stdout, "\nDFS traverse:\n");

    p = map_dfs(stdout, map);

    fprintf(stdout, "\n");

    if (!p){
    
        map_free(map);
        return 1;
    }
    
    map_free(map);
    point_free(p);
   

    return 0;
}
