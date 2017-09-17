#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int my_rank, size;
    char tmp[256];
    char hostname[128];

    /* Initialize the infrastructure necessary for communication */
    MPI_Init(&argc, &argv);

    /* Identify this process */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Find out how many total processes are active */
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    gethostname(hostname, 128);

    /* Until this point, all programs have been doing exactly the same.
       Here, we check the rank to distinguish the roles of the programs */
    if (my_rank == 0) {
        printf("We have %i processes.\n", size);
    } else {
        if (my_rank == 2) {
            printf("Hello world! I'm %d of %d process and I'll work for some time to solve a problem\n", my_rank, size);
            /* block one process for some time */
            int j = 0;
            for (; j < 10000000; j++) {
                sprintf(tmp, "I'm PI  %f!", 3.1416);
            } 
        }
    }

    printf("Hello world! I'm %d of %d process and I finish my job just now. By the way, I'm running on host %s.\n", 
                               my_rank, size, hostname);

    /* Tear down the communication infrastructure */
    MPI_Finalize();

    return 0;
}

