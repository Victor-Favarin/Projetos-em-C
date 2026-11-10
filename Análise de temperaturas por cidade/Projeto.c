#include <string.h>
#include <stdio.h>

#define CIDADES 5
#define MESES 6
#define TEMP_MIN -90
#define TEMP_MAX 60

typedef struct {
    char nome[50];
    float temperatura[MESES];
    float media;
    float maior;
    float menor;
} Cidade;

void calcularEstatisticas(Cidade *cidade) {
    float soma = 0;
    float *p;

    p = (*cidade).temperatura;

    (*cidade).maior = *p;
    (*cidade).menor = *p;

    for (int i = 0; i < MESES; i++) {
        soma = soma + *(p + i);

        if (*(p + i) > (*cidade).maior) {
            (*cidade).maior = *(p + i);
        }

        if (*(p + i) < (*cidade).menor) {
            (*cidade).menor = *(p + i);
        }
    }

    (*cidade).media = soma / MESES;
}

int nomeValido(char *nome) {
    char *p = nome;
    int letras = 0;

    while (*p != '\0') {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') ||
            (unsigned char)*p >= 128) {
            letras++;
        } else if (*p != ' ' && *p != '-' && *p != '\'') {
            return 0;
        }
        p++;
    }

    return letras > 0;
}

int main() {
    Cidade cidades[CIDADES];
    float *p;
    int valido, c, sobra;

    float somaGeral = 0, maiorGeral, menorGeral;

    int cidadeMaior = 0, cidadeMenor = 0, mesMaior = 0, mesMenor = 0;

    printf("ANALISE DE TEMPERATURAS\n");

    for (int i = 0; i < CIDADES; i++) {
        do {
            printf("\nDigite o nome da cidade %d: ", i + 1);
            valido = scanf(" %49[^\n]", cidades[i].nome);

            if (valido == EOF) {
                printf("\nEntrada encerrada.\n");
                return 1;
            }

            while ((c = getchar()) != '\n' && c != EOF);

            if (valido != 1 || !nomeValido(cidades[i].nome)) {
                printf("Nome invalido! Use apenas letras (sem numeros).\n");
                valido = 0;
            }
        } while (valido != 1);

        p = cidades[i].temperatura;

        for (int j = 0; j < MESES; j++) {
            do {
                printf("Temperatura do mes %d: ", j + 1);
                valido = scanf("%f", p + j);

                if (valido == EOF) {
                    printf("\nEntrada encerrada.\n");
                    return 1;
                }

                sobra = 0;
                while ((c = getchar()) != '\n' && c != EOF) {
                    if (c != ' ' && c != '\t') {
                        sobra = 1;
                    }
                }

                if (valido != 1 || sobra) {
                    printf("Valor invalido! Digite so o numero (use ponto, nao virgula).\n");
                    valido = 0;
                } else if (*(p + j) < TEMP_MIN || *(p + j) > TEMP_MAX) {
                    printf("Temperatura fora do limite (%d a %d C). Tente de novo.\n",
                           TEMP_MIN, TEMP_MAX);
                    valido = 0;
                }
            } while (valido != 1);
        }

        calcularEstatisticas(&cidades[i]);
    }

    maiorGeral = cidades[0].temperatura[0];
    menorGeral = cidades[0].temperatura[0];

    float *pSoma, *pMaior, *pMenor;

    pSoma = &somaGeral;
    pMaior = &maiorGeral;
    pMenor = &menorGeral;

    for (int i = 0; i < CIDADES; i++) {

        p = cidades[i].temperatura;

        for (int j = 0; j < MESES; j++, p++) {
            float temperatura = *p;

            *pSoma = *pSoma + temperatura;

            if (temperatura > *pMaior) {
                *pMaior = temperatura;
                cidadeMaior = i;
                mesMaior = j;
            }

            if (temperatura < *pMenor) {
                *pMenor = temperatura;
                cidadeMenor = i;
                mesMenor = j;
            }
        }
    }

    printf("\n\n===== RESULTADOS GERAIS =====\n");

    printf("Media geral: %.2f C\n",
           *pSoma / (CIDADES * MESES));

    printf("Maior temperatura: %.2f C\n", *pMaior);
    printf("Cidade: %s | Mes: %d\n",
           cidades[cidadeMaior].nome, mesMaior + 1);

    printf("Menor temperatura: %.2f C\n", *pMenor);
    printf("Cidade: %s | Mes: %d\n",
           cidades[cidadeMenor].nome, mesMenor + 1);

    for (int i = 0; i < CIDADES - 1; i++) {
        for (int j = 0; j < CIDADES - 1 - i; j++) {
            if (cidades[j].media < cidades[j + 1].media) {
                Cidade auxiliar = cidades[j];
                cidades[j] = cidades[j + 1];
                cidades[j + 1] = auxiliar;
            }
        }
    }

    printf("\n===== RESULTADOS POR CIDADE =====\n");

    for (int i = 0; i < CIDADES; i++) {
        int mesMaiorCidade = 0;
        int mesMenorCidade = 0;

        p = cidades[i].temperatura;

        for (int j = 0; j < MESES; j++) {
            if (*(p + j) == cidades[i].maior) {
                mesMaiorCidade = j;
            }

            if (*(p + j) == cidades[i].menor) {
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

    return 0;
}
