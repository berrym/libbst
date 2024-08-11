/** test_2_string.c - Test of using libbst binary search trees with strings.

Copyright (c) 2024 Michael Berry

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "../include/bst.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_bst_test();

int main() {
    signal(SIGSEGV, sig_seg);
    str_bst_test();
    exit(EXIT_SUCCESS);
}

void str_bst_test() {
    size_t size = sizeof(char *);
    size_t limit = 7;
    size_t i;
    const char *initial_tree_values[] = {"hello", "cruel", "world", "I'm",
                                         "hard",  "to",    "kill!"};
    bst_node *root = NULL;

    for (i = 0; i < limit; i++) {
        printf("Inserting into tree value: %s\n", initial_tree_values[i]);
        const char *s = initial_tree_values[i];
        root = bst_insert(root, size * strlen(s), (void *)s, compare_str);
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
