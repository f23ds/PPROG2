#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "stack_fDoble.h"

#define MAX_STACK 100

struct _Stack
{
    void *data[MAX_STACK];
    int top;
};

Stack *stack_orderPoints(Stack *sin)
{
    Stack *sout, *e1, *e2;

    sout = stack_init();

    if (sout == NULL)
        return NULL;

    while (stack_isEmpty(sin))
    {
        e1 = stack_pop(sin);
        while (!stack_isEmpty(sout) && e1 < stack_top(sout))
        {
            e2 = stack_pop(sout);
            stack_push(sin, e2);
        }
        stack_push(sout, e1);
    }

    return sout;
}