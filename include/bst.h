/**
 * bst.h - Header file for libbst.
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

#ifndef BST_H
#define BST_H

#include <stddef.h>             // for size_t
#include <stdbool.h>            // for bool type

// Enum for comparison functions
typedef enum result {
    LESSER = -1,
    EQUAL = 0,
    GREATER = 1
} result;

// Node comparison function definition
typedef result (*comparator)(const void *, const void *);

// Free function definition
typedef void (*free_func)(void *);

// Display function definition
typedef void (*display_func)(void *);

// Binary search tree node
typedef struct bst_node {
    void *data;
    struct bst_node *left;
    struct bst_node *right;
    size_t height;
} bst_node;

// Type agnostic functions
bst_node *bst_new_node(size_t, void *);
bst_node *bst_rotate_left(bst_node *);
bst_node *bst_rotate_right(bst_node *);
bst_node *bst_insert(bst_node *, size_t, void *, comparator);
bst_node *bst_remove_node(bst_node *, void *, comparator, free_func);
bst_node* bst_lookup(bst_node *, void *, comparator);
size_t bst_height(bst_node *);
size_t bst_size(bst_node *);
size_t bst_max_depth(bst_node *);
void bst_delete_tree(bst_node *, free_func, display_func);
bst_node *bst_min_value_node(bst_node *);
bst_node *bst_max_value_node(bst_node *);
bool bst_is_bst(bst_node *, comparator);
void bst_traverse_inorder(bst_node *, display_func);
void bst_traverse_postorder(bst_node *, display_func);
void bst_traverse_preorder(bst_node *, display_func);

// Int specific functions
result compare_int(const void *, const void *);
void print_int(void *);
void print_rm_int(void *);

// String specific functions
result compare_str(const void *, const void *);
void print_str(void *);
void print_rm_str(void *);

#endif
