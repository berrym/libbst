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

bst_node *bst_min_value(bst_node *node)
{
    bst_node *curr = node;

    while (curr->left)
        curr = curr->left;

    return curr;
}

bst_node *bst_remove_int_node(bst_node *root, void *data)
{
    // Base case
    if (!root)
        return root;

    if (compare_int(&data, root->data) == LESS) {
        root->left = bst_remove_int_node(root->left, data);
    } else if (compare_int(&data, root->data) == GREATER) {
        root->right = bst_remove_int_node(root->right,data);
    } else {
        if (!root->left) {
            bst_node *temp = root->right;
            free(root->data);
            root->data = NULL;
            free(root);
            root = NULL;
            return temp;
        } else if (!root->right) {
            bst_node *temp = root->left;
            free(root->data);
            root->data = NULL;
            free(root);
            root = NULL;
            return temp;
        }

        bst_node *temp = bst_min_value(root->right);
        root->data = temp->data;

        root->right = bst_remove_int_node(root->right, temp->data);
    }

    return root;
}

void bst_delete_int_tree(bst_node *root)
{
    if (!root)
        return;

    bst_delete_int_tree(root->left);
    bst_delete_int_tree(root->right);
    printf("\nDeleting node: %d", CastIntPrint root->data);
    free(root->data);
    root->data = NULL;
    free(root);
    root = NULL;
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
    if (!node)
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
