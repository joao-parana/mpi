/*
  "Hello World" MPI Test Program

  To run with 4 cores use: mpicc hello_1.c && mpiexec -n 4 ./a.out
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

void doSomeWork(int counter)
{
    char tmp[256];

    printf("I'm doing some work: %d\n", counter);

    int j = 0;
    for (; j < counter; j++) {
        sprintf(tmp, "I'm PI  %f!", 3.1416);
    } 
}

int main(int argc, char **argv)
{
    char buf[256];
    int my_rank, num_procs;

    /* Initialize the infrastructure necessary for communication */
    MPI_Init(&argc, &argv);

    /* Identify this process */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Find out how many total processes are active */
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    /* Until this point, all programs have been doing exactly the same.
       Here, we check the rank to distinguish the roles of the programs */
    if (my_rank == 0) {
        int other_rank;
        printf("We have %i processes.\n", num_procs);

        /* Send messages to all other processes */
        for (other_rank = 1; other_rank < num_procs; other_rank++)
        {
            sprintf(buf, "Hello %i!", other_rank);
            MPI_Send(buf, sizeof(buf), MPI_CHAR, other_rank,
                     0, MPI_COMM_WORLD);
            printf("MPI_Send message to %d\n", other_rank);
            if (other_rank == (num_procs - 2)) {
                doSomeWork(10000000);
            }
        }

        /* Receive messages from all other process */
        for (other_rank = 1; other_rank < num_procs; other_rank++)
        {
            MPI_Recv(buf, sizeof(buf), MPI_CHAR, other_rank,
                     0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("MPI_Recv from %d\n", other_rank);
            printf("%s\n", buf);
        }

    } else {
        if (my_rank == 2) {
            doSomeWork(10000000);
        }

        /* Receive message from process #0 */
        MPI_Recv(buf, sizeof(buf), MPI_CHAR, 0,
                 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        assert(memcmp(buf, "Hello ", 6) == 0),

        /* Send message to process #0 */
        sprintf(buf, "Process %i reporting for duty.", my_rank);
        MPI_Send(buf, sizeof(buf), MPI_CHAR, 0,
                 0, MPI_COMM_WORLD);

    }

    /* Tear down the communication infrastructure */
    MPI_Finalize();
    return 0;
}


