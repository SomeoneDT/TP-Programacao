/**
Trabalho Prático - Programação 2022/23
Daniel Vitor Baroa Domingues Tinoco
2021132552
**/

#ifndef PTP_ESTACOES_H
#define PTP_ESTACOES_H

#include <sistemas.h>


//estacoes.c
pstation addstation(station *paragens, int *total);
void printstations(station *paragens, int total);
pstation delstation(station *paragens, int *total, pline linhas);

#endif //PTP_ESTACOES_H
