#include <stdio.h>
#include <stdlib.h>
#include "Arvore_Ocorrencias.h"

void Inicializar_Arvore_AVL(No** raiz)
{
    (*raiz) = NULL;
}

No* CriarNo(Ocorrencia ocorrencia)
{
    No* novo = malloc(sizeof(No));
    if(novo == NULL)
    {
        return NULL;
    }

    novo->direita = NULL;
    novo->esquerda = NULL;
    novo->ocorrencia = ocorrencia;

    return novo;
}

int Altura(No* raiz)
{
    if(raiz == NULL)
    {
        return -1;
    }

    int direita = Altura(raiz->direita);
    int esquerda = Altura(raiz->esquerda);

    if(direita > esquerda)
    {
        return direita + 1;
    }
    else
    {
        return esquerda + 1;
    }

}

int CalcularFatorBalanceamento(No* raiz)
{
    if (raiz == NULL) {
        return 0;
    }
    int fatorBalanceamento = Altura(raiz->esquerda) - Altura(raiz->direita);
    return fatorBalanceamento;
}

void PreOrdem(No* raiz)
{
    if(raiz != NULL)
    {
        printf("%d ", raiz->ocorrencia.idOcorrencia);
        PreOrdem(raiz->esquerda);
        PreOrdem(raiz->direita);
    }
}

void EmOrdem(No* raiz)
{
    if(raiz != NULL)
    {
        EmOrdem(raiz->esquerda);
        printf("%d ", raiz->ocorrencia.idOcorrencia);
        EmOrdem(raiz->direita);
    }
}

void PosOrdem(No* raiz)
{
    if(raiz != NULL)
    {
        PosOrdem(raiz->esquerda);
        PosOrdem(raiz->direita);
        printf("%d ", raiz->ocorrencia.idOcorrencia);
    }
}

void RotacaoEsquerda(No** raiz)
{
    No* aux = (*raiz)->direita;
    (*raiz)->direita = aux->esquerda;
    aux->esquerda = (*raiz);
    *raiz = aux;
}

void RotacaoDireita(No** raiz)
{
    No* aux = (*raiz)->esquerda;
    (*raiz)->esquerda = aux->direita;
    aux->direita = (*raiz);
    *raiz = aux;
}

void Inserir_Arvore_AVL(No** raiz, Ocorrencia ocorrencia)
{
    //Arvore nula
    if((*raiz) == NULL)
    {
        No* novo = CriarNo(ocorrencia);
        if(novo == NULL)
        {
            printf("Erro ao alocar na memoria!");
            return;
        }

        *raiz = novo;
        return;
    }
    else
    {
        //Caminha ate o no folha
        if(ocorrencia.idOcorrencia > (*raiz)->ocorrencia.idOcorrencia)
        {
            Inserir_Arvore_AVL(&((*raiz)->direita), ocorrencia);
        }
        else if(ocorrencia.idOcorrencia < (*raiz)->ocorrencia.idOcorrencia)
        {
            Inserir_Arvore_AVL(&((*raiz)->esquerda), ocorrencia);
        }
        else
        {
            printf("O no ja existe!\n");
            return;
        }

        //Balanceamento
        int fatorBalanceamento = CalcularFatorBalanceamento(*raiz);

        //Arvore desbalanceada para a esquerda
        if(fatorBalanceamento > 1)
        {
            //Fator de Balanceamento diferente do sinal do pai
            if(CalcularFatorBalanceamento((*raiz)->esquerda) < 0)
            {
                RotacaoEsquerda(&(*raiz)->esquerda);
                RotacaoDireita(&(*raiz));
            }
            //Fator de Balanceamento com o mesmo sinal do pai
            else
            {
                RotacaoDireita(&(*raiz));
            }
        }
        //Arvore desbalanceada para a direita
        else if(fatorBalanceamento < -1)
        {
            //Fator de Balanceamento diferente do sinal do pai
            if(CalcularFatorBalanceamento((*raiz)->direita) > 0)
            {
                RotacaoDireita(&(*raiz)->direita);
                RotacaoEsquerda(&(*raiz));
            }
             //Fator de Balanceamento com o mesmo sinal do pai
            else
            {
                RotacaoEsquerda(&(*raiz));
            }
        }
    }
}

No* MaiorDosMenores(No* raiz)
{
    No* aux = raiz->esquerda;
    while(aux->direita != NULL)
    {
        aux = aux->direita;
    }

    return aux;
}

void Remover_Arvore_AVL(No** raiz, int idOcorrencia)
{
    if((*raiz) == NULL)
    {
        printf("Impossivel remover de Arvore Vazia");
        return;
    }

    if(idOcorrencia > (*raiz)->ocorrencia.idOcorrencia)
    {
        Remover_Arvore_AVL(&(*raiz)->direita, idOcorrencia);
    }
    else if(idOcorrencia < (*raiz)->ocorrencia.idOcorrencia)
    {
        Remover_Arvore_AVL(&((*raiz)->esquerda), idOcorrencia);
    }
    else //encontramos o no a ser removido
    {
        No* aux;
        //Se o no possuir duas subarvores
        if((*raiz)->direita != NULL && (*raiz)->esquerda != NULL)
        {
            aux = MaiorDosMenores((*raiz));
            (*raiz)->ocorrencia = aux->ocorrencia;
            Remover_Arvore_AVL(&(*raiz)->esquerda, aux->ocorrencia.idOcorrencia);
        }
        //Nao ha uma subarvore ou ha em algum dos lados
        else
        {
            aux = *raiz;
            if((*raiz)->esquerda == NULL)
            {
                *raiz = (*raiz)->direita;
            }
            else if((*raiz)->direita == NULL)
            {
                *raiz = (*raiz)->esquerda;
            }
            free(aux);
        }
    }
    
    if ((*raiz) != NULL) {
        //Balanceamento caso a remocao gere desbalanceamento
        int fatorBalanceamento = CalcularFatorBalanceamento(*raiz);

        if(fatorBalanceamento > 1)
        {
            if(CalcularFatorBalanceamento((*raiz)->esquerda) < 0)
            {
                RotacaoEsquerda(&(*raiz)->esquerda);
            }
            RotacaoDireita(&(*raiz));
        }
        else if(fatorBalanceamento < -1)
        {
            if(CalcularFatorBalanceamento((*raiz)->direita) > 0)
            {
                RotacaoDireita(&(*raiz)->direita);
            }
            RotacaoEsquerda(&(*raiz));
        }
    }
}

int CompararOcorrencias(Ocorrencia atual, Ocorrencia melhor)
{
    //ocorrencia com mais urgencia a comparada
    if (atual.nivel < melhor.nivel)
    {
        return 1;
    }
    //mesma urgencia, mas com id menor (antes na fila)
    if (atual.nivel == melhor.nivel && atual.idOcorrencia < melhor.idOcorrencia)
    {
        return 1;
    }

    return 0;
}

void BuscarOcorrenciaPrioritaria(No* raiz, Ocorrencia* melhor)
{
    if (raiz == NULL)
    {
        return;
    }

    if (CompararOcorrencias(raiz->ocorrencia, *melhor) == 1)//encontrou uma ocorrencia melhor
    {
        *melhor = raiz->ocorrencia;
    }

    BuscarOcorrenciaPrioritaria(raiz->esquerda, melhor);
    BuscarOcorrenciaPrioritaria(raiz->direita, melhor);
}

void ObterOcorrenciaPrioritaria(No* raiz, Ocorrencia* resultado)
{
    if (raiz == NULL)
    {
        return;
    }

    *resultado = raiz->ocorrencia; //inicia com a raiz
    BuscarOcorrenciaPrioritaria(raiz, resultado);
}