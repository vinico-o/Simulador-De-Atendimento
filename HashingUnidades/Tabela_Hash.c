#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tabela_Hash.h"

void Inicializar(TabHashUnidade *tabela)
{
    for(int i = 0; i < MAXTABHASH; i++)
    {
        tabela->tabelaUnidades[i] = NULL;
    }
}

int HashUnidades(char nome[])
{
    int soma = 0;
    int tamanho = strlen(nome);

    for(int i = 0; i < tamanho; i++)
    {
        soma += i * nome[i];
    }

    return soma % MAXTABHASH;
}

