/**
Trabalho Prático - Programação 2022/23
Daniel Vitor Baroa Domingues Tinoco
2021132552
**/


#include "sistemas.h"
#include "estacoes.h"
#include "utils.h"
#include "linhas.h"
#include "menu.h"

void generatecode(station *estacao, int total);
int station_is_in_line(pline p, char *codigo);

void generatecode(station *estacao, int total)
{
    int i, flag;
    time_t t;
    char codechars[36] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // Array de caracteres que podem ser usados para gerar o código.
    char temp;

    srand((unsigned) time(&t));
    do
    {
        flag = 0;
        for(i = 0; i<CODE_LEN; i++)
        {
            temp = codechars[rand()%36];
            estacao[total].codigo[i] = temp;
        }
        // Adiciona o caracter de fim de string.
        estacao[total].codigo[CODE_LEN] = '\0';
        // Verifica se o código gerado já está acossiado a outra estação.
        for(i = 0; i<total; i++)
        {
            if(strcmp(estacao[total].codigo,estacao[i].codigo) == 0)
            flag = 1;
        }
    }
    while(flag == 1);

}

// Função que verifica se uma estação está numa linha.
int station_is_in_line(pline p,char *codigo)
{
    int i;
    for(i = 0; i<p->station_count; i++)
    {
        if(strcmp(p->stations_in_line[i].codigo,codigo) == 0)
            return 1;
    }
    return 0;
}

// Função que verifica se duas linhas têm estações em comum.
int lines_station_common(pline inicio, pline destino)
{
    int i;


    for(i = 0; i<inicio->station_count; i++)
    {
        if(station_is_in_line(destino,inicio->stations_in_line[i].codigo) == 1)
            return 1;
    }
    return 0;
}

void guarda_dados(pstation paragens, int total, pline linhas)
{
    FILE *f;


    f = fopen("estacoes.dat","w+b");
    if(f == NULL)
    {
        printf("\nErro a abrir ficheiro! Loc: guarddados\n");
        return;
    }

    // Escreve o total de estações, e depois escreve as estações.
    fwrite(&total,sizeof(int),1,f);
    fwrite(paragens,sizeof(station),total,f);
    fclose(f);

    f = fopen("linhas.dat","w+b");
    // Escreve cada linha e o array dinamico de estações que cada linha tem.
    while(linhas != NULL)
    {
        fwrite(linhas,sizeof(line),1,f);
        fwrite(linhas->stations_in_line,sizeof(station),linhas->station_count,f);
        linhas = linhas->prox;
    }
    fclose(f);

}

pstation carrega_estacoes(int *total)
{
    FILE *f;
    pstation p = NULL;
    f = fopen("estacoes.dat","rb");
    if(f == NULL)
    {
        printf("\nErro a abrir ficheiro! Loc: carregadados\n");
        return NULL;
    }

    // Le o total.
    fread(total,sizeof(int),1,f);

    // Aloca memoria para "total" de estações.
    p = malloc(sizeof(station) * (*total));
    if(p==NULL)
    {
        fclose(f);
        *total = 0;
        printf("\nErro a alocar memoria! Loc: carregadados\n");
        return NULL;
    }
    // Le as estações um total de vezes.
    fread(p,sizeof(station),*total,f);
    fclose(f);
    return p;
}
pline addiciona_final(pline p, pline novo)
{
    pline aux;

    if(novo == NULL)
        return p;

    if(p == NULL)
        p = novo;
    else
    {
        aux = p;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return p;
}
pline carrega_linhas(pline p)
{
    pline novo;
    line linha;
    FILE *f;

    f = fopen("linhas.dat","rb");
    if(f == NULL)
    {
        printf("\nErro a abrir ficheiro! Loc: carregalinhas\n");
        return NULL;
    }

    // Le ate ao fim do ficheiro.
    while(fread(&linha, sizeof(line), 1, f) == 1){
        // Aloca memoria para a linha.
        novo = malloc(sizeof(line));
        if(novo == NULL){
            fclose(f); return p;
        }

        *novo = linha;
        // Aloca memoria para o array de estações da linha.
        novo->stations_in_line = malloc(sizeof(station) * novo->station_count);
        // Le o array de estações da linha.
        fread(novo->stations_in_line, sizeof(station), novo->station_count, f);
        novo->prox = NULL;
        // Adiciona a linha ao final da lista.
        p = addiciona_final(p, novo);
    }
    fclose(f);
    return p;
}

void freelines(pline p)
{
    pline aux;
    while(p != NULL)
    {
        aux = p;
        p = p->prox;
        free(aux->stations_in_line);
        free(aux);
    }
}

