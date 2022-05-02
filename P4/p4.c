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

void _free_points_array(Point **p, long n)
{
    /* Función para liberar los punteros a puntos reservados con malloc */
    long i;

    for (i = 0; i < n; i++)
    {
        point_free(p[i]);
    }

    free(p);
}

Status test(FILE *f, FILE *salida, P_tree_ele_print print_ele, P_tree_ele_cmp cmp_ele)
{
    BSTree *tree = NULL;
    long i, n, x, y;
    Point **p, *minSol, *maxSol, *min, *max, *ct = NULL, *cf = NULL;
    char s;
    Bool contains = FALSE;

    fscanf(f, "%ld", &n);
    if (n < 0)
    {
        fprintf(salida, "El número no es correcto.");
        return ERROR;
    }

    /* Creamos los puntos para el test de tree_find_min y tree_find_max */
    minSol = point_new(1, 1, BARRIER);
    maxSol = point_new(6, 5, BARRIER);

    /* Reservamos memoria para el array de puntos */
    p = (Point **)malloc(n * sizeof(Point *));

    /* Creamos los puntos para el test de tree_contains */
    ct = point_new(2, 2, BARRIER);
    if (!ct)
    {
        _free_points_array(p, n);
        tree_destroy(tree);
        return ERROR;
    }

    cf = point_new(23, 13, BARRIER);
    if (!cf)
    {
        _free_points_array(p, n);
        point_free(ct);
        tree_destroy(tree);
        return ERROR;
    }

    tree = tree_init(print_ele, cmp_ele);

    if (tree == NULL)
    {
        fprintf(salida, "Error en la reserva de memoria del árbol.\n");
        point_free(ct);
        point_free(cf);
        free(p);
        return ERROR;
    }

    fprintf(salida, "Creando árbol...\n");
    for (i = 0; i < n; i++)
    {

        fscanf(f, "%ld %ld %c", &x, &y, &s);
        p[i] = point_new(x, y, BARRIER);

        if (!p[i])
        {
            _free_points_array(p, n);
            return ERROR;
        }

        if (tree_insert(tree, p[i]) == ERROR)
        {
            _free_points_array(p, n);
            tree_destroy(tree);
            return ERROR;
        }
    }

    fprintf(stdout, "Árbol creado con éxito.\n");
    fprintf(stdout, "Tamaño árbol: %ld\n", n);

    fprintf(stdout, "-------------------------------------------------------\n");
    fprintf(stdout, "TEST TREE_INSERT (In order): \n");
    tree_inOrder(stdout, tree);

    fprintf(stdout, "-------------------------------------------------------\n");
    fprintf(stdout, "Elemento mínimo del árbol:\n");
    min = tree_find_min(tree);
    fprintf(stdout, "Expected: ");
    print_ele(stdout, minSol);
    fprintf(stdout, "Obtained: ");
    print_ele(stdout, min);

    fprintf(stdout, "-------------------------------------------------------\n");
    fprintf(stdout, "Elemento máximo del árbol:\n");
    max = tree_find_max(tree);
    fprintf(stdout, "Expected: ");
    print_ele(stdout, maxSol);
    fprintf(stdout, "Obtained: ");
    print_ele(stdout, max);

    fprintf(stdout, "-------------------------------------------------------\n");
    fprintf(stdout, "TEST TREE_CONTAINS: \n");
    contains = tree_contains(tree, (Point *)ct);
    // TODO: EL ERROR ESTÁ EN QUE LA RAÍZ DEL ÁRBOL ES NULA PERO NO TENGO NI IDEA DE POR QUÉ
    fprintf(stdout, "TEST 1: [(2, 2): +]\n");
    fprintf(stdout, "Expected: TRUE\n");
    if (contains == TRUE)
    {
        fprintf(stdout, "Obtained: TRUE\n");
    }
    else
    {
        fprintf(stdout, "Obtained: FALSE\n");
    }

    contains = tree_contains(tree, (Point *)cf);
    fprintf(stdout, "TEST 1: [(23, 13): +]\n");
    fprintf(stdout, "Expected: FALSE\n");
    if (contains == TRUE)
    {
        fprintf(stdout, "Obtained: TRUE\n");
    }
    else
    {
        fprintf(stdout, "Obtained: FALSE\n");
    }

    /* Liberamos los recursos utilizados */
    _free_points_array(p, n);
    point_free(minSol);
    point_free(maxSol);
    point_free(ct);
    point_free(cf);
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

    fclose(pf);
    return 1;
}
