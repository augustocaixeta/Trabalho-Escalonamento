#include <stdio.h>
#include <limits.h>

#define MAX 100

void lerProcessos(int n, int chegada[], int duracao[], int restante[]);
int escolherProcesso(int tempo, int n, int chegada[], int restante[]);
void imprimirResultados(int n, int chegada[], int duracao[], int tempoEspera[], int tempoTurnaround[]);

int main() {
    int n;
    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    int chegada[MAX], duracao[MAX], restante[MAX];
    int tempoEspera[MAX] = {0}, tempoTurnaround[MAX] = {0};

    lerProcessos(n, chegada, duracao, restante);

    int tempo = 0, completo = 0, inicio = 0, fim;
    int ultimoProcesso = -1;

    printf("\nExecucao dos processos (linha do tempo):\n");

    while (completo < n) {
        int menor = escolherProcesso(tempo, n, chegada, restante);

        if (menor == -1) {
            tempo++; // CPU ociosa
            continue;
        }

        // Detecta troca de processo
        if (menor != ultimoProcesso) {
            if (ultimoProcesso != -1 && restante[ultimoProcesso] > 0) {
                printf("P%d [%d - %d]\n", ultimoProcesso + 1, inicio, tempo);
            }
            inicio = tempo;
            ultimoProcesso = menor;
        }

        restante[menor]--;
        tempo++;

        if (restante[menor] == 0) {
            completo++;
            fim = tempo;

            tempoTurnaround[menor] = fim - chegada[menor];
            tempoEspera[menor] = tempoTurnaround[menor] - duracao[menor];

            printf("P%d [%d - %d]\n", menor + 1, inicio, fim);

            ultimoProcesso = -1; // Libera a CPU para detectar troca
        }
    }

    imprimirResultados(n, chegada, duracao, tempoEspera, tempoTurnaround);

    return 0;
}

void lerProcessos(int n, int chegada[], int duracao[], int restante[]) {
    for (int i = 0; i < n; i++) {
        printf("Processo %d - Tempo de chegada: ", i + 1);
        scanf("%d", &chegada[i]);
        printf("Processo %d - Tempo de execucao: ", i + 1);
        scanf("%d", &duracao[i]);
        restante[i] = duracao[i];
    }
}

int escolherProcesso(int tempo, int n, int chegada[], int restante[]) {
    int menor = -1;
    int menorTempo = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (chegada[i] <= tempo && restante[i] > 0 && restante[i] < menorTempo) {
            menorTempo = restante[i];
            menor = i;
        }
    }

    return menor;
}

void imprimirResultados(int n, int chegada[], int duracao[], int tempoEspera[], int tempoTurnaround[]) {
    int somaEspera = 0, somaTurnaround = 0;

    printf("\nProcesso\tChegada\tDuracao\tEspera\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\n", i + 1, chegada[i], duracao[i], tempoEspera[i], tempoTurnaround[i]);
        somaEspera += tempoEspera[i];
        somaTurnaround += tempoTurnaround[i];
    }

    printf("\nMedia de tempo de espera: %.2f\n", (float)somaEspera / n);
    printf("Media de turnaround: %.2f\n", (float)somaTurnaround / n);
}
