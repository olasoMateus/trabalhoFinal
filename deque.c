Baralho de Cartas
Daniel Hashimoto Andrade
•
9 de out.Editado às 22 de out.

carddeck.c
C

Enunciado Baralho de Cartas.odt
OpenOffice Writer
Comentários da turma


Seus trabalhos
Atribuído
Comentários particulares


#include <stdio.h>

/* ---------- ---------- ---------- ---------- ---------- ----------
 * Agora uma implementação de Deque (
 * Double-Ended Queue: uma Queue que pode mexer no inicio e no final
 * ), modifique por sua conta e risco :)
 * Já esta implementado
 * Se encontar algum bug avise ao monitor @hashi364
 * ---------- ---------- ---------- ---------- ---------- ----------
 */
#define TEST_DEQUE
#undef TEST_DEQUE

 /* O tipo que o Deck vai guardar. Pode mudar */
#define TIPO int
/* O tamanho máximo+1 que Deck pode guardar. Pode mudar, mantenha > 1 */
#define TAM_DEQUE 65

/* Isso é uma struct: uma junção de vários dados
 * gerando um dado personalizado
 */
	typedef struct {
	TIPO d[TAM_DEQUE];		// data  | dados
	size_t s;				// start | início
	size_t e;	  			// end   | final
} deque;
/* size_t é um unsigned grande o suficiente para
 * fazer operações com vetor (Ex: v[3])
 */

 /* Está vazio
  * retorna
  * 0 em "deque não vazio",
  * 1 em "deque vazio"
  */
int isEmpty(deque* d) {
	return !(d->s - d->e);
}

/* Está cheio
 * retorna
 * 0 em "deque não cheio",
 * 1 em "deque cheio"
 */
int isFull(deque* d) {
	return d->s == (d->e + 1) % TAM_DEQUE;
}

/* Tamanho
 * retona o tamanho (quantidade de itens)
 */
size_t size(deque* d) {
	return (d->e - d->s + TAM_DEQUE) % TAM_DEQUE;
}

/* Add Start | Adiciona Início
 * Adiciona thing no início do deque
 * retorna
 * 0 em sucesso,
 * -1 em "deque cheio"
 */
int addS(deque* d, TIPO thing) {
	return isFull(d) ?
		(-1) :
		(
			d->s = (d->s - 1 + TAM_DEQUE) % TAM_DEQUE,
			*(d->d + d->s) = thing, 0
			);
}

/* Add End | Adiciona Final
 * Adiciona thing no final do deque
 * retorna
 * 0 em sucesso,
 * -1 em "deque cheio"
 */
int addE(deque* d, TIPO thing) {
	return isFull(d) ?
		(-1) :
		(
			d->e = (d->e + 1) % TAM_DEQUE,
			*(d->d + d->e) = thing, 0
			);
}

/* Pop Start | Remove Início
 * Retira um TIPO do início do deque,
 * guarda em *thing
 * retorna
 * 0 em sucesso,
 * -1 em "deque vazio"
 */
int popS(deque* d, TIPO* thing) {
	return isEmpty(d) ?
		(-1) :
		(
			*thing = *(d->d + d->s),
			d->s = (d->s + 1) % TAM_DEQUE, 0
			);
}

/* Pop End | Remove Final
 * Retira um TIPO do final do deque,
 * guarda em *thing
 * retorna
 * 0 em sucesso,
 * -1 em "deque vazio"
 */
int popE(deque* d, TIPO* thing) {
	return isEmpty(d) ?
		(-1) :
		(
			d->e = (d->e - 1 + TAM_DEQUE) % TAM_DEQUE,
			*thing = *(d->d + d->e), 0
			);
}

/* Peak Start | Espia Início
 * Olha um TIPO do início do deque,
 * guarda em *thing
 * retorna
 * 0 em sucesso,
 * -1 em "deque vazio"
 */
int peakS(deque* d, TIPO* thing) {
	return isEmpty(d) ?
		(-1) :
		(
			*thing = *(d->d + d->s), 0
			);
}

/* Pop End | Remove Final
 * Retira um TIPO do final do deque,
 * guarda em *thing
 * retorna
 * 0 em sucesso,
 * -1 em "deque vazio"
 */
int peakE(deque* d, TIPO* thing) {
	return isEmpty(d) ?
		(-1) :
		(
			*thing = *(d->d + d->e), 0
			);
}

/* ---------- ---------- ---------- ---------- ---------- ----------
 * Termina implementação de Deque
 * ---------- ---------- ---------- ---------- ---------- ----------
 */

 /* ---------- ---------- ---------- ---------- ---------- ----------
  * Agora seguem códigos para implementar, implemente :)
  * ---------- ---------- ---------- ---------- ---------- ----------
  */

  /* Para acessar um elemento dentro de uma struct se usa var.ele
   * ou var->ele se var for um ponteiro
   */
typedef struct {
	deque* d;
	// insira dados se necessários
} deck;

/* Inicializa o baralho com a seed.
 * returna 0 em sucesso, -1 em erro.
 * Erros acontecem quando a função não foi implementada
 */
int reset(deck* d, unsigned int seed) {
	return -1;
}

/* Reorganiza as cartas de forma aleatória.
 * returna 0 em sucesso, -1 em erro.
 * Erros acontecem quando a função não foi implementada
 */
int shuffle(deck* d) {
	return -1;
}

/* Retira uma carta do baralho e guarda em carta.
 * returna 0 em sucesso, -1 em erro.
 * Erros acontecem quando a função não foi implementada
 * ou o deck está vazio.
 */
int draw(deck* d, TIPO* card) {
	return -1;
}

/* Põe uma carta no topo do baralho.
 * returna 0 em sucesso, -1 em erro.
 * Erros acontecem quando a função não foi implementada
 * ou deck está cheio.
 */
int PutTop(deck* d, TIPO card) {
	return -1;
}

/* Põe uma carta no final do baralho.
 * returna 0 em sucesso, -1 em erro.
 * Erros acontecem quando a função não foi implementada
 * ou deck está cheio.
 */
int PutBot(deck* d, TIPO card) {
	return -1;
}

/* Transforma carta em uma string e guarda em s.
 * returna 0 em sucesso, -1 em erro.
 * Erros acontecem quando a função não foi implementada
 * ou não cabe em s.
 * Não precisa implementar.
 */
int printCard(TIPO card, char* s, size_t len) {
	return -1;
}

#define SEED1 123
#define SEED2 321

#define DRAW_AMOUNT 3

#define LEN 30

/* ---------- ---------- ---------- ---------- ---------- ----------
 * Agora seguem códigos de teste, modifique por sua conta e risco :)
 * ---------- ---------- ---------- ---------- ---------- ----------
 */

int main() {
	int err, err2, i;
	deck mem1, * d1 = &mem1, mem2, * d2 = &mem2;
	TIPO card;
	char s[LEN] = "";

	puts("Testando reset");
	err = reset(d1, SEED1);
	printf("err=%d: Reset de d1 com a seed (%u)\n", err, SEED1);

	err = reset(d2, SEED2);
	printf("err=%d: Reset de d2 com a seed (%u)\n", err, SEED2);

	puts("\n\nTestando draw");
	for (i = 0; i < DRAW_AMOUNT; i++) {
		err = draw(d1, &card);
		if (!(err2 = printCard(card, s, LEN))) {
			printf("err=%d: PrintCard card(0x%X): %s\n", err, card, s);
		}
		printf("err=%d: Draw d1: %s\n", err, s);
	}
	for (i = 0; i < DRAW_AMOUNT; i++) {
		err = draw(d2, &card);
		if (!(err2 = printCard(card, s, LEN))) {
			printf("err=%d: PrintCard card(0x%X): %s\n", err, card, s);
		}
		printf("err=%d: Draw d2: %s\n", err, s);
	}

	return 0;
}