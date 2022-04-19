#include "queue.h"
#include "sorted_queue.h"
#include "list.h"
#include "point.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*--------------------------------------------------------------------------*/
int int_print(FILE *f, const void *x)
{
  int *z = (int *)x;
  return fprintf(f, "%d ", *z);
}

int int_cmp(const void *c1, const void *c2)
{
  if (!c1 || !c2)
    return INT_MIN;
  return (*(int *)c1 - *(int *)c2);
}

/*--------------------------------------------------------------------------*/
int str_print(FILE *f, const void *x)
{
  char *z = (char *)x;
  return fprintf(f, "%s ", z);
}

int string_cmp(const void *s1, const void *s2)
{
  return strcmp((char *)s1, (char *)s2);
}

/*----------------------------------------------------------*/
void run_tests_int() {
    int i1[] = {4, 5, 12, 21, 29, 35, 40, 42, 48};
    int tam = 9, i = 0, num = 24;
    Status st = OK;
    Queue *q;

    q = queue_new();
    if (!q) return;

    for (i = 0; i < tam && st == OK; i++) {
        st = queue_push(q, &i1[i]);
    }
 
    if (st == ERROR) {
        fprintf(stdout, "Error");
        return;
    }
    
    queue_print(stdout, q, int_print);

    squeue_push(q, &num, int_cmp);

    fprintf(stdout, "\n");

    queue_print(stdout, q, int_print);

    queue_free(q);
}

int main() {
    run_tests_int();
    return EXIT_SUCCESS;
}