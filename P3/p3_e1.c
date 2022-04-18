#include "queue.h"
#include "sorted_queue.h"
#include "point.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ct(X) (CONSTANTS + (X))
#define TAM 4

int CONSTANTS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                   10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                   20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                   30};

typedef int (*pprint)(FILE *, const void *);

//--------------------------------------------------------------------------
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

//--------------------------------------------------------------------------
int str_print(FILE *f, const void *x)
{
  char *z = (char *)x;
  return fprintf(f, "%s ", z);
}

int string_cmp(const void *s1, const void *s2)
{
  return strcmp((char *)s1, (char *)s2);
}

//--------------------------------------------------------------------------

void print_report(Queue *q, void *sol[], pprint p)
{
  int i;
  int n = *((int *)(sol[-1]));

  if (!q || !sol || !p)
    return;

  fprintf(stdout, "Expected: ");
  for (i = 0; i < n; i++)
    (*p)(stdout, sol[i]);
  fprintf(stdout, "\n");

  fprintf(stdout, "Obtained: ");
  queue_print(stdout, q, p);
}

//--------------------------------------------------------------------------
void test_int(void *test[], void *sol[], pprint p)
{
  Queue *q, *qinter;
  int i;
  // Trick: Access position -1 to get the number of elements in the array
  // (see comments in run_tests_interleave)
  int n = *((int *)(test[-1])), num = 2;

  // Create queue:
  q = queue_new();
  if (!q)
  {
    return;
  }

  // Insert data into queue:
  for (i = 0; i < n; i++)
  {
    queue_push(q, test[i]);
  }

  // Arrange elements:
  squeue_push(q, num, int_cmp);

  // Print results:
  print_report(q, sol, p);

  // Free resources:
  queue_free(q);
}

//--------------------------------------------------------------------------
void test_string(void *test[], void *sol[], pprint p)
{
  Queue *q, *qinter;
  int i;
  // Trick: Access position -1 to get the number of elements in the array
  // (see comments in run_tests_interleave)
  int n = *((int *)(test[-1])), num = 2;
  char l = 'J';
  // Create queue:
  q = queue_new();
  if (!q)
  {
    return;
  }

  // Insert data into queue:
  for (i = 0; i < n; i++)
  {
    queue_push(q, test[i]);
  }

  // Arrange elements:
  squeue_push(q, l, string_cmp);

  // Print results:
  print_report(q, sol, p);

  // Free resources:
  queue_free(q);
}

//--------------------------------------------------------------------------
void test_point()
{
  Queue *q;
  Point *p[TAM], *n;
  int i;

  fprintf(stdout, "Test puntos array tamaño 4: \n");
  /* Inicializar los elementos del array p[0] y p[1]*/
  p[0] = point_new(0, 0, BARRIER);
  p[1] = point_new(0, 1, BARRIER);
  p[2] = point_new(1, 1, BARRIER);
  p[3] = point_new(1, 2, BARRIER);

  n = point_new(3, 3, BARRIER);

  // Create queue:
  q = queue_new();
  if (!q)
  {
    return;
  }

  // Insert data into queue:
  for (i = 0; i < n; i++)
  {
    queue_push(q, p[i]);
  }

  fprintf(stdout, "Cola inicial: \n");
  queue_print(stdout, q, point_print);

  // Arrange elements:
  squeue_push(q, n, point_cmpEuDistance);

  fprintf(stdout, "Cola ordenada: \n");
  queue_print(stdout, q, point_print);

  // Free resources:
  point_free(n);
  for (i = 0; i < n; i++)
  {
    point_free(p[i]);
  }
  queue_free(q);
}

//--------------------------------------------------------------------------
void run_tests_int()
{
  // The first element in each array is the number of elements
  // The array content starts at position 1
  // This is why use pointer+1 in the calls to test_interleave
  // Note also that ct(x) is a pointer to a variable with value x
  void *t1[] = {ct(7), ct(3), ct(4), ct(6), ct(8), ct(7), ct(1), ct(5)};
  void *s1[] = {ct(8), ct(1), ct(2), ct(3), ct(4), ct(5), ct(6), ct(7), ct(8)};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 1 (int):\n");
  test_int(t1 + 1, s1 + 1, (&int_print));

  void *t2[] = {ct(8), ct(12), ct(4), ct(3), ct(6), ct(5), ct(9), ct(8), ct(7)};
  void *s2[] = {ct(9), ct(2), ct(3), ct(4), ct(5), ct(6), ct(7), ct(8), ct(9), ct(12)};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 2 (int):\n");
  test_int(t2 + 1, s2 + 1, (&int_print));

  void *t3[] = {ct(0)};
  void *s3[] = {ct(0)};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 3 (int):\n");
  test_int(t3 + 1, s3 + 1, (&int_print));
}

//--------------------------------------------------------------------------
void run_tests_string()
{

  void *t3[] = {ct(6), 'A', 'C', 'D', 'B', 'H', 'M'};
  void *s3[] = {ct(7), 'A', 'B', 'C', 'D', 'H', 'J', 'M'};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 1 (string):\n");
  test_string(t3 + 1, s3 + 1, (&str_print));

  void *t4[] = {ct(4), "the", "snow", "is", "white"};
  void *s4[] = {ct(5), "is", "snow", "the", "white", 'J'};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 2 (string):\n");
  test_string(t4 + 1, s4 + 1, (&str_print));

  void *t5[] = {ct(5), 'z', 'A', 'a', 'b', 'd'};
  void *s5[] = {ct(5), 'A', 'J', 'a', 'b', 'd', 'z'};
  fprintf(stdout, "-----------------------------------------------------------\n");
  fprintf(stdout, "TEST 3 (string):\n");
  test_string(t4 + 1, s4 + 1, (&str_print));
}

//--------------------------------------------------------------------------
int main()
{
  run_tests_int();
  run_tests_string();
  test_point();
  return EXIT_SUCCESS;
}