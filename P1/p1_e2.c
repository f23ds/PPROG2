#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "map.h"
#include "map.c"

int main()
{
    Map *map;
    Point p;
    int i;

    // Inicializa un Map de 4 columnas y 3 filas
    map = map_new(3, 4);

    // Inserta en el Map el laberinto del enunciado punto a punto

    /* Primero vamos a imprimir la primera fila de + */
    p.x, p.y = 0;
    p.symbol = "+";

    for (i = 0; i < map->ncols; i++)
    {
        map_insertPoint(map, &p);
        p.x++;
    }

    /* Ahora imprimiremos la útima fila de + */
    p.x = 0;
    p.y = 2;
    for (i = 0; i < map->ncols; i++)
    {
        map_insertPoint(map, &p);
        p.x++;
    }

    /* Ahora insertaremos manualmente la fila intermedia */
    p.x = 0;
    p.y = 1;
    map_insertPoint(map, &p);

    p.x = 3;
    map_insertPoint(map, &p);

    p.x = 1;
    p.symbol = "i";
    map_insertPoint(map, &p);

    p.x = 2;
    p.symbol = "o";
    map_insertPoint(map, &p);

    // Imprimimos el mapa
    map_print(stdout, map);

    // Devuelve los vecinos en el Map del punto correspondiente al output del laberinto
    // TODO:

    // Liberar la memoria del mapa
    map_free(map);
}