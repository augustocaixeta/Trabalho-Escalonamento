#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSOS 10
#define MAX_NOME 10

// Definição da estrutura para armazenar os dados dos processos
struct Processo {
    char nome[MAX_NOME];
    int chegada;
    int duracao;
    int restante;
    int tempoEspera;
    int tempoTurnaround;
};

// Função de comparação para ordenar os processos pelo tempo de chegada
int compararChegada(const void *a, const void *b) {
    const Processo *pa = (const Processo *) a;
    const Processo *pb = (const Processo *) b;

    if (pa->chegada < pb->chegada) return -1;
    if (pa->chegada > pb->chegada) return 1;
    return 0;
}

int main() {
    int n;
    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    Processo processos[MAX_PROCESSOS];
    int tempo = 0, completo = 0;

    // Entrada dos dados dos processos
    for (int i = 0; i < n; i++) {
        printf("Digite o nome do processo %d: ", i + 1);
        scanf("%s", processos[i].nome);

        printf("Digite o tempo de chegada do processo %d: ", i + 1);
        scanf("%d", &processos[i].chegada);

        printf("Digite o tempo de duracao do processo %d: ", i + 1);
        scanf("%d", &processos[i].duracao);

        processos[i].restante = processos[i].duracao;
        processos[i].tempoEspera = 0;
        processos[i].tempoTurnaround = 0;
    }

    // Ordenar os processos pelo tempo de chegada
    qsort(processos, n, sizeof(Processo), compararChegada);

    // Execução dos processos
    printf("\nLinha do Tempo:\n");
    while (completo < n) {
        int menor = -1;
        for (int i = 0; i < n; i++) {
            if (processos[i].chegada <= tempo && processos[i].restante > 0) {
                if (menor == -1 || processos[i].restante < processos[menor].restante ||
                    (processos[i].restante == processos[menor].restante && strcmp(processos[i].nome, processos[menor].nome) < 0)) {
                    menor = i;
                }
            }
        }

        if (menor == -1) {
            printf("- ");
            tempo++;
            continue;
        }

        printf("%s ", processos[menor].nome);
        processos[menor].restante--;
        tempo++;

        if (processos[menor].restante == 0) {
            completo++;
            int fim = tempo;
            processos[menor].tempoTurnaround = fim - processos[menor].chegada;
            processos[menor].tempoEspera = processos[menor].tempoTurnaround - processos[menor].duracao;
        }
    }

    printf("\n");

    // Exibição dos resultados
    int somaEspera = 0, somaTurnaround = 0;
    printf("\nProcesso\tChegada\tDuracao\tEspera\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%d\t\t%d\t%d\n",
               processos[i].nome,
               processos[i].chegada,
               processos[i].duracao,
               processos[i].tempoEspera,
               processos[i].tempoTurnaround);

        somaEspera += processos[i].tempoEspera;
        somaTurnaround += processos[i].tempoTurnaround;
    }

    printf("\nMédia de tempo de espera: %.2f\n", (float) somaEspera / n);
    printf("Média de turnaround: %.2f\n", (float) somaTurnaround / n);

    return 0;
}
