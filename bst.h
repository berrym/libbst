#ifndef BST_H
#define BST_H

#include <stddef.h>
#include <stdbool.h>

#define CastInt (int *)
#define CastIntPrint *(int *)

typedef enum result {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1
} result;

typedef result (*node_comaprator)(const void *, const void *);

typedef struct bst_node {
    void *data;
    struct bst_node *left;
    struct bst_node *right;
} bst_node;

bst_node *bst_new_node(size_t, void *);
bst_node *bst_int_insert(bst_node *, size_t, void *);
void bst_traverse_inorder(bst_node *);
void bst_traverse_postorder(bst_node *);
void bst_traverse_preorder(bst_node *);

result compare_int(const void *, const void *);

#endif
