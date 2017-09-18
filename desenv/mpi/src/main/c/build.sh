mpicc  hello.c     -o test   && mpiexec -n 6 ./test         # Programa C
mpicc  hello_1.c   -o test_1 && mpiexec -n 6 ./test_1       # Programa C
mpicc  hello_2.c   -o test_2 && mpiexec -n 6 ./test_2       # Programa C
mpic++ calc_pi.cpp -o test_3 && mpiexec -n 6 ./test_3 50000 # Programa C++