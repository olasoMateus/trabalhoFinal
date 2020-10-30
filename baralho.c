#include<stdio.h>
#include<string.h>
#include<stdio.h>
#include<time.h>


typedef struct _CARTAS{
	char naipe[10];
	int valor, pega;
	char info;
} CARTA;

typedef struct _MAO{
	CARTA * cartas;
	int pontos, dinheiro;
} MAO;

int main(void)
{
    char naipe2[12] = "Espadas";
    char naipe4[12] = "Ouros";
    char naipe1[12] = "Copas";
    char naipe3[12] = "Paus";
    int i, n, n2;
    CARTA baralho[52] = { 0 }; /* Melhor label para esse objeto � baralho. */


    srand(time(NULL));
    /*==============================================================================*/
    for (i = 0; i <= 12; i++)
    {
        baralho[i].valor = i + 1;
        strcpy(baralho[i].naipe, naipe1);
        baralho[i].pega = 0;
    }
    for (i = 13; i <= 25; i++)
    {
        baralho[i].valor = i - 12;
        strcpy(baralho[i].naipe, naipe2);
        baralho[i].pega = 0;
    }
    for (i = 26; i <= 38; i++)
    {
        baralho[i].valor = i - 25;
        strcpy(baralho[i].naipe, naipe3);
        baralho[i].pega = 0;
    }
    for (i = 39; i <= 52; i++)
    {
        baralho[i].valor = i - 38;
        strcpy(baralho[i].naipe, naipe4);
        baralho[i].pega = 0;
    }
    /*==============================================================================*/

    for (i = 0;i < 52;i++) {
        if (baralho[i].valor == 1) {
            printf("As de %s.\n", baralho[i].naipe);
        }
        else if (baralho[i].valor == 11) {
            printf("Valete (J) de %s.\n", baralho[i].naipe);
        }
        else if (baralho[i].valor == 12) {
            printf("Dama (Q) de %s.\n", baralho[i].naipe);
        }
        else if (baralho[i].valor == 13) {
            printf("Rei (K) de %s.\n", baralho[i].naipe);
        }
        else{
            printf("%d de %s.\n", baralho[i].valor,baralho[i].naipe);
        }
    }

    printf("\n\nAgora, sorteado:\n\n");

    for (i = 0; i < 52; i++)
    {
        n = rand() % 52;
        while (baralho[n].pega == 1) {
            n = rand() % 52;
        }
        baralho[n].pega = 1;
        if (baralho[n].valor == 1) {
            printf("%d: As de %s.\n", n, baralho[n].naipe);
        }
        else if (baralho[n].valor == 11) {
            printf("%d: Valete (J) de %s.\n", n, baralho[n].naipe);
        }
        else if (baralho[n].valor == 12) {
            printf("%d: Dama (Q) de %s.\n", n, baralho[n].naipe);
        }
        else if (baralho[n].valor == 13) {
            printf("%d: Rei (K) de %s.\n", n, baralho[n].naipe);
        }
        else {
            printf("%d: %d de %s.\n", n, baralho[n].valor, baralho[n].naipe);
        }
    }

    puts("\n");
    system("PAUSE");


    return 0;
}