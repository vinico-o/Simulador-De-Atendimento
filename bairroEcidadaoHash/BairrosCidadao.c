#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "BairrosCidadao.h"


int idBairros = 1;   // simula o ID de bancos de dados para BAIRROS

    // funcao de inicializacao da tabela de bairros
void inicializarTabelaBairros (tabelaBairros *tabela)
{
    for (int i = 0; i < tamanhoMaxVetorBairros; i++)
    {
        tabela->vetorBairros[i] = NULL;
    }
}

    // funcao hash para bairros
int hashBairros (char nome[])
{
    int soma = 0;

    int tamanho = strlen(nome);

    for (int i = 0; i < tamanho; i++)
    {
        soma += i * nome[i];
    }

    return soma % tamanhoMaxVetorBairros;
}

Bairro* criarBairro (char nome[])
{
    Bairro* novoBairro = malloc (sizeof(Bairro));

    if (novoBairro != NULL){
        strcpy (novoBairro->nome, nome);
        return novoBairro;
    }


    return NULL;
}


    // funcao de insercao na tabela hash de bairros
void inserirTabelaBairros (char nome[],tabelaBairros *tabela)
{
    int indice = hashBairros(nome);

    BairroHash *novoBairro =  malloc(sizeof(BairroHash));
    if (novoBairro == NULL){
        printf ("\nErro ao alocar");
        return;
    }

    Bairro *b = criarBairro(nome);

    novoBairro->b = b;


    if (b != NULL){
     
        novoBairro->b->id = idBairros;

        idBairros++;

        novoBairro->prox = NULL;

        if (tabela->vetorBairros[indice] == NULL){

            tabela->vetorBairros[indice] = novoBairro;

        }

            // tratamento de colisão
        else {
            BairroHash *aux = tabela->vetorBairros[indice];

            while (aux->prox != NULL){
                aux = aux->prox;
            }

            aux->prox = novoBairro;
        }
    }
    
}

    // funcao para buscar um bairro pelo nome

Bairro* buscarBairro (char nome[], tabelaBairros *tabela)
{
    int indice = hashBairros(nome);

    BairroHash *aux = tabela->vetorBairros[indice];

    while (aux != NULL)
    {
        if (strcmp(aux->b->nome, nome) == 0){

            return aux->b;

        }

        aux = aux->prox;
    }

    return NULL;
}


    // funcao para imprimir a tabela inteira de bairros (somente para correção de problemas)
void imprimirTabelaDeBairros(tabelaBairros *tabela)
{
   printf("\n-----TABELA HASH BAIRROS-----\n");

    for (int i = 0; i < tamanhoMaxVetorBairros; i++)
    {
        printf ("\n\n%d:", i);

        if (tabela->vetorBairros[i] != NULL){

            BairroHash *aux = tabela->vetorBairros[i];

            while (aux != NULL){
                printf ("\nId do bairro: %d", aux->b->id);
                printf ("\nNome do bairro: %s", aux->b->nome);

                printf ("\n");

                aux = aux->prox;

            }

            printf ("\n");

        }
    }
}

    // funcao para inicializar a tabela de cidadaos
void inicializarTabelaCidadaos (tabelaCidadaos *tabela)
{
    tabela->populacaoTotal = 0;

    for (int i = 0; i < tamanhoMaxVetorCidadaos; i++)
    {
        tabela->vetorCidadaos[i] = NULL;

    }
}
    // funcao hash para cidadaos
int hashCidadaos (int cpf)
{
    return cpf % tamanhoMaxVetorCidadaos;
}

/* Cidadao* criarCidadao (char nome[], tabelaBairros *tBairros)
{
    Cidadao *novoCidadao = malloc (sizeof(Cidadao));

    char bairro[MAXNOME];

    printf ("\nInforme o cpf: ");
    scanf ("%d", &novoCidadao->cpf);
    getchar(); // limpa o '\n' deixado pelo scanf

    printf ("\nInforme o email: ");
    fgets(novoCidadao->email, MAXNOME, stdin);
    novoCidadao->email[strcspn(novoCidadao->email, "\n")] = '\0'; // remove '\n'

    printf ("\nInforme o nome do bairro: ");
    fgets(bairro, MAXNOME, stdin);
    bairro[strcspn(bairro, "\n")] = '\0'; // remove '\n'



    Bairro *b = buscarBairro (bairro, tBairros);

    if (b != NULL){

        novoCidadao->endereco = b;
        novoCidadao->id = idCidadao;
        strcpy (novoCidadao->nome, nome);


        return novoCidadao;
    }
    else {
        printf ("\nBairro nao encontrado -> pessoa nao criada");
        free (novoCidadao);
        return NULL;
    }
} */


    // funcao para insercao na tabela de cidadaos

void inserirTabelaCidadaos(Cidadao *novoCidadao, tabelaCidadaos *tabela) {

    int indice = hashCidadaos(novoCidadao->nome);

    CidadaoHash *novoCidadaoNaTabela = malloc(sizeof(CidadaoHash));
    if (novoCidadaoNaTabela == NULL) {
        printf("Erro de alocação de memória\n");
        return;
    }

    novoCidadaoNaTabela->c = novoCidadao;
    novoCidadaoNaTabela->prox = NULL;

    if (tabela->vetorCidadaos[indice] == NULL) {
        tabela->vetorCidadaos[indice] = novoCidadaoNaTabela;
    } else {
        CidadaoHash *aux = tabela->vetorCidadaos[indice];
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novoCidadaoNaTabela;
    }

    tabela->populacaoTotal++;
}


    // funcao para imprimir os cidadaos

void imprimirTabelaCidadaos (tabelaCidadaos *tabela)
{
    printf("\n-----TABELA HASH CIDADAOS-----\n");


    for (int i = 0; i < tamanhoMaxVetorCidadaos; i++) {
        
        printf("\n\n%d:", i);
        
        CidadaoHash *aux = tabela->vetorCidadaos[i];

        while (aux != NULL) 
        {
            if (aux->c != NULL) {
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

    // funcao para buscar cidadao a partir do nome

CidadaoHash* buscarCidadao (tabelaCidadaos *tabela, char nome[])
{
    int indice = hashCidadaos(nome);

    CidadaoHash *aux = tabela->vetorCidadaos[indice];

    while (aux != NULL) {
        if (strcmp(aux->c->nome, nome) == 0) {
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}
