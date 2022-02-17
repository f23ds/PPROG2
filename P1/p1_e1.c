#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "point.c"

int main()
{
    /*Declaramos el array*/
    Point *p[4];
    int i;

    /*Inicializamos los punteros*/
    p[0] = point_new(0, 0, BARRIER);
    p[1] = point_new(0, 1, BARRIER);

    /*Imprimimos los punteros*/
    point_print(stdout, p[0]);
    point_print(stdout, p[1]);
    printf("\n");

    /*Comparamos los puntos p[0] y p[1]*/
    printf("Equal points p[0] and p[1]? ");
    if (point_equal(p[0], p[1]) == FALSE)
    {
        printf("No\n");
    }
    else
    {
        printf("Yes\n");
    }

    /*Creamos una copia de p[0] y la imprimimos*/
    p[2] = point_hardcpy(p[0]);
    printf("Creating p[2]: ");
    point_print(stdout, p[2]);
    printf("\n");

    /*Comparar original y su copia */
    printf("Equal points p[0] and p[2]? ");
    if (point_equal(p[0], p[2]) == FALSE)
    {
        printf("No\n");
    }
    else
    {
        printf("Yes\n");
    }

    /* Asignamos en simbolo SPACE a p[2]*/
    if (point_setSymbol(p[2], SPACE) == OK)
    {
        /*Imprimir p[2] con la modificación*/
        printf("Modifying p[2]: ");
        point_print(stdout, p[2]);
        printf("\n");
    }
    else
    {
        return EXIT_FAILURE;
    }

    /*Comparar de nuevo p[0] y p[2]*/
    printf("Equal points p[0] and p[2]? ");
    if (point_equal(p[0], p[2]) == FALSE)
    {
        printf("No\n");
    }
    else
    {
        printf("Yes\n");
    }

    /*Asignar a p[3] p[0]*/
    p[3] = p[0];

    /*Modificar el simbolo de p[3] y lo imprimimos*/
    if (point_setSymbol(p[3], OUTPUT) == OK)
    {
        /*Imprimir p[3] con la modificación*/
        printf("Modifying p[3]: ");
        point_print(stdout, p[3]);
        printf("\n");
    }
    else
    {
        return EXIT_FAILURE;
    }

    /*Imprimimos los cuatro puntos*/
    for (i = 0; i < 4; i++)
    {
        point_print(stdout, p[i]);
    }

    /*Liberamos la memoria*/
    for (i = 0; i < 4; i++)
    {
        point_free(p[i]);
    }

    return EXIT_SUCCESS;
}
