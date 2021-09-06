#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;
duration<double> time_span;
high_resolution_clock::time_point Start, End;


int main() {
    int n = 1000, chunk_size = 5, time_taken1 = 0, time_taken2 = 0;
    vector<int> A(n), B(n), C(n);
    iota(begin(A), end(A), 1);
    iota(begin(B), end(B), 1000);

    // Q.3.i : static scheduling
    Start = high_resolution_clock::now();
    #pragma omp parallel for schedule(static, chunk_size) num_threads(10)
    for(int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
        printf("Thread: %d is processing element-%d\n", omp_get_thread_num(), i);
    }
    End = high_resolution_clock::now();
    time_taken1 = duration_cast<milliseconds>(End - Start).count();

    /* uncomment to print result
    cout<<"\ni\tA[i] + \tB[i] = \tC[i]\n";
    for(int i = 0; i < n; i++) {
        cout<<i<<"\t"<<A[i]<<"\t"<<B[i]<<"\t"<<C[i]<<"\n";
    }
    */
   cout<<"\n\n";
    iota(begin(A), end(A), 1);
    iota(begin(B), end(B), 1000);

   // Q.3.ii : dynamic scheduling
   Start = high_resolution_clock::now();
   #pragma omp parallel for schedule(static, 1) num_threads(10)
    for(int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
        printf("Thread: %d is processing element-%d\n", omp_get_thread_num(), i);
    }
    End = high_resolution_clock::now();
    time_taken2 = duration_cast<milliseconds>(End - Start).count();

    
    /* uncomment to print result
    cout<<"\ni\tA[i] + \tB[i] = \tC[i]\n";
    for(int i = 0; i < n; i++) {
        cout<<i<<"\t"<<A[i]<<"\t"<<B[i]<<"\t"<<C[i]<<"\n";
    }
    */

    printf("\nTotal time taken by static scheduling with chunk size: %d = %dms\n", chunk_size, time_taken1);
    printf("\nTotal time taken by dynamic scheduling with chunk size: %d = %dms\n", chunk_size, time_taken2);
}
