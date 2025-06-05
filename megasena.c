#include <stdio.h>
#include "megasena.h"

void solicitar_quantidades(int *QD, int *QM) {
    printf("Digite a quantidade de dezenas (6 a 15): ");
    scanf("%d", QD);

    while (*QD < 6 || *QD > 15) {
        printf("Valor inválido! Digite novamente (6 a 15): ");
        scanf("%d", QD);
    }

    printf("Digite quantos jogos deseja (1 a 3): ");
    scanf("%d", QM);

    while (*QM < 1 || *QM > 3) {
        printf("Quantidade inválida! Digite novamente (1 a 3): ");
        scanf("%d", QM);
    }
}

void solicitar_apostas(int QD, int QM, int apostas[][15]) {
    for (int j = 0; j < QM; j++) {
        printf("\nJogo %d:\n", j + 1);
        for (int i = 0; i < QD; i++) {
            printf("Digite a %d dezena: ", i + 1);
            scanf("%d", &apostas[j][i]);
        }
    }
}
