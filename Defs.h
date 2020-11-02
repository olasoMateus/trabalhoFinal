#ifndef DEFS_H
#define DEFS_H

typedef struct _CARTAS
{
    char naipe[10];
    int pontos;
    int valor;
} CARTA;

typedef struct _MAO
{
    CARTA cartas[14];
    int pontos, qtdCartas;
} MAO;

#endif