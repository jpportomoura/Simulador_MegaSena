#ifndef MEGASENA_H
#define MEGASENA_H
#define MAX_DEZENA 60

void saudacao(int cartela[6][10]);
void solicitar_quantidades(int *QD, int *QM, int *QS, int *QT);
void solicitar_dezenas(int QD, int QM, int apostas[][15]);
void mostrar_apostas(int QD, int QM, int QT, int QS, int apostas[][15]);
int entrada_valida(int *numero);
void calcular_total(int QT, int QM, int QD, int QS, int *valor_total);
void mostra_valor(int valor_total);
char deseja_gravar();
char deseja_recomecar();
void gerar_jogo(int jogo[6]);
int calcular_acertos(int jogo_usuario[], int QD, int jogo_premiado[]);
void gerar_surpresinhas(int QD, int QS, int surpresinhas[][15]);
float calcular_premio(int QD, int acertos);


#endif
