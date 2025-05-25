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

void lerProcessoTempoExecucao(int processoTemposExecucao[], int n) {
    for (int i = 0; i < n; i++) {
        int tempo;
        do {
            printf("Processo %d - Tempo de Execucao: ", i + 1);
            scanf("%d", &tempo);
            if (tempo <= 0) {
                printf("Tempo invalido. Tente novamente.\n");
            }
        } while (tempo <= 0);
        processoTemposExecucao[i] = tempo;
    }
}

void executarRoundRobin(int processoTemposExecucao[], int n, int quantum) {
    int processosRestantes = n;
    int tempoAnterior = 0;
    int i = 0;

    printf("\nTempo Atual\tProcesso\tTempo Executado\tTempo Restante\n");

    while (processosRestantes > 0) {
        if (processoTemposExecucao[i] > 0) {
            int tempoExecucao = min(processoTemposExecucao[i], quantum);
            int tempoInicio = tempoAnterior;
            int tempoFim = tempoAnterior + tempoExecucao;

            processoTemposExecucao[i] -= tempoExecucao;
            tempoAnterior = tempoFim;

            printf("%d-%d\t\tP%d\t\t%d\t\t%d\n",
                   tempoInicio, tempoFim,
                   i + 1,
                   tempoExecucao,
                   processoTemposExecucao[i]);

            if (processoTemposExecucao[i] == 0) {
                processosRestantes--;
            }
        }

        i = (i + 1) % n;
    }
}

int main() {
    int n = lerNumeroProcessos();

    int processoTemposExecucao[n];
    lerProcessoTempoExecucao(processoTemposExecucao, n);

    int quantum = lerQuantum();

    executarRoundRobin(processoTemposExecucao, n, quantum);

    return 0;
}
