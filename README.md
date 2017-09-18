# mpi

Aplicação de Teste MPI rodando via Docker 


```bash
./start_container.sh /Users/parana/.ssh/id_rsa.pub
```

Para fazer o build dos programas de teste e executá-los use os comandos abaixo dentro do contêiner

```bash
cd desenv/mpi/src/main/c
./build.sh
```

Veja o [desenv/mpi/src/main/c/build.sh](desenv/mpi/src/main/c/build.sh)

### Calculo aproximado de PI

![approximating-PI](docs/approximating-PI.png)

Um dos exemplos (`calc_pi.cpp`) mostra como usar Broadcast (`MPI_Bcast`) e Reduce (`MPI_Reduce`) 
para calcular o valor de PI por aproximações com sub-intervalos assinaladosaos *ranks* 
usando **round-robin**

Exemplo com 13 sub-intervalos e 4 processadores: 

* rank 0: 1, 5, 9, 13
* rank 1: 2, 6, 10
* rank 2: 3, 7, 11
* rank 3: 4, 8, 12

Para testar como o erro diminui a medida que aumentamos o número de 
sub-intervalos podemos executar:

```bash
for a in 5 25 50 250 500 2500 5000 25000 50000 250000 500000 2500000
do 
  ./test_3 $a 
done | grep "Error is"
```
