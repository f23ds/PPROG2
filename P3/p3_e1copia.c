#include "queue.h"
#include "sorted_queue.h"
#include "list.h"
#include "point.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TAM 4
#define ct(X) (CONSTANTS + (X))

int CONSTANTS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
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

/*--------------------------------------------------------------------------*/
void test_int(void *test[], void *sol[], pprint p)
{
    Queue *q;
    int i;

    int n = *((int *)test[-1]);

    q = queue_new();
    if (!q)
        return;

    for (i = 0; i < n; i++)
    {
        squeue_push(q, test[i], int_cmp);
    }

    print_report(q, sol, p);

    queue_free(q);
}

void run_tests_int()
{
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

int main()
{
    run_tests_int();
    return EXIT_SUCCESS;
}
