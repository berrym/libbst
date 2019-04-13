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
bst_node* bst_search(bst_node *, void *, comparator);
void bst_delete_tree(bst_node *, free_func, display_func);
bst_node *bst_min_value(bst_node *);
bst_node *bst_max_value(bst_node *);
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
