#include <stdio.h>
#include <stdlib.h>
#include "ArvBB.h"
void inicializanoArvBB(noArvBB **abb)
{
    *abb = NULL;
}
int verif_vazianoArvBB(noArvBB *abb)
{
    if(!abb) return 1;
    return 0;
}
void inserirnoArvBB(noArvBB **abb,int elem)
{
    noArvBB *newNo = malloc(sizeof(noArvBB));
    newNo->dir=NULL;
    newNo->esq=NULL;
    newNo->elem = elem;

    if(verif_vazianoArvBB(*abb))
    {
        *abb = newNo;
        printf("Elemento inserido com sucesso! %d\n",elem);
        return;
    }
    else
    {
        noArvBB *aux = *abb;
        if(aux->elem == elem)
        {
            printf("Elemento ja contido na arvore!\n");
            free(newNo);
            return;
        }
        if(aux->elem>elem)
        {
            if(!aux->esq)
            {
                aux->esq = newNo;
                printf("Elemento inserido com sucesso! %d\n",elem);
                return;
            }
            else
            {
                free(newNo);
                inserirnoArvBB(&(aux->esq),elem);
            }
        }
        if(aux->elem<elem)
        {
            if(!aux->dir)
            {
                aux->dir = newNo;
                printf("Elemento inserido com sucesso! %d\n",elem);
                return;
            }
            else
            {
                free(newNo);
                inserirnoArvBB(&(aux->dir),elem);
            }
        }
    }
}
noArvBB* buscanoArvBB(noArvBB **abb,int elem)
{
    if(verif_vazianoArvBB(*abb))
    {
        printf("Arvore esta vazia!\n");
        return NULL;
    }
    else
    {
        noArvBB *aux =  *abb;
        if(aux->elem==elem)
        {
            printf("Elemento esta na arvore!\n");
            return aux;
        }
        if(aux->elem>elem)
        {
            if(!aux->esq)
            {
                printf("Elemento nao esta na arvore!\n");
                return NULL;
            }
            else
            {
                return buscanoArvBB(&(aux->esq),elem);
            }
        }
        if(aux->elem<elem)
        {
            if(!aux->dir)
            {
                printf("Elemento nao esta na arvore!\n");
                return NULL;
            }
            else
            {
                return buscanoArvBB(&(aux->dir),elem);
            }
        }
    }
}
noArvBB* buscaSubstArvBB(noArvBB **abb,int *elem)
{
    if(verif_vazianoArvBB(*abb))
    {
        printf("Arvore esta vazia!\n");
        return NULL;
    }
    else
    {
        noArvBB *aux =  *abb;
        if(aux->elem==*elem)
        {
            printf("Elemento esta na arvore!\n");
            //agora q eu achei o elem que quero remover vou procurar um substituto para remover ele
            //se pa que eu vou 1 para esq do elem e dps full dir para achar
            //TODO fazer indo 1 para dir do elem e dps full esq para achar, caso nao tenha nada a esq e algo a dir.
            noArvBB *antaux = NULL;
            if(aux->esq)
            {
                antaux = aux;
                aux = aux->esq;
                while(aux->dir)
                {
                    antaux = aux;
                    aux = aux->dir;
                }
                //*elem = aux->elem;

                return aux;
            }
            else if(aux->dir)
            {
                antaux = aux;
                aux = aux->dir;
                while(aux->esq)
                {
                    antaux = aux;
                    aux = aux->esq;
                }
                //*elem = aux->elem;

                return aux;
            }
            else
            {
                printf("O nó é um folha. Não há subst, apenas remova-o!\n");
                return NULL;
            }

        }
        if(aux->elem>*elem)
        {
            if(!aux->esq)
            {
                printf("Elemento nao esta na arvore!\n");
                return NULL;
            }
            else
            {
                return buscaSubstArvBB(&(aux->esq),elem);
            }
        }
        if(aux->elem<*elem)
        {
            if(!aux->dir)
            {
                printf("Elemento nao esta na arvore!");
                return NULL;
            }
            else
            {
                return buscaSubstArvBB(&(aux->dir),elem);
            }
        }
    }

}
noArvBB* buscaAntecessorArvBB(noArvBB **abb,int elem,noArvBB *antaux)
{
    if(verif_vazianoArvBB(*abb))
    {
        printf("Arvore esta vazia!\n");
        return NULL;
    }
    else
    {
        noArvBB *aux =  *abb;
        if(aux->elem==elem)
        {
            return antaux;
        }
        if(aux->elem>elem)
        {
            if(!aux->esq)
            {
                printf("Elemento nao esta na arvore!\n");
                return NULL;
            }
            else
            {
                return buscaAntecessorArvBB(&(aux->esq),elem,aux);
            }
        }
        if(aux->elem<elem)
        {
            if(!aux->dir)
            {
                printf("Elemento nao esta na arvore!\n");
                return NULL;
            }
            else
            {
                return buscaAntecessorArvBB(&(aux->dir),elem,aux);
            }
        }
    }
}
void removerNoArvBB(noArvBB **abb,int *elem)
{
    if(verif_vazianoArvBB(*abb))
    {
        printf("Arvore esta vazia!\n");
        return;
    }
    else
    {
        noArvBB *remocao = buscanoArvBB(abb,*elem);
        if(!remocao)
        {
            printf("Elemento nao encontrado!\n");
            return;
        }
        noArvBB *ant = buscaAntecessorArvBB(abb,*elem,NULL);
        if(!remocao->esq && !remocao->dir)
        {
            if(ant)
            {
                if(ant->esq==remocao) ant->esq = NULL;
                if(ant->dir==remocao) ant->dir = NULL;
            }
            else
            {
                *abb = NULL;
            }
            free(remocao);
            return;
        }
        if(!remocao->esq || !remocao->dir)
        {
            noArvBB *filho;
            if(remocao->esq) filho = remocao->esq;
            else filho = remocao->dir;
            if(ant)
            {
                if(ant->esq == remocao) ant->esq = filho;
                if(ant->dir == remocao) ant->dir = filho;
            }
            else
            {
                *abb = filho;
            }
            free(remocao);
            return;
        }
        else
        {
            noArvBB *subst = buscaSubstArvBB(abb,&(remocao->elem));
            if(subst)
            {
                remocao->elem = subst->elem;
                noArvBB *antsubst = buscaAntecessorArvBB(abb,subst->elem,NULL);
                if (antsubst)
                {
                    if (antsubst->esq == subst)
                    {
                        antsubst->esq = NULL;
                    }
                    else
                    {
                        antsubst->dir = NULL;
                    }
                }
                free(subst);
            }
        }

    }
}
void imprimirPreOrdem(noArvBB **abb)
{
    noArvBB *aux = *abb;
    if(aux)
    {
        printf("%d ",aux->elem);
        imprimirPreOrdem(&(aux->esq));
        imprimirPreOrdem(&(aux->dir));
    }

}
void imprimirEmOrdem(noArvBB **abb)
{
    noArvBB *aux = *abb;
    if(aux)
    {
        imprimirEmOrdem(&(aux->esq));
        printf("%d ",aux->elem);
        imprimirEmOrdem(&(aux->dir));
    }
}
void imprimirPosOrdem(noArvBB **abb)
{
    noArvBB *aux = *abb;
    if(aux)
    {
        imprimirPosOrdem(&(aux->esq));
        imprimirPosOrdem(&(aux->dir));
        printf("%d ",aux->elem);
    }
}
noArvBB* inverter_arv(noArvBB *abb)
{
    if(!abb) return NULL;
    noArvBB *newNo = malloc(sizeof(noArvBB));
    newNo->elem = abb->elem;

    newNo->esq = inverter_arv(abb->dir);
    newNo->dir = inverter_arv(abb->esq);


    return newNo;
}
