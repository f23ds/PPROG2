#include "sorted_queue.h"
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------
SortedQueue *squeue_new()
{
  return queue_new();
}

//--------------------------------------------------------------------------
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

  /* Comprobamos los punteros */
  if (!q || !ele)
    return ERROR;

  /* Mientras el elemento sea menor que el front de la cola, lo extraemos y lo añadimos al final */
  while (pcmp(queue_getFront(q), ele) >= 0 && st == OK) {
    aux = squeue_pop(q);
    st = queue_push(q, aux);
  }

  /* Control de errores */
  if (st == ERROR) {
    squeue_free(q);
    return ERROR;
  }

  /* Ahora que hemos terminado este proceso, añadimos el elemento a la cola */
  st = queue_push(q, ele);
   
  /* Control de errores */
  if (st == ERROR) {
    squeue_free(q);
    return ERROR;
  }

  /* Mientras que el front de la cola sea mayor o igual que el elemento a insertar, lo extraemos y lo añadimos al final de la cola */
  while (pcmp(queue_getFront(q), ele) <= 0 && st == OK) {
    aux = squeue_pop(q);
    st = queue_push(q, aux);
  }

  return st;
}

//--------------------------------------------------------------------------
void *squeue_pop(SortedQueue *q)
{
  return queue_pop(q);
}

//--------------------------------------------------------------------------
void *squeue_getFront(const SortedQueue *q)
{
  return queue_getFront(q);
}

//--------------------------------------------------------------------------
void *squeue_getBack(const SortedQueue *q)
{
  return queue_getBack(q);
}

//--------------------------------------------------------------------------
Bool squeue_isEmpty(const SortedQueue *q)
{
  return queue_isEmpty(q);
}

//--------------------------------------------------------------------------
size_t squeue_size(const SortedQueue *q)
{
  return queue_size(q);
}

//--------------------------------------------------------------------------
int squeue_print(FILE *fp, const SortedQueue *q, p_queue_ele_print f)
{
  return queue_print(fp, q, f);
}
