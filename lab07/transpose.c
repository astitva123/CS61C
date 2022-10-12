#include "transpose.h"
#include <stdio.h>

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // YOUR CODE HERE
    for(int i = 0;i<n*n;i+=blocksize*n)
    {

        for(int j = i; j<i+n ;j+=blocksize)
        {
            int j_transpose = j/n + n*(j%n);
            int h = min(blocksize, n-i%n), w = min(blocksize, n-i/n);
            // int h = blocksize, w = blocksize;
            for (int x = 0; x < h; x++) {
                for (int y = 0; y < w; y++) {
                    dst[j_transpose + y + x * n] = src[j + x + y * n];
                }
            }
            // dst[j_transpose] = src[j];

        }
    }

}
