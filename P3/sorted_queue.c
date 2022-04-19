#include "sorted_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

SortedQueue *squeue_new()
{
  return queue_new();
}

void squeue_free(SortedQueue *q)
{
  queue_free(q);
}

int _int_print(FILE *f, const void *x)
{
  int *z = (int *)x;
  return fprintf(f, "%d ", *z);
}

/**
 * @brief  Inserta un elemento en la cola ordenada.
 *
 * Incluye aqui el pseudocodigo del algoritmo implementado.
 * @pseudocodigo
 *Si q o ele o pcmp son NULL
   dev error
 *queue_empty(q) = TRUE
  queue_push(ele)
  dev OK
 *Si pcmp(front,ele)<0
   mientras pcmp(back,ele)<=0 y tam(q)<x
   queue_push(queue_pop(q))
   x+1
   Si com(back,front)<0
 * mientras pcmp(back,front)<0
   queue_push(queue_pop(q))

   dev 0K
 *
 * @param q, puntero a la cola.
 * @param ele, puntero al elemento a insertar.
 * @param pcmp, puntero a la funcion de comparacion.
 *
 * @return OK si la insercion se realiza con exito, ERROR en caso contrario.
 **/
Status squeue_push(SortedQueue *q, void *ele, p_queue_ele_cmp pcmp)
{
  Status st = OK;
  void *aux = NULL, *t = NULL;
  int i = 0, size = 0;

  /* Comprobamos los punteros */
  if (!q || !ele || !pcmp)
    return ERROR;

  /* Si la cola está vacía insertamos el elemento */
  if (squeue_isEmpty(q) == TRUE)
  {
    st = queue_push(q, ele);
    return st;
  }

  /* Si la cola no está vacía: */
  size = squeue_size(q);
  aux = squeue_getFront(q);

  while (pcmp(aux, ele) <= 0 && pcmp(aux, ele) != INT_MIN && i < size && st == OK)
  {
    t = squeue_pop(q);
    st = queue_push(q, t);
    aux = squeue_getFront(q);
    i++;
  }

  if (st == ERROR)
  {
    return ERROR;
  }

  st = queue_push(q, ele);

  if (st == ERROR)
    return ERROR;

  i = 0;

  aux = squeue_getFront(q);
  while (pcmp(aux, ele) > 0 && i < size && st == OK)
  {
    t = squeue_pop(q);
    st = queue_push(q, t);
    aux = squeue_getFront(q);
    i++;
  }

  if (st == ERROR)
    return ERROR;

  return st;
}

void *squeue_pop(SortedQueue *q)
{
  return queue_pop(q);
}

void *squeue_getFront(const SortedQueue *q)
{
  return queue_getFront(q);
}

void *squeue_getBack(const SortedQueue *q)
{
  return queue_getBack(q);
}

Bool squeue_isEmpty(const SortedQueue *q)
{
  return queue_isEmpty(q);
}

size_t squeue_size(const SortedQueue *q)
{
  return queue_size(q);
}

int squeue_print(FILE *fp, const SortedQueue *q, p_queue_ele_print f)
{
  return queue_print(fp, q, f);
}
