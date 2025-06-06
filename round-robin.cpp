#include <stdio.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int lerNumeroProcessos() {
    int n;
    do {
        printf("Numero de Processos: ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Numero de processos invalido. Tente novamente.\n");
        }
    } while (n <= 0);
    return n;
}

int lerQuantum() {
    int quantum;
    do {
        printf("Parcela do Quantum: ");
        scanf("%d", &quantum);
        if (quantum <= 0) {
            printf("Quantum invalido. Tente novamente.\n");
        }
    } while (quantum <= 0);
    return quantum;
}

void lerTempos(int chegada[], int execucao[], int n) {
    for (int i = 0; i < n; i++) {
        do {
            printf("Processo %d - Tempo de Chegada: ", i + 1);
            scanf("%d", &chegada[i]);
            if (chegada[i] < 0)
                printf("Tempo de chegada invalido. Tente novamente.\n");
        } while (chegada[i] < 0);

        do {
            printf("Processo %d - Tempo de Execucao: ", i + 1);
            scanf("%d", &execucao[i]);
            if (execucao[i] <= 0)
                printf("Tempo de execucao invalido. Tente novamente.\n");
        } while (execucao[i] <= 0);
    }
}

void executarRoundRobin(int chegada[], int execucao[], int n, int quantum) {
    int tempo = 0;
    int restantes[n];
    int concluidos = 0;
    int i = 0;
    int pronto;

    for (int j = 0; j < n; j++) {
        restantes[j] = execucao[j];
    }

    printf("\nTempo Atual\tProcesso\tTempo Executado\tTempo Restante\n");

    while (concluidos < n) {
        pronto = 0;

        /**
         * Problema: o escalonamento está sendo feito com base na rotação circular
         * a partir do índice 'i', que representa o último processo executado.
         * Isso faz com que o próximo processo escolhido não seja necessariamente
         * o que chegou primeiro, mas sim o próximo na ordem circular que estiver pronto.
         *
         * Exemplo de erro:
         * Suponha os processos:
         *  P1 (chegada = 1, execução = 3)
         *  P2 (chegada = 0, execução = 4)
         *  P3 (chegada = 2, execução = 5)
         *
         * No tempo 0, P2 é executado. i = 1 (índice de P2).
         * No tempo 2, a rotação começa de i+1, ou seja: P3, P1, P2
         * (pid = (i + tentativas) % n).
         *
         * Nesse momento, tanto P1 (chegada = 1) quanto P3 (chegada = 2) estão prontos.
         * No entanto, como a rotação começa de P3, ele é escolhido primeiro,
         * mesmo que P1 tenha chegado antes.
         *
         * Isso ocorre porque a seleção não reavalia a ordem de chegada a cada rodada,
         * apenas continua ciclicamente a partir do último processo executado.
         *
         * Correção: Manter uma fila de prontos ou sempre percorrer a lista
         * completa dos processos, respeitando a ordem de chegada (e nome, se empate).
         */
        for (int tentativas = 0; tentativas < n; tentativas++) {
            int pid = (i + tentativas) % n;

            if (chegada[pid] <= tempo && restantes[pid] > 0) {
                int exec = min(quantum, restantes[pid]);

                printf("%d-%d\t\tP%d\t\t%d\t\t%d\n",
                       tempo, tempo + exec,
                       pid + 1,
                       exec,
                       restantes[pid] - exec);

                tempo += exec;
                restantes[pid] -= exec;

                if (restantes[pid] == 0)
                    concluidos++;

                i = (pid + 1) % n;
                pronto = 1;
                break;
            }
        }

        if (!pronto) {
            tempo++;
        }
    }
}

int main() {
    int n = lerNumeroProcessos();

    int chegada[n];
    int execucao[n];

    lerTempos(chegada, execucao, n);

    int quantum = lerQuantum();

    executarRoundRobin(chegada, execucao, n, quantum);

    return 0;
}
