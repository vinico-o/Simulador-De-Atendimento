#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
void inicializa_pilha(Pilha* pilha)
{
    pilha->topo=NULL;
}
int se_vazia(Pilha* pilha)
{
    if(!pilha->topo)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void push(Pilha *pilha,char str[])
{
    noPilha* novo_no = malloc(sizeof(noPilha));
    strcpy(novo_no->str,str);
    novo_no->prox = pilha->topo;
    pilha->topo = novo_no;
}
void pop(Pilha *pilha,char *str)
{
    if(se_vazia(pilha))
    {
        printf("Sem elementos!\n");
        return;
    }
    else
    {
        noPilha* aux = malloc(sizeof(noPilha));
        aux = pilha->topo;
        strcpy(str,aux->str);
        pilha->topo = pilha->topo->prox;
        free(aux);
    }
}
void obter_topoPilha(Pilha *pilha,char *str)
{
    if(se_vazia(pilha))
    {
        printf("Pilha vazia!\n");
        return;
    }
    else
    {
        strcpy(str,pilha->topo->str);
    }
}
void reinicializa(Pilha *pilha)
{
    if(se_vazia(pilha))
    {
        printf("Pilha vazia!\n");
        return;
    }
    else
    {
        while(pilha->topo)
        {
            noPilha* temp = malloc(sizeof(noPilha));
            temp = pilha->topo;
            pilha->topo = pilha->topo->prox;
            free(temp);
        }
        printf("Pilha esvaziada!\n");
        return;
    }
}
