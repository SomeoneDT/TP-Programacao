/**
Trabalho Prático - Programação 2022/23
Daniel Vitor Baroa Domingues Tinoco
2021132552
**/

#ifndef PTP_UTILS_H
#define PTP_UTILS_H


#include "sistemas.h"

void generatecode(station *estacao, int total);
int station_is_in_line(pline p, char *codigo);
int lines_station_common(pline inicio, pline destino);
void guarda_dados(pstation paragens, int total, pline linhas);
pstation carrega_estacoes(int *total);
pline carrega_linhas(pline p);
pline addiciona_final(pline p, pline novo);
void freelines(pline p);


#endif //PTP_UTILS_H
