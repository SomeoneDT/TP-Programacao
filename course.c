/**
Trabalho Prático - Programação 2022/23
Daniel Vitor Baroa Domingues Tinoco
2021132552
**/

#include "sistemas.h"
#include "estacoes.h"
#include "utils.h"
#include "linhas.h"
#include "course.h"

void simula_percurso_2_linhas(pline p,char *codigo_incial, char *codigo_destino);

void simula_percurso(pline linhas, station *paragens, int total) { // Função "base" da simulação do percurso.


    int i, j, k, l;
    pline aux = linhas;
    char codigo_inicial[5];
    char codigo_destino[5];
    int flag_inicial, umalinha = 0, flag_destino;

    printstations(paragens, total);


    // Pedir ao utilizador o código da estação inicial e da estação de destino.
    do {
        printf("\nInsira o codigo da estacao inicial: ");
        scanf(" %5[^\n]", codigo_inicial);
    } while (strlen(codigo_inicial) != 4);

    do {
        printf("\nInsira o codigo da estacao destino: ");
        scanf(" %5[^\n]", codigo_destino);
        if (strcmp(codigo_inicial, codigo_destino) == 0)
            printf("\nA estacao destino nao pode ser igual a estacao inicial!");

    } while (strlen(codigo_destino) != 4 && strcmp(codigo_inicial, codigo_destino) == 0);

    // Loop para percorrer todas as linhas.
    while (aux != NULL) {
        flag_inicial = 0;
        flag_destino = 0;
        // Verificar se encontra as estações inicial e destino na linha atual.
        for (i = 0; i < aux->station_count; i++) {
            if (strcmp(aux->stations_in_line[i].codigo, codigo_inicial) == 0) {
                flag_inicial = 1;
            }
            if (strcmp(aux->stations_in_line[i].codigo, codigo_destino) == 0) {
                flag_destino = 1;
            }
        }

        // Se encontrar as duas estações, imprime a linha e as estações entre elas.
        if (flag_inicial == 1 && flag_destino == 1) {
            printf("\nPodera usar a linha: %s com as seguintes paragens: \n", aux->nome);

            for (i = 0; strcmp(aux->stations_in_line[i].codigo, codigo_inicial) != 0; i++);
            for (j = 0; strcmp(aux->stations_in_line[j].codigo, codigo_destino) != 0; j++);
            if (i > j) {
                for (k = i; k >= j; k--) {
                    printf(" %s", aux->stations_in_line[k].nome);
                    if (k != j)
                        printf(" ->");
                }
            } else {
                for (k = i; k <= j; k++) {
                    printf(" %s", aux->stations_in_line[k].nome);
                    if (k != j)
                        printf(" ->");
                }
            }
            umalinha = 1;
        }
        aux = aux->prox;

    }
    if (umalinha == 0) {
        printf("\nNao e possivel chegar ao seu destino usando apenas uma linha");
    }
    // Chama a função que simula o percurso usando duas linhas.
    simula_percurso_2_linhas(linhas, codigo_inicial, codigo_destino);
}

void simula_percurso_2_linhas(pline p,char *codigo_inicial, char *codigo_destino)
{
    pline aux = p, aux2;
    int i,j,k;
    int estacao_inicial, estacao_destino, flag1;
    // Loop a percorrer para encontrar as linhas que possuem a estação inicial.
    while(aux!=NULL)
    {
        // Verifica se a linha contem a estação inicial
        if(station_is_in_line(aux,codigo_inicial) == 0)
        {
            aux = aux->prox;
            continue;
        }
        // Encontra a posição da estação inicial na linha.
        for(i = 0; strcmp(aux->stations_in_line[i].codigo,codigo_inicial) != 0; i++)
            ;
        aux2 = p;

        // Loop a percorrer para encontrar as linhas que possuem a estação de destino.
        while(aux2!=NULL)
        {
            // Este if verifica que: As linhas não são a mesma, a linha contem a estação de destino e as linhas têm uma estação em comum.
            if(aux == aux2  || station_is_in_line(aux2,codigo_destino) == 0 || lines_station_common(aux,aux2) == 0)
            {
                aux2 = aux2->prox;
                continue;
            }
            // Encontra a posição da estação de destino na linha.
            for(j = 0; strcmp(aux2->stations_in_line[j].codigo,codigo_destino);j++)
                ;
            flag1 = 0;

            // Loop a percorrer para encontrar a estação em comum entre as duas linhas.
            for(estacao_inicial = 0; estacao_inicial < aux->station_count; estacao_inicial++)
            {

                for(estacao_destino = 0; estacao_destino < aux2->station_count; estacao_destino++)
                {
                    if(strcmp(aux->stations_in_line[estacao_inicial].codigo,aux2->stations_in_line[estacao_destino].codigo) == 0)
                    {
                        // verifica se estacao em comum nao é a inicial ou a final
                        if(estacao_inicial == i || estacao_destino == j)
                            continue;
                        flag1 = 1;
                        break;
                    }
                }
                // Se encontrar a estação em comum, imprime as linhas e as estações entre elas.
                if(flag1 == 1)
                {

                    printf("\nPodera usar as linhas: [%s] e [%s] com as seguintes paragens: ",aux->nome,aux2->nome);
                    printf("\nLinha: [%s]\n",aux->nome);
                    if(estacao_inicial > i)
                    {
                        for(k = i; k <= estacao_inicial; k++)
                        {
                            printf(" %s ",aux->stations_in_line[k].nome);
                            if(k != estacao_inicial)
                                printf(" - ");
                        }
                    }
                    else
                    {
                        for(k = estacao_inicial; k <= i; k++)
                        {
                            printf("%s ",aux->stations_in_line[k].nome);
                            if(k != i)
                                printf(" - ");
                        }
                    }
                    printf("\nLinha: [%s]\n",aux2->nome);
                    if(estacao_destino > j)
                    {
                        for(k = j; k <= estacao_destino; k++)
                        {
                            printf(" %s ",aux2->stations_in_line[k].nome);
                            if(k != estacao_destino)
                                printf(" - ");
                        }
                    }
                    else
                    {
                        for(k = estacao_destino; k <= j; k++)
                        {
                            printf(" %s ",aux2->stations_in_line[k].nome);
                            if(k != j)
                                printf(" - ");
                        }
                    }
                    break;
                }
            }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
}
