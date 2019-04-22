/**
 * bst.h - Header file for libbst.
 *
 * Copyright (c) 2019 Michael Berry <trismegustis@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BST_H
#define BST_H

#include <stddef.h>             // for size_t
#include <stdbool.h>            // for bool type

// Enum for comparison functions
typedef enum result {
    LESS = -1,
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
} bst_node;

// Type agnostic functions
bst_node *bst_new_node(size_t, void *);
bst_node *bst_insert(bst_node *, size_t, void *, comparator);
bst_node *bst_remove_node(bst_node *, void *, comparator, free_func);
bst_node* bst_lookup(bst_node *, void *, comparator);
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
