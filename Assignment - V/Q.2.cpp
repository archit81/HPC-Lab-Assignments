#include <mpi.h>
#include <bits/stdc++.h>

int main() {
    MPI_Init(0, NULL);

    int size, rank, len, grp;
    MPI_Request r[4];
    MPI_Status s[4];
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int next = rank + 1;
    if(next >= size) next = 0;
    int prev = rank - 1;
    if(prev < 0) prev = size-1;


    int prev_data=0, next_data=0;

    MPI_Isend(&rank, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &r[2]);
    MPI_Isend(&rank, 1, MPI_INT, next, 1, MPI_COMM_WORLD, &r[3]);

    MPI_Irecv(&prev_data, 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &r[0]);
    MPI_Irecv(&next_data, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &r[1]);

    MPI_Waitall(4, r, s);

    printf("Process %d received data:%d from prev process-%d and data:%d from next process-%d\n", rank, prev_data, prev, next_data, next);


    MPI_Finalize();
}
