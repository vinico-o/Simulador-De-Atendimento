#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "Lista_Cruzada.h"
#include "../struct_comum.h"

int qntdNomesBairro = MAXBAIRRO;
int qntdNomesUnidades = MAXUNIDADE;

void GerarBairroAleatorio(Bairro* bairro, int* indice)
{
    *indice = rand() % qntdNomesBairro;
    bairro->id = *indice;
    strcpy(bairro->nome, nomesBairros[*indice]);
}

void GerarUnidadeAleatoria(Unidade* unidade, int* indice)
{
    *indice = rand() % qntdNomesUnidades;
    unidade->id = *indice;
    strcpy(unidade->nome, nomesUnidades[*indice]);
}

void Inicializar_Matriz(Matriz* matriz)
{
    for(int i = 0; i < MAXBAIRRO; i++)
    {
        matriz->listaBairros[i] = NULL;
    }

    for(int j = 0; j < MAXUNIDADE; j++)
    {
        matriz->listaUnidades[j] = NULL;
    }
}

void InserirMatrizCruzada(Matriz* matriz, int linha, int coluna, Bairro bairro, Unidade unidade)
{
    Ligacao* nova = malloc(sizeof(Ligacao));
    if (!nova)
    {
        printf("Erro de alocacao!\n");
        return;
    }

    Ligacao *ant = NULL;
    Ligacao *ptrColuna = matriz->listaUnidades[coluna];
    Ligacao *ptrLinha = matriz->listaBairros[linha];

    nova->proxUnidade = NULL;
    nova->proxBairro = NULL;
    nova->infoBairro = bairro;
    nova->infoUnidade = unidade;
    nova->linha = linha;
    nova->coluna = coluna;

    // Inserção na lista de bairros (linhas)
    if(ptrLinha == NULL)
    {
        matriz->listaBairros[linha] = nova;
    }
    else
    {
        while(ptrLinha != NULL && ptrLinha->coluna < coluna)
        {
            ant = ptrLinha;
            ptrLinha = ptrLinha->proxBairro;
        }

        if(ant == NULL)
        {
            nova->proxBairro = matriz->listaBairros[linha];
            matriz->listaBairros[linha] = nova;
        }
        else
        {
            nova->proxBairro = ant->proxBairro;
            ant->proxBairro = nova;
        }
    }

    // Inserção na lista de unidades (colunas)
    ant = NULL;
    ptrColuna = matriz->listaUnidades[coluna];

    if(ptrColuna == NULL)
    {
        matriz->listaUnidades[coluna] = nova;
    }
    else
    {
        while(ptrColuna != NULL && ptrColuna->linha < linha)
        {
            ant = ptrColuna;
            ptrColuna = ptrColuna->proxUnidade;
        }

        if(ant == NULL)
        {
            nova->proxUnidade = matriz->listaUnidades[coluna];
            matriz->listaUnidades[coluna] = nova;
        }
        else
        {
            nova->proxUnidade = ant->proxUnidade;
            ant->proxUnidade = nova;
        }
    }
}

void RemoverMatrizCruzada(Matriz* matriz, int linha, int coluna)
{
    Ligacao *ptrLinha = matriz->listaBairros[linha];
    Ligacao *ptrColuna = matriz->listaUnidades[coluna];
    Ligacao *ant = NULL;

    // Remoção da lista de bairros (linhas)
    while(ptrLinha != NULL && ptrLinha->coluna < coluna)
    {
        ant = ptrLinha;
        ptrLinha = ptrLinha->proxBairro;
    }

    if(ptrLinha == NULL || ptrLinha->coluna != coluna)
    {
        printf("Elemento nao encontrado!\n");
        return;
    }

    if(ant == NULL)
    {
        matriz->listaBairros[linha] = ptrLinha->proxBairro;
    }
    else
    {
        ant->proxBairro = ptrLinha->proxBairro;
    }

    // Remoção da lista de unidades (colunas)
    ant = NULL;
    while(ptrColuna != NULL && ptrColuna->linha < linha)
    {
        ant = ptrColuna;
        ptrColuna = ptrColuna->proxUnidade;
    }

    if(ant == NULL)
    {
        matriz->listaUnidades[coluna] = ptrColuna->proxUnidade;
    }
    else
    {
        ant->proxUnidade = ptrColuna->proxUnidade;
    }

    free(ptrLinha);
}

void ImprimirMatrizCruzada(Matriz *matriz)
{
    printf("    Bairro   | %-17s%-17s%-17s\n", "Policia", "Bombeiro", "Hospital");
    printf("-------------+---------------------------------------------------\n");

    for(int i = 0; i < MAXBAIRRO; i++)
    {
        printf("%-12s |", nomesBairros[i]);
        Ligacao* ptr = matriz->listaBairros[i];

        for(int j = 0; j < MAXUNIDADE; j++)
        {
            if(ptr != NULL && ptr->coluna == j)
            {
                printf(" [BID:%02d UID%02d] |", ptr->infoBairro.id, ptr->infoUnidade.id);
                ptr = ptr->proxBairro; // segue pela lista de bairros (linhas)
            }
            else
            {
                printf("%-16s|", " ");
            }
        }
        printf("\n");
    }

    printf("\n");
}

bool BuscarUnidadeBairro(Matriz* matriz, int idBairro, int idUnidade)
{
    Ligacao* ptr = matriz->listaBairros[idBairro]; 

    while (ptr != NULL)
    {
        if (ptr->coluna == idUnidade)
        {
            // Encontrou a unidade no bairro
            return true;
        }
        ptr = ptr->proxBairro;
    }

    return false;
}

void GerarMatrizAleatoria(Matriz* matriz)
{
    int numero;
    for(int i = 0; i < MAXBAIRRO; i++)
    {
        for(int j = 0; j < MAXUNIDADE; j++)
        {
            numero = rand() % 3;
            if(numero % 2 == 0)
            {
                Bairro tempBairro;
                tempBairro.id = i;
                strcpy(tempBairro.nome, nomesBairros[i]);

                Unidade tempUnidade;
                tempUnidade.id = j;
                strcpy(tempUnidade.nome, nomesBairros[i]);

                InserirMatrizCruzada(matriz, i, j, tempBairro, tempUnidade);
            }
        }
    }
}