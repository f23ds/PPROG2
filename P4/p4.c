#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"
#include "point.h"

BSTree *tree_read_points_from_file(FILE *pf);

/* EL main debe probar la implementación de las funciones find_min, find_max, insert, contain, remove */
int main(int argc, char *argv[])
{
    BSTree *tree;
    Point *min, *max;

    /* Leemos el árbol */
    if (argc < 2)
    {
        tree = tree_read_points_from_file("tree_example.txt");
    }
    else if (argc == 2)
    {
        tree = tree_read_points_from_file(argv[1]);
    }
    else
    {
        fprintf(stdout, "ERROR: el comando debe ser del tipo ./p4 o ./p4 tree_example.txt");
        return 1;
    }

    if (!tree)
        return 1;

    fprintf(stdout, "TESTS BSTREE.C");
    /* TEST FIND MIN: resultado esperado -- (1,1) */
    fprintf(stdout, "------------------------------------------------\n");
    fprintf(stdout, "TEST FIND MIN:\n");
    fprintf(stdout, "Obtained: ");
    min = (Point *) tree_find_min(tree);
    point_print(stdout, min);
    fprintf(stdout, "Expected: (1, 1)\n");

    /* TEST FIND MAX: resultado esperado -- (6, 5) */
    fprintf(stdout, "------------------------------------------------\n");
    fprintf(stdout, "TEST FIND MAX:\n");
    fprintf(stdout, "Obtained: ");
    max = (Point *) tree_find_max(tree);
    point_print(stdout, max);
    fprintf(stdout, "Expected: (6, 5)\n");

    /* TEST INSERT */


    /* TEST CONTAINS */


    /* TEST REMOVE */
    /* CASO 1: leaf */


    /* CASO 2: 1 hijo */


    /* CASO 3: 2 hijos */

    tree_destroy(t);
    return 0;
}

BSTree *tree_read_points_from_file(FILE *pf)
{
    BSTree *t;
    int nnodes = 0, i;
    Status st = OK;
    int x, y;
    char symbol;
    Point *p;

    if (!pf)
    {
        return NULL;
    }

    /* Read number of nodes */
    if (fscanf(pf, "%d\n", &nnodes) != 1)
    {
        return NULL;
    }

    /* Create tree */
    t = tree_init(point_print, point_cmpEuDistance);
    if (!t)
    {
        return NULL;
    }

    /* Read nodes */
    for (i = 0; i < nnodes && st == OK; i++)
    {
        if (fscanf(pf, "%d %d %c", &x, &y, &symbol) != 3)
        {
            return NULL;
        }
        p = point_new(x, y, symbol);
        if (!p)
        {
            tree_destroy(t);
            return NULL;
        }

        st = tree_insert(t, p);
        if (st == ERROR)
        {
            tree_destroy(t);
            point_free(p);
            return NULL;
        }
    }

    return t;
}
