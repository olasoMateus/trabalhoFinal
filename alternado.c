#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>



typedef struct _CARTAS{
	char naipe[10];
	int pontos;
	int valor;
} CARTA;

typedef struct _MAO{
	CARTA cartas[7];
	int pontos, dinheiro;
} MAO;

void embaralhar(int* ordem);
void darCartas(MAO* dealer, MAO* jogador1, CARTA baralho[], int* ordem);


int gNumCArta = 0;

int main(void)
{
    char naipe2[12] = "Espadas";
    char naipe4[12] = "Ouros";
    char naipe1[12] = "Copas";
    char naipe3[12] = "Paus";
    int i, j, n, n2;
    int* ordem;
    CARTA baralho[52] = { 0 }; /* Melhor label para esse objeto é baralho. */

    MAO* dealer;
    MAO* jogador1, split;

    ordem = (int*)malloc(52 * sizeof(int));
    dealer = (MAO*)malloc(1 * sizeof(MAO));
    jogador1 = (MAO*)malloc(1 * sizeof(MAO));

    srand(time(NULL));
    /*==============================================================================*/
    for (i = 0; i <= 12; i++)
    {

        if (i - 9 >= 0) baralho[i].pontos = 10;

        else baralho[i].pontos = i + 1;

        baralho[i].valor = i + 1;

        strcpy(baralho[i].naipe, naipe1);
    }
    for (i = 13; i <= 25; i++)
    {
        if (i - 12 >= 10) baralho[i].pontos = 10;

        else baralho[i].pontos = i - 12;

        baralho[i].valor = i - 12;

        strcpy(baralho[i].naipe, naipe2);
    }
    for (i = 26; i <= 38; i++)
    {
        if (i - 25 >= 10) baralho[i].pontos = 10;

        else baralho[i].pontos = i - 25;

        baralho[i].valor = i - 25;

        strcpy(baralho[i].naipe, naipe3);
    }
    for (i = 39; i <= 52; i++)
    {
        if (i - 38 >= 10) baralho[i].pontos = 10;

        else baralho[i].pontos = i - 38;


        baralho[i].valor = i - 38;
        strcpy(baralho[i].naipe, naipe4);
    }


    /*for (i = 0;i < 52;i++) {
        if (baralho[i].valor == 1) {
            printf("As de %s. Valor: %d\n", baralho[i].naipe, baralho[i].pontos);
        }
        else if (baralho[i].valor == 11) {
            printf("Valete (J) de %s. Valor: %d\n", baralho[i].naipe, baralho[i].pontos);
        }
        else if (baralho[i].valor == 12) {
            printf("Dama (Q) de %s. Valor: %d\n", baralho[i].naipe, baralho[i].pontos);
        }
        else if (baralho[i].valor == 13) {
            printf("Rei (K) de %s. Valor: %d\n", baralho[i].naipe, baralho[i].pontos);
        }
        else{
            printf("%d de %s. Valor: %d\n", baralho[i].valor,baralho[i].naipe, baralho[i].pontos);
        }
    }*/

    embaralhar(ordem);
    printf("Cartas do dealer: \n");

    darCartas(dealer, jogador1, baralho, ordem);

    for (j = 0;j < 2; j++) {
        if (dealer->cartas[j].valor == 1) {
            printf("As de %s. Valor: %d\n", dealer->cartas[j].naipe, dealer->cartas[j].pontos);
        }
        else if (dealer->cartas[j].valor == 11) {
            printf("Valete (J) de %s. Valor: %d\n", dealer->cartas[j].naipe, dealer->cartas[j].pontos);
        }
        else if (dealer->cartas[j].valor == 12) {
            printf("Dama (Q) de %s. Valor: %d\n", dealer->cartas[j].naipe, dealer->cartas[j].pontos);
        }
        else if (dealer->cartas[j].valor == 13) {
            printf("Rei (K) de %s. Valor: %d\n", dealer->cartas[j].naipe, dealer->cartas[j].pontos);
        }
        else {
            printf("%d de %s. Valor: %d\n", dealer->cartas[j].valor, dealer->cartas[j].naipe, dealer->cartas[j].pontos);
        }
    }


    /*printf("\n\nAgora, sorteado:\n\n");


    for (j = 0; j < 52; j++)
    {
        if (baralho[*(ordem + j)].valor == 1) {
            printf("%d: As de %s.\n", *(ordem + j), baralho[*(ordem + j)].naipe);
        }
        else if (baralho[*(ordem + j)].valor == 11) {
            printf("%d: Valete (J) de %s.\n", *(ordem + j), baralho[*(ordem + j)].naipe);
        }
        else if (baralho[*(ordem + j)].valor == 12) {
            printf("%d: Dama (Q) de %s.\n", *(ordem + j), baralho[*(ordem + j)].naipe);
        }
        else if (baralho[*(ordem + j)].valor == 13) {
            printf("%d: Rei (K) de %s.\n", *(ordem + j), baralho[*(ordem + j)].naipe);
        }
        else {
            printf("%d: %d de %s.\n", *(ordem + j), baralho[*(ordem + j)].valor, baralho[*(ordem + j)].naipe);
        }
    }*/

    puts("\n");
    system("PAUSE");


    return 0;
}

void embaralhar(int * ordem) {
    int i = 0, j = 0, n;

    srand(time(NULL));

    for (i = 0; i < 52; i++)
    {
        n = rand() % 52;
        for (j = 0; j < i; j++) {
            if (n == *(ordem + j)) {
                i--;
                break;
            }
        }
        if (j == i) {
            *(ordem + i) = n;
        }
    }
    gNumCArta = 0;

    return;

}

void darCartas(MAO *dealer, MAO *jogador1, CARTA baralho[], int* ordem) {
    int i = 0, j = 1;

    for (i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            dealer->cartas[j - 1].pontos = baralho[*(ordem + gNumCArta)].pontos;
            strcpy(dealer->cartas[j - 1].naipe, baralho[*(ordem + gNumCArta)].naipe);
            dealer->cartas[j - 1].valor = baralho[*(ordem + gNumCArta)].valor;
            gNumCArta++;
        }
        if (i % 2 == 1) {
            jogador1->cartas[j - 1].pontos = baralho[*(ordem + gNumCArta)].pontos;
            strcpy(jogador1->cartas[j - 1].naipe, baralho[*(ordem + gNumCArta)].naipe);
            jogador1->cartas[j - 1].valor = baralho[*(ordem + gNumCArta)].valor;
            gNumCArta++;
            j++;
        }
    }

    return;
}