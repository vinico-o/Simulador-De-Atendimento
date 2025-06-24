#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tabela_Hash.h"

void InicializarTabelaHashUnidades(TabHashUnidade *tabela)
{
    for(int i = 0; i < MAXTABHASH; i++)
    {
        tabela->tabelaUnidades[i] = NULL;
    }
}

//O hashing eh feito pelo id da unidade
int HashUnidades(int id)
{
    return id % MAXTABHASH;
}

void InserirTabelaUnidades(int id, char nome[], TabHashUnidade *tabela)
{
    int indice = HashUnidades(id);

    UnidadeHash *novo = malloc(sizeof(UnidadeHash));
    if(novo == NULL)
    {
        printf("Erro ao alocar na memoria!\n");
        return;
    }

    //TODO: definir como os ids serao gerados
    //por enquando esta definido um id fixo, que acresce a cada unidade
    novo->unidade.id = id;
    strcpy(novo->unidade.nome, nome);
    novo->prox = NULL;

    if(tabela->tabelaUnidades[indice] == NULL)
    {
        tabela->tabelaUnidades[indice] = novo;
    }
    else
    {
        UnidadeHash *ptr = tabela->tabelaUnidades[indice];
        while(ptr->prox != NULL)
        {
            ptr = ptr->prox;
        }
        ptr->prox = novo;

    }

}

void ImprimirTabelaHashUnidades(TabHashUnidade *tabela)
{
    printf("\n-----TABELA HASH UNIDADES-----\n");
    for (int i = 0; i < MAXTABHASH; i++)
    {
        printf ("\n%d:\n", i);

        if (tabela->tabelaUnidades[i] != NULL)
        {
            UnidadeHash *ptr = tabela->tabelaUnidades[i];

            while (ptr != NULL)
            {
                printf("Id do Unidade: %d\n", ptr->unidade.id);
                printf("Nome do Unidade: %s\n", ptr->unidade.nome);

                ptr = ptr->prox;
            }

            printf ("\n");
        }
    }
}

UnidadeHash* BuscarTabelaHashUnidades(char nome[], TabHashUnidade *tabela)
{
    int indice = HashUnidades(nome);

    UnidadeHash *ptr = tabela->tabelaUnidades[indice];

    while (ptr != NULL)
    {
        if (strcmp(ptr->unidade.nome, nome) == 0)
        {
            return ptr;
        }

        ptr = ptr->prox;
    }

    return NULL;
}