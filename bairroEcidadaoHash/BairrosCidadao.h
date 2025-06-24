#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXNOME 50

#define tamanhoMaxVetorBairros 5
#define tamanhoMaxVetorCidadaos 9

// estrutura de cada bairro
typedef struct Bairro
{
    int id;
    char nome[MAXNOME];
}  Bairro;

// nó para cada bairro 
typedef struct BairroHash
{
    struct Bairro *b;
    struct BairroHash *prox;
} BairroHash;


// tabela hash para bairros
typedef struct
{
    struct BairroHash *vetorBairros[tamanhoMaxVetorBairros];
} tabelaBairros;

// estrutura de cada cidadão
typedef struct Cidadao
{
    int id;
    int cpf;
    char nome[MAXNOME];
    char email[MAXNOME];
    struct Bairro *endereco;
} Cidadao;

// nó para cada cidadão
typedef struct CidadaoHash
{
    struct Cidadao *c;
    struct CidadaoHash *prox; 
} CidadaoHash;

// tabela hash para cidadãos
typedef struct tabelaCidadaos
{
    int populacaoTotal;
    struct CidadaoHash *vetorCidadaos[tamanhoMaxVetorCidadaos];
} tabelaCidadaos;


