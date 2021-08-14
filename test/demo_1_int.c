#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include "bst.h"
#include "errors.h"

void int_bst_test();

int main()
{
    signal(SIGSEGV, sig_seg);
    int_bst_test();
    exit(EXIT_SUCCESS);
}

void int_bst_test()
{
    size_t size = sizeof(int);
    size_t limit = 7;
    size_t i;
    int initial_tree_values[] = { 50, 30, 20, 40, 70, 60, 80 };
    bst_node *root = NULL;

    for (i = 0; i < limit; i++) {
        printf("Inserting into tree value: %d\n", initial_tree_values[i]);
        root = bst_insert(root,
                          size,
                          (int *)initial_tree_values[i],
                          compare_int);
    }

    printf("\nChecking if tree is a bst: ");
    if (bst_is_bst(root, compare_int))
        printf("Yes.\n");
    else
        printf("No.\n");

    printf("Deleting value 50\n");
    root = bst_remove_node(root, (int *)50, compare_int, NULL);

    printf("\nChecking if tree is a bst: ");
    if (bst_is_bst(root, compare_int))
        printf("Yes.\n");
    else
        printf("No.\n");

    printf("\ninorder traversal:\n");
    bst_traverse_inorder(root, print_int);
    printf("\n\npostorder traversal:\n");
    bst_traverse_postorder(root, print_int);
    printf("\n\npreorder traversal:\n");
    bst_traverse_preorder(root, print_int);
    printf("\n\nlevel order:\n");
    bst_print_level_order(root, print_int);
    printf("\n\n");
    fflush(stdout);

    printf("Searching for value 50: ");
    bst_node *temp = bst_lookup(root, (int *)50, compare_int);
    if (temp)
        printf("Found.\n\n");
    else
        printf("Not Found\n\n");

    printf("The size of the tree is %zu\n\n", bst_size(root));
    printf("Maximum depth of tree is %zu\n\n", bst_max_depth(root));

    printf("Deleting tree\n");
    bst_delete_tree(root, NULL, print_rm_int);
    printf("\n\n");
    fflush(stdout);
}
