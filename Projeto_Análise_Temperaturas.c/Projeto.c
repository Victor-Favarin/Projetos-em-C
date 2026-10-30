#include <string.h>
#include <stdio.h>

#define CIDADES 5
#define MESES 6

typedef struct {
    char nome[50];
    float temperatura[MESES];
    float media;
    float maior;
    float menor;
} Cidade;

/* Calcula a media, a maior e a menor temperatura */
void calcularEstatisticas(Cidade *cidade) {
    float soma = 0;

    (*cidade).maior = (*cidade).temperatura[0];
    (*cidade).menor = (*cidade).temperatura[0];

    for (int i = 0; i < MESES; i++) {
        soma = soma + (*cidade).temperatura[i];

        if ((*cidade).temperatura[i] > (*cidade).maior) {
            (*cidade).maior = (*cidade).temperatura[i];
        }

        if ((*cidade).temperatura[i] < (*cidade).menor) {
            (*cidade).menor = (*cidade).temperatura[i];
        }
    }

    (*cidade).media = soma / MESES;
}

int main() {
    Cidade cidades[CIDADES];

    float somaGeral = 0;
    float maiorGeral, menorGeral;
    int cidadeMaior = 0, cidadeMenor = 0;
    int mesMaior = 0, mesMenor = 0;

    /* Entrada dos nomes e das temperaturas */
    printf("ANALISE DE TEMPERATURAS\n");

    for (int i = 0; i < CIDADES; i++) {
        printf("\nDigite o nome da cidade %d: ", i + 1);
        scanf(" %49[^\n]", cidades[i].nome);

        for (int j = 0; j < MESES; j++) {
            printf("Temperatura do mes %d: ", j + 1);
            scanf("%f", &cidades[i].temperatura[j]);
        }

        /* Calcula os dados dessa cidade */
        calcularEstatisticas(&cidades[i]);
    }

    /* Comeca considerando a primeira temperatura */
    maiorGeral = cidades[0].temperatura[0];
    menorGeral = cidades[0].temperatura[0];

    /* Procura a maior e a menor temperatura geral */
    for (int i = 0; i < CIDADES; i++) {
        for (int j = 0; j < MESES; j++) {
            float temperatura = cidades[i].temperatura[j];

            somaGeral = somaGeral + temperatura;

            if (temperatura > maiorGeral) {
                maiorGeral = temperatura;
                cidadeMaior = i;
                mesMaior = j;
            }

            if (temperatura < menorGeral) {
                menorGeral = temperatura;
                cidadeMenor = i;
                mesMenor = j;
            }
        }
    }

    /* Mostra os resultados gerais */
    printf("\n\n===== RESULTADOS GERAIS =====\n");

    printf("Media geral: %.2f C\n",
           somaGeral / (CIDADES * MESES));

    printf("Maior temperatura: %.2f C\n", maiorGeral);
    printf("Cidade: %s | Mes: %d\n",
           cidades[cidadeMaior].nome, mesMaior + 1);

    printf("Menor temperatura: %.2f C\n", menorGeral);
    printf("Cidade: %s | Mes: %d\n",
           cidades[cidadeMenor].nome, mesMenor + 1);

    /* Organiza as cidades pela media, da maior para a menor */
    for (int i = 0; i < CIDADES - 1; i++) {
        for (int j = 0; j < CIDADES - 1 - i; j++) {
            if (cidades[j].media < cidades[j + 1].media) {
                Cidade auxiliar = cidades[j];
                cidades[j] = cidades[j + 1];
                cidades[j + 1] = auxiliar;
            }
        }
    }

   
    /* Mostra os resultados de cada cidade */
    printf("\n===== RESULTADOS POR CIDADE =====\n");

    for (int i = 0; i < CIDADES; i++) {
        int mesMaiorCidade = 0;
        int mesMenorCidade = 0;

        for (int j = 0; j < MESES; j++) {
            if (cidades[i].temperatura[j] == cidades[i].maior) {
                mesMaiorCidade = j;
            }

            if (cidades[i].temperatura[j] == cidades[i].menor) {
                mesMenorCidade = j;
            }
        }

        printf("\nCidade: %s\n", cidades[i].nome);
        printf("Media: %.2f C\n", cidades[i].media);

        printf("Maior temperatura: %.2f C - Mes %d\n",
               cidades[i].maior, mesMaiorCidade + 1);

        printf("Menor temperatura: %.2f C - Mes %d\n",
               cidades[i].menor, mesMenorCidade + 1);
    }
}