/**
Trabalho Prático - Programação 2022/23
Daniel Vitor Baroa Domingues Tinoco
2021132552
**/

#ifndef PTP_LINHAS_H
#define PTP_LINHAS_H

#include "sistemas.h"


pline addline(pline linhas, pstation paragens_sistema, int total_sistema);
pline editline(pline p, pstation paragens_sistema, int total_sistema);
pline addstation_to_line(pline p, pstation paragens_sistema, int total_sistema);
pline delline(pline p);
void printlines(pline p, int flag);
void printlines_with_station(pline p);
void savelinetofile(pline p);

#endif //PTP_LINHAS_H
