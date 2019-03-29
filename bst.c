#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bst.h"
#include "errors.h"

bst_node *bst_new_node(size_t size, void *data)
{
    bst_node *node = calloc(1, sizeof(bst_node));
    if (!node)
        error_syscall("Unable to allocate memory for bst_node");

    if (!(node->data = calloc(1, size)))
        error_syscall("Unable to allocate bst_node->data");

    memcpy(node->data, &data, size);
    node->left = node->right = NULL;

    return node;
}

bst_node *bst_int_insert(bst_node *node, size_t size, void *data)
{
    if (!node)
        return bst_new_node(size, data);

    if (compare_int(&data, node->data) <= EQUAL)
        node->left = bst_int_insert(node->left, size, data); 
    else
        node->right = bst_int_insert(node->right, size, data);

    return node;
}

void bst_traverse_inorder(bst_node *node)
{
    if (!node)
        return;

    bst_traverse_inorder(node->left);
    printf("%d ", CastIntPrint node->data);
    bst_traverse_inorder(node->right);
}

void bst_traverse_postorder(bst_node *node)
{
    if (node == NULL)
        return;

    bst_traverse_postorder(node->left);
    bst_traverse_postorder(node->right);
    printf("%d ", CastIntPrint node->data);
}

void bst_traverse_preorder(bst_node * node)
{
    if (!node)
        return;

    printf("%d ", CastIntPrint node->data);
    bst_traverse_preorder(node->left);
    bst_traverse_preorder(node->right);
}

result compare_int(const void *a, const void *b)
{
    const int ia = *(const int *)a;
    const int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}