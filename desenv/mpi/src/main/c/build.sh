mpicc hello.c -o test && mpiexec -n 8 ./test
mpicc hello_1.c -o test_1 && mpiexec -n 4 ./test_1
