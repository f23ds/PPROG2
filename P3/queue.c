#include "queue.h"
#include "list.h"
#include "types.h"
#include "limits.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE 100

struct _Queue
{
    List *pl;
};

Queue *queue_new()
{
    Queue *q = NULL;

    q = (Queue *)malloc(sizeof(Queue));
    if (!q)
        return NULL;

    q->pl = list_new();
    if (q->pl == NULL)
    {
        free(q);
        return NULL;
    }

    return q;
}

void queue_free(Queue *q)
{
    list_free(q->pl);
    free(q);
}

Bool queue_isEmpty(const Queue *q)
{
    if (q == NULL)
        return TRUE;

    return list_isEmpty(q->pl);
}

Bool _queue_isFUll(const Queue *q)
{
    if (q == NULL)
        return TRUE;

    return FALSE; /* Siempre devuelve FALSE porque la cola nunca está llena */
}

Status queue_push(Queue *q, void *ele)
{
    if (q == NULL || ele == NULL)
        return ERROR;

    return list_pushBack(q->pl, ele);
}

void *queue_pop(Queue *q)
{

    if (q == NULL)
        return NULL;

    return list_popFront(q->pl);
}

void *queue_getFront(const Queue *q)
{
    if (q == NULL)
        return NULL;

    return list_getFront(q->pl);
}

void *queue_getBack(const Queue *q)
{
    if (q == NULL)
        return NULL;

    return list_getBack(q->pl);
}

size_t queue_size(const Queue *q)
{
    if (!q)
        return -1;

    return list_size(q->pl);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f)
{
    if (fp == NULL || q == NULL)
        return INT_MIN;

    return list_print(fp, q->pl, f);
}