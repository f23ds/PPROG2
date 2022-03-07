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

Stack *stack_init() {
Stack *s = NULL;
int i;
s = (Stack *) malloc (sizeof(Stack));
if (s == NULL) {
return NULL;
}
for (i = 0; i < MAX_STACK; i++) {
s->data[i] = NULL;
}
s->top = -1; // Alt: s->top = 0
return s;
}

void stack_free(Stack *s) {
free(s);
}

Status stack_push(Stack *s, const void *e) {
if (s == NULL || e == NULL || _stack_isFull(s) == TRUE) {
return ERR;
}
s->top++;
s->data[s->top] = e; // s->data[++s->top] = e;
return OK;
}

void *stack_pop(Stack *s) {
void *e = NULL;
if (s == NULL || stack_isEmpty(s) == TRUE) {
return NULL;
}
e = s->data[s->top];
s->data[s->top] = NULL;
s->top--;
return e;
}

void *stack_top(const Stack *s) {
if (s == NULL || stack_isEmpty(s) == TRUE) {
return NULL;
}
return s->data[s->top];
}

Boolean stack_isEmpty(const Stack *s) {
if (s == NULL) {
return TRUE;
}
if (s->top == -1) {
return TRUE;
}
return FALSE;
}

/**
* @brief This function returns the size of the stack.
*
* Time complexity: O(1).
* @param s A pointer to the stack.
* @return the size
*/
size_t stack_size (const Stack *s);
/**
* @brief This function writes the elements of the stack to the
stream.
* @param fp A pointer to the stream
* @param s A pointer to the element to the stack
* @return Upon successful return, these function returns the number
of characters writted.
* The function returns a negative value if there was a problem
writing to the file.
* */
int stack_print(FILE* fp, const Stack *s, P_stack_ele_print f){

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
