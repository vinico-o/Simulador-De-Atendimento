#ifndef PILHA_H
#define PILHA_H

#include "../struct_comum.h"

typedef struct noPilha
{
    Ocorrencia atendimento;
    struct noPilha *prox;
}noPilha;
typedef struct
{
    struct noPilha *topo;
}Pilha;
void inicializa_pilha(Pilha *pilha);
int se_vazia(Pilha *pilha);
void push(Pilha *pilha,Ocorrencia atend);
void pop(Pilha *pilha,Ocorrencia *atend);
void obter_topoPilha(Pilha *pilha,Ocorrencia *atend);
void reinicializa(Pilha *pilha);
#endif
