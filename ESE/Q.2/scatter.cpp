#include <mpi.h>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    MPI_Init(0, 0);

    int size, rank, n = 10, per_process;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    per_process = ceil((float)n / size);

    int *rand_arr;
    if (rank == 0)
    {
        rand_arr = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            rand_arr[i] = rand();
        cout << "Array generated at rank 0 is: [ ";
        for (int i = 0; i < n; i++)
            cout << rand_arr[i] << " ";
        cout << " ]\n";
    }

    int *tmp_arr = (int *)malloc(per_process * sizeof(int));
    // Scatter the random numbers to all processes
    MPI_Scatter(rand_arr, per_process, MPI_INT, tmp_arr, per_process, MPI_INT, 0, MPI_COMM_WORLD);

    cout << "The sub-array received by process with rank " << rank << " is: [ ";
    for (int i = 0; i < per_process; i++)
    {
        cout << tmp_arr[i] << " ";
    }
    cout << " ]\n";

    MPI_Finalize();
}
