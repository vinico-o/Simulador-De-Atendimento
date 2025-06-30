#include <stdio.h>
#include <stdlib.h>
#include "fila_din.h"
void inicializar(Fila* fila)
{
    fila->inicio=NULL;
    fila->fim=NULL;
}
int vazia(Fila* fila)
{
    if(!fila->inicio)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int cheia(Fila* fila)
{
    noFila *novoNo = malloc(sizeof(noFila));
    if(!novoNo)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void inserir(Fila *fila,int elem)
{
    noFila *novoNo = malloc(sizeof(noFila));
    novoNo->elem = elem;
    novoNo->prox = NULL;
    if(vazia(fila))
    {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    }
    else
    {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}
void remover(Fila* fila,int* elem)
{
    if(vazia(fila))
    {
        printf("Sem elementos na fila!\n");
        return;
    }

    noFila *percorreFilaAtual = fila->inicio;
    noFila *percorreFilaAnt = NULL;

    while(percorreFilaAtual != NULL && percorreFilaAtual->elem > *elem)
    {
        percorreFilaAnt = percorreFilaAtual;
        percorreFilaAtual = percorreFilaAtual->prox;
    }

    if(!percorreFilaAtual)
    {
        return;
    }
    if(!percorreFilaAnt)
    {
        fila->inicio = percorreFilaAtual->prox;
    }
    else
    {
        percorreFilaAnt->prox = percorreFilaAtual->prox;
    }
    free(percorreFilaAtual);
}
void obter_topo(Fila* fila,int* elem)
{
    if(vazia(fila))
    {
        printf("Fila esta vazia!\n");
        return;
    }
    else
    {
        *elem = fila->inicio->elem;
    }
}
void num_elem(Fila* fila,int *elem)
{
    noFila *temp = fila->inicio;
    int cont=0;
    while(temp)
    {
        cont++;
        temp = temp->prox;
    }
    *elem = cont;
}
void imprimir_fila(Fila* fila)
{
    if(vazia(fila))
    {
        printf("\tfila vazia!\n");
        return;
    }
    else
    {
        noFila *temp = fila->inicio;
        printf("\t");
        while(temp)
        {
            printf("%d ",temp->elem);
            temp = temp->prox;
        }
        printf("\n");
    }
}
int tamanhoFila(Fila* fila)
{
    noFila *percorreFila = fila->inicio;
    int cont=0;

    while(percorreFila)
    {
        cont++;
        percorreFila = percorreFila->prox;
    }
    return cont;
}