/* Bibliotecas públicas */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Bibliotecas privadas */
#include "sorted_queue.h"
#include "queue.h"
#include "point.h"
#include "types.h"

/* Macros */
#define MAX_RAND 23
#define MAX_INT 10

#define ct(X) (CONSTANTS + (X)) 

int CONSTANTS[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
		    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,  
		    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,  
		    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,  
		    40, 41, 42, 43, 44, 45, 46, 47, 48, 49,  
		    50, 51, 52, 53, 54, 55, 56, 57, 58, 59,  
		    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,  
		    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,  
		    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,  
		    90, 91, 92, 93, 94, 95, 96, 97, 98, 99}; 

typedef int (*pprint)(FILE *, const void *);

/* Como la función de comparación utilizaremos la función string_cmp para que
coincida el prototipo con lo que espera squeue_push */

int string_cmp(const void *s1, const void *s2)
{
    return strcmp((char *)s1, (char *)s2);
}

int int_cmp(const void *c1, const void *c2)
{
    return (*(int *)c1 - *(int *)c2);
}

void print_report(Queue *q, void *sol[], pprint p) {
  int i;
  int n = *((int *)(sol[-1]));
  
  if (!q || !sol || !p)
    return;

  fprintf(stdout, "Expected: ");
  for (i=0; i<n; i++) (*p)(stdout, sol[i]); 
  fprintf(stdout, "\n");
  
  fprintf(stdout, "Obtained: ");
  queue_print(stdout, q, p);
}

int str_print(FILE *f, const void *x) {
  char *z = (char *) x;
  return fprintf(f, "%s ", z);
}

/* Tests para los números enteros */
Status int_tests()
{
    int nums[MAX_INT], i;
    Status st = OK;
    Queue *qi = NULL, *qf = NULL;

    /* Inicializamos el array de números a valores random */
    for (i = 0; i < MAX_INT; i++)
    {
        nums[i] = rand() % MAX_RAND;
    }

    /* Inicializamos las colas (la primera desordenada y la segunda ordenada) */
    qi = queue_new();
    qf = queue_new();

    if (!qi)
        return ERROR;

    /* Si la segunda falla, necesitamos liberar la primera */
    if (!qf)
    {
        queue_free(qi);
        return ERROR;
    }

    /* Probamos primero a rellenar una cola desordenada */
    for (i = 0; i < MAX_INT && st == OK; i++)
    {
        st = queue_push(qi, &nums[i]);
    }

    if (st == ERROR)
    {
        queue_free(qi);
        return ERROR;
    }

    /* Ahora rellenamos la cola con squeue_push */
    for (i = 0; i < MAX_INT && st == OK; i++)
    {
        st = squeue_push(qf, &nums[i], int_cmp);
    }

    if (st == ERROR)
    {
        queue_free(qi);
        queue_free(qf);
        return ERROR;
    }

    return st;
}

Status point_tests()
{
    Status st = OK;
    return st;
}

void string_tests(void *test[], void *sol[], pprint p) {
  Queue *q, *qo;
  int i;
  // Trick: Access position -1 to get the number of elements in the array
  // (see comments in run_tests_interleave)
  int n = *((int *)(test[-1]));

  // Create queue:
  q = queue_new();
  if (!q) {
    return;
  }
    
   qo = queue_new();
  if (!q) {
      queue_free(q);
    return;
  }
  
  // Insert data into queue:
  for (i=0; i<n; i++) {
    queue_push(q, test[i]);
  }

  // Interleave elements:
   /* Ahora rellenamos la cola con squeue_push */
    for (i = 0; i < n && st == OK; i++)
    {
        st = squeue_push(qf, &test[i], string_cmp);
    }
  
  // Print results:
  print_report(qf, sol, p);
  
  // Free resources:
  queue_free(q);
  queue_free(qo);
}

void run_tests_interleave() {
  // The first element in each array is the number of elements
  // The array content starts at position 1
  // This is why use pointer+1 in the calls to test_interleave
  // Note also that ct(x) is a pointer to a variable with value x
  void *t1[] = {ct(8), ct(1), ct(2), ct(3), ct(4), ct(5), ct(6), ct(7), ct(8)};
  void *s1[] = {ct(8), ct(1), ct(5), ct(2), ct(6), ct(3), ct(7), ct(4), ct(8)};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 1 (strings):\n");
  test_interleave(t1+1, s1+1, (&int_print));

  void *t2[] = {ct(7), ct(3), ct(4), ct(5), ct(6), ct(7), ct(8), ct(9)};
  void *s2[] = {ct(7), ct(3), ct(7), ct(4), ct(8), ct(5), ct(9), ct(6)};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 2 (strings):\n");
  test_interleave(t2+1, s2+1, (&int_print));

  void *t3[] = {ct(6), "A", "B", "C", "D", "E", "F"};
  void *s3[] = {ct(6), "A", "B", "C", "D", "E", "F"};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 3 (strings):\n");
  test_interleave(t3+1, s3+1, (&str_print));

  void *t4[] = {ct(5), "A", "D", "C", "L", "U"};
  void *s4[] = {ct(5), "A", "C", "D", "L", "U"};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 4 (interleave):\n");
  test_interleave(t4+1, s4+1, (&str_print));

  void *t5[] = {ct(0)};
  void *s5[] = {ct(0)};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 5 (strings):\n");
  test_interleave(t5+1, s5+1, (&str_print));
}

int main()
{
    /* Tenemos que probar la funcionalidad del TAD SortedQueue usando
    números enteros, puntos y cadenas de texto */
    int test = 0;
    Status st = OK;

    /* Vamos a hacer que el usuario pueda elegir el tipo de tests que quiere correr */
    do
    {
        printf("Tests disponibles:\n\t(1) Números enteros\n\t(2) Puntos\n\t(3) Cadenas\n");
        printf("Inserte el código: ");
        scanf("%d", &test);
        if (test < 1 || test > 3)
        {
            printf("\nERROR: Modo de uso incorrecto\n\n");
        }
    } while (test < 1 || test > 3);

    /* Diferenciamos los tests */
    if (test == 1)
    {
        st = int_tests();
    }
    else if (test == 2)
    {
        st = point_tests();
    }
    else
    {
        st = string_tests();
    }

    if (st == ERROR)
        return 1;

    return 0;
}
