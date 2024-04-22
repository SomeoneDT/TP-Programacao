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
#include "course.h"
#include <ctype.h>

void menu(station *paragens, int *total, pline linhas);

void menu(station *paragens, int *total, pline linhas) {
    int choice, choice2, n, i;
    int flag = 1;

    do {
        printf("\nDeseja carregar as estacoes guardadas?\n"
               "Antes de selecionar sim garanta que o ficheiro \"estacoes.dat \" existe.\n"
               "[1 - Sim | 0 - Nao]: ");
        scanf("%d", &choice);
    } while (choice != 0 && choice != 1);

    if (choice == 1) {
        paragens = carrega_estacoes(total);
        do {
            printf("\nDeseja carregar as linhas guardas?\n"
                   "Antes de selecionar sim garanta que o ficheiro \"linhas.dat \" existe.\n"
                   "[1 - Sim | 0 - Nao]: ");
            scanf("%d", &choice2);
        } while (choice2 != 0 && choice2 != 1);
        if (choice2 == 1)
            linhas = carrega_linhas(linhas);
    }
    while (flag) {

        printf("\n---");
        printf("\n1. Opcoes de estacoes.");
        printf("\n2. Opcoes de linhas.");
        printf("\n3. Calcular precurso.");
        printf("\n4. Guardar dados.");
        printf("\n5. Sair.");
        printf("\n---\n");
        // Por norma teria um do while para garantir que o utilizador escolhe um numero entre 1 e 5.
        // No entanto, usei o switch case (default) para fazer o mesmo.
        // O mesmo aplica-se a qualquer outro switch case do programa.
        // Introduzir um valor não inteiro ou introduzir um char irá fazer com que o programa entre em loop infinito.
        printf("\nInsira a opcao desejada: ");
        // Verifica se o utilizador não introduziu um caracter inválido.
        if(scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
            case 1:

                printf("\n---");
                printf("\n1. Adicionar estacao.");
                printf("\n2. Remover estacao.");
                printf("\n3. Listar estacoes.");
                printf("\n4. Voltar.");
                printf("\n---\n");
                printf("\nInsira a opcao desejada: ");
                // Verifica se o utilizador não introduziu um caracter inválido.
                if(scanf("%d", &choice2) != 1)
                {
                    while (getchar() != '\n');
                    continue;
                }

                switch (choice2) {
                    case 1:
                        printf("\nNumero de estacoes a adicionar: ");
                        scanf("%d", &n);
                        for (i = 0; i < n; i++) {
                            paragens = addstation(paragens, total);
                        }
                        break;
                    case 2:
                        paragens = delstation(paragens, total, linhas);
                        break;
                    case 3:
                        printstations(paragens, *total);
                        printf("\n\n");
                        break;
                    default:
                        break;
                }
                // while (getchar() != '\n');
                break;
            case 2:
                printf("\n---");
                printf("\n1. Adicionar linha.");
                printf("\n2. Editar linha.");
                printf("\n3. Apagar linha.");
                printf("\n4. Listar linhas.");
                printf("\n5. Listar linhas que contem uma paragem.");
                printf("\n6. Voltar.");
                printf("\n---\n");
                printf("\nInsira a opcao desejada: ");

                // Verifica se o utilizador não introduziu um caracter inválido.
                if(scanf("%d", &choice2) != 1)
                {
                    while (getchar() != '\n');
                    continue;
                }
                switch (choice2) {
                    case 1:
                        linhas = addline(linhas, paragens, *total);
                        break;
                    case 2:
                        linhas = editline(linhas, paragens, *total);
                        break;
                    case 3:
                        linhas = delline(linhas);
                        break;
                    case 4:
                        printlines(linhas, 1);
                        break;
                    case 5:
                        printstations(paragens, *total);
                        printlines_with_station(linhas);
                        break;
                    default:
                        break;
                }
                //while (getchar() != '\n');
                break;
            case 3:
                simula_percurso(linhas, paragens, *total);
                break;
            case 4:
                guarda_dados(paragens, *total, linhas);
                printf("\nDados guardados com sucesso!\n");
                break;
            case 5:
                flag = 0;
                guarda_dados(paragens, *total, linhas);
                break;
            default:
                printf("Erro: Nao e uma opcao!");
                break;
        }

    }
}
