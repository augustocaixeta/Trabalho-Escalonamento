#include <stdio.h>

#define MAX_PROCESSOS 100

int tempos_execucao[MAX_PROCESSOS];
int tempos_restante[MAX_PROCESSOS];
int tat[MAX_PROCESSOS];     // Turnaround Time
int espera[MAX_PROCESSOS];  // Tempo de Espera

int tempo_total = 0;

void ler_dados(int n) {
    for (int p = 0; p < n; p++) {
        printf("P [%02d]: ", p + 1);
        scanf("%d", &tempos_execucao[p]);
        tempos_restante[p] = tempos_execucao[p];
    }
}

void round_robin(int n, int quantum) {
    int processos_restantes = n;
    int tempo = 0;
    int terminou = 0;
    int p = 0;

    printf("\nTempo Atual\tProcesso\tTempo Executado\tTempo Restante\n");

    while (processos_restantes > 0) {
        if (tempos_restante[p] > 0) {
            int exec_time = (tempos_restante[p] >= quantum) ? quantum : tempos_restante[p];
            int tempo_inicial = tempo;
            int tempo_final = tempo + exec_time;

            tempos_restante[p] -= exec_time;
            tempo = tempo_final;

            printf("%d-%d\t\tP%d\t\t%d\t\t%d\n",
                   tempo_inicial, tempo_final,
                   p + 1,
                   exec_time,
                   tempos_restante[p]);

            if (tempos_restante[p] == 0) {
                int tempo_espera = tempo - tempos_execucao[p];
                tat[p] = tempo;
                espera[p] = tempo_espera;
                processos_restantes--;
            }
        }

        p = (p + 1) % n;
    }

    tempo_total = tempo;
}

int main() {
    int n, quantum;

    printf("Numero de processos: ");
    scanf("%d", &n);

    ler_dados(n);

    printf("Quantum: ");
    scanf("%d", &quantum);

    round_robin(n, quantum);

    return 0;
}
