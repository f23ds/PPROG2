#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "stack_fDoble.h"
#include "types.h"
#include "point.h"

#define MIN_POINTS 0
#define MAX_POINTS 10
#define MAX_RAND 10

Stack *stack_orderPoints(Stack *sin)
{
    Stack *sout;
    int *tmp = NULL, cmp;

    sout = stack_init();

    if (!sout)
        return NULL;

    while (!stack_isEmpty(sin))
    {
        tmp = stack_top(sin);
        stack_pop(sin);

        cmp = point_cmpEuDistance(stack_top(sout), tmp);

        while (!stack_isEmpty(sout) && cmp == -1)
        {
            stack_push(sin, stack_top(sout));
            stack_pop(sout);
        }
        stack_push(sout, tmp);
    }

    return sout;
}

int main(int argc, char **argv)
{
    int n, i, j;
    double d;
    Stack *sin, *sout;
    Point *origen, *p[MAX_POINTS];

    /* Comprobamos la command line */
    if (argc < 2)
        return 1;

    n = atoi(argv[1]);

    /* Comprobamos que el número de puntos es correcto */
    if (n < MIN_POINTS || n > MAX_POINTS)
        return 1;

    /* Calcular la distancia euclídea de los puntos al origen de coordenadas */
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
        fprintf(stdout, " distance: %f\n", d);
    }

    /* Almacenar los puntos en una pila */
    sin = stack_init();

    if (!sin)
        return 1;

    /* TODO: MIRAR SI LA PILA ESTÁ LLENA */
    for (i = 0; i < n; i++)
    {
        stack_push(sin, p[i]);
    }

    /* Imprimimos los punts */
    fprintf(stdout, "Original stack: \n");
    stack_print(stdout, sin, point_print);

    /* Ordenamos la pila de mayor a menor según la distancia euclídea entre los puntos */
    sout = stack_orderPoints(sin);

    fprintf(stdout, "Ordered stack: \n");
    stack_print(stdout, sout, point_print);

    fprintf(stdout, "Original stack: \n");
    stack_print(stdout, sin, point_print);

    return 0;
}