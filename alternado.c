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
	int pontos, dinheiro, qtdCartas;
} MAO;

void embaralhar(int* ordem);
void darCartas(MAO* dealer, MAO* jogador1, CARTA baralho[], int* ordem);
void pontos(MAO* mao);
void hit(MAO* mao, CARTA baralho[], int* ordem);
void mostrarCartas(MAO* mao, int u);


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


    embaralhar(ordem);
    printf("Cartas do dealer: \n");

    darCartas(dealer, jogador1, baralho, ordem);

    mostrarCartas(dealer, 1);


    pontos(dealer);
    if (dealer->pontos == 21) {
        printf("21!! Jogador perde automaticamente.\n");
    }

    printf("Cartas do jogador: \n");

    mostrarCartas(jogador1, 0);
    pontos(jogador1);
    printf("Pontos do jogador: %d\n", jogador1->pontos);

    


    while (jogador1->pontos < 21) {
        printf("Deseja dar hit? 1 -s 2 -n\n");
        scanf("%d", &j);
        if (j == 1) {
            hit(jogador1, baralho, ordem);
            printf("Cartas do jogador: \n");
            mostrarCartas(jogador1, 0);
            pontos(jogador1);
            printf("Pontos do jogador: %d\n", jogador1->pontos);
        }
        else if (j == 2) {
            break;
        }
    }

    mostrarCartas(dealer, 0);

    printf("Pontos do dealer: %d\n", dealer->pontos);
    while (dealer->pontos < 17 && dealer->qtdCartas < 5) {
        hit(dealer, baralho, ordem);
        printf("Cartas do dealer: \n");
        mostrarCartas(dealer, 0);
        pontos(dealer);
        printf("Pontos do dealer: %d\n", dealer->pontos);
    }

    if (jogador1->pontos > dealer->pontos) printf("Jogador venceu!!!\n");
    else if (dealer->pontos > jogador1->pontos) printf("Dealer venceu!!!!\n");
    else printf("Push!!!(empate)\n");


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

    dealer->qtdCartas = 0;
    jogador1->qtdCartas = 0;

    for (i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            dealer->cartas[j - 1].pontos = baralho[*(ordem + gNumCArta)].pontos;
            strcpy(dealer->cartas[j - 1].naipe, baralho[*(ordem + gNumCArta)].naipe);
            dealer->cartas[j - 1].valor = baralho[*(ordem + gNumCArta)].valor;
            gNumCArta++;
            dealer->qtdCartas++;
        }
        if (i % 2 == 1) {
            jogador1->cartas[j - 1].pontos = baralho[*(ordem + gNumCArta)].pontos;
            strcpy(jogador1->cartas[j - 1].naipe, baralho[*(ordem + gNumCArta)].naipe);
            jogador1->cartas[j - 1].valor = baralho[*(ordem + gNumCArta)].valor;
            gNumCArta++;
            j++;
            jogador1->qtdCartas++;
        }
    }

    return;
}

void pontos(MAO* mao) {
    int i = 0, j = 0, h = 0, total = 0;
    for (i = 0;i < mao->qtdCartas; i++) {
        if (mao->cartas[i].pontos == 1) {
            j = 1;
            continue;
        }
        if (mao->cartas[i].pontos == 10) {
            h = 1;
        }
        total = total + mao->cartas[i].pontos;
    }

    if (total > 21) {
        printf("Estouro!\n");
        mao->pontos = total;
        return;
    }

    if (j == 1 && h == 1) {
        printf("21!!\n");
        mao->pontos = 21;
        return;
    }
    else if(j == 1)
    {
        if (total > 10) {
            mao->pontos = total + 1;
            return;
        }
        else {
            mao->pontos = total + 11;
            return;
        }
    }
    else {
        mao->pontos = total;
        return;
    }
}

void hit(MAO* mao, CARTA baralho[], int* ordem) {
    int  i = 0;

    mao->cartas[mao->qtdCartas].pontos = baralho[*(ordem + gNumCArta)].pontos;
    strcpy(mao->cartas[mao->qtdCartas].naipe, baralho[*(ordem + gNumCArta)].naipe);
    mao->cartas[mao->qtdCartas].valor = baralho[*(ordem + gNumCArta)].valor;
    gNumCArta++;
    mao->qtdCartas++;

    pontos(mao);

    return;
}

void mostrarCartas(MAO* mao, int u) {
    int  j = 0;

    for (j = 0;j < mao->qtdCartas - u; j++) {
        if (mao->cartas[j].valor == 1) {
            printf("As de %s. Valor: %d\n", mao->cartas[j].naipe, mao->cartas[j].pontos);
        }
        else if (mao->cartas[j].valor == 11) {
            printf("Valete (J) de %s. Valor: %d\n", mao->cartas[j].naipe, mao->cartas[j].pontos);
        }
        else if (mao->cartas[j].valor == 12) {
            printf("Dama (Q) de %s. Valor: %d\n", mao->cartas[j].naipe, mao->cartas[j].pontos);
        }
        else if (mao->cartas[j].valor == 13) {
            printf("Rei (K) de %s. Valor: %d\n", mao->cartas[j].naipe, mao->cartas[j].pontos);
        }
        else {
            printf("%d de %s. Valor: %d\n", mao->cartas[j].valor, mao->cartas[j].naipe, mao->cartas[j].pontos);
        }
    }
}

