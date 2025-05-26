#include <stdio.h>

struct Processo {
    int chegada;
    int duracao;
    int restante;
    int tempoEspera;
    int tempoTurnaround;

    Processo() {
        tempoEspera = 0;
        tempoTurnaround = 0;
    }
};

void lerProcessos(int n, Processo processos[]) {
    for (int i = 0; i < n; i++) {
        printf("Processo %d - Tempo de chegada: ", i + 1);
        scanf("%d", &processos[i].chegada);
        printf("Processo %d - Tempo de execucao: ", i + 1);
        scanf("%d", &processos[i].duracao);
        processos[i].restante = processos[i].duracao;
    }
}

int escolherProcesso(int tempo, int n, Processo processos[]) {
    int menor = -1;

    for (int i = 0; i < n; i++) {
        if (processos[i].chegada <= tempo && processos[i].restante > 0) {
            if (menor == -1 || processos[i].restante < processos[menor].restante) {
                menor = i;
            }
        }
    }

    return menor;
}

void imprimirResultados(int n, Processo processos[]) {
    int somaEspera = 0, somaTurnaround = 0;

    printf("\nProcesso\tChegada\tDuracao\tEspera\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\n",
               i + 1,
               processos[i].chegada,
               processos[i].duracao,
               processos[i].tempoEspera,
               processos[i].tempoTurnaround);

        somaEspera += processos[i].tempoEspera;
        somaTurnaround += processos[i].tempoTurnaround;
    }

    printf("\nMedia de tempo de espera: %.2f\n", (float) somaEspera / n);
    printf("Media de turnaround: %.2f\n", (float) somaTurnaround / n);
}

int main() {
    int n;
    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    Processo processos[n];

    lerProcessos(n, processos);

    int tempo = 0, completo = 0, inicio = 0, fim;
    int ultimoProcesso = -1;

    printf("\nExecucao dos processos (linha do tempo):\n");

    while (completo < n) {
        int menor = escolherProcesso(tempo, n, processos);

        if (menor == -1) {
            tempo++; // CPU ociosa
            continue;
        }

        // Detecta troca de processo
        if (menor != ultimoProcesso) {
            if (ultimoProcesso != -1 && processos[ultimoProcesso].restante > 0) {
                printf("P%d [%d - %d]\n", ultimoProcesso + 1, inicio, tempo);
            }
            inicio = tempo;
            ultimoProcesso = menor;
        }

        processos[menor].restante--;
        tempo++;

        if (processos[menor].restante == 0) {
            completo++;
            fim = tempo;

            processos[menor].tempoTurnaround = fim - processos[menor].chegada;
            processos[menor].tempoEspera = processos[menor].tempoTurnaround - processos[menor].duracao;

            printf("P%d [%d - %d]\n", menor + 1, inicio, fim);

            ultimoProcesso = -1; // Libera a CPU para detectar troca
        }
    }

    imprimirResultados(n, processos);

    return 0;
}
