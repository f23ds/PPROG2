#include "sorted_queue.h"
#include <stdio.h>
#include <stdlib.h>

SortedQueue *squeue_new()
{
  return queue_new();
}

void squeue_free(SortedQueue *q)
{
  queue_free(q);
}

/**
 * @brief  Inserta un elemento en la cola ordenada.
 *
 * TODO: Incluye aqui el pseudocodigo del algoritmo implementado.
 * @pseudocodigo
 *
 *
 *
 *
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
  void *aux = NULL;
  int x;

  /* Comprobamos los punteros */
  if (!q || !ele || !pcmp)
    return ERROR;

  /* Si la cola está vacía insertamos el elemento */
  if (queue_isEmpty(q) == TRUE)
  {
    st = queue_push(q, ele);
    return st;
  }

  if (queue_isEmpty(q) == FALSE && pcmp(ele, queue_getBack(q)) < 0 && st == OK)
  {
    x=0;
    while (pcmp(queue_getFront(q), ele) <= 0 && queue_size(q)>x )
    {
      aux = queue_pop(q);
      st = queue_push(q, aux);
      x++;
    }
  }

  if (st == ERROR)
  {
    return ERROR;
  }

  st = queue_push(q, ele);

  if (queue_isEmpty(q) ==  FALSE && pcmp(queue_getBack(q), queue_getFront(q)) < 0 && st == OK) {
    while (pcmp(ele, queue_getFront(q)) <0) {
      aux = queue_pop(q);
      st = queue_push(q, aux);  
    }
  }

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
