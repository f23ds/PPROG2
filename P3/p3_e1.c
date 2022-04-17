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

//--------------------------------------------------------------------------
int int_print(FILE *f, const void *x)
{
    int *z = (int *)x;
    return fprintf(f, "%d ", *z);
}

//--------------------------------------------------------------------------
int str_print(FILE *f, const void *x)
{
    char *z = (char *)x;
    return fprintf(f, "%s ", z);
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
void test_interleave(void *test[], void *sol[], pprint p)
{
    Queue *q, *qinter;
    int i;
    // Trick: Access position -1 to get the number of elements in the array
    // (see comments in run_tests_interleave)
    int n = *((int *)(test[-1]));

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

    // Interleave elements:
    qinter = interleave(q);

    // Print results:
    print_report(qinter, sol, p);

    // Free resources:
    queue_free(q);
    queue_free(qinter);
}

//--------------------------------------------------------------------------
void test_concatenate(void *t1[], void *t2[], void *s1[], void *s2[], pprint p)
{
    Queue *q1, *q2;
    int i;
    // Trick: Access position -1 to get the number of elements in the array
    // (see comments in run_tests_concatenate)
    int n1 = *((int *)(t1[-1]));
    int n2 = *((int *)(t2[-1]));

    // Create first queue:
    q1 = queue_new();
    if (!q1)
    {
        return;
    }

    // Create second queue:
    q2 = queue_new();
    if (!q2)
    {
        queue_free(q1);
        return;
    }

    // Insert data into queue1:
    for (i = 0; i < n1; i++)
    {
        queue_push(q1, t1[i]);
    }

    // Insert data into queue2:
    for (i = 0; i < n2; i++)
    {
        queue_push(q2, t2[i]);
    }

    // Concatenate queues:
    concatenate(q1, q2);

    // Print results:
    fprintf(stdout, "(q1)\n");
    print_report(q1, s1, p);
    fprintf(stdout, "(q2)\n");
    print_report(q2, s2, p);

    // Free resources:
    queue_free(q1);
    queue_free(q2);
}

//--------------------------------------------------------------------------
void run_tests_interleave()
{
    // The first element in each array is the number of elements
    // The array content starts at position 1
    // This is why use pointer+1 in the calls to test_interleave
    // Note also that ct(x) is a pointer to a variable with value x
    void *t1[] = {ct(8), ct(1), ct(2), ct(3), ct(4), ct(5), ct(6), ct(7), ct(8)};
    void *s1[] = {ct(8), ct(1), ct(5), ct(2), ct(6), ct(3), ct(7), ct(4), ct(8)};
    fprintf(stdout, "-----------------------------------------------------------\n");
    fprintf(stdout, "TEST 1 (interleave):\n");
    test_interleave(t1 + 1, s1 + 1, (&int_print));

    void *t2[] = {ct(7), ct(3), ct(4), ct(5), ct(6), ct(7), ct(8), ct(9)};
    void *s2[] = {ct(7), ct(3), ct(7), ct(4), ct(8), ct(5), ct(9), ct(6)};
    fprintf(stdout, "-----------------------------------------------------------\n");
    fprintf(stdout, "TEST 2 (interleave):\n");
    test_interleave(t2 + 1, s2 + 1, (&int_print));

    void *t3[] = {ct(6), "AA", "BB", "CC", "DD", "EE", "FF"};
    void *s3[] = {ct(6), "AA", "DD", "BB", "EE", "CC", "FF"};
    fprintf(stdout, "-----------------------------------------------------------\n");
    fprintf(stdout, "TEST 3 (interleave):\n");
    test_interleave(t3 + 1, s3 + 1, (&str_print));

    void *t4[] = {ct(5), "I", "pasta", "pizza", "like", "and"};
    void *s4[] = {ct(5), "I", "like", "pasta", "and", "pizza"};
    fprintf(stdout, "-----------------------------------------------------------\n");
    fprintf(stdout, "TEST 4 (interleave):\n");
    test_interleave(t4 + 1, s4 + 1, (&str_print));

    void *t5[] = {ct(0)};
    void *s5[] = {ct(0)};
    fprintf(stdout, "-----------------------------------------------------------\n");
    fprintf(stdout, "TEST 5 (interleave):\n");
    test_interleave(t5 + 1, s5 + 1, (&str_print));
}

//--------------------------------------------------------------------------
void run_tests_concatenate()
{
    // The first element in each array is the number of elements
    // The array content starts at position 1
    // This is why use pointer+1 in the calls to test_concatenate
    // Note also that ct(x) is a pointer to a variable with value x
    void *ta1[] = {ct(6), ct(1), ct(2), ct(3), ct(4), ct(5), ct(6)};
    void *tb1[] = {ct(3), ct(7), ct(8), ct(9)};
    void *sa1[] = {ct(9), ct(1), ct(2), ct(3), ct(4), ct(5), ct(6), ct(7), ct(8), ct(9)};
    void *sb1[] = {ct(0)};
    fprintf(stdout, "-----------------------------------------------------------\n");
    fprintf(stdout, "TEST 1 (concatenate):\n");
    test_concatenate(ta1 + 1, tb1 + 1, sa1 + 1, sb1 + 1, (&int_print));

    void *ta2[] = {ct(2), "AA", "BB"};
    void *tb2[] = {ct(4), "CC", "DD", "EE", "FF"};
    void *sa2[] = {ct(6), "AA", "BB", "CC", "DD", "EE", "FF"};
    void *sb2[] = {ct(0)};
    fprintf(stdout, "-----------------------------------------------------------\n");
    fprintf(stdout, "TEST 2 (concatenate):\n");
    test_concatenate(ta2 + 1, tb2 + 1, sa2 + 1, sb2 + 1, (&str_print));

    void *ta3[] = {ct(6), "AA", "BB", "CC", "DD", "EE", "FF"};
    void *tb3[] = {ct(5), "HH", "II", "JJ", "KK", "LL"};
    void *sa3[] = {ct(6), "AA", "BB", "CC", "DD", "EE", "FF"};
    void *sb3[] = {ct(5), "HH", "II", "JJ", "KK", "LL"};
    fprintf(stdout, "-----------------------------------------------------------\n");
    fprintf(stdout, "TEST 3 (concatenate):\n");
    test_concatenate(ta3 + 1, tb3 + 1, sa3 + 1, sb3 + 1, (&str_print));
}

//--------------------------------------------------------------------------
int main()
{
    run_tests_interleave();
    run_tests_concatenate();
    return EXIT_SUCCESS;
}