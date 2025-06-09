#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <ctype.h>   
#include "megasena.h"

//Boas vindas ao usuário e explica o jogo
 void saudacao (int cartela [6][10]){
    printf("\nSeja bem-vindo a Mega Sena 2025\n");
    printf("---- Conheca o nosso jogo ----\n");
    printf("\nCARTELA DAS APOSTAS:\n");
    printf("(Nela voce pode jogar ate 15 dezenas dessas e pode jogar com ate 3 volantes)\n");
    int valor = 0;
    for(int i= 0; i < 6; i++){
        for(int j = 0; j < 10; j++){
            valor = valor + 1;
            cartela [i][j] = valor;
        }
    }for(int i = 0; i < 6; i++){
        for(int j = 0; j < 10; j++){
            printf("%02d   ", cartela[i][j]);   
        }printf("\n");
    }
    printf("\nSURPRESINHA - Aqui o sistema escolhe os numeros por voce.\n");
    printf("(Voce pode escolher ate 7 surpresinhas)\n");
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
    printf("\nTEIMOSINHA - Escolhe em quantos concursos quer participar com o mesmo jogo!\n");
    printf("(Voce pode escolher 2, 4 ou 8 vezes que vai usar o mesmo jogo)\n");
    printf("| 2 | 4 | 8 |\n");
 }
//Solicita ao usuário as quantidades de dezenas, apostas manuais, surpresinha e teimosinha
void solicitar_quantidades(int *QD, int *QM, int *QS, int *QT) { 
    printf("\nDigite quantas dezenas deseja apostar (valores possiveis: 6 a 15): ");
    scanf("%d", QD);
    while (*QD < 6 || *QD > 15) {
        printf("Valor invalido! Digite novamente (6 a 15): ");
        scanf("%d", QD);
    }
    printf("\nDigite quantas apostas manuais deseja fazer (valores possiveis: 1 a 3): ");
    scanf("%d", QM);
    while (*QM < 1 || *QM > 3) {
        printf("Valor invalido! Digite novamente (1 a 3): ");
        scanf("%d", QM);
    }
    printf("\nDigite a quantidade de Surpresinhas que deseja apostar (valores possiveis: 0 a 7):");
    scanf("%d", QS);
    while (*QS < 0 || *QS > 7) {
        printf("Valor invalido! Digite novamente (0 a 7): ");
        scanf("%d", QS);
    }
    printf("\nDigite a quantidade de Teimosinhas. Valores validos: 2, 4, 8 (Digite 1 para jogar somente um jogo):");
    scanf("%d", QT);
    while (*QT < 1 || (*QT != 1 && *QT != 2 && *QT != 4 && *QT != 8)) {
        printf("Valor invalido! Digite novamente (1, 2, 4 ou 8): ");
        scanf("%d", QT);
    }
    while (getchar() != '\n');
}
//Função para o usuário não digitar dezenas repetidas
int entrada_valida(int *numero) { 
    char buffer[100];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return 0;

    buffer[strcspn(buffer, "\n")] = 0;

    for (int i = 0; buffer[i]; i++) {
        if (!isdigit(buffer[i])) return 0;
    }

    *numero = atoi(buffer);
    return 1;
}
//Solicita ao usuário as dezenas que irá marcar no volante
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
                printf("Dezena fora do intervalo permitido (1 a %d)!\n", MAX_DEZENA);
                continue;
            }
            int repetida = 0;
            for (int k = 0; k < j; k++) {
                if (apostas[i][k] == dezena) {
                    printf("Dezena repetida! Digite uma diferente.\n");
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
//Mostra ao usuário as apostas realizadas pelo mesmo e o valor total para pagamento.
void mostrar_apostas (int QD, int QM, int QT, int QS, int apostas [][15]){
    printf("\n------ APOSTAS ------\n");
    for (int j = 0; j < QM; j++) {
        printf("Jogo %d - Dezenas: ", j + 1);
        for (int i = 0; i < QD; i++) {
            printf("| %02d | ", apostas[j][i]);
        }
        printf("\n");
    }
    printf("\nSurpresinhas: %d", QS);
    printf("\nTeimosinhas: %d", QT);
}
//Efetua o calculo do valor que será pago pelas apostas
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
    *valor_total = QT * (VD * (QM + QS));
}
//Função para mostrar os valor das apostas
void mostra_valor(int valor_total) {
    printf("\nValor total das apostas: R$ %d,00\n", valor_total);
}
//Função para confirmar se o usuário quer concluir o jogo digitado anteriormente
char deseja_gravar() {
    char resposta;
    do {
        printf("\nDeseja gravar o seu jogo? (S/N): ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta);

        if (resposta != 'S' && resposta != 'N') {
            printf("Opcao invalida! Digite apenas S ou N.\n");
        }
    } while (resposta != 'S' && resposta != 'N');

    return resposta;
}
//Se o usuário não quiser gravar o jogo, pergunta se quer efetuar outro jogo
char deseja_recomecar() {
    char resposta;
    do {
        printf("Deseja recomecar? (S/N): ");
        scanf(" %c", &resposta);
        resposta = toupper(resposta);

        if (resposta != 'S' && resposta != 'N') {
            printf("Opcao invalida! Digite apenas S ou N.\n");
        }
    } while (resposta != 'S' && resposta != 'N');

    return resposta;
}
//Função para gerar o jogo que será premiado na mega sena
void gerar_jogo(int jogo[6]){
    int i = 0;
    while(i<6){
        int numero = rand() % 60 +1;
        int repetido = 0;
        for(int j = 0; j < i; j++){
            if (jogo[j] == numero){
                repetido = 1;
                break;
            }
        }
        if (!repetido){
            jogo[i] = numero;
            i++;
        }
    }
}
//Função para calcular os acertos do usuário
int calcular_acertos(int jogo_usuario[], int QD, int jogo_premiado[]){
    int acertos = 0;
    for (int i = 0; i < QD; i++){
        for (int j = 0; j < 6; j++){
            if (jogo_usuario[i] == jogo_premiado[j]){
                acertos++;
                break;
            }
        }
    }
    return acertos;
}