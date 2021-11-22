using namespace std;
#include <iostream>
#include <stdlib.h>
#include <math.h>

__global__ void
matrixMultiplication(double *a, double *b, double *c, int n)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.x * blockDim.y + threadIdx.y;
    if (row < n && col < n)
        for (int i = 0; i < n; i++)
            c[row * n + col] += a[row * n + i] * b[i * n + col];
}

int main()
{
    // Size of vectors
    cout << "Enter dimension of matrix:\n";
    int n;
    cin >> n;
    size_t size = n * n * sizeof(double);
    double *ha, *hb, *hc;
    double *da, *db, *dc;

    ha = (double *)malloc(size);
    hb = (double *)malloc(size);
    hc = (double *)malloc(size);

    cudaMalloc(&da, size);
    cudaMalloc(&db, size);
    cudaMalloc(&dc, size);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ha[i * n + j] = rand() % 100;
            hb[i * n + j] = rand() % 100;
        }
    }

    cudaMemcpy(da, ha, size, cudaMemcpyHostToDevice);
    cudaMemcpy(db, hb, size, cudaMemcpyHostToDevice);

    dim3 blockDim(16, 16), gridDim(ceil((float)n / blockDim.x), ceil((float)n / blockDim.y));
    matrixMultiplication<<<gridDim, blockDim>>>(da, db, dc, n);

    cudaMemcpy(hc, dc, size, cudaMemcpyDeviceToHost);

    cout << "\nMatrix A is:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << ha[i * n + j] << " ";
        }
        cout << "\n";
    }
    cout << "\nMatrix B is:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << hb[i * n + j] << " ";
        }
        cout << "\n";
    }
    cout << "\nResult matrix after multiplication is:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << hc[i * n + j] << " ";
        }
        cout << "\n";
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
