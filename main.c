#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "funcoes.h"
#include "Defs.h"
#include "Globais.h"

int main(void)
{
    int j = 1, h = 0;
    int dinheiro = 1500;
    int aposta = 0;
    const int apostaMinima = 50, apostaMaxima = 500;
    int *ordem;
    char p;
    CARTA baralho[104] = {0}; 
    FILE* pFile;

    MAO* dealer;
    MAO* jogador1;
    
    setlocale(LC_ALL, "Portuguese");

    system("CLS");

    printf("Ola, bem - vindo ao nosso jogo de 21!!! Voce deseja ver as regras ou quer jogar imediatamente?(1 - Sim/ Qualquer outro numero - nao)\n");
    scanf("%d", &j);
    if (j == 1) {
        pFile = fopen("Regras.txt", "r");
        if (!pFile) exit(1);
        p = fgetc(pFile);
        while (p != EOF) {
            if (p == '\n') {
                h = 0;
            }
            if (h >= 80) {
                if (p == ' ') {
                    printf("\n");
                    h = 0;
                }
            }

            printf("%c", p);
            p = fgetc(pFile);
            h++;
        }
        
        system("PAUSE");
        fclose(pFile);
    }

    ordem = (int *)malloc(52 * sizeof(int));
    dealer = (MAO *)malloc(1 * sizeof(MAO));
    jogador1 = (MAO *)malloc(1 * sizeof(MAO));

    srand(time(NULL));
    /*==============================================================================*/

    criarBaralho(baralho);
    embaralhar(ordem);
    j = 1;
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
        printf("RODADA %d\n\n\n", gNumRodadas);
        rodada(dealer, jogador1, baralho, ordem, &aposta);
        if (gNumRodadas % 5 == 0)
        {
            printf("Embaralhando...\n");
            embaralhar(ordem);
            curiosidade(pFile);
            printf("\n\nPronto!!!\n");
            system("PAUSE");
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
        while (j != 1 && j != 2) {
            printf("Digite um valor valido!!!!\n\n");
            printf("Dinheiro: %d\nDeseja jogar outra rodada(1 - sim/ 2 - nao)?\n", dinheiro);
            scanf("%d", &j);
        }
    }

    if (dinheiro < 50) printf("Que pena, voce faliu.\n");
    else if (dinheiro == 1500) printf("Voce nao teve nem lucro nem prejuizo!\n");
    else if (dinheiro < 1500) printf("Voce teve %d de prejuizo!! Treine mais e melhore seu ganho!!!\n", 1500 - dinheiro);
    else printf("Voce teve %d de lucro!! Parabens!!!\n", dinheiro - 1500);

    puts("\n");

    return 0;
}

