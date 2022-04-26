#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "types.h"
#include "bstree.h"

int int_print(FILE *f, const void *x)
{
    int *z = (int *)x;
    return fprintf(f, "%d ", *z);
}

int main()
{
    BSTree *tree = NULL;
    Point *p, *q;
    Bool contains = FALSE;

    p = point_new(2, 3, BARRIER);
    q = point_new(0, 0, BARRIER);

    tree = tree_init(point_print, point_cmpEuDistance);

    if (tree_insert(tree, p) == ERROR)
    {
        tree_destroy(tree);
        point_free(p);
        return ERROR;
    }

    contains = tree_contains(tree, q);

    if (contains)
    {
        fprintf(stdout, "1");
    }
    else
    {
        fprintf(stdout, "0");
    }

    return 0;
}
