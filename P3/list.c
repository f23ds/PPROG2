#include "list.h"
#include "types.h"
#include "limits.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node Node;
    
struct _Node
{
    void *info;
    struct _Node *next;
};

struct _List
{
    Node *first;
    Node *last;
    int size;
};

Node *node_new(const void *e)
{
    Node *pn = NULL;

    pn = (Node *)malloc(sizeof(Node));
    if (pn == NULL)
        return NULL;

    pn->info = (void *)e;
    pn->next = NULL;

    return pn;
}

List *list_new()
{
    List *pl = NULL;

    pl = (List *)malloc(sizeof(List));
    if (pl == NULL)
        return NULL;

    pl->first = NULL;
    pl->last = NULL;
    pl->size = 0;

    return pl;
}

Bool list_isEmpty(const List *pl)
{
    if (pl == NULL)
        return TRUE;

    if (pl->size == 0)
        return TRUE;

    return FALSE;
}

Status list_pushFront(List *pl, const void *e)
{
    Node *pn = NULL;

    if (pl == NULL || e == NULL)
        return ERROR;

    /* Guardamos el nodo nuevo que queremos introducir en la lista */
    pn = node_new(e);
    if (pn == NULL)
        return ERROR;

    pn->next = pl->first;
    pl->first = pn;
    
    if (list_size(pl) == 0) {
        pl->last = pn;
    }

    pl->size++;

    return OK;
}

Status list_pushBack(List *pl, const void *e)
{
    Node *pn = NULL;

    if (pl == NULL || e == NULL)
        return ERROR;

    pn = node_new(e);

    if (list_size(pl) == 0)
    {
        pn->next = pl->first;
        pl->first = pn;
        pl->last = pn;
        pl->size++;
        return OK;
    }

    pn->next = pl->last->next;
    pl->last->next = pn;
    pl->last = pn;
    pl->size++;

    return OK;
}

void *list_popFront(List *pl)
{
    Node *pn = NULL;
    void *e = NULL;

    if (pl == NULL || list_isEmpty(pl) == TRUE)
        return NULL;

    pn = pl->first;
    e = pn->info;
    pl->first = pn->next;
    pl->size--;

    free(pn);
    return e;
}

void *list_popBack(List *pl)
{
    Node *pn = NULL;
    void *e = NULL;

    if (pl == NULL || list_isEmpty(pl) == TRUE)
        return NULL;

    e = pl->last->info;
    free(pl->last);
    pl->last = NULL;
    pl->size--;

    free(pn);
    return e;
}

void *list_getFront(List *pl)
{
    if (pl == NULL)
        return NULL;

    return pl->first->info;
}

void *list_getBack(List *pl)
{
    if (pl == NULL)
        return NULL;

    return pl->last->info;
}

void list_free(List *pl)
{
    while (pl->size != 0)
    {
        list_popFront(pl);
    }

    free(pl);
}

int list_size(const List *pl)
{
    if (pl == NULL)
        return -1;

    return pl->size;
}

int list_print(FILE *fp, const List *pl, p_list_ele_print f)
{
    Node *pn = NULL;
    int num = 0, print = 0;
    size_t size = 0;

    if (fp == NULL || pl == NULL || f == NULL)
        return INT_MIN;

    size = list_size(pl);

    pn = pl->first;
    while (num < size)
    {
        print += f(fp, pn->info);
        pn = pn->next;
        num++;
    }

    fprintf(stdout, "\n");
    return print;
}