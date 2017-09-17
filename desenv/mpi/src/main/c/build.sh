mpicc hello.c -o test && mpiexec -n 8 ./test
mpicc hello_1.c -o test_1 && mpiexec -n 6 ./test_1
mpicc hello_2.c -o test_2 && mpiexec -n 6 ./test_2
