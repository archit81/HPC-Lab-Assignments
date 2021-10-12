#include <mpi.h>
#include <bits/stdc++.h>

#define N 1000

int main() {
    MPI_Init(NULL, NULL);

    int size, rank, len, arr[N];
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank == 0) {
        for(int i = 0; i < N; i++) arr[i] = i;

        int start, end, cur_segment_size, per_process;
        per_process = N / size-1;
        for(int i = 1; i < size; i++) {
            start = (i) * per_process, end = (i+1) * per_process - 1;
            if(i == size-1) end = N-1;
            cur_segment_size = end - start + 1;

            MPI_Send(&cur_segment_size, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
            MPI_Send(&arr[start], cur_segment_size, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

        int total = 0, partial = 0;
        for(int i = 0; i < per_process; i++) total += arr[i];
        
        for(int i = 1; i < size; i++) {
            MPI_Recv( &partial, 1, MPI_LONG, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total += partial;
        }
         printf("The total sum of array is: %i\n", total);

    }
    else {
        int cur_segment_size, partial = 0;

        MPI_Recv(&cur_segment_size, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&arr, cur_segment_size, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        for(int i = 0; i < cur_segment_size; i++) partial += arr[i];
        
        MPI_Send(&partial, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
