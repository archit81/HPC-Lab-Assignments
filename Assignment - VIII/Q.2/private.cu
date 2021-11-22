using namespace std;
#include <iostream>
#include <stdlib.h>
#include <math.h>

__global__ void
my_kernel(double *a, double *c, int n, int k)
{
    int id = threadIdx.x;
    double private_arr[1024];
    for (int i = 0; i < n; i++)
    {
        private_arr[i] = a[i];
    }

    c[id] = private_arr[id];
    for (int j = 1; j <= k; j++)
    {
        if (id + j < n)
            c[id] += private_arr[id + j];
        if (id - j >= 0)
            c[id] += private_arr[id - j];
    }
}

int main()
{
    // Size of vectors
    cout << "\n*******Neighbour addition using CUDA private memory:*******\n";
    int n = 10, k = 3;
    size_t size = n * sizeof(double);
    double *ha, *hc;
    double *da, *dc;

    ha = (double *)malloc(size);
    hc = (double *)malloc(size);

    cudaMalloc(&da, size);
    cudaMalloc(&dc, size);

    cout << "\nInitial Vector is:\n";
    for (int i = 0; i < n; i++)
    {
        ha[i] = rand() % 100;
        cout << ha[i] << " ";
    }

    cudaMemcpy(da, ha, size, cudaMemcpyHostToDevice);

    my_kernel<<<1, 10, n>>>(da, dc, n, k);

    cudaMemcpy(hc, dc, size, cudaMemcpyDeviceToHost);

    cout << "\nResult matrix after Neighbour addition is:\n";
    for (int i = 0; i < n; i++)
    {
        cout << hc[i] << " ";
    }
    cout << "\n";

    cudaFree(da);
    cudaFree(dc);

    free(ha);
    free(hc);

    return 0;
}
