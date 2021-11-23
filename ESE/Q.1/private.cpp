// private clause program Demo
#include <omp.h>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 10, no_threads = 5, i, addNum = 10;
    vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

#pragma omp parallel for num_threads(no_threads) private(addNum)
    for (i = 0; i < n; i++)
    {
        printf("Thread: %d takes i=%d  and  addNum=%d  &  adds them together to get result = %d\n", omp_get_thread_num(), i, addNum, A[i] + addNum);
        A[i] = A[i] + addNum;
        addNum++;
    }

    cout << "\nResult A[i] = \t";
    for (i = 0; i < n; i++)
    {
        cout << A[i] << "\t";
    }
    cout << "\n";
}
