#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#include "Defs.h"
#include "Globais.h"

int main(void)
{
    int j = 1;
    int dinheiro = 1500;
    int aposta = 0;
    const int apostaMinima = 50, apostaMaxima = 500;
    int *ordem;
    CARTA baralho[104] = {0}; /* Melhor label para esse objeto � baralho. */

    MAO *dealer;
    MAO *jogador1;

    ordem = (int *)malloc(52 * sizeof(int));
    dealer = (MAO *)malloc(1 * sizeof(MAO));
    jogador1 = (MAO *)malloc(1 * sizeof(MAO));

    system("CLS");
    srand(time(NULL));
    /*==============================================================================*/

    criarBaralho(baralho);
    embaralhar(ordem);

    while (dinheiro >= 50 && j == 1)
    {
        system("CLS");
        aposta = 0;
        gNumRodadas++;
        while (aposta < apostaMinima || aposta > apostaMaxima || aposta % 50 != 0)
        {
            printf("Dinheiro do jogador: %d // Aposta minima : %d // aposta maxima: %d\n", dinheiro, apostaMinima, apostaMaxima);
            printf("Quanto deseja apostar?\n");
            scanf("%d", &aposta);
            if (aposta < apostaMinima)
                printf("Aposta muito baixa!!!\n");
            if (aposta > apostaMaxima)
                printf("Aposta muito alta!!!\n");
            if (aposta % 50 != 0)
                printf("Cada ficha vale 50. Nao eh possivel apostar uma fracao de ficha!!!\n");
        }
        rodada(dealer, jogador1, baralho, ordem);
        if (gNumRodadas % 5 == 0)
        {
            printf("Embaralhando...\nPronto!!!\n");
            embaralhar(ordem);
            gNumRodadas = 0;
        }
        if (gVitorioso == 1 && jogador1->pontos == 21 && jogador1->qtdCartas == 2)
            dinheiro += aposta * 2;
        else if (gVitorioso == 1)
            dinheiro += aposta;
        if (gVitorioso == -1)
            dinheiro -= aposta;
        printf("Dinheiro: %d\nDeseja jogar outra rodada(1 - sim/ 2 - nao)?\n", dinheiro);
        scanf("%d", &j);
    }

    if (dinheiro < 50)
        printf("Que pena, voce faliu.\n");

    puts("\n");

    return 0;
}

