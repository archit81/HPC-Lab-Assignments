using namespace std;
#include <iostream>
#include <stdlib.h>
#include <math.h>

__global__ void
fibonacci(int n, int *res)
{
    // nth fibonacci formula = [[(√5 + 1)/2] ^ n] / √5
    int threadID = threadIdx.x;
    double phi = (1 + sqrt(5.0)) / 2;
    res[threadID] = round(pow(phi, threadID) / sqrt(5.0));
}

int main()
{
    // Size of vectors
    cout << "Enter length of fibonacci series:\n";
    int n;
    cin >> n;

    size_t size = n * sizeof(int);
    int *h_arr;
    int *d_arr;

    h_arr = (int *)malloc(size);

    cudaMalloc(&d_arr, size);

    fibonacci<<<1, n>>>(n, d_arr);

    cudaMemcpy(h_arr, d_arr, size, cudaMemcpyDeviceToHost);

    cout << "\nFibonacci Series is:\n";
    for (int i = 0; i < n; i++)
    {
        cout << h_arr[i] << " ";
    }

    cudaFree(d_arr);

    free(h_arr);

    return 0;
}
