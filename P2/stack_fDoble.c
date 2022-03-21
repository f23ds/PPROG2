#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "limits.h"
#include "stack_fDoble.h"

#define INIT_CAPACITY 2
#define FCT_CAPACITY 2

struct _Stack
{
    void **items;
    int top;
    int capacity;
};

typedef struct _Stack Stack;

typedef int (*P_stack_ele_print)(FILE *, const void *);

Bool stack_isEmpty(const Stack *s);
Bool _stack_isFull(const Stack *s);
size_t stack_size(const Stack *s);

Stack *stack_init()
{
    Stack *s = NULL;

    /* Creamos la stack */
    s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL)
        return NULL;

    /* Inicializamos la capacidad */
    s->capacity = INIT_CAPACITY;

    /* Reservamos memoria para el global pointer de items */
    s->items = (void **)calloc(INIT_CAPACITY, sizeof(void *));

    /* Inicializamos el top */
    s->top = -1;
    return s;
}

void stack_free(Stack *s)
{
    /* Liberamos el global pointer */
    free(s->items);
    /* Liberamos la stack */
    free(s);
}

Status stack_push(Stack *s, const void *ele)
{
    size_t size;
    if (s == NULL || ele == NULL)
        return ERROR;


    /* Si la stack no está llena realizamos el procedimiento habitual */
    if (_stack_isFull(s) == FALSE)
    {
        s->top++;
        s->items[s->top] = (void *) ele;
        return OK;
    }
    else
    {
        size = stack_size(s);
        /* Comprobación de errores */
        if (!size)
            return ERROR;

        /* Reallocamos memoria dinámicamente */
        if ((s = (Stack *)realloc(s, size * FCT_CAPACITY)) == NULL)
            return ERROR;
        s->top++;
        s->items[s->top] = (void *) ele;
        return OK;
    }

    return OK;
}

void *stack_pop(Stack *s)
{
    void *e = NULL;

    if (s == NULL || stack_isEmpty(s))
        return NULL;

    e = s->items[s->top];
    s->items[s->top] = NULL;
    s->top--;

    return e;
}

void *stack_top(const Stack *s)
{
    if (s == NULL || stack_isEmpty(s))
        return NULL;

    return s->items[s->top];
}

Bool stack_isEmpty(const Stack *s)
{
    if (s == NULL)
        return TRUE;

    if (s->top == -1)
        return TRUE;

    return FALSE;
}

Bool _stack_isFull(const Stack *s)
{
    if (s == NULL)
        return TRUE;

    if (s->top == s->capacity - 1)
        return TRUE;

    return FALSE;
}

size_t stack_size(const Stack *s)
{
    size_t size;

    if (s == NULL)
        return 0;

    size = s->capacity * sizeof(Stack);

    return size;
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)
{
    int t, print = 0;
    void *ele = NULL;

    if (fp == NULL || s == NULL)
        return INT_MIN;

    if (stack_isEmpty(s) == TRUE)
        return INT_MIN;

    t = s->top;

    while (t >= 0)
    {
        ele = s->items[t];
        print += f(fp, ele);
        t--;
    }

    return print;
}
