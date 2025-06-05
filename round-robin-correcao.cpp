#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSOS (16)
#define MAX_NOME (8)

struct Processo {
    char nome[MAX_NOME];
    int chegada;
    int execucao;
    int restante;
    int finalizado;

    void lerTempos() {
        printf("Nome do processo (ex: P1): ");
        scanf("%s", nome);

        printf("Processo %s - Tempo de chegada: ", nome);
        scanf("%d", &chegada);

        printf("Processo %s - Tempo de execucao: ", nome);
        scanf("%d", &execucao);

        restante = execucao;
        finalizado = 0;

        printf("\n");
    }
};

int min(int a, int b) {
    return (a < b) ? a : b;
}

int compararProcessos(const void* a, const void* b) {
    Processo* p1 = (Processo*)a;
    Processo* p2 = (Processo*)b;

    if (p1->chegada != p2->chegada)
        return p1->chegada - p2->chegada;

    return strcmp(p1->nome, p2->nome);
}

int lerNumeroProcessos() {
    int n;
    printf("Numero de processos: ");
    scanf("%d", &n);
    return n;
}

int lerQuantum() {
    int quantum;
    printf("Parcela do quantum: ");
    scanf("%d", &quantum);
    return quantum;
}

void roundRobin(Processo processos[], int n, int quantum) {
    int tempo = 0;
    int concluidos = 0;

    qsort(processos, n, sizeof (Processo), compararProcessos);

    while (concluidos < n) {
        int executou = 0;

        for (int i = 0; i < n; i++) {
            if (processos[i].chegada <= tempo && processos[i].restante > 0) {
                int exec = min(quantum, processos[i].restante);

                printf("%d-%d\t%s\tExec: %d\tRestante: %d\n",
                       tempo, tempo + exec,
                       processos[i].nome,
                       exec,
                       processos[i].restante - exec);

                tempo += exec;
                processos[i].restante -= exec;

                if (processos[i].restante == 0) {
                    processos[i].finalizado = 1;
                    concluidos++;
                }

                executou = 1;
            }
        }

        if (!executou) {
            tempo++;
        }
    }
}

int main() {
    int n = lerNumeroProcessos();

    Processo processos[MAX_PROCESSOS];

    for (int i = 0; i < n; i++) {
        processos[i].lerTempos();
    }

    int quantum = lerQuantum();

    roundRobin(processos, n, quantum);

    return 0;
}
