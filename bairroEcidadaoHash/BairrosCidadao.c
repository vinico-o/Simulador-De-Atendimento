#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "BairrosCidadao.h"
#include "../struct_comum.h"


int idBairros = 1;   // simula o ID de bancos de dados para BAIRROS
    
// função de inicializacao da tabela de bairros
    void inicializarTabelaBairros (tabelaBairros *tabela)
{
    for (int i = 0; i < tamanhoMaxVetorBairros; i++)
    {
        tabela->vetorBairros[i] = NULL;             // inicializa o vetor de bairros como NULL;
    }
}

// função hash para bairros
int hashBairros (char nome[])
{
    int soma = 0;

    int tamanho = strlen(nome);

    for (int i = 0; i < tamanho; i++)       // loop que soma os caracteres (com base na tabela ASCII)
    {
        soma += i * nome[i];
    }

    return soma % tamanhoMaxVetorBairros;   // retorna uma chave como índice
}

// funcao para criar o bairro
Bairro* criarBairro (char nome[])
{
    Bairro* novoBairro = malloc (sizeof(Bairro));   // aloca o bairro na memoria

    if (novoBairro != NULL){                        // e retorna o ponteiro para o bairro
        strcpy (novoBairro->nome, nome);
        return novoBairro;
    }


    return NULL;
}


// função de inserção na tabela hash de bairros
void inserirTabelaBairros (char nome[],tabelaBairros *tabela)
{
    int indice = hashBairros(nome);

    BairroHash *novoBairro =  malloc(sizeof(BairroHash));       // a inserção do bairro usa uma outra estrutura -> BairroHash
    if (novoBairro == NULL){                                    // ela guarda o bairro e faz encadeamento para o próximo BairroHash
        printf ("\nErro ao alocar");
        return;
    }

    Bairro *b = criarBairro(nome);                              // função que retorna um ponteiro para o bairro criado

    novoBairro->b = b;


    if (b != NULL){
     
        novoBairro->b->id = idBairros;                          // coloca o ID do bairro

        idBairros++;

        novoBairro->prox = NULL;

        if (tabela->vetorBairros[indice] == NULL){              // se o índice do vetorBairros estiver vazia -> insere normalmente

            tabela->vetorBairros[indice] = novoBairro;

        }

                                                                // tratamento de colisão
        else {
            BairroHash *aux = tabela->vetorBairros[indice];

            while (aux->prox != NULL){                          // insere o bairro no final da lista 
                aux = aux->prox;
            }

            aux->prox = novoBairro;
        }
    }
    
}

// função para buscar um bairro pelo nome
Bairro* buscarBairro (char nome[], tabelaBairros *tabela)
{
    int indice = hashBairros(nome);

    BairroHash *aux = tabela->vetorBairros[indice];

    while (aux != NULL)                                         // procura, comparando o bairro com o nome de parâmetro
    {
        if (strcmp(aux->b->nome, nome) == 0){

            return aux->b;                                      // retorna o ponteiro ao bairro se encontrar

        }

        aux = aux->prox;
    }

    return NULL;
}


// função para imprimir a tabela inteira de bairros (somente para correção de problemas)
void imprimirTabelaDeBairros(tabelaBairros *tabela)
{
   printf("\n-----TABELA HASH BAIRROS-----\n");

    for (int i = 0; i < tamanhoMaxVetorBairros; i++)                // caminha por cada índice do vetor de Bairros
    {
        printf ("\n\n%d:", i);

        if (tabela->vetorBairros[i] != NULL){

            BairroHash *aux = tabela->vetorBairros[i];

            while (aux != NULL){                                    // caminha por cada BairroHash, imprimindo as informções dos bairros
                printf ("\nId do bairro: %d", aux->b->id);
                printf ("\nNome do bairro: %s", aux->b->nome);

                printf ("\n");

                aux = aux->prox;

            }

            printf ("\n");

        }
    }
}

// função para inicializar a tabela de cidadãos
void inicializarTabelaCidadaos (tabelaCidadaos *tabela)
{
    tabela->populacaoTotal = 0;

    for (int i = 0; i < tamanhoMaxVetorCidadaos; i++)                   // inicializa o vetor de cidadão como NULL
    {
        tabela->vetorCidadaos[i] = NULL;

    }
}

// função hash para cidadãos
int hashCidadaos (int cpf)
{
    return cpf % tamanhoMaxVetorCidadaos;                               // função hash que retorna o índice do cidadao
}                                                                       // como o sistema usa nomes aleatorios e repetidos, é melhor utilizar
                                                                        // o cpf como chave

// função para inserção na tabela de cidadãos
void inserirTabelaCidadaos(Cidadao *novoCidadao, tabelaCidadaos *tabela) {

    int indice = hashCidadaos(novoCidadao->cpf);

    CidadaoHash *novoCidadaoNaTabela = malloc(sizeof(CidadaoHash));         // o cidadaoHash é uma estrutura que guarda o Cidadao e faz o encadeamento
    if (novoCidadaoNaTabela == NULL) {
        printf("Erro de alocação de memória\n");
        return;
    }

    novoCidadaoNaTabela->c = novoCidadao;                                   // guarda o Cidadao
    novoCidadaoNaTabela->prox = NULL;

    if (tabela->vetorCidadaos[indice] == NULL)                              // se o índice do vetor estiver vazio, guarda diretamente
    {
        tabela->vetorCidadaos[indice] = novoCidadaoNaTabela;
    } 
    
    else                                                                    // tratamento de colisão
    {
        CidadaoHash *aux = tabela->vetorCidadaos[indice];

        while (aux->prox != NULL)                                           // guarda no final da lista o novo cidadão
        {
            aux = aux->prox;
        }
        
        aux->prox = novoCidadaoNaTabela;
    }

    tabela->populacaoTotal++;
}


// função para imprimir os cidadãos
void imprimirTabelaCidadaos (tabelaCidadaos *tabela)
{
    printf("\n-----TABELA HASH CIDADAOS-----\n");


    for (int i = 0; i < tamanhoMaxVetorCidadaos; i++) 
    {                                                                       // caminha por cada índice do vetor
        
        printf("\n\n%d:", i);
        
        CidadaoHash *aux = tabela->vetorCidadaos[i];

        while (aux != NULL)                                                 // caminha por cada Cidadao, imprimindo suas informações   
        {
            if (aux->c != NULL) 
            {
                printf("\nID do cidadao: %d\n", aux->c->id);
                printf("CPF: %d\n", aux->c->cpf);
                printf("Nome: %s\n", aux->c->nome);
                printf("Email: %s\n", aux->c->email);
                printf("Bairro: %s\n", aux->c->endereco->nome);
            }
            aux = aux->prox;
        }
    }
}

// função para buscar cidadão a partir do nome
Cidadao* buscarCidadao (tabelaCidadaos *tabela, int cpf)
{
    int indice = hashCidadaos(cpf);

    CidadaoHash *aux = tabela->vetorCidadaos[indice];

    while (aux != NULL)                                                       // procura, comparando com o nome de parâmetro
    {
        if (aux->c->cpf == cpf)
        {
            return aux->c;                                                       // retorna o ponteiro ao cidadão, se encontrar
        }
        aux = aux->prox;
    }

    return NULL;
}


