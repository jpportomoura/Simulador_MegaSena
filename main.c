#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "megasena.h"

int main() {
    int cartela[6][10];
    int QD, QM, QS, QT, valor_total;
    int apostas[3][15];
    char finalizar;
    int jogo_premiado[6];

    do {
        saudacao(cartela);
        solicitar_quantidades(&QD, &QM, &QS, &QT);
        solicitar_dezenas(QD, QM, apostas);
        mostrar_apostas(QD, QM, QT, QS, apostas);
        calcular_total(QT, QM, QD, QS, &valor_total);
        mostra_valor(valor_total);

        char gravar = deseja_gravar();
        if (gravar == 'N') {
            finalizar = deseja_recomecar(); 
        } 
        else {
            finalizar = 'N';  
        }
        srand(time(NULL));
        gerar_jogo(jogo_premiado);
        printf("\n----- DEZENAS PREMIADAS -----\n");
        for(int i = 0; i < 6; i++){
            printf("| %02d | ", jogo_premiado[i]);
        }

        for (int i = 0; i < QM; i++){
            int acertos = calcular_acertos(apostas[i], QD, jogo_premiado);
            printf("O seu jogo %d teve %d acertos!", i + 1, acertos);
        }

    } while (finalizar == 'S');

    return 0;
}

