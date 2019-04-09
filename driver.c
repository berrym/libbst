#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bst.h"

int main(void)
{
    size_t size = sizeof(int);
    size_t limit = 7;
    size_t i;
    intptr_t initial_tree_values[] = { 50, 30, 20, 40, 70, 60, 80 };
    bst_node *root = NULL;

    for (i = 0; i < limit; i++) {
        printf("Inserting into tree value: %ld\n", initial_tree_values[i]);
        root = bst_int_insert(root, size, CastInt initial_tree_values[i]);
    }

    printf("\ninorder traversal:\n");
    bst_traverse_inorder(root);
    printf("\n\npostorder traversal:\n");
    bst_traverse_postorder(root);
    printf("\n\npreorder traversal:\n");
    bst_traverse_preorder(root);
    printf("\n");
    fflush(stdout);

    bst_delete_int_tree(root);
    printf("\n");
    fflush(stdout);

    exit(EXIT_SUCCESS);
}
