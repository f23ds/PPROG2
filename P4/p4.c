#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "bstree.h"
#include "point.h"

/* START [_BSTNode] */
typedef struct _BSTNode
{
    void *info;
    struct _BSTNode *left;
    struct _BSTNode *right;
    struct _BSTNode *parent;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree
{
    BSTNode *root;
    P_tree_ele_print print_ele;
    P_tree_ele_cmp cmp_ele;
};
/* END [_BSTree] */

BSTree *tree_read_points_from_file(FILE *pf);

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

int main(int argc, char *argv[])
{
    BSTree *tree;
    BSTNode n[7];
    void *min, *max;
    int nums[7] = {1, 2, 3, 4, 5, 6, 7};

    /* Inicializamos los nodos */
    for (int i = 0; i < 7; i++)
    {
        n[i].info = nums + 1;
    }

    /* Asignamos las relaciones entre ellos */
    n[3].left = &n[1];
    n[3].right = &n[5];

    n[1].left = &n[0];
    n[1].right = &n[2];

    n[0].left = n[0].right = NULL;

    n[2].left = n[2].right = NULL;

    n[5].left = &n[4];
    n[5].right = &n[6];

    n[4].left = n[4].right = NULL;

    n[6].left = n[6].right = NULL;

    /* TESTS: */
    tree = tree_init(int_print, int_cmp);
    tree->root = &n[3];

    min = tree_find_min(tree);
    max = tree_find_max(tree);

    if (!min || !max)
        return 1;

    int_print(stdout, min);
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
