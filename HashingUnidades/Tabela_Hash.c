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

void InserirTabelaUnidades(char nome[], TabHashUnidade *tabela)
{
    int indice = HashUnidades(nome);

    UnidadeHash *novo = malloc(sizeof(UnidadeHash));
    if(novo == NULL)
    {
        printf("Erro ao alocar na memoria!\n");
        return;
    }

    //TODO: definir como os ids serao gerados
    novo->unidade.id = 0;
    strcpy(novo->unidade.nome, nome);
    novo->prox = NULL;

    if(tabela->tabelaUnidades[indice] == NULL)
    {
        tabela->tabelaUnidades[indice] = novo;
    }
    else
    {
        UnidadeHash *ptr = tabela->tabelaUnidades[indice];
        while(ptr != NULL)
        {
            ptr = ptr->prox;
        }
        ptr->prox = novo;

    }

}

void ImprimirTabela(TabHashUnidade *tabela)
{
    printf("\n-----TABELA HASH UNIDADES-----\n");
    for (int i = 0; i < MAXTABHASH; i++)
    {
        printf ("\n\n%d:", i);

        if (tabela->tabelaUnidades[i] != NULL)
        {
            UnidadeHash *ptr = tabela->tabelaUnidades[i];

            while (ptr != NULL)
            {
                printf("\nId do bairro: %d", ptr->unidade.id);
                printf("\nNome do bairro: %s", ptr->unidade.nome);

                printf("\n");

                ptr = ptr->prox;
            }

            printf ("\n");
        }
    }
}