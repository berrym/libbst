#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 * bst_insert:
 *      Insert a bst_node with a data value into a bst.
 *
 *      Cases:
 *          1) If the tree is empty return a new node.
 *          2) Otherwise recur down the tree until an empty node is found
 *             and insert the new node there.
 *          3) Return unchanged node.
 */
bst_node *bst_insert(bst_node *node, size_t size, void *data, comparator cmp)
{
    if (!node)
        return bst_new_node(size, data);

    if (cmp(&data, node->data) == LESS)
        node->left = bst_insert(node->left, size, data, cmp);
    else if (cmp(&data, node->data) == GREATER)
        node->right = bst_insert(node->right, size, data, cmp);

    return node;
}

/**
 * bst_remove_node:
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
bst_node *bst_remove_node(bst_node *root, void *data,
                          comparator cmp, free_func freefn)
{
    if (!root)
        return root;

    if (cmp(&data, root->data) == LESS) {
        root->left = bst_remove_node(root->left, data, cmp, freefn);
    } else if (cmp(&data, root->data) == GREATER) {
        root->right = bst_remove_node(root->right, data, cmp, freefn);
    } else {
        if (!root->left) {
            bst_node *temp = root->right;
            if (freefn)
                freefn(root->data);
            free(root->data);
            root->data = NULL;
            free(root);
            root = NULL;
            return temp;
        } else if (!root->right) {
            bst_node *temp = root->left;
            if (freefn)
                freefn(root->data);
            free(root->data);
            root->data = NULL;
            free(root);
            root = NULL;
            return temp;
        }

        bst_node *temp = bst_min_value(root->right);
        root->data = temp->data;

        root->right = bst_remove_node(root->right, temp->data, cmp, freefn);
    }

    return root;
}

/**
 * bst_locate:
 *      Serach a bst for a node containing a give value.
 *
 *      Cases:
 *          1) Empty tree, return root.
 *          2) Root node is equal to data, return root.
 *          3) Recur down correct subtree.
 */
bst_node* bst_locate(bst_node *root, void *data, comparator cmp)
{
    if (!root || cmp(&data, root->data) == EQUAL)
       return root;

    if (cmp(&data, root->data) == LESS)
        return bst_locate(root->left, data, cmp);

    return bst_locate(root->right, data, cmp);
}

/**
 * bst_delete_tree:
 *      Delete an entire bst by using postorder traversal.
 */
void bst_delete_tree(bst_node *root, free_func freefn, display_func display)
{
    if (!root)
        return;

    bst_delete_tree(root->left, freefn, display);
    bst_delete_tree(root->right, freefn, display);
    if (display)
        display(root->data);
    if (freefn)
        freefn(root->data);
    free(root->data);
    root->data = NULL;
    free(root);
    root = NULL;
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
 * bst_traverse_inorder:
 *      Traverse a bst inorder and print out the data in each node.
 */
void bst_traverse_inorder(bst_node *node, display_func display)
{
    if (!node)
        return;

    bst_traverse_inorder(node->left, display);
    display(node->data);
    bst_traverse_inorder(node->right, display);
}

/**
 * bst_traverse_postorder:
 *      Traverse a bst postorder and print out the data in each node.
 */
void bst_traverse_postorder(bst_node *node, display_func display)
{
    if (!node)
        return;

    bst_traverse_postorder(node->left, display);
    bst_traverse_postorder(node->right, display);
    display(node->data);
}

/**
 * bst_traverse_preorder:
 *      Traverse a bst preorder and print out the data in each node.
 */
void bst_traverse_preorder(bst_node * node, display_func display)
{
    if (!node)
        return;

    display(node->data);
    bst_traverse_preorder(node->left, display);
    bst_traverse_preorder(node->right, display);
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

/**
 * Display function to print out an int.
 */
void print_int(void *data)
{
    printf("%d ", *(int *)data);
}

/**
 * print_rm_int:
 *      Display function to inform when removing an int value from a bst.
 */
void print_rm_int(void *data)
{
    printf("Removing value: %d\n", *(int *)data);
}

/**
 * compare_str:
 *      Compare two strings for equality.
 *      Result is LESS for a < b, EQUAL for a == b, GREATER for a > b
 */
result compare_str(const void *a, const void *b)
{
    const char *ca = *(const char **)a;
    const char *cb = *(const char **)b;

    if (strcmp(ca, cb) < 0) return LESS;
    else if (strcmp(ca, cb) > 0) return GREATER;

    return EQUAL;
}

/**
 * print_str:
 *      Display function to print a string.
 */
void print_str(void *data)
{
    printf("%s ", *(char **)data);
}

/**
 * print_rm_str:
 *      Display function to inform when removing a string value from a bst.
 */
void print_rm_str(void *data)
{
    printf("Removing value: %s\n", *(char **)data);
}
