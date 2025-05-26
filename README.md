# Sobre

### Round Robin (RR)
Cada processo recebe uma fatia de tempo (quantum) para executar. Se não terminar nesse intervalo, ele é colocado no final da fila, e o próximo processo é executado. Essa abordagem garante que todos os processos recebam atenção igual, evitando a inanição e promovendo justiça no uso da CPU. 

### Shortest Remaining Time (SRT)
É uma variação preemptiva do SJF (Shortest Job First). Sempre escolhe para execução o processo com menor tempo restante de CPU. Se um novo processo chega com um tempo menor que o tempo restante do processo atual, o escalonador interrompe o processo em execução e troca para o novo processo.

# Linguagem

* C/C++

# Equipe

* Augusto
* Bruno
* Diego Silva
* Douglas
* Natan
