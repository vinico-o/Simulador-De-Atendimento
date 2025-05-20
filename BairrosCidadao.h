#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanhoMaxVetorBairros 9
#define tamanhoMaxVetorCidadaos 9

static int idBairros = 1;   // simula o ID de bancos de dados para BAIRROS
static int idCidadao = 1;   // simula o ID de bancos de dados para CIDADAOS

    // estrutura de cada bairro
typedef struct Bairro{
    int id;
    char nome[20];
    int quantidadeDeCasas;
    struct Bairro *prox;
}  Bairro;

    // tabela hash para bairros
typedef struct {
    struct Bairro *vetorBairros[tamanhoMaxVetorBairros];
} tabelaBairros;

    // estrutura de cada cidadao
typedef struct Cidadao{
    int id;
    int cpf;
    char nome[20];
    char email[20];
    char endereco[50];
    struct Cidadao *prox;
    struct Bairro *bairro;
} Cidadao;

    // tabela hash para cidadaos
typedef struct {
    int populacaoTotal;
    struct Cidadao *vetorCidadaos[tamanhoMaxVetorCidadaos];
} tabelaCidadaos;


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

    for (int i = 0; i < strlen(nome); i++)
    {
        soma += i * nome[i];
    }

    return soma % tamanhoMaxVetorBairros;
}


    // funcao de insercao na tabela hash de bairros
void inserirTabelaBairros (char nome[],tabelaBairros *tabela)
{
    printf ("\n(CRIANDO BAIRRO)\n");                        // remover isto
    
    int casas;
    printf("Informe a quantidade de casas do bairro: ");
    scanf ("%d", &casas);

    int indice = hashBairros(nome);

    Bairro *novoBairro = malloc (sizeof(Bairro));
    if (novoBairro == NULL){
        printf ("\nErro ao alocar");
        return;
    }

    novoBairro->id = idBairros;

    idBairros++;

    strcpy(novoBairro->nome, nome);

    novoBairro->quantidadeDeCasas = casas;
    novoBairro->prox = NULL;

    if (tabela->vetorBairros[indice] == NULL){

        tabela->vetorBairros[indice] = novoBairro;

    }
    
        // tratamento de colisão
    else { 
        Bairro *aux = tabela->vetorBairros[indice];

        while (aux->prox != NULL){
            aux = aux->prox;
        }

        aux->prox = novoBairro;
    }

}

Bairro* buscarBairro (char nome[], tabelaBairros *tabela)
{
    int indice = hashBairros(nome);
    
    Bairro *aux = tabela->vetorBairros[indice];

    while (aux != NULL)
    {
        if (strcmp(aux->nome, nome) == 0){
            
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

            Bairro *aux = tabela->vetorBairros[i];

            while (aux != NULL){
                printf ("\nId do bairro: %d", aux->id);
                printf ("\nNome do bairro: %s", aux->nome);
                printf ("\nQuantidade de casas que o bairro tem: %d", aux->quantidadeDeCasas);
            
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

    for (int i = 0; i < strlen (nome); i++)
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

    Cidadao *novoCidadao = malloc (sizeof(Cidadao));

    if (novoCidadao == NULL){
        printf ("\nErro ao alocar");
        return;
    }

    novoCidadao->id = idCidadao;
    novoCidadao->cpf = cpf;
    strcpy (novoCidadao->nome, nome);
    strcpy (novoCidadao->email, email);
    strcpy (novoCidadao->endereco, endereco);
    novoCidadao->prox = NULL;

    Bairro *b = buscarBairro(bairro, tBairros);

    if (b != NULL){
        novoCidadao->bairro = b;
    
        int indice = hashCidadaos(nome);

        if (tabela->vetorCidadaos[indice] == NULL){
            tabela->vetorCidadaos[indice] = novoCidadao;
            
            
        }

        else {

            Cidadao *aux = tabela->vetorCidadaos[indice];

            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }

            aux->prox = novoCidadao;


            
        }

        tabela->populacaoTotal++;
        idCidadao++;

        printf ("\nPessoa criada");
    }

    else {
        printf ("\nBairro nao encontrado -> pessoa nao criada");
    }
}

void imprimirTabelaCidadaos (tabelaCidadaos *tabela)
{
    for (int i = 0; i < tamanhoMaxVetorCidadaos; i++)
    {
        printf ("\n\n%d: ", i);
        if (tabela->vetorCidadaos[i] != NULL){

            Cidadao *aux = tabela->vetorCidadaos[i];

            while (aux != NULL)
            {

                printf ("\nId: %d", aux->id);
                printf ("\nCpf: %d", aux->cpf);
                printf ("\nNome: %s", aux->nome);
                printf ("\nEmail: %s", aux->email);
                printf ("\nEndereco: %s", aux->endereco);
                printf ("\nNome do bairro: %s", aux->bairro->nome);

                printf ("\n");

                aux = aux->prox;
            }

        }
    }
}

