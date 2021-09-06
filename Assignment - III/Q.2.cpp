/* compute matrix A multiplied by matrix B; the results are stored in matrix C */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#define N 400 /* number of rows in matrix A */
#define P 400 /* number of columns in matrix A */
#define M 400 /* number of columns in matrix B */

using namespace std::chrono;
duration<double> time_span;
high_resolution_clock::time_point Start, End;

int main() {
    omp_set_num_threads(8);
    int tid, nthreads, i, j, k;
    int a[N][P], b[P][M], c[N][M];

    long time_taken = 0;

/*** Create a parallel region explicitly scoping all variables ***/
Start = high_resolution_clock::now();
#pragma omp parallel shared(a, b, c, nthreads) private(tid, i, j, k)
{
    tid = omp_get_thread_num();
    if (tid == 0) {
        nthreads = omp_get_num_threads();
        printf("Starting matrix multiple example with %d threads\n", nthreads);
        printf("Initializing matrices...\n");
    }

    /*** Initialize matrices ***/
    #pragma omp for
    for (i = 0; i < N; i++)
        for (j = 0; j < P; j++) a[i][j] = i + j;

    #pragma omp for
    for (i = 0; i < P; i++)
        for (j = 0; j < M; j++) b[i][j] = i * j;

    #pragma omp for
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++) c[i][j] = 0;


    /*** Do matrix multiply sharing iterations on outer loop ***/
    /*** Display who does which iterations for demonstration purposes ***/

    // printf("Thread %d starting matrix multiply...\n", tid);
    #pragma omp for
    for (i = 0; i < N; i++) {
        // printf("Thread=%d did row=%d\n", tid, i);
        for (j = 0; j < M; j++)
            for (k = 0; k < P; k++) c[i][j] += a[i][k] * b[k][j];
    }
} /*** End of parallel region ***/

    End = high_resolution_clock::now();
    time_taken = duration_cast<milliseconds>(End - Start).count();
    printf("\nTotal time taken by %d threads = %dms\n", nthreads, time_taken);


    // /*** Print results ***/
    // printf("******************************************************\n");
    // printf("Result Matrix:\n");
    // for (i = 0; i < N; i++) {
    //     for (j = 0; j < M; j++) printf("%6.2f ", c[i][j]);
    //     printf("\n");
    // }
    // printf("******************************************************\n");
    // printf("Done.\n");
    // return (0);
}


