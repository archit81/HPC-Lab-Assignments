// nowait clause demonstration
#include <omp.h> 
#include <bits/stdc++.h>
using namespace std;

int main()
{	
    int n = 10, i;
    vector<int> A = {1,2,3,4,5, 6, 7, 8, 9, 10}, B = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

	#pragma omp parallel num_threads(5) 
    {
        #pragma omp for nowait
        for(int i = 0; i < n; i++) {
            A[i] = A[i] * A[i];
            printf("Thread: %d is processing element-%d of vector A\n", omp_get_thread_num(), i);
        }
        #pragma omp for
        for(int i = 0; i < n; i++) {
            printf("Thread: %d is processing element-%d of vector B\n", omp_get_thread_num(), i);
            B[i] = B[i] * B[i];
        }
    }
}
