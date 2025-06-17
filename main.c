#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "megasena.h"

int main() {
    int cartela[6][10];
    int QD, QM, QS, QT, valor_total;
    int apostas[3][15];
    int surpresinhas[7][15];
    int jogo_premiado[6];
    char finalizar;

    srand(time(NULL));

    do {
        saudacao(cartela);
        solicitar_quantidades(&QD, &QM, &QS, &QT);
        solicitar_dezenas(QD, QM, apostas);

        if (QS > 0) {
            gerar_surpresinhas(QD, QS, surpresinhas);
        }

        mostrar_apostas(QD, QM, QT, QS, apostas);

        if (QS > 0) {
            printf("\n------ SURPRESINHAS GERADAS ------\n");
            for (int i = 0; i < QS; i++) {
                printf("Surpresinha %d - Dezenas: ", i + 1);
                for (int j = 0; j < QD; j++) {
                    printf("| %02d | ", surpresinhas[i][j]);
                }
                printf("\n");
            }
        }

        calcular_total(QT, QM, QD, QS, &valor_total);
        mostra_valor(valor_total);

        char gravar = deseja_gravar();
        if (gravar == 'N') {
            finalizar = deseja_recomecar();
            if (finalizar == 'N') {
                printf("\nEncerrando o programa. Nenhum jogo foi gravado ou executado.\n");
                return 0; 
            }
        } else {
            finalizar = 'N';
        }

        if (QT == 0) QT = 1;

        float total_premiado = 0.0;

        for (int rodada = 1; rodada <= QT; rodada++) {
            printf("\n===========================\n");
            printf(" Rodada %d da Teimosinha\n", rodada);
            printf("===========================\n");

            gerar_jogo(jogo_premiado);

            printf("----- DEZENAS DO JOGO PREMIADO -----\n");
            for (int i = 0; i < 6; i++) {
                printf("| %02d | ", jogo_premiado[i]);
            }
            printf("\n");

            for (int i = 0; i < QM; i++) {
                int acertos = calcular_acertos(apostas[i], QD, jogo_premiado);
                printf("Aposta Manual %d teve %d acertos", i + 1, acertos);
                if (acertos == 6) printf(" --- SENA!");
                else if (acertos == 5) printf(" --- QUINA!");
                else if (acertos == 4) printf(" --- QUADRA!");
                else printf(".");

                float premio = calcular_premio(QD, acertos);
                printf(" --- Prêmio: R$ %.2f", premio);
                total_premiado += premio;
                printf("\n");
            }

            for (int i = 0; i < QS; i++) {
                int acertos = calcular_acertos(surpresinhas[i], QD, jogo_premiado);
                printf("Surpresinha %d teve %d acertos", i + 1, acertos);
                if (acertos == 6) printf(" --- SENA!");
                else if (acertos == 5) printf(" --- QUINA!");
                else if (acertos == 4) printf(" --- QUADRA!");
                else printf(".");

                float premio = calcular_premio(QD, acertos);
                printf(" --- Prêmio: R$ %.2f", premio);
                total_premiado += premio;
                printf("\n");
            }
            printf("\n");
        }

        printf("=====================================\n");
        printf("Valor total investido: R$ %d,00\n", valor_total);
        printf("Valor total premiado:  R$ %.2f\n", total_premiado);
        printf("=====================================\n");

    } while (finalizar == 'S');
    
    printf("\nObrigado por jogar na MEGA SENA!");

    return 0;
}
