#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void) {
 
    char greeting[MAX_STRING];
    int size, rank;
    
    /* Start the MPI environment */
    MPI_Init(NULL, NULL);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    /* If this process is not the master */
    if (rank != 0) {
        
        sprintf(greeting, "Hello from process %d of %d!",
            rank, size);
            
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, 
            MPI_COMM_WORLD);

    } else {
        
        printf("Hello from process %d of %d!\n", rank, size);
        
        for (int p = 1; p < size; p++) {
            
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, p, 
                0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                
            printf("%s\n", greeting);
            
        }
        
    }
    
    /* Close the MPI environment */
    MPI_Finalize();
    
    return 0;
 
}
