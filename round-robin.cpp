
#include <stdio.h>

void lerProcessoTempoExecucao(int processoTemposExecucao[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Processo %d: ", i + 1);
        scanf("%d", &processoTemposExecucao[i]);
    }
}

void executarRoundRobin(int processoTemposExecucao[], int n, int quantum) {
    int processosRestantes = n;
    int tempoAnterior = 0;
    int i = 0;                  // Índice do processo que acontecerá o rodízio (Round).

    printf("\nTempo Atual\tProcesso\tTempo Executado\tTempo Restante\n");

    while (processosRestantes > 0) {
        if (processoTemposExecucao[i] > 0) {
            int tempoExecucao = (processoTemposExecucao[i] >= quantum) ? quantum : processoTemposExecucao[i];
            int tempoInicio = tempoAnterior;
            int tempoFim = tempoAnterior + tempoExecucao;

            processoTemposExecucao[i] -= tempoExecucao;
            tempoAnterior = tempoFim;

            printf("%d-%d\t\tP%d\t\t%d\t\t%d\n",
                   tempoInicio, tempoFim,
                   i + 1,
                   tempoExecucao,
                   processoTemposExecucao[i]);

            // Decrementar a variável de processos restantes quanto terminar para não entrar no próximo while.
            if (processoTemposExecucao[i] == 0) {
                processosRestantes--;
            }
        }

        // Isso faz com que o indice do processo (no caso "i") retorne para o valor "0" quando chegar ao valor "n".
        // Trazendo a ideia do "Round" (rodízio).
        i = (i + 1) % n;
    }
}

int main() {
    int n;
    printf("Numero de Processos: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Numero de processos invalido.\n");
        return 1;
    }

    int processoTemposExecucao[n];
    lerProcessoTempoExecucao(processoTemposExecucao, n);

    int quantum;
    printf("Parcela do Quantum: ");
    scanf("%d", &quantum);

    if (quantum <= 0) {
        printf("Quantum invalido.\n");
        return 1;
    }

    executarRoundRobin(processoTemposExecucao, n, quantum);

    return 0;
}
