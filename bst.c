#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bst.h"
#include "errors.h"

/**
 * bst_new_node:
 *      Allocate a new bst_node on the heap and return it.
 */
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

/**
 * bst_int_insert:
 *      Insert an integer value into a bst_node.
 *
 *      1) If the tree is empty return a new node.
 *      2) Otherwise recur down the tree until an empty node is found
 *      and insert the new node there.
 *      3) Return unchanged node.
 */
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

/**
 * bst_min_value:
 *      Given a non-empty tree traverse down the left hand side of the
 *      tree and return the node with the minimum data value.
 */
bst_node *bst_min_value(bst_node *node)
{
    bst_node *curr = node;

    while (curr->left)
        curr = curr->left;

    return curr;
}

/**
 * bst_max_value:
 *      Given a non-empty tree traverse down the right hand side of the
 *      tree and return the node with the maximum data value.
 */
bst_node *bst_max_value(bst_node *node)
{
    bst_node *curr = node;

    while (curr->right)
        curr = curr->right;

    return curr;
}

/**
 * bst_remove_int_node:
 *      Given a bst and a data value, remove the node containing data
 *      and return the new root.
 *
 *      Cases:
 *          1) Base case, if the root node is empty, return it.
 *          2) If the data to removed is smaller than the root,
 *             it is in the left subtree.
 *          3) If the data to be removed is greater than the root,
 *             it is in the right subtree.
 *          4) Data is equal to the root, remove this node by handling
 *             the case of a node with zero or one children, or
 *             by handling the case where the node has two children.
 */
bst_node *bst_remove_int_node(bst_node *root, void *data)
{
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

/**
 * bst_delete_int_tree:
 *      Delete an entire bst by using postorder traversal.
 */
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

/**
 * bst_int_traverse_inorder:
 *      Traverse a bst inorder and print out the data in each node.
 */
void bst_int_traverse_inorder(bst_node *node)
{
    if (!node)
        return;

    bst_int_traverse_inorder(node->left);
    printf("%d ", CastIntPrint node->data);
    bst_int_traverse_inorder(node->right);
}

/**
 * bst_int_traverse_postorder:
 *      Traverse a bst postorder and print out the data in each node.
 */
void bst_int_traverse_postorder(bst_node *node)
{
    if (!node)
        return;

    bst_int_traverse_postorder(node->left);
    bst_int_traverse_postorder(node->right);
    printf("%d ", CastIntPrint node->data);
}

/**
 * bst_int_traverse_preorder:
 *      Traverse a bst preorder and print out the data in each node.
 */
void bst_int_traverse_preorder(bst_node * node)
{
    if (!node)
        return;

    printf("%d ", CastIntPrint node->data);
    bst_int_traverse_preorder(node->left);
    bst_int_traverse_preorder(node->right);
}

/**
 * compare_int:
 *      Compare two interger values for equality.
 *      Result is LESS for a < b, EQUAL for a == b, GREATER for a > b.
 */
result compare_int(const void *a, const void *b)
{
    const int ia = *(const int *)a;
    const int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}
