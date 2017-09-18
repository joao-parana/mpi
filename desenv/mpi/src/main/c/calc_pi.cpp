#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)   {
    char tmp[256];
    char hostname[128];
    int n = 0, rank, size, i, root_process = 0, instances = 1;
    double PI25DT = 3.141592653589793238462643; 
    double mypi, pi, h, sum, x;
    char processor_name[MPI_MAX_PROCESSOR_NAME]; 
    int namelen;

    /* Initialize the infrastructure necessary for communication */
    MPI_Init(&argc, &argv);

    /* Identify this process */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* Find out how many total processes are active */
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Get_processor_name(processor_name, &namelen);

    gethostname(hostname, 128);

    cout << "Hello from process " << rank << " of " << size << " on " << processor_name << " of " << hostname << endl;

    if (rank == 0) {
        // cout << "Enter the number of intervals: (0 quits) "; 
        // cin >> n;
        if (argc < 2 || argc > 2) {
          n = 0;
        }
        else {
          n = atoi(argv[1]);
        }
        cout << "n is " << n << " on " << argv[0] << endl;
    }
    
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (n > 0) {
        h = 1.0 / (double) n;
        sum = 0.0;
        for (i = rank + 1; i <= n; i += size) {
            x = h * ((double)i - 0.5);
            sum += (4.0 / (1.0 + x * x)); 
        }
        mypi = h * sum;
        // my_pi:        Partial contribution of “this” process
        // pi:           Where the reduce operation stores the result
        // instances:    How many instances of this data type are moving around
        // MPI_DOUBLE:   Data type we are moving around
        // MPI_SUM:      Reduce through a “sum” operation
        // root_process: Root process, it ends up storing the result
        MPI_Reduce(&mypi, &pi, instances, MPI_DOUBLE, MPI_SUM, root_process, MPI_COMM_WORLD);
        if (rank == 0)  {
            cout << "pi is approximately " << fabs(pi) << ", Error is " << fabs(pi - PI25DT) << endl;
        }
    }

    MPI_Finalize();
    return 0;
}
