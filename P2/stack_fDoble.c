#include <stdlib.h>
#include <limits.h>

#include "stack_fDoble.h"

#define INIT_CAPACITY 2
#define FCT_CAPACITY 2

struct _Stack
{
    void **items;
    int top;
    int capacity;
};

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
    s->items = malloc(sizeof (void*)*INIT_CAPACITY);
    
    if(s->items == NULL)
    {
     free(s);
     return NULL;
     }

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
    void *p_aux = NULL;
    
    if (s == NULL || ele == NULL)
        return ERROR;


    if (_stack_isFull(s))
    {
        p_aux = realloc(s->items, FCT_CAPACITY * s->capacity * sizeof(void*));
        
        if(p_aux==NULL) return ERROR;
       
        s->items = p_aux;
        s->capacity = s->capacity * FCT_CAPACITY;
        }
        
        s->top++;
        s->items[s->top] = (void*) ele;
        
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

    if (s == NULL) return 0;

    return s->top;
 }

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)
{
    int t, print = 0;

    if (fp == NULL || s == NULL) return INT_MIN;


    t = s->top;

    while (t > -1)
    {
        print += f(fp, s->items[t]);
        fprintf(stdout, "\n");
        t--;
    }

    return print;
}
