/** demo_4_primes.c - Demo calculating prime numbers.

Copyright (c) 2021 Michael Berry

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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include "bst.h"
#include "errors.h"

#define MAXGEN 100

void primes_to_limit(size_t);

/**
 * main:
 *      Main function, program entry point.
 */
int main(int argc, char **argv)
{
    char *line = NULL, *endptr = NULL;
    size_t len;
    ssize_t nread;

    // Set up some signal handlers
    signal(SIGINT, sig_int);
    signal(SIGSEGV, sig_seg);

    printf("Prime Numbers\nHow many numbers do you want? %d is max: ", MAXGEN);
    if ((nread = getline(&line, &len, stdin)) == -1)
        error_syscall("getline failed");

    errno = 0;
    size_t n = strtol(line, &endptr, 10);

    if (errno != 0)
        error_syscall("strtol failed");

    if (line == endptr) {
        fprintf(stderr, "No digitis were found\n\n");
        exit(EXIT_FAILURE);
    }

    if (n <= MAXGEN) {
        primes_to_limit(n);
    } else {
        printf("Number to large.\n");
        exit(EXIT_SUCCESS);
    }

    free(line);

    return 0;
}

/**
 * primes_to_limit:
 *      Calculate prime numbers up to limit.
 */
void primes_to_limit(size_t limit)
{
    bst_node *primes = NULL;

    intptr_t p = 3, c;

    for (size_t count = 2 ; count <= limit ;  ) {
        for (c = 2 ; c <= p - 1 ; c++)
            if (p % c == 0 )
                break;
        
        if (c == p) {
            primes = bst_insert(primes, sizeof(int), (int *)p, compare_int);
            count++;
        }

        p++;
    }

    bst_traverse_inorder(primes, print_int);
    printf("\n");
    fflush(stdout);

    bst_delete_tree(primes, NULL, NULL);
}
