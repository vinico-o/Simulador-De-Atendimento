#include <stdio.h>

#define MAXNOME 50
#define MAXTABHASH 9

//TODO: decidir quais as informacoes necessarias na estrutura unidades
typedef struct Unidade
{
    int id;
    char nome[MAXNOME];
} Unidade;

typedef struct UnidadeHash
{
    Unidade unidade;
    struct UnidadeHash *prox;
} UnidadeHash;

typedef struct TabHashUnidade
{
    UnidadeHash *tabelaUnidades[MAXTABHASH];
} TabHashUnidade;

void Inicializar(TabHashUnidade *tabela);
