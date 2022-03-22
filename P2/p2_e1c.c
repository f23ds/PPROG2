#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "stack_fDoble.h"
#include "types.h"
#include "point.h"

#define MIN_NUMS 0
#define MAX_NUMS 10
#define MAX_RAND 100
#define INT_MAX __INT_MAX__
#define INT_MIN -INT_MAX - 1

Stack *stack_order(Stack *sin, int (*f_cmp)(const void *, const void *))
{
    Stack *sout;
    int *tmp = NULL;

    sout = stack_init();

    if (!sout)
        return NULL;

    while (!stack_isEmpty(sin))
    {
        tmp = stack_top(sin);
        stack_pop(sin);

        while (!stack_isEmpty(sout) && f_cmp(stack_top(sout), tmp) < 0)
        {
            stack_push(sin, stack_top(sout));
            stack_pop(sout);
        }
        stack_push(sout, tmp);
    }

    return sout;
}

int int_print(FILE *pf, const void *a)
{
    if (!pf || !a)
        return -1;
    return fprintf(pf, "%d", *(int *)a);
}

int int_cmp(const void *c1, const void *c2)
{
    if (!c1 || !c2)
        return INT_MIN;
    return (*(int *)c1 - *(int *)c2);
}

int main(int argc, char **argv)
{
    Stack *s, *sout;
    int nums[MAX_NUMS], n, i, *tmp = NULL, tam;

    /* Comprobamos la command line */
    if (argc < 2)
        return 1;

    n = atoi(argv[1]);

    if (n < MIN_NUMS || n > MAX_NUMS)
        return 1;

    /* Semilla random */
    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        nums[i] = rand() % MAX_RAND;
    }

    /* Almacenamos los números en la pila */
    s = stack_init();

    if (!s)
        return 1;

    for (i = 0; i < n; i++)
    {
        tmp = &nums[i];
        stack_push(s, tmp);
    }

    /* Imprimimos los números antes y después de ordenarlos */
    fprintf(stdout, "Original stack: \n");
    fprintf(stdout, "SIZE:% d\n", n);
    stack_print(stdout, s, int_print);

    sout = stack_order(s, int_cmp);
    
    if(!sout)
    {
      stack_free(s);
      return 1;
    }

    fprintf(stdout, "Ordered stack: \n");
    fprintf(stdout, "SIZE:% d\n", n);
    stack_print(stdout, sout, int_print);
    
    fprintf(stdout, "Original stack: \n");
    tam = stack_size(s);
    fprintf(stdout, "SIZE:%d\n", tam+1);
    stack_print(stdout, s, int_print);
    
    stack_free(sout);
    stack_free(s);

    return 0;
}
