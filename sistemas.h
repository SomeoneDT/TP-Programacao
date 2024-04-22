/**
Trabalho Prático - Programação 2022/23
Daniel Vitor Baroa Domingues Tinoco
2021132552
**/


#ifndef SISTEMAS_H_INCLUDED
#define SISTEMAS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define CODE_LEN 4

typedef struct station station, *pstation;
typedef struct line line, *pline;

struct station {
    char nome[100]; // Nome da estação
    char codigo[5]; // Código da estação
};

struct line {
    char nome[100]; // Nome a linha.
    pstation stations_in_line; // Array dinamico de estações presentes na linha.
    int station_count; // Quantidade de estações presentes na linha.
    pline prox; // Ponteiro para a proxima linha.
};

#endif // SISTEMAS_H_INCLUDED
