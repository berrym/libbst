#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "bst.h"
#include "errors.h"

void str_bst_test();

int main()
{
    signal(SIGSEGV, sig_seg);
    str_bst_test();
    exit(EXIT_SUCCESS);
}

void str_bst_test()
{
    size_t size = sizeof(char *);
    size_t limit = 7;
    size_t i;
    const char *initial_tree_values[] = { "e", "c", "b", "d", "g", "f", "h" };
    bst_node *root = NULL;

    for (i = 0; i < limit; i++) {
        printf("Inserting into tree value: %s\n", initial_tree_values[i]);
        root = bst_insert(root,
                          size,
                          (char *)initial_tree_values[i],
                          compare_str);
    }

    printf("\ninorder traversal:\n");
    bst_traverse_inorder(root, print_str);
    printf("\n\npostorder traversal:\n");
    bst_traverse_postorder(root, print_str);
    printf("\n\npreorder traversal:\n");
    bst_traverse_preorder(root, print_str);
    printf("\n\n");
    fflush(stdout);

    bst_delete_tree(root, NULL, print_rm_str);
    printf("\n");
    fflush(stdout);
}
