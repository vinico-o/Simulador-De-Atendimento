#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "BairrosCidadao.h"


static int idBairros = 1;   // simula o ID de bancos de dados para BAIRROS
static int idCidadao = 1;   // simula o ID de bancos de dados para CIDADAOS


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


    // funcao de insercao na tabela hash de bairros
void inserirTabelaBairros (char nome[],tabelaBairros *tabela)
{
    int indice = hashBairros(nome);

    BairroHash *novoBairro =  malloc(sizeof(BairroHash));
    if (novoBairro == NULL){
        printf ("\nErro ao alocar");
        return;
    }

    novoBairro->b.id = idBairros;

    idBairros++;

    strcpy(novoBairro->b.nome, nome);

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

    // funcao para buscar um bairro pelo nome

BairroHash* buscarBairro (char nome[], tabelaBairros *tabela)
{
    int indice = hashBairros(nome);

    BairroHash *aux = tabela->vetorBairros[indice];

    while (aux != NULL)
    {
        if (strcmp(aux->b.nome, nome) == 0){

            return aux;

        }

        aux = aux->prox;
    }

    return NULL;
}


    // funcao para imprimir a tabela inteira de bairros (somente para correção de problemas)
void imprimirTabelaDeBairros(tabelaBairros *tabela)
{
    for (int i = 0; i < tamanhoMaxVetorBairros; i++)
    {
        printf ("\n\n%d:", i);

        if (tabela->vetorBairros[i] != NULL){

            BairroHash *aux = tabela->vetorBairros[i];

            while (aux != NULL){
                printf ("\nId do bairro: %d", aux->b.id);
                printf ("\nNome do bairro: %s", aux->b.nome);

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
int hashCidadaos (char nome[])
{
    int soma = 0;

    int tamanho = strlen(nome);

    for (int i = 0; i < tamanho; i++)
    {
        soma += i * nome[i];
    }

    return soma % tamanhoMaxVetorCidadaos;
}


    // funcao para insercao na tabela de cidadaos

void inserirTabelaCidadaos (char nome[], tabelaCidadaos *tabela, tabelaBairros *tBairros)
{
    printf ("\n\n(CRIANDO CIDADAO)\n");                           // remover isto

    int cpf;
    char email[20];
    char endereco[50];
    char bairro[20];

    printf ("\nInforme o cpf: ");
    scanf ("%d", &cpf);

    getchar();

    printf ("\nInforme o email: ");
    fgets(email, sizeof(email), stdin);
    email[strlen(email) - 1] = '\0';        // o '\n' tava dando problema

    printf ("\nInforme o endereco: ");
    fgets(endereco, sizeof(endereco), stdin);
    endereco[strlen(endereco) - 1] = '\0';

    printf ("\nInforme o nome do bairro: ");
    fgets(bairro, sizeof(bairro), stdin);
    bairro[strlen(bairro) - 1] = '\0';

    CidadaoHash *novoCidadao = malloc (sizeof(CidadaoHash));

    if (novoCidadao == NULL){
        printf ("\nErro ao alocar");
        return;
    }

    novoCidadao->c.id = idCidadao;
    novoCidadao->c.cpf = cpf;
    strcpy (novoCidadao->c.nome, nome);
    strcpy (novoCidadao->c.email, email);
    strcpy (novoCidadao->c.endereco, endereco);
    novoCidadao->prox = NULL;

    BairroHash *b = buscarBairro(bairro, tBairros);

    if (b != NULL){
        novoCidadao->c.bairro = b;

        int indice = hashCidadaos(nome);

        if (tabela->vetorCidadaos[indice] == NULL){
            tabela->vetorCidadaos[indice] = novoCidadao;


        }

        else {

            CidadaoHash *aux = tabela->vetorCidadaos[indice];

            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }

            aux->prox = novoCidadao;



        }

        tabela->populacaoTotal++;
        idCidadao++;

    }

    else {
        printf ("\nBairro nao encontrado -> pessoa nao criada");
    }
}

    // funcao para imprimir os cidadaos

void imprimirTabelaCidadaos (tabelaCidadaos *tabela)
{
    for (int i = 0; i < tamanhoMaxVetorCidadaos; i++)
    {
        printf ("\n\n%d: ", i);
        if (tabela->vetorCidadaos[i] != NULL){

            CidadaoHash *aux = tabela->vetorCidadaos[i];

            while (aux != NULL)
            {

                printf ("\nId: %d", aux->c.id);
                printf ("\nCpf: %d", aux->c.cpf);
                printf ("\nNome: %s", aux->c.nome);
                printf ("\nEmail: %s", aux->c.email);
                printf ("\nEndereco: %s", aux->c.endereco);
                printf ("\nNome do bairro: %s", aux->c.bairro->b.nome);

                printf ("\n");

                aux = aux->prox;
            }

        }
    }
}

    // funcao para buscar cidadao a partir do nome

CidadaoHash* buscarCidadao (tabelaCidadaos *tabela, char nome[])
{
    int indice = hashCidadaos(nome);

    CidadaoHash *aux = tabela->vetorCidadaos[indice];

    if (strcmp(aux->c.nome, nome) == 0){
        return aux;
    }


    else {
        while (aux != NULL){

            if (strcmp(aux->c.nome, nome)){
                return aux;
            }
            
            aux = aux->prox;

        }
    }
    return NULL;

}