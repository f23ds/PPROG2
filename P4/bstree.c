
#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"

/* START [_BSTNode] */
typedef struct _BSTNode
{
    void *info;
    struct _BSTNode *left;
    struct _BSTNode *right;
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
BSTNode *_bst_remove_rec(BSTNode *pn, const void *elem, P_tree_ele_cmp cmp_ele);

BSTNode *_bst_node_new()
{
    BSTNode *pn = NULL;

    pn = malloc(sizeof(BSTNode));
    if (!pn)
    {
        return NULL;
    }

    pn->left = pn->right = NULL;
    pn->info = NULL;
    return pn;
}

void _bst_node_free(BSTNode *pn)
{
    if (!pn)
        return;
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
BSTNode *_bst_find_min_rec(BSTNode *root)
{
    if (!root)
        return NULL;

    if (root->left == NULL)
        return root;

    return _bst_find_min_rec(root->left);
}

void *tree_find_min(BSTree *tree)
{
    BSTNode *nodo = NULL;
    if (tree == NULL)
    {
        return NULL;
    }
    if (tree_isEmpty(tree) == TRUE)
    {
        return NULL;
    }

    nodo = _bst_find_min_rec(tree->root);

    return nodo->info;
}

BSTNode *_bst_find_max_rec(BSTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->right == NULL)
    {
        return root;
    }

    return _bst_find_max_rec(root->right);
}

void *tree_find_max(BSTree *tree)
{
    BSTNode *nodo = NULL;
    if (tree == NULL)
    {
        return NULL;
    }
    if (tree_isEmpty(tree) == TRUE)
    {
        return NULL;
    }

    nodo = _bst_find_max_rec(tree->root);

    return nodo->info;
}

Bool _bst_tree_contains(BSTNode *node, const void *elem, P_tree_ele_cmp cmp_ele)
{
    Bool contains = FALSE;
    int cmp;

    if (!node || !elem || !cmp_ele)
        return FALSE;

    cmp = cmp_ele(node->info, elem);

    /* CASO BASE */
    if (cmp == 0)
    {
        return TRUE;
    }
    else if (cmp < 0)
    {
        contains = _bst_tree_contains(node->left, elem, cmp_ele);
    }
    else
    {
        contains = _bst_tree_contains(node->right, elem, cmp_ele);
    }

    return contains;
}

Bool tree_contains(BSTree *tree, const void *elem)
{
    if (!tree || !elem)
        return FALSE;

    return _bst_tree_contains(tree->root, elem, tree->cmp_ele);
}

BSTNode *_bst_insert_rec(BSTNode *node, const void *elem, P_tree_ele_cmp cmp_ele)
{
    if (!elem || !cmp_ele)
        return NULL;

    /* CASO BASE: Si el árbol está vacío, el elemento a insertar será su raíz */
    if (!node)
    {
        node = _bst_node_new();
        if (!node)
        {
            return NULL;
        }

        node->info = (void *)elem;
        return node;
    }

    /* CASO GENERAL: árbol no vacío -- modificar el subárbol que corresponda */
    if (cmp_ele(node->info, elem) > 0)
    {
        node->left = _bst_insert_rec(node->left, elem, cmp_ele);
    }
    else
    {
        node->right = _bst_insert_rec(node->right, elem, cmp_ele);
    }

    return node;
}

Status tree_insert(BSTree *tree, const void *elem)
{
    BSTNode *st = NULL;

    if (tree == NULL || elem == NULL)
    {
        return ERROR;
    }

    /* Si el árbol contiene el elemento, return OK para evitar repetición */
    if (tree_contains(tree, elem))
        return OK;

    st = _bst_insert_rec(tree->root, elem, tree->cmp_ele);
    if (!st)
        return ERROR;

    tree->root = st;

    return OK;
}
