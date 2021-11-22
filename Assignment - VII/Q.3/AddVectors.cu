using namespace std;
#include <iostream>
#include <stdlib.h>
#include <math.h>

// CUDA addition kernel
__global__ void
vectorAdd(double *a, double *b, double *c, int n)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < n)
        c[id] = a[id] + b[id];
}

int main(int argc, char *argv[])
{
    // Size of vectors
    cout << "Enter size of vectors:\n";
    int n;
    cin >> n;
    size_t size = n * sizeof(double);
    // Host input & output vectors
    double *ha, *hb, *hc;
    // Device input & output vectors
    double *da, *db, *dc;

    ha = (double *)malloc(size);
    hb = (double *)malloc(size);
    hc = (double *)malloc(size);
    cout << "Enter elements of vector-a:\n";
    for (int i = 0; i < n; i++)
        cin >> ha[i];

    cout << "Enter elements of vector-b:\n";
    for (int i = 0; i < n; i++)
        cin >> hb[i];

    cudaMalloc(&da, size);
    cudaMalloc(&db, size);
    cudaMalloc(&dc, size);

    cudaMemcpy(da, ha, size, cudaMemcpyHostToDevice);
    cudaMemcpy(db, hb, size, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256, numBlocks = (int)ceil((float)n / threadsPerBlock);
    vectorAdd<<<numBlocks, threadsPerBlock>>>(da, db, dc, n);

    cudaMemcpy(hc, dc, size, cudaMemcpyDeviceToHost);

    cout << "\nResult Vector after addition is:\n";
    for (int i = 0; i < n; i++)
    {
        cout << hc[i] << " ";
    }
    cout << "\n";

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);

    free(ha);
    free(hb);
    free(hc);

    return 0;
}
