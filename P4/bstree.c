#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"

#define MAX_BUFFER 64 // Maximum file line size

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

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new()
{
    BSTNode *pn = NULL;

    pn = malloc(sizeof(BSTNode));
    if (!pn)
    {
        return NULL;
    }

    pn->left = pn->right = NULL;
    pn->parent = NULL;
    pn->info = NULL;
    return pn;
}

void _bst_node_free(BSTNode *pn)
{
    if (!pn)
        return;
    if (pn->info)
        free(pn->info);
    free(pn);
}

void _bst_node_free_rec(BSTNode *pn)
{
    if (!pn)
        return;

    _bst_node_free_rec(pn->left);
    _bst_node_free_rec(pn->right);
    _bst_node_free(pn);

    return;
}

int _bst_depth_rec(BSTNode *pn)
{
    int depthR, depthL;
    if (!pn)
        return 0;

    depthL = _bst_depth_rec(pn->left);
    depthR = _bst_depth_rec(pn->right);

    if (depthR > depthL)
    {
        return depthR + 1;
    }
    else
    {
        return depthL + 1;
    }
}

int _bst_size_rec(BSTNode *pn)
{
    int count = 0;
    if (!pn)
        return count;

    count += _bst_size_rec(pn->left);
    count += _bst_size_rec(pn->right);

    return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_tree_ele_print print_ele)
{
    int count = 0;
    if (!pn)
        return count;

    count += print_ele(pf, pn->info);
    count += _bst_preOrder_rec(pn->left, pf, print_ele);
    count += _bst_preOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_tree_ele_print print_ele)
{
    int count = 0;
    if (!pn)
        return count;

    count += _bst_inOrder_rec(pn->left, pf, print_ele);
    count += print_ele(pf, pn->info);
    count += _bst_inOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_tree_ele_print print_ele)
{
    int count = 0;
    if (!pn)
        return count;

    count += _bst_postOrder_rec(pn->left, pf, print_ele);
    count += _bst_postOrder_rec(pn->right, pf, print_ele);
    count += print_ele(pf, pn->info);

    return count;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_tree_ele_print print_ele, P_tree_ele_cmp cmp_ele)
{
    if (!print_ele || !cmp_ele)
        return NULL;

    BSTree *tree = malloc(sizeof(BSTree));
    if (!tree)
    {
        return NULL;
    }

    tree->root = NULL;
    tree->print_ele = print_ele;
    tree->cmp_ele = cmp_ele;

    return tree;
}

void tree_destroy(BSTree *tree)
{
    if (!tree)
        return;

    _bst_node_free_rec(tree->root);

    free(tree);
    return;
}

Bool tree_isEmpty(const BSTree *tree)
{
    if (!tree || !tree->root)
        return TRUE;
    return FALSE;
}

int tree_depth(const BSTree *tree)
{
    if (!tree)
        return -1;

    return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree)
{
    if (!tree)
        return -1;

    return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree)
{
    if (!f || !tree)
        return -1;

    return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree)
{
    if (!f || !tree)
        return -1;

    return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree)
{
    if (!f || !tree)
        return -1;

    return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

/**** TODO: find_min, find_max, insert, contains, remove ****/
void *tree_find_min(BSTree *tree)
{
    if (!tree)
        return NULL;

    if (tree->root->left == NULL)
    {
        return tree->root->info;
    }

    /* Buscamos en el subárbol izquierdo */
    return tree_find_min(tree->root->left);
}

void *tree_find_max(BSTree *tree)
{
    if (!tree)
        return NULL;

    if (tree->root->right == NULL)
    {
        return tree->root->info;
    }

    /* Buscamos en el subárbol derecho */
    return tree_find_max(tree->root->right);
}

Bool tree_contains(BSTree *tree, const void *elem)
{
    if (!tree || !elem)
        return FALSE;

    /* Comprobamos la raíz (caso base)*/
    if (tree->cmp_ele(tree->root->info, elem) == 0)
    {
        return TRUE;
    }
    else if (tree->cmp_ele(tree->root->info, elem) < 0)
    {
        tree_contains(tree->root->right, elem);
    }
    else
    {
        tree_contains(tree->root->left, elem);
    }

    return FALSE;
}

Status tree_insert(BSTree *tree, const void *elem)
{
    if (!tree || !elem)
        return ERROR;

    /* Si el árbol está vacío, asignamos la información del elemento a la raíz */
    if (tree_isEmpty(tree) == TRUE)
    {
        tree->root = _bst_node_new();
        if (!tree->root)
            return ERROR;
        tree->root->info = elem;
        return OK;
    }

    /* Si el árbol ya contiene este elemento, return OK */
    if (tree_contains(tree, elem) == TRUE)
        return OK;

    /* Si el elemento es menor que la raíz, nos desplazaremos a la izquierda */
    if (tree->cmp_ele(tree->root->info, elem) < 0)
    {
        tree_insert(tree->root->left, elem);
    }
    else
    {
        tree_insert(tree->root->right, elem);
    }

    return OK;
}

BSTNode *_bst_search(BSTree *tree, const void *elem)
{
    if (!tree || !elem || !tree->root)
        return NULL;

    if (tree->cmp_ele(tree->root->info, elem) == 0)
    {
        return tree->root;
    }
    else if (tree->cmp_ele(tree->root->info, elem) < 0)
    {
        return _bst_search(tree->root->left, elem);
    }

    return _bst_search(tree->root->right, elem);
}

Status _bst_replace_root(BSTree *tree)
{
    /* Si tree es NULL o el árbol está vacío no hay nada que reemplazar */
    if (!tree || !tree->root)
        return OK;

    /* Existen tres casos: */

    /* CASO 1: La raíz de tree es hoja */
    if (!tree->root->left && !tree->root->right) 
    {
        tree->root->parent = NULL;
        _bst_node_free(tree->root);
    }
    /* CASO 2: La raíz de tree tiene 2 hijos */
    else if (tree->root->left && tree->root->right) {
        /* Buscamos su sucesor en orden */
        // TODO: 
    } else {

    }
}

Status tree_remove(BSTree *tree, const void *elem)
{
    BSTNode *t;

    if (!tree || !elem || !tree->root)
        return ERROR;

    if (tree_contains(tree, elem) == FALSE)
        return OK;

    /* Buscamos el nodo con elemento elem */
    t = _bst_search(tree, elem);
    if (!t)
        return OK;

    return _bst_replace_root(t);
}