#include <mpi.h>
#include <bits/stdc++.h>

int main() {
    MPI_Init(0, NULL);

    int size, rank, len;
    MPI_Group grp;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_group(MPI_COMM_WORLD, &grp);
    MPI_Get_processor_name(processor_name, &len);

    printf("Hello world printed by processor %s having rank %d out of %d processors and belongs to %d communicator group\n", processor_name, rank, size, grp);
    MPI_Finalize();
}
