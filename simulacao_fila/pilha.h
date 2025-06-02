#ifndef PILHA_H
#define PILHA_H
#define TAMSTR 100
typedef struct noPilha
{
    char str[TAMSTR];
    struct noPilha *prox;
}noPilha;
typedef struct
{
    struct noPilha *topo;
}Pilha;
void inicializa_pilha(Pilha *pilha);
int se_vazia(Pilha *pilha);
void push(Pilha *pilha,char str[]);
void pop(Pilha *pilha,char *str);
void obter_topoPilha(Pilha *pilha,char *str);
void reinicializa(Pilha *pilha);
#endif
