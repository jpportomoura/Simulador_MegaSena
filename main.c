#include <stdio.h>
#include "megasena.h"

int main() {
    int QD, QM;
    int apostas[3][15]; 

    solicitar_quantidades(&QD, &QM);
    solicitar_apostas(QD, QM, apostas);

    printf("Apostas:\n");
    for (int j = 0; j < QM; j++) {
        printf("Jogo %d: ", j + 1);
        for (int i = 0; i < QD; i++) {
            printf("%d ", apostas[j][i]);
        }
        printf("\n");
    }

    return 0;
}