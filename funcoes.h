#ifndef FUNCOES_H
#define FUNCOES_H

#include "Defs.h"
#include "Globais.h"

void embaralhar(int *ordem);
void darCartas(MAO *dealer, MAO *jogador1, CARTA baralho[], int *ordem);
int pontos(MAO *mao, MAO *jogador1, MAO *dealer);
int hit(MAO *mao, CARTA baralho[], int *ordem, MAO *jogador1, MAO *dealer);
int doubleAposta(MAO* mao, CARTA baralho[], int* ordem, int* aposta,MAO* jogador1, MAO* dealer);
void mostrarCartas(MAO *mao, int u);
void vencedor(MAO *jogador1, MAO *dealer);
void criarBaralho(CARTA baralho[]);
void rodada(MAO *dealer, MAO *jogador1, CARTA baralho[], int *ordem, int* aposta);

#endif