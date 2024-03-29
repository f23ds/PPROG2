
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

    return _bst_inOrder_rec(tree->root, f, tree->print_ele);
}

int tree_postOrder(FILE *f, const BSTree *tree)
{
    if (!f || !tree)
        return -1;

    return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

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
        contains = _bst_tree_contains(node->right, elem, cmp_ele);
    }
    else
    {
        contains = _bst_tree_contains(node->left, elem, cmp_ele);
    }

    return contains;
}

Bool tree_contains(BSTree *tree, const void *elem)
{
    if (!tree || !elem || !tree->root)
        return FALSE;

    return _bst_tree_contains(tree->root, elem, tree->cmp_ele);
}

BSTNode *_bst_insert_rec(BSTree *tree, BSTNode *node, const void *elem, P_tree_ele_cmp cmp_ele)
{
    if (!tree || !elem || !cmp_ele)
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
        tree->root = node;
        return node;
    }

    /* CASO GENERAL: árbol no vacío -- modificar el subárbol que corresponda */
    if (cmp_ele(node->info, elem) > 0)
    {
        node->left = _bst_insert_rec(tree, node->left, elem, cmp_ele);
    }
    else
    {
        node->right = _bst_insert_rec(tree, node->right, elem, cmp_ele);
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

    st = _bst_insert_rec(tree, tree->root, elem, tree->cmp_ele);
    if (!st)
        return ERROR;

    tree->root = st;

    return OK;
}

BSTNode *_bst_remove_rec (BSTNode * pn, const void * elem, P_tree_ele_cmp cmp_ele) {
    
    int n;
    BSTNode *ret_node, *aux_node;
    
    /*Comprobamos los argumentos*/
    
    if(pn == NULL || elem == NULL || cmp_ele == NULL){
        return NULL;
    }
    
    /*Comprobamos elemento a eliminar para poder recorrer árbol*/
    
    n = cmp_ele(elem, pn->info);
    
    /*Si el elemento es menor que pn->info nos movemos hacia la derecha del árbol*/
    
    if(n < 0){
        pn->left = _bst_remove_rec(pn->left, elem, cmp_ele);
    } else if(n> 0){ /*Si el elemento es mayor que pn->info nos movemos hacia la izquierda del árbol*/
        pn->right = _bst_remove_rec(pn->right, elem, cmp_ele);
    } else{
        if( !(pn->right) && !(pn->left)){
            _bst_node_free(pn);
            return NULL;
        }
        else if(pn->right != NULL && pn->left == NULL){
            ret_node = pn->right;
            _bst_node_free(pn);
            return ret_node;
        }
        else if(pn->right == NULL && pn->left != NULL){
            ret_node = pn->left;
            _bst_node_free(pn);
            return ret_node;
        }
        else if(pn->right != NULL && pn->left != NULL){
            aux_node = _bst_find_min_rec(pn->right);
            pn->info = aux_node->info;
            pn->right = _bst_remove_rec(pn->right, aux_node->info, cmp_ele);
            return pn;
        }
    }
    return pn;
}

/**
* @brief Public function that removes an element into a Binary Search
Tree.
*
* Removes the (first) occurrence of the element received as argument.
*
* Note that it is necessary to descend the subtree to obtain the
* remove position. So this operation is logarithm with the length of
the path
* from the leaf to the root.
*
* @param tree Pointer to the Tree.
* @param elem Pointer to the element to be removed from the Tree.
*
* @return Status value OK if the removal could be done or the element
was not
* in the BST, Status value ERROR otherwise.
*/
Status tree_remove (BSTree * tree, const void * elem){
    BSTNode *st = NULL;
    
    /*Comprobamos si los argumentos son válidos*/
    
    if(!tree || !elem){
        return ERROR;
    }

    /*Llamamos a la función recursiva*/
    
    st = _bst_remove_rec(tree->root, elem, tree->cmp_ele);
    /*Establecemos nodo como raíz del árbol*/
    tree->root = st;
    return OK;
}

BSTNode * _bst_remove_rec(BSTNode * pn, const void * elem, P_tree_ele_cmp cmp_ele){
   
    BSTNode *ret, *aux_node;
    int comp;
    
    
    if( !pn || !elem || !cmp_ele){
        return NULL;
    }

    comp = cmp_ele(elem, pn->info);

    if(comp < 0){
        pn->left = _bst_remove_rec(pn->left, elem, cmp_ele);
    }

    else if(comp > 0){
        pn->right = _bst_remove_rec(pn->right, elem, cmp_ele);
    } else{ /*Ambos nodos son iguales*/
        /*CASO 1: No tiene hijos, eliminamos el nodo, no hay sustitución*/
        if(!(pn->right) && !(pn->left)){
            _bst_node_free(pn);
            return NULL;
        /*CASO 2: Tiene un hijo a la derecha, eliminamos nodo pero guardando su valor*/
        } else if(pn->right != NULL && !(pn->left)){
            ret = pn->right;
            _bst_node_free(pn);
            return ret;

        /*CASO 3: Tiene un hijo a la izquierda, eliminamos nodo pero guardando su valor*/
        } else if(!(pn->right) && pn->left != NULL){
            ret = pn->left;
            _bst_node_free(pn);
            return ret;

        /*CASO 4: Tiene dos hijos*/
        } else if( pn->right != NULL &&  pn->left != NULL){
            aux_node = _bst_find_min_rec(pn->right);
            pn->info = aux_node->info;
            pn->right = _bst_remove_rec(pn->right, aux_node->info, cmp_ele);
            return pn;
        }
    }
    return pn;
}


