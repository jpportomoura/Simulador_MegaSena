#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "megasena.h"

//Função para saudar e apresentar o jogo
void saudacao(int cartela[6][10]) {
    printf("\nSeja bem-vindo a Mega Sena 2025\n");
    printf("----- CONHECA O NOSSO JOGO -----\n");
    printf("\n--- CARTELA DAS APOSTAS ---\n");
    printf("(Nela voce pode jogar ate 15 dezenas dessas e pode jogar ate 3 apostas manuais)\n");

    int valor = 1;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            cartela[i][j] = valor++;
            printf("%02d   ", cartela[i][j]);
        }
        printf("\n");
    }
    printf("\n--- SURPRESINHA ---\n");
    printf("Aqui o sistema escolhe os numeros por voce.\n");
    printf("(Voce pode escolher ate 7 surpresinhas)\n");
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");

    printf("\n--- TEIMOSINHA ---\n");
    printf("Escolhe em quantos concursos quer participar com o mesmo jogo!\n");
    printf("(Voce pode escolher 2, 4 ou 8 vezes)\n");
    printf("| 2 | 4 | 8 |\n");
    printf("\n=== VAMOS COMECAR ===\n");
}
//Função para solicitar as quantidades que deseja apostar
void solicitar_quantidades(int *QD, int *QM, int *QS, int *QT) {
    printf("\nDigite quantas dezenas deseja apostar (6 a 15): ");
    scanf("%d", QD);
    while (*QD < 6 || *QD > 15) {
        printf("Valor invalido! Digite novamente (6 a 15): ");
        scanf("%d", QD);
    }
    printf("Digite quantas apostas manuais deseja fazer (1 a 3): ");
    scanf("%d", QM);
    while (*QM < 1 || *QM > 3) {
        printf("Valor invalido! Digite novamente (1 a 3): ");
        scanf("%d", QM);
    }
    printf("Digite a quantidade de Surpresinhas (0 a 7): ");
    scanf("%d", QS);
    while (*QS < 0 || *QS > 7) {
        printf("Valor invalido! Digite novamente (0 a 7): ");
        scanf("%d", QS);
    }
    printf("Digite a quantidade de Teimosinhas (0, 2, 4 ou 8): ");
    scanf("%d", QT);
    while (*QT != 0 && *QT != 2 && *QT != 4 && *QT != 8) {
        printf("Valor invalido! Digite novamente (0, 2, 4 ou 8): ");
        scanf("%d", QT);
    }
    while (getchar() != '\n');
}
//Verifica e protege as entradas válidas
int entrada_valida(int *numero) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;
    buffer[strcspn(buffer, "\n")] = 0;
    for (int i = 0; buffer[i]; i++) {
        if (!isdigit(buffer[i])) return 0;
    }
    *numero = atoi(buffer);
    return 1;
}
//Função para solicitar as dezenas que deseja apostar
void solicitar_dezenas(int QD, int QM, int apostas[][15]) {
    for (int i = 0; i < QM; i++) {
        printf("\nJogo %d:\n", i + 1);
        for (int j = 0; j < QD; ) {
            int dezena = 0;
            printf("Digite a %d dezena (1 a %d): ", j + 1, MAX_DEZENA);
            if (!entrada_valida(&dezena)) {
                printf("Entrada invalida! Digite apenas números inteiros.\n");
                continue;
            }
            if (dezena < 1 || dezena > MAX_DEZENA) {
                printf("Dezena fora do intervalo permitido!\n");
                continue;
            }
            int repetida = 0;
            for (int k = 0; k < j; k++) {
                if (apostas[i][k] == dezena) {
                    printf("Dezena repetida! Digite outra.\n");
                    repetida = 1;
                    break;
                }
            }
            if (!repetida) {
                apostas[i][j] = dezena;
                j++;
            }
        }
    }
}
//Função para mostrar as apostas realizada pelo usuário
void mostrar_apostas(int QD, int QM, int QT, int QS, int apostas[][15]) {
    printf("\n------ APOSTAS MANUAIS ------\n");
    for (int j = 0; j < QM; j++) {
        printf("Jogo %d - Dezenas: ", j + 1);
        for (int i = 0; i < QD; i++) {
            printf("| %02d | ", apostas[j][i]);
        }
        printf("\n");
    }
    printf("\nSurpresinhas: %d", QS);
    printf("\nTeimosinhas: %d", QT);
    printf("\n");
}
//Função para calcular o total de acordo com o QD
void calcular_total(int QT, int QM, int QD, int QS, int *valor_total) {
    int VD = 0;
    switch (QD) {
        case 6:  VD = 6; break;
        case 7:  VD = 35; break;
        case 8:  VD = 140; break;
        case 9:  VD = 420; break;
        case 10: VD = 1050; break;
        case 11: VD = 2310; break;
        case 12: VD = 4620; break;
        case 13: VD = 8580; break;
        case 14: VD = 15015; break;
        case 15: VD = 25025; break;
    }
    *valor_total = (QT == 0 ? 1 : QT) * VD * (QM + QS);
}
//Mostra o valor das apostas realizada.
void mostra_valor(int valor_total) {
    printf("\nValor total das apostas: R$ %d,00\n", valor_total);
}
//Pergunta o usuário a confirmação de gravar o jogo
char deseja_gravar() {
    char resposta;
    do {
        printf("\nDeseja gravar o seu jogo? (S/N): ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta);
        if (resposta != 'S' && resposta != 'N') {
            printf("Opcao invalida! Digite S ou N.\n");
        }
    } while (resposta != 'S' && resposta != 'N');
    return resposta;
}
//Se o usuário falar que não quer gravar, pergunta se quer recomeçar
char deseja_recomecar() {
    char resposta;
    do {
        printf("Deseja recomecar? (S/N): ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta);
        if (resposta != 'S' && resposta != 'N') {
            printf("Opcao invalida! Digite S ou N.\n");
        }
    } while (resposta != 'S' && resposta != 'N');
    return resposta;
}
//Função para gerar os jogos
void gerar_jogo(int jogo[6]) {
    int i = 0;
    while (i < 6) {
        int numero = rand() % 60 + 1;
        int repetido = 0;
        for (int j = 0; j < i; j++) {
            if (jogo[j] == numero) {
                repetido = 1;
                break;
            }
        }
        if (!repetido) {
            jogo[i++] = numero;
        }
    }
}
//Função para calcular os acertos do usuário
int calcular_acertos(int jogo_usuario[], int QD, int jogo_premiado[]) {
    int acertos = 0;
    for (int i = 0; i < QD; i++) {
        for (int j = 0; j < 6; j++) {
            if (jogo_usuario[i] == jogo_premiado[j]) {
                acertos++;
                break;
            }
        }
    }
    return acertos;
}
//Função para gerar as surpresinhas
void gerar_surpresinhas(int QD, int QS, int surpresinhas[][15]) {
    for (int i = 0; i < QS; i++) {
        int count = 0;
        while (count < QD) {
            int num = rand() % MAX_DEZENA + 1;
            int repetido = 0;
            for (int k = 0; k < count; k++) {
                if (surpresinhas[i][k] == num) {
                    repetido = 1;
                    break;
                }
            }
            if (!repetido) {
                surpresinhas[i][count++] = num;
            }
        }
    }
}
//Função para calcular o prémio do usuário
float calcular_premio(int QD, int acertos) {
    const int quadra[10] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55};
    const int quina[10]  = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
    const int sena[10]   = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    float valor_quadra = 834.93;
    float valor_quina  = 32797.02;
    float valor_sena   = 118265926.76;

    if (QD < 6 || QD > 15 || acertos < 4 || acertos > 6)
        return 0.0;

    int idx = QD - 6;

    switch (acertos) {
        case 4: return quadra[idx] * valor_quadra;
        case 5: return quina[idx] * valor_quina;
        case 6: return sena[idx] * valor_sena;
        default: return 0.0;
    }
}




