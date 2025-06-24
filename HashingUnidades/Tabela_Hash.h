#include <stdio.h>
#include "../struct_comum.h"

#define MAXNOME 50
#define MAXTABHASH 9

//TODO: decidir quais as informacoes necessarias na estrutura unidades

typedef struct UnidadeHash
{
    Unidade unidade;
    struct UnidadeHash *prox;
} UnidadeHash;

typedef struct TabHashUnidade
{
    UnidadeHash *tabelaUnidades[MAXTABHASH];
} TabHashUnidade;

void InicializarTabelaHashUnidades(TabHashUnidade *tabela);
int HashUnidades(int id);
void InserirTabelaUnidades(int id, char nome[], TabHashUnidade *tabela);
void ImprimirTabelaHashUnidades(TabHashUnidade *tabela);
UnidadeHash* BuscarTabelaHashUnidades(char nome[], TabHashUnidade *tabela);