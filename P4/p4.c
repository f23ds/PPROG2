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

Status test(FILE *f, FILE *salida, P_tree_ele_print print_ele, P_tree_ele_cmp cmp_ele)
{
    BSTree *tree = NULL;
    long i, n, x, y;
    Point **p;
    char s;

    fscanf(f, "%ld", &n);
    if (n < 0)
    {
        fprintf(salida, "El número no es correcto.");
        return ERROR;
    }

    /* Reservamos memoria para el array de puntos */
    //TODO:

    tree = tree_init(print_ele, cmp_ele);

    if (tree == NULL)
    {
        fprintf(salida, "Error en la reserva de memoria del árbol.\n");
        return ERROR;
    }

    fprintf(salida, "Creando árbol...\n");
    for (i = 0; i < n; i++)
    {

        fscanf(f, "%ld %ld %c", &x, &y, &s);
        p = point_new(x, y, BARRIER);

        if (!p)
            return -1;

        if (tree_insert(tree, p) == ERROR)
        {
            tree_destroy(tree);
            return ERROR;
        }
    }

    fprintf(stdout, "Árbol creado con éxito.\n");
    fprintf(stdout, "Tamaño árbol: %ld\n", n);

    fprintf(stdout, "Elemento mínimo del árbol: ");
    print_ele(stdout, tree_find_min(tree));

    fprintf(stdout, "Elemento máximo del árbol: ");
    print_ele(stdout, tree_find_max(tree));

    fprintf(stdout, "In order:\n");
    tree_inOrder(stdout, tree);
    fprintf(stdout, "\n");

    tree_destroy(tree);
    return OK;
}

int main(int argc, char **argv)
{
    FILE *pf;
    Status st = OK;

    /* Comprobamos que hay el número correcto de argumentos en la command line */
    if (argc != 2)
    {
        printf("Error en la ejecución. Debe ser del tipo: './p4 tree_example.txt'\n");
        return -1;
    }

    /* Abrimos el archivo cuyo nombre es el segundo argumentos de la command line */
    pf = fopen(argv[1], "r");

    if (!pf)
        return -1;

    st = test(pf, stdout, point_print, point_cmpEuDistance);

    if (st == ERROR)
    {
        fprintf(stdout, "Error en la ejecución del programa.");
        return -1;
    }

    return 1;
}
