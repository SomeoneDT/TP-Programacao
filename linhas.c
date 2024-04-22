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


void preenche(pline p, pline linhas,pstation paragens_sistema, int total_sistema);
pline addline(pline linhas, pstation paragens_sistema, int total_sistema);
pline editline(pline p, pstation paragens_sistema, int total_sistema);
pline addstation_to_line(pline p, pstation paragens_sistema, int total_sistema);
void printlines(pline p, int flag);
pline addfromfile(pline p, char *nome, pstation paragens_sistema, int total_sistema);
pline delline(pline p);
void savelinetofile(pline p);

void preenche(pline p, pline linhas,pstation paragens_sistema, int total_sistema)
{
    int i,n, flag;
    pline aux;
    do
    {
        flag = 1;
        printf("\nInsira o nome da linha: ");
        scanf(" %99[^\n]", p->nome);
        for(aux = linhas; aux != NULL; aux = aux->prox)
        {
            if(strcmp(aux->nome,p->nome) == 0)
            {
                printf("\nErro: Nome ja esta em uso!");
                flag = 0;
            }
        }
    }while(flag == 0);

    do {
        printf("\nInsira quantas estacões pretende adicionar: ");
        scanf("%d", &n);
        // Verifica que o utilizador não está a tentar adicionar mais estações do que as existentes no sistema, uma vez que não podem existir estações iguais numa linha.
        if (n > total_sistema) {
            printf("\nErro: Não pode adicionar mais estações do que as existentes no sistema!");
        }
    }while(n > total_sistema);

    p->stations_in_line = malloc(sizeof(station));
    p->station_count = 0;

    // Addiciona n estações à linha
    for(i = 0; i<n; i++)
    {
        addstation_to_line(p,paragens_sistema,total_sistema);
    }

    p->prox = NULL;
}

pline addline(pline linhas, pstation paragens_sistema, int total_sistema)
{
    int manual;
    pline novo, aux;
    novo = malloc(sizeof(line));
    char ficheiro[100];

    // Verifica se o utilizador quer adicionar manualmente ou através de um ficheiro
    do {
        printf("\nDeseja adicionar manualmente ou por ficheiro (.txt)? (1 - Manualmente, 0 - Ficheiro): ");

        // Verifica se o utilizador não introduziu um caracter inválido.
        if(scanf("%d", &manual) != 1)
        {
            while (getchar() != '\n')
                continue;
        }
    }while(manual != 0 && manual != 1);

    if(manual)
    {
        if (novo == NULL) {
            printf("Erro na alocacao de memoria\n");
            return linhas;
        }

        preenche(novo, linhas, paragens_sistema, total_sistema);
        // Adiciona a linha à lista de linhas
        linhas = addiciona_final(linhas, novo);
        printf("\nLinha criada com sucesso!");
        return linhas;
    }
    else
    {
        printf("\nInsira o nome do ficheiro: ");
        scanf(" %99[^\n]",ficheiro);
        linhas = addfromfile(linhas,ficheiro, paragens_sistema, total_sistema);
    }
    return linhas;
}

pline addstation_to_line(pline p, pstation paragens_sistema, int total_sistema)
{
    pstation aux = realloc(p->stations_in_line,sizeof(station) * (p->station_count+1));
    int flag, manual = 0;
    char codigo[5];

        if (aux != NULL) {
            p->stations_in_line = aux;
            do {
                flag = 0;
                printstations(paragens_sistema, total_sistema);

                // Verifica se a estação a adicionar não está na linha.
                do {
                    printf("\nInsira o codigo a adicionar: ");
                    scanf(" %5[^\n]", codigo);
                    if (station_is_in_line(p, codigo))
                        printf("\nErro: Estacao ja esta na linha!");
                } while (station_is_in_line(p, codigo));

                // Verifica se a estação a adicionar existe no sistema, se existir, adiciona-a à linha.
                for (int j = 0; j < total_sistema; j++) {
                    if (strcmp(paragens_sistema[j].codigo, codigo) == 0) {
                        p->stations_in_line[p->station_count] = paragens_sistema[j];
                        flag = 1;
                        printf("\nEstacao adicionada com sucesso!");
                    }

                }
                if (flag == 0) {
                    printf("\nErro: Estacao nao encontrada!");
                }
            } while (flag == 0);
            p->station_count++;
        }

    return p;
}

pline editline(pline p, pstation paragens_sistema, int total_sistema)
{
    pline aux_line;
    pstation aux_station;
    int i,choice,n, flag;
    char codigo[5], nome[100];
    printf("\n---");
    printlines(p,0);
    printf("\nInsira o nome da linha a editar:");
    scanf(" %99[^\n]",nome);
    aux_line = p;
    while(aux_line != NULL && strcmp(nome,aux_line->nome)!=0)
        aux_line = aux_line->prox;

    // Menu de edição de linhas
    if(aux_line != NULL)
    {
        while (1) {
            printf("\n---");
            printf("\nInsira a opção desejada:");
            printf("\n1. Adicionar Estacoes.");
            printf("\n2. Remover Estacoes.");
            printf("\n3. Voltar a tras.");
            printf("\n---");
            printf("Insira a opcao desejada: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    do {
                        printf("\nInsira quantas estacões pretende adicionar: ");
                        scanf("%d", &n);
                        n += aux_line->station_count;
                        // Verifica se a linha irá ficar com mais estações do que as existentes no sistema.
                        if(n > total_sistema)
                        {
                            printf("\nErro: Não pode adicionar mais estações do que as existentes no sistema!");
                        }
                    }while(n>total_sistema);

                    // Adiciona n estações à linha.
                    for (i = aux_line->station_count; i < n; i++) {

                        addstation_to_line(aux_line, paragens_sistema, total_sistema);
                    }
                    return p;
                case 2:
                    printstations(aux_line->stations_in_line, aux_line->station_count);
                    printf("\nInsira o codigo a eliminar: ");
                    scanf(" %5[^\n]", codigo);

                    for(i=0; i<aux_line->station_count; i++)
                    {
                        // Encontra codigo a eliminar.
                        if(strcmp(aux_line->stations_in_line[i].codigo,codigo) == 0)
                        {
                            aux_station = aux_line->stations_in_line;
                            if(aux_station != NULL)
                            {
                                aux_line->stations_in_line = aux_station;

                                // Remove a estação da linha.
                                for(int j = i; j<aux_line->station_count; j++)
                                {
                                    aux_line->stations_in_line[j] = aux_line->stations_in_line[j+1];
                                }
                                aux_line->station_count = aux_line->station_count - 1;

                            }
                            else
                            {
                                printf("\nErro a alocar memoria! Loc: Editline\n");
                                return p;
                            }
                        }
                    }
                    return p;
                case 3:
                    return p;
                default:
                    printf("\nOpcao invalida!");
            }
        }
    }
    else
    {
        printf("\nErro: Linha nao encontrada!");
        return p;
    }
}

void printlines(pline p, int flag)
{
    while(p != NULL)
    {
        printf("\n---");
        printf("\nLinha: %s",p->nome);
        printf("\nNumero de estacoes: %d\n",p->station_count);
        if(flag == 1)
        {
            printstations(p->stations_in_line,p->station_count);
        }
        printf("\n");
        p = p->prox;
    }
}

void printlines_with_station(pline p)
{
    int i,flag;
    char codigo[5];
    printf("\nInsira o codigo a adicionar: ");
    scanf(" %5[^\n]",codigo);
    while(p!= NULL)
    {
        flag = 0;
        for(i = 0; i<p->station_count; i++)
        {
                if(strcmp(p->stations_in_line[i].codigo,codigo) == 0)
                {
                    flag = 1;
                }
        }
        if(flag == 1)
        {
            printf("\n---");
            printf("\nLinha: %s",p->nome);
            printf("\nNumero de estacoes: %d\n",p->station_count);
            printstations(p->stations_in_line,p->station_count);
            printf("\n");
        }
        p = p->prox;
    }
}

pline addfromfile(pline p, char *nome, pstation paragens_sistema, int total_sistema)
{
    char tempstring[100];
    FILE *f;
    pline novo = malloc(sizeof(line)), run;
    char *token;
    int valido;
    int i,j,k;

    if(novo == NULL)
    {
        printf("\nErro a alocar memoria! Loc: Addfromfile\n");
        return p;
    }
    f = fopen(nome,"r+");
    if(f == NULL)
    {
        printf("\nErro a abrir o ficheiro!");
        return p;
    }
    else
    {
        fscanf(f,"%s",novo->nome);
        run = p;
        // Verifica se já existe uma linha com o mesmo nome.
        while(run != NULL )
        {
            if(strcmp(run->nome,novo->nome) == 0)
            {
                printf("\nErro: Ja existe uma linha com este nome!");
                return p;
            }
            run = run->prox;
        }
        novo->stations_in_line = malloc(sizeof(station));

        novo->station_count = 0;
        // fscanf le a linha toda.
        while(fscanf(f," %108[^\n]",tempstring) == 1)
        {
            valido = 0;
            //printf("\n%s",tempstring);
            novo->stations_in_line = realloc(novo->stations_in_line,(novo->station_count+1)*sizeof(station));
            // Le o nome da estação.
            for(i = 0; tempstring[i] != '#';i++)
            {
                novo->stations_in_line[novo->station_count].nome[i] = tempstring[i];
            }
            novo->stations_in_line[novo->station_count].nome[i-1] = '\0';
            // Le o codigo da estaçao. (4 caracteres, começando no espaço apos # "i+2")
            // Como os nomes e codigos das estações estão separados por " # ", e i encontra-se no primeiro espaço, i+2 é o primeiro caracter do codigo.
            for(j = i+2, k = 0; k<5; j++, k++)
            {
                novo->stations_in_line[novo->station_count].codigo[k] = tempstring[j];
            }
            novo->stations_in_line[novo->station_count].codigo[k] = '\0';
            //printf("\n%s | %s",novo->stations_in_line[novo->station_count].nome,novo->stations_in_line[novo->station_count].codigo);

            // Verifica se o codigo da estação existe no sistema.
            for(i = 0; i<total_sistema; i++)
            {
                if(strcmp(novo->stations_in_line[novo->station_count].codigo,paragens_sistema[i].codigo) == 0)
                {
                    valido = 1;
                    // printf("\nSucesso!");
                    // Se o codigo estiver correto mas o nome não, altera o nome, uma vez que é mais provavel o utilizador cometer erros ao escrever o nome, do que o código.
                    if(strcmp(novo->stations_in_line[novo->station_count].nome,paragens_sistema[i].nome) != 0)
                    {

                        printf("\nParagem com o codigo %s tem o codigo pertencente a paragem com o nome %s no sistema, alterando o nome.\n",novo->stations_in_line[novo->station_count].codigo,paragens_sistema[i].nome);
                        strcpy(novo->stations_in_line[novo->station_count].nome,paragens_sistema[i].nome);
                    }
                }
            }

            // Caso o codigo não exista no sistema, a linha não é valida, logo sai do loop.
            if(valido == 0)
                break;

            novo->station_count++;
        }

        novo->prox = NULL;

        // Se for valida, adiciona a ao final da lista.
        if(valido == 1)
        {
            addiciona_final(p,novo);
        }
        else
        {
            printf("\nErro: Linha nao adicionada, o ficheiro contem uma ou mais estacoes nao encontradas no sistema!");
            free(novo->stations_in_line);
            free(novo);

        }
        fclose(f);
        return p;
    }
}

// Função para eliminar uma linha do sistema. Baseada nos powerpoints apresentados nas aulas teóricas.
pline delline(pline p)
{
    char nome[100];
    pline atual, anterior = NULL;

    printf("\nInsira o nome da linha a remover: ");
    scanf(" %99[^\n]",nome);

    atual = p;
    while(atual != NULL && strcmp(atual->nome,nome) != 0)
    {
        anterior = atual;
        atual = atual->prox;
    }
    if(atual == NULL)
    {
        printf("\nErro: A linha inserida nao existe no sistema!");
        return p;
    }
    if(anterior == NULL)
        p = atual->prox;
    else
        anterior->prox = atual->prox;

    // Libertar as memórias alocadas ao array dinamico e struct line.
    free(atual->stations_in_line);
    free(atual);

    return p;

}

// Função de teste usada para criar um ficheiro com uma linha.
void savelinetofile(pline p)
{
    FILE *f;

    f = fopen("linha.txt","w+");


    fprintf(f,"%s\n",p->nome);
    for(int i = 0; i<p->station_count; i++)
    {
        fprintf(f,"%s # %s\n",p->stations_in_line[i].nome,p->stations_in_line[i].codigo);
    }
    fclose(f);

}