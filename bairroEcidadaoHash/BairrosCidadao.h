#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXNOME 50

#define tamanhoMaxVetorBairros 9
#define tamanhoMaxVetorCidadaos 9

    // estrutura de cada bairro
typedef struct Bairro{
    int id;
    char nome[MAXNOME];
}  Bairro;

    // no para cada 
typedef struct BairroHash{
    struct Bairro b;
    struct BairroHash *prox;
} BairroHash;


    // tabela hash para bairros
typedef struct {
    struct BairroHash *vetorBairros[tamanhoMaxVetorBairros];
} tabelaBairros;

    // estrutura de cada cidadao
typedef struct Cidadao{
    int id;
    int cpf;
    char nome[MAXNOME];
    char email[MAXNOME];
    char endereco[MAXNOME];
    struct BairroHash *bairro;
} Cidadao;


typedef struct CidadaoHash{
    struct Cidadao c;
    struct Cidadao *prox;
}CidadaoHash;


    // tabela hash para cidadaos
typedef struct tabelaCidadaos{
    int populacaoTotal;
    struct Cidadao *vetorCidadaos[tamanhoMaxVetorCidadaos];
} tabelaCidadaos;


void inicializarTabelaBairros (tabelaBairros *tabela);
int hashBairros (char nome[]);
void inserirTabelaBairros (char nome[],tabelaBairros *tabela);
BairroHash* buscarBairro (char nome[], tabelaBairros *tabela);
void imprimirTabelaDeBairros(tabelaBairros *tabela);
void inicializarTabelaCidadaos (tabelaCidadaos *tabela);
int hashCidadaos (char nome[]);
void inserirTabelaCidadaos (char nome[], tabelaCidadaos *tabela, tabelaBairros *tBairros);
void imprimirTabelaCidadaos (tabelaCidadaos *tabela);
CidadaoHash* buscarCidadao (tabelaCidadaos *tabela, char nome[]);