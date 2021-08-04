/**
 * bst.c - Binary search tree routines.
 *
 * Copyright (c) 2021 Michael Berry
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "errors.h"

#define max(a, b) (a > b) ? a : b

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

    node->height = 1;           // initialize as a leaf node

    return node;
}

/**
 * Rotate a bst to the left.
 */
bst_node *bst_rotate_left(bst_node *x)
{
    bst_node *y = x->right;
    bst_node *t2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = t2;

    // Update heights
    x->height = max(bst_height(x->left), bst_height(x->right)) + 1;
    y->height = max(bst_height(y->left), bst_height(y->right)) + 1;

    return y;
}

/**
 * Rotate a bst to the right.
 */
bst_node *bst_rotate_right(bst_node *y)
{
    bst_node *x = y->left;
    bst_node *t2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = t2;

    // Update heights
    y->height = max(bst_height(y->left), bst_height(y->right)) + 1;
    x->height = max(bst_height(x->left), bst_height(x->right)) + 1;

    return x;
}

/**
 * bst_get_balance:
 *     Get the balance factor of a bst.
 */
int bst_get_balance(bst_node *root)
{
    if (!root)
        return 0;

    return bst_height(root->left) - bst_height(root->right);
}

/**
 * bst_insert:
 *      Insert a bst_node with a data value into a bst.
 *
 *      Cases for normal insertion:
 *          1) If the tree is empty return a new node.
 *          2) Otherwise recur down the tree until an empty node is found
 *             and insert the new node there.
 *          3) Return unchanged node.
 */
bst_node *bst_insert(bst_node *node, size_t size, void *data, comparator cmp)
{
    if (!node)
        return bst_new_node(size, data);

    // Perform normal insertion
    if (cmp(&data, node->data) == LESSER)
        node->left = bst_insert(node->left, size, data, cmp);
    else if (cmp(&data, node->data) == GREATER)
        node->right = bst_insert(node->right, size, data, cmp);
    else
        return node;

    // Update height of ancestor node
    node->height = max(bst_height(node->left), bst_height(node->right)) + 1;

    // Get the balance factor of this ancestor node
    int balance = bst_get_balance(node);

    // There are 4 cases if the bst is unbalanced

    // Left Left Case
    if (balance > 1 && cmp(&data, node->left->data) == LESSER)
        return bst_rotate_right(node);

    // Right Right Case
    if (balance < -1 && cmp(&data, node->right->data) == GREATER)
        return bst_rotate_left(node);

    // Left Right Case
    if (balance > 1 && cmp(&data, node->left->data) == GREATER) {
        node->left = bst_rotate_left(node->left);
        return bst_rotate_right(node);
    }

    // Right Left Case
    if (balance < -1 && cmp(&data, node->right->data) == LESSER) {
        node->right = bst_rotate_right(node->right);
        return bst_rotate_left(node);
    }

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
bst_node* bst_remove_node(bst_node* root, void *data,
                          comparator cmp, free_func freefn)
{
    bst_node *curr = root;
    bst_node *prev = NULL;

    // Find the node to be delivered, prev is it's parent
    while (curr && cmp(curr->data, &data) != EQUAL) {
        prev = curr;
        if (cmp(&data, curr->data) == LESSER)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (!curr)
        return root;

    // Node to be removed has one child
    if (!curr->left || !curr->right) {
        bst_node *new_curr;

        if (!curr->left)
            new_curr = curr->right;
        else
            new_curr = curr->left;

        // Node to be removed is root
        if (!prev)
            return new_curr;

        // Replace parent node's left or right child
        if (curr == prev->left)
            prev->left = new_curr;
        else
            prev->right = new_curr;

        // Free memory of node to be removed
        if (freefn)
            freefn(curr->data);
        else
            free(curr->data);
        free(curr);
    } else {                    // Node has two or more children
        bst_node *p = NULL;     // Parent node
        bst_node *temp = NULL;

        // Compute the inorder successor
        temp = curr->right;
        while (temp->left) {
            p = temp;
            temp = temp->left;
        }

        if (p)
            p->left = temp->right;
        else
            curr->right = temp->right;

        // Free memory of the node to be removed
        memcpy(curr->data, temp->data, sizeof(*temp->data));
        if (freefn)
            freefn(temp->data);
        else
            free(temp->data);
        free(temp);
    }

    return root;
}

/**
 * bst_lookup:
 *      Search a bst for a node containing a give value.
 *
 *      Cases:
 *          1) Empty tree, return root.
 *          2) Root node is equal to data, return root.
 *          3) Recur down correct subtree.
 */
bst_node* bst_lookup(bst_node *root, void *data, comparator cmp)
{
    if (!root || cmp(&data, root->data) == EQUAL)
       return root;

    if (cmp(&data, root->data) == LESSER)
        return bst_lookup(root->left, data, cmp);

    return bst_lookup(root->right, data, cmp);
}

/**
 * bst_height:
 *      Get the height of a tree.
 */
size_t bst_height(bst_node *root)
{
    if (!root)
        return 0;

    return root->height;
}

/**
 * bst_size:
 *      Count the number of nodes in a tree.
 */
size_t bst_size(bst_node *root)
{
    if (!root)
        return 0;

    return(bst_size(root->left) + 1 + bst_size(root->right));
}

/**
 * bst_max_depth:
 *      Calculate the number of nodes along the longest path from the
 *      root node down to the farthest leaf node.
 */
size_t bst_max_depth(bst_node *root)
{
    if (!root)
        return 0;

    size_t l_depth = bst_max_depth(root->left);
    size_t r_depth = bst_max_depth(root->right);

    if (l_depth > r_depth)
        return l_depth + 1;

    return r_depth + 1;
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
    else
        free(root->data);
    root->data = NULL;
    free(root);
    root = NULL;
}

/**
 * bst_min_value_node:
 *      Given a non-empty tree traverse down the left hand side of the
 *      tree and return the node with the minimum data value.
 */
bst_node *bst_min_value_node(bst_node *root)
{
    bst_node *curr = root;

    while (curr->left)
        curr = curr->left;

    return curr;
}

/**
 * bst_max_value_node:
 *      Given a non-empty tree traverse down the right hand side of the
 *      tree and return the node with the maximum data value.
 */
bst_node *bst_max_value_node(bst_node *root)
{
    bst_node *curr = root;

    while (curr->right)
        curr = curr->right;

    return curr;
}

/**
 * bst_is_bst:
 *      Check that a binary tree is a bst by recursively checking
 *      the left and right constraints of each node.
 */
bool bst_is_bst(bst_node *root, comparator cmp)
{
    if (!root)
        return true;

    if (root->left &&
        cmp(bst_max_value_node(root->left)->data, root->data) == GREATER)
        return false;

    if (root->right &&
        (cmp(bst_min_value_node(root->right)->data, root->data) <= EQUAL))
        return false;

    if (!bst_is_bst(root->left, cmp) || !bst_is_bst(root->right, cmp))
        return false;

    return true;
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
 *      Result is LESSER for a < b, EQUAL for a == b, GREATER for a > b.
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
 *      Result is LESSER for a < b, EQUAL for a == b, GREATER for a > b
 */
result compare_str(const void *a, const void *b)
{
    const char *ca = *(const char **)a;
    const char *cb = *(const char **)b;

    if (strcmp(ca, cb) < 0) return LESSER;
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
