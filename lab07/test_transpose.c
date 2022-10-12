#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "transpose.h"

#define srand48(x) srand((int)(x))
#define drand48() ((double)rand()/RAND_MAX)

void benchmark(int *A, int *B, int n, int blocksize,
    void (*transpose)(int, int, int*, int*), char *description) {

    int i, j;
    printf("Testing %s: ", description);

    /* initialize A,B to random integers */
    srand48( time( NULL ) );
    // for( i = 0; i < n*n; i++ ) A[i] = drand48( );
    // for( i = 0; i < n*n; i++ ) B[i] = drand48( );
    // for( i = 0; i < n*n; i++ ) A[i] = rand( );
    // for( i = 0; i < n*n; i++ ) B[i] = rand( );
    for( i = 0; i < n*n; i++ ) A[i] = i;
    for( i = 0; i < n*n; i++ ) B[i] = i;

    /* measure performance */
    struct timeval start, end;

    gettimeofday( &start, NULL );
    transpose( n, blocksize, B, A );
    gettimeofday( &end, NULL );

    double seconds = (end.tv_sec - start.tv_sec) +
        1.0e-6 * (end.tv_usec - start.tv_usec);
    printf( "%g milliseconds\n", seconds*1e3 );

    // for( i = 0; i < n*n; i++ ) {
    //     if(i%n == 0) printf("\n");
    //     printf("%d ", A[i]);
    // }

    // for( i = 0; i < n*n; i++ ) {
    //     if(i%n == 0) printf("\n");
    //     printf("%d ", B[i]);
    // }

    /* check correctness */
    for( i = 0; i < n; i++ ) {
        for( j = 0; j < n; j++ ) {
            if( B[j+i*n] != A[i+j*n] ) {
                printf("%d\n", A[i+j*n]);
                printf("Error!!!! Transpose does not result in correct answer!!\n");
                exit( -1 );
            }
        }
    }
}

int main( int argc, char **argv ) {
    if (argc != 3) {
        printf("Usage: transpose <n> <blocksize>\nExiting.\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    int blocksize = atoi(argv[2]);

    /* allocate an n*n block of integers for the matrices */
    int *A = (int*)malloc( n*n*sizeof(int) );
    int *B = (int*)malloc( n*n*sizeof(int) );

    /* run tests */
    benchmark(A, B, n, blocksize, transpose_naive, "naive transpose");
    benchmark(A, B, n, blocksize, transpose_blocking, "transpose with blocking");

    /* release resources */
    free( A );
    free( B );
    return 0;
}
