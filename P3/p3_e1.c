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

/* Macros */
#define MAX_RAND 23
#define MAX_INT 10

/* Como la función de comparación utilizaremos la función string_cmp para que
coincida el prototipo con lo que espera squeue_push */

int string_cmp(const void *s1, const void *s2)
{
    return strcmp((char *)s1, (char *)s2);
}

int int_cmp(const void *c1, const void *c2)
{
    return (*(int *)c1 - *(int *)c2);
}

/* Tests para los números enteros */
Status int_tests()
{
    int nums[MAX_INT], i;
    Status st = OK;
    Queue *qi = NULL, *qf = NULL;

    /* Inicializamos el array de números a valores random */
    for (i = 0; i < MAX_INT; i++)
    {
        nums[i] = rand() % MAX_RAND;
    }

    /* Inicializamos las colas (la primera desordenada y la segunda ordenada) */
    qi = queue_new();
    qf = queue_new();

    if (!qi)
        return ERROR;

    /* Si la segunda falla, necesitamos liberar la primera */
    if (!qf)
    {
        queue_free(qi);
        return ERROR;
    }

    /* Probamos primero a rellenar una cola desordenada */
    for (i = 0; i < MAX_INT && st == OK; i++)
    {
        st = queue_push(qi, &nums[i]);
    }

    if (st == ERROR)
    {
        queue_free(qi);
        return ERROR;
    }

    /* Ahora rellenamos la cola con squeue_push */
    for (i = 0; i < MAX_INT && st == OK; i++)
    {
        st = squeue_push(qf, &nums[i], int_cmp);
    }

    if (st == ERROR)
    {
        queue_free(qi);
        queue_free(qf);
        return ERROR;
    }

    return st;
}

Status point_tests()
{
    Status st = OK;
    return st;
}

Status string_tests()
{
    Status st = OK;
    return st;
}

int main()
{
    /* Tenemos que probar la funcionalidad del TAD SortedQueue usando
    números enteros, puntos y cadenas de texto */
    int test = 0;
    Status st = OK;

    /* Vamos a hacer que el usuario pueda elegir el tipo de tests que quiere correr */
    do
    {
        printf("Tests disponibles:\n\t(1) Números enteros\n\t(2) Puntos\n\t(3) Cadenas\n");
        printf("Inserte el código: ");
        scanf("%d", &test);
        if (test < 1 || test > 3)
        {
            printf("\nERROR: Modo de uso incorrecto\n\n");
        }
    } while (test < 1 || test > 3);

    /* Diferenciamos los tests */
    if (test == 1)
    {
        st = int_tests();
    }
    else if (test == 2)
    {
        st = point_tests();
    }
    else
    {
        st = string_tests();
    }

    if (st == ERROR)
        return 1;

    return 0;
}