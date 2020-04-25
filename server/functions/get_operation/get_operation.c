#include <stdio.h>
#include <stdlib.h>

void get_operation(int op)
{
    switch (op)
    {
    case 1:
        printf("Listagem de filmes\n");
        break;
    case 2:
        printf("Adicionando Filme\n");
        break;
    case 3:
        printf("Removendo Filme\n");
        break;
    case 4:
        printf("Retornando Filme\n");
        break;
    case 5:
        printf("Retornando Título do Filme\n");
        break;
    case 6:
        printf("Listando Filmes de um Gênero\n");
        break;
    case 7:
        printf("Listagem de filmes (apenas Título e Salas)\n");
        break;
    default:
        printf("Operação inválida!\n");
        break;
    }
}