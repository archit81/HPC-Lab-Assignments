#include <mpi.h>
#include <bits/stdc++.h>

int main() {
    MPI_Init(0, NULL);

    int size, rank, len, grp;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &len);
    
    if(size != 4) {
        printf("Minimum 4 processes are required...\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int send_data, recv_data, dest, src;
    if(rank == 0) {
        send_data = 2, dest = 1;
        MPI_Send(&send_data, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        printf("\nProcess %d sends number %d to process %d\n", rank, send_data, dest);
    } 
    
    else if(rank == 1) {
        src = 0;
        MPI_Recv(&recv_data, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nProcess %d received number %d from process %d\n", rank, recv_data, src);

        send_data = recv_data*recv_data, dest = 2;
        MPI_Send(&send_data, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        printf("Process %d sends number %d to process %d\n", rank, send_data, dest);
    } 
    
    else if(rank == 2) {
        src = 1;
        MPI_Recv(&recv_data, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nProcess %d received number %d from process %d\n", rank, recv_data, src);

        send_data = recv_data*recv_data, dest = 3;
        MPI_Send(&send_data, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        printf("Process %d sends number %d to process %d\n", rank, send_data, dest);
    } 
    
    else {
        src = 2;
        MPI_Recv(&recv_data, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nProcess %d received number %d from process %d\n", rank, recv_data, src);
    }

    MPI_Finalize();
}
