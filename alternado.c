#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct _CARTAS {
    char naipe[10];
    int pontos;
    int valor;
} CARTA;

typedef struct _MAO {
    CARTA cartas[7];
    int pontos, qtdCartas;
} MAO;

void embaralhar(int* ordem);
void darCartas(MAO* dealer, MAO* jogador1, CARTA baralho[], int* ordem);
int pontos(MAO* mao, MAO* jogador1, MAO* dealer);
int hit(MAO* mao, CARTA baralho[], int* ordem, MAO* jogador1, MAO* dealer);
void mostrarCartas(MAO* mao, int u);
void vencedor(MAO* jogador1, MAO* dealer);
void criarBaralho(CARTA baralho[]);
void rodada(MAO* dealer, MAO* jogador1, CARTA baralho[], int* ordem);

int gNumCArta = 0;
int gNumRodadas = 0;
int gVitorioso = 0;

int main(void)
{
    int j = 1;
    int dinheiro = 1500;
    int aposta = 0;
    const int apostaMinima = 50, apostaMaxima = 500;
    int* ordem;
    CARTA baralho[104] = { 0 }; /* Melhor label para esse objeto � baralho. */

    MAO* dealer;
    MAO* jogador1;

    ordem = (int*)malloc(52 * sizeof(int));
    dealer = (MAO*)malloc(1 * sizeof(MAO));
    jogador1 = (MAO*)malloc(1 * sizeof(MAO));

    system("CLS");
    srand(time(NULL));
    /*==============================================================================*/
    criarBaralho(baralho);

    embaralhar(ordem);

    while (dinheiro >= 50 && j == 1) {
        system("CLS");
        aposta = 0;
        gNumRodadas++;
        while (aposta < apostaMinima || aposta > apostaMaxima || aposta % 50 != 0) {
            printf("Quanto deseja apostar?\n");
            scanf("%d", &aposta);
            if (aposta < apostaMinima) printf("Aposta muito baixa!!!\n");
            if (aposta > apostaMaxima) printf("Aposta muito alta!!!\n");
            if (aposta % 50 != 0) printf("Cada ficha vale 50. Nao eh possivel apostar uma fracao de ficha!!!\n");
        }
        rodada(dealer, jogador1, baralho, ordem);
        if (gNumRodadas == 5) {
            printf("Embaralhando...\nPronto!!!\n");
            embaralhar(ordem);
            gNumRodadas = 0;
        }
        if (gVitorioso == 1 && jogador1->pontos == 21 && jogador1->qtdCartas == 2) dinheiro += aposta * 2;
        else if (gVitorioso == 1) dinheiro += aposta;
        if (gVitorioso == -1) dinheiro -= aposta;
        printf("Dinheiro: %d\nDeseja jogar outra rodada(1 - sim/ 2 - nao)?\n", dinheiro);
        scanf("%d", &j);
    }

    if (dinheiro < 50) printf("Que pena, voce faliu.\n");


    puts("\n");

    return 0;
}

void embaralhar(int* ordem) {
    int i = 0, j = 0, n;

    srand(time(NULL));

    for (i = 0; i < 104; i++)
    {
        n = rand() % 104;
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

void darCartas(MAO* dealer, MAO* jogador1, CARTA baralho[], int* ordem) {
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

int pontos(MAO* mao, MAO* jogador1, MAO* dealer) {
    int i = 0, as = 0, vdr = 0, total = 0;
    for (i = 0;i < mao->qtdCartas; i++) {
        if (mao->cartas[i].pontos == 1) {
            as = 1;
            continue;
        }
        if (mao->cartas[i].pontos == 10) {
            vdr = 1;
        }
        total = total + mao->cartas[i].pontos;
    }

    if (total > 21) {
        printf("Estouro!\n");
        mao->pontos = total;
        mostrarCartas(mao, 0);
        vencedor(jogador1, dealer);
        return 1;
    }

    if (as == 1 && vdr == 1 && mao->qtdCartas == 2) {
        printf("21!!\n");
        mao->pontos = 21;
        vencedor(jogador1, dealer);
        return 1;
    }
    else if (as == 1)
    {
        if (total > 10) {
            mao->pontos = total + 1;
            return 0;
        }
        else {
            mao->pontos = total + 11;
            return 0;
        }
    }
    else {
        mao->pontos = total;
        if (mao->pontos == 21) return 1;
        return 0;
    }
}

int hit(MAO* mao, CARTA baralho[], int* ordem, MAO* jogador1, MAO* dealer) {

    mao->cartas[mao->qtdCartas].pontos = baralho[*(ordem + gNumCArta)].pontos;
    strcpy(mao->cartas[mao->qtdCartas].naipe, baralho[*(ordem + gNumCArta)].naipe);
    mao->cartas[mao->qtdCartas].valor = baralho[*(ordem + gNumCArta)].valor;
    gNumCArta++;
    mao->qtdCartas++;

    if (pontos(mao, jogador1, dealer) == 1) return 1;


    return 0;
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
    printf("\n");
}

void vencedor(MAO* jogador1, MAO* dealer) {

    printf("\n");
    printf("pontuacao do jogador: %d\n", jogador1->pontos);
    printf("pontuacao do dealer: %d\n", dealer->pontos);

    printf("\n");
    if ((jogador1->pontos > dealer->pontos && jogador1->pontos <= 21) || (dealer->pontos > 21 && jogador1->pontos <= 21)) gVitorioso = 1,printf("Jogador venceu!!!\n");
    else if ((dealer->pontos > jogador1->pontos && dealer->pontos <= 21) || (jogador1->pontos > 21 && dealer->pontos <= 21)) gVitorioso = -1,printf("Dealer venceu!!!!\n");
    else gVitorioso = 0,printf("Push!!!(empate)\n");

    system("PAUSE");
    return;
}


void criarBaralho(CARTA baralho[]) {
    int i = 0;
    char naipe2[12] = "Espadas";
    char naipe4[12] = "Ouros";
    char naipe1[12] = "Copas";
    char naipe3[12] = "Paus";

    for (i = 0; i <= 12; i++)
    {
        if (i - 9 >= 0) {
            baralho[i].pontos = 10;
            baralho[i + 52].pontos = 10;
        }

        else {
            baralho[i].pontos = i + 1;
            baralho[i + 52].pontos = i + 1;
        }
        baralho[i].valor = i + 1;
        baralho[i + 52].valor = i + 1;

        strcpy(baralho[i].naipe, naipe1);
        strcpy(baralho[i + 52].naipe, naipe1);
    }
    for (i = 13; i <= 25; i++)
    {
        if (i - 12 >= 10) {
            baralho[i].pontos = 10;
            baralho[i + 52].pontos = 10;
        }

        else {
            baralho[i].pontos = i - 12;
            baralho[i + 52].pontos = i - 12;
        }

        baralho[i].valor = i - 12;
        baralho[i + 52].valor = i - 12;

        strcpy(baralho[i].naipe, naipe2);
        strcpy(baralho[i + 52].naipe, naipe2);
    }
    for (i = 26; i <= 38; i++)
    {
        if (i - 25 >= 10) {
            baralho[i].pontos = 10;
            baralho[i + 52].pontos = 10;
        }
        else {
            baralho[i].pontos = i - 25;
            baralho[i + 52].pontos = i - 25;
        }


        baralho[i].valor = i - 25;
        baralho[i + 52].valor = i - 25;

        strcpy(baralho[i].naipe, naipe3);
        strcpy(baralho[i + 52].naipe, naipe3);
    }
    for (i = 39; i < 52; i++)
    {
        if (i - 38 >= 10) {
            baralho[i].pontos = 10;
            baralho[i + 52].pontos = 10;
        }
        else {
            baralho[i].pontos = i - 38;
            baralho[i + 52].pontos = i - 38;
        }


        baralho[i].valor = i - 38;
        baralho[i + 52].valor = i - 38;

        strcpy(baralho[i].naipe, naipe4);
        strcpy(baralho[i + 52].naipe, naipe4);
    }

    return;
}

void rodada(MAO* dealer, MAO* jogador1, CARTA baralho[], int* ordem) {
    int j = 0;

    printf("Cartas do dealer: \n");

    darCartas(dealer, jogador1, baralho, ordem);
    if (dealer->pontos)
    {
        jogador1->pontos = 0;
    }

    mostrarCartas(dealer, 1);

    pontos(dealer, jogador1, dealer);

    printf("Cartas do jogador: \n");

    mostrarCartas(jogador1, 0);
    pontos(jogador1, jogador1, dealer);
    printf("Pontos do jogador: %d\n", jogador1->pontos);

    while (jogador1->pontos < 21) {
        printf("Deseja dar hit? 1 -s 2 -n\n");
        scanf("%d", &j);
        if (j == 1) {
            if (hit(jogador1, baralho, ordem, jogador1, dealer) == 1) return;
            if(pontos(jogador1, jogador1, dealer) == 1) return;
            printf("Pontos do jogador: %d\n", jogador1->pontos);
            printf("\n");
        }
        else if (j == 2) {
            break;
        }
    }

    mostrarCartas(dealer, 0);

    printf("Pontos do dealer: %d\n", dealer->pontos);
    while (dealer->pontos < 17 && dealer->qtdCartas < 5) {
        if (hit(dealer, baralho, ordem, jogador1, dealer) == 1) return;
        printf("Cartas do dealer: \n");
        mostrarCartas(dealer, 0);
        if(pontos(dealer, jogador1, dealer) == 1) return;
        printf("Pontos do dealer: %d\n", dealer->pontos);
    }

    vencedor(jogador1, dealer);


    return;
}