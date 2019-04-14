#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include "bst.h"
#include "errors.h"

void int_bst_test();
void str_bst_test();

int main()
{
    signal(SIGSEGV, sig_seg);
    int_bst_test();
    str_bst_test();
    exit(EXIT_SUCCESS);
}

void int_bst_test()
{
    size_t size = sizeof(int);
    size_t limit = 7;
    size_t i;
    intptr_t initial_tree_values[] = { 50, 30, 20, 40, 70, 60, 80 };
    bst_node *root = NULL;

    for (i = 0; i < limit; i++) {
        printf("Inserting into tree value: %ld\n", initial_tree_values[i]);
        root = bst_insert(root, size, (int *)initial_tree_values[i],
                          compare_int);
    }

    printf("\ninorder traversal:\n");
    bst_traverse_inorder(root, print_int);
    printf("\n\npostorder traversal:\n");
    bst_traverse_postorder(root, print_int);
    printf("\n\npreorder traversal:\n");
    bst_traverse_preorder(root, print_int);
    printf("\n\n");
    fflush(stdout);

    printf("Searching for value 50: ");
    bst_node *temp = bst_locate(root, (int *)50, compare_int);
    if (temp)
        printf("Found.\n\n");
    else
        printf("Not Found\n\n");

    bst_delete_tree(root, NULL, print_rm_int);
    printf("\n\n");
    fflush(stdout);
}

void str_bst_test()
{
    size_t size = sizeof(char *);
    size_t limit = 7;
    size_t i;
    const char *initial_tree_values[] = { "e",
                                          "c",
                                          "b",
                                          "d",
                                          "g",
                                          "f",
                                          "h" };
    bst_node *root = NULL;

    for (i = 0; i < limit; i++) {
        printf("Inserting into tree value: %s\n", initial_tree_values[i]);
        root = bst_insert(root, size, (char *)initial_tree_values[i],
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
