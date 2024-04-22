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


pstation addstation(station *paragens, int *total);
void printstations(station *paragens, int total);
pstation delstation(station *paragens, int *total, pline linhas);




pstation addstation(station *paragens, int *total)
{
    // Limpa o buffer, por algum motivo tinha erros constantes caso isto não fosse feito.
    fflush(stdin);
    station *p = realloc(paragens,sizeof(station) * (*total+1));

    int i,flag;

    if(p != NULL)
    {
        paragens = p;

        do
        {
            flag = 0;
            printf("\nInsira o nome: ");
            gets(paragens[*total].nome);

            // Verifica se o nome já existe
            for(i = 0; i<*total; i++)
            {
                if(strcmp(paragens[*total].nome,paragens[i].nome) == 0)
                {
                    printf("\nNome ja esta em uso!");
                    flag = 1;
                }
            }

            /**
             * Verifica se o nome contem o caracter '#'
             * Devido ao facto de ser usado para separar o nome e codigo durante o carregamento de linhas atravez de ficheiros .txt
             * Caso o nome contenha o caracter, o carregamento nao seria realizado, sendo impossivel adicionar a linha.
             *
             */
            for(i=0; i<strlen(paragens[*total].nome);i++)
            {
                if(paragens[*total].nome[i] == '#')
                {
                    printf("\nNome nao pode conter o caracter '#'!");
                    flag = 1;
                    break;
                }
            }

        }
        while(flag == 1);
    }
    else
    {
        printf("\nErro a alocar memoria! Loc: addstation\n");
        return paragens;
    }


    // Gera o código da estação
    generatecode(paragens,*total);
    printf("Estacao adicionada! Codigo: %s\n",paragens[*total].codigo);
    (*total)++;
    return paragens;
}

void printstations(station *paragens, int total)
{
    int i;
    for(i = 0; i<total; i++)
    {
        printf("\n%d: Nome: %s\tCodigo: %s\t",i,paragens[i].nome,paragens[i].codigo);
    }
    printf("\n");
}

pstation delstation(station *paragens, int *total, pline linhas)
{

    station *p;
    pline aux;
    int i;
    char codigo[5];

    // Caso o sistema não tenha estacoes, o utilizador não pode apagar nenhuma, logo retorna.
    if(*total == 0)
    {
        printf("\nErro: Nao existem estacoes!");
        return paragens;
    }

    // Mostra as estacoes atuais
    printf("\n\nAs estacoes atuais sao: \n");
    printstations(paragens,*total);


    do
    {
        printf("\nInsira o codigo da estacao a apagar: ");
        scanf(" %5[^\n]", codigo);
    }
    while(strlen(codigo) != 4);

    aux = linhas;

    // O utilizador não pode apagar uma estacao que esteja em uso por uma linha, caso esteja, retorna.
    while(aux != NULL)
    {
        for(i = 0; i<aux->station_count; i++)
        {
            if(strcmp(aux->stations_in_line[i].codigo,codigo) == 0)
            {
                printf("\nErro: Estacao esta em uso!");
                return paragens;
            }
        }
        aux = aux->prox;
    }
    int j;
    // Procura a estacao com o codigo inserido pelo utilizador, e remove-a.
    for(i=0; i<*total; i++)
    {
        if(strcmp(paragens[i].codigo,codigo) == 0)
        {
            p = realloc(paragens,sizeof(station) * (*total-1));
            if(p != NULL)
            {
                for(j = i; j<*total-1; j++)
                    paragens[j] = paragens[j+1];
                *total = *total - 1;
            }
            else {
                printf("\nErro a alocar memoria! Loc: delstation\n");
            }
            printf("\nEstacao removida! Lista de estacoes ainda no sistema: \n");
            printstations(paragens,*total);
            return paragens;
        }
    }
    return paragens;
}