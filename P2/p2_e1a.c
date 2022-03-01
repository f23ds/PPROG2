/* PRÁCTICA 2 EJERCICIO 1
  Grupo: 2102
  Número de grupo:4
  Nombres: Fabio Desio Suárez
           Silvia Jiménez Real
  Fecha entrega: TODO:
*/

/* Declaración de bibliotecas públicas */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* Declaración de bibliotecas privadas */

#include "map.h"
#include "point.h"

/* Declaración de macros */
#define MIN_POINTS 0
#define MAX_POINTS 100
#define MAX_RAND 10

int main(int argc, char **argv)
{
    Point *origen;
    int n, i, j, cmp;
    double d;

    /* Comprobamos los argumentos de la command line */
    if (argc != 2)
        return 1;

    n = atoi(argv[1]);

    /* Comprobamos el valor de n */
    if (n < MIN_POINTS || n > MAX_POINTS)
        return 1;

    /* Creamos el array de puntos */
    Point *p[n];

    /* set the random seed */
    srand(time(NULL));
    /* coordinate origin point */
    origen = point_new(0, 0, BARRIER);

    /* Imprimimos la distancia euclídea para cada uno de los puntos */
    for (i = 0; i < n; i++)
    {
        /* point with random coordinates */
        p[i] = point_new(rand() % MAX_RAND, rand() % MAX_RAND,
                         BARRIER);

        /* Liberamos los puntos anteriores  en el caso de que erre la función point_new */
        if (p[i] == NULL)
        {
            for (j = i - 1; j >= 0; j--)
            {
                point_free(p[j]);
            }
            return 1;
        }

        point_print(stdout, p[i]);
        point_euDistance(p[i], origen, &d);
        fprintf(stdout, "Euclidean distance: %lf", d);
    }

    /* Comparamos las distancias euclídeas para todos los pares de puntos */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cmp = point_cmpEuDistance(p[i], p[j]);
            if (cmp == INT_MIN)
            {
                return 1;
            }
            else if (cmp == -1)
            {
                fprintf(stdout, "p[%d] < p[%d]: True", i, j);
            }
            else
            {
                fprintf(stdout, "p[%d] < p[%d]: False", i, j);
            }
        }
    }

    return 0;
}
