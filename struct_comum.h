#ifndef STRUCT_COMUM_H
#define STRUCT_COMUM_H
#include <stdio.h>

#define MAXBAIRRO 5 //linha da matriz indica os bairros
#define MAXUNIDADE 3 //coluna da matriz indica os servicos 
#define MAXNOME 50

typedef struct Bairro
{
    int id;
    char nome[MAXNOME];
} Bairro;

typedef struct Unidade
{
    int id;
    char nome[MAXNOME];
} Unidade;

typedef enum{
    ALTA,MEDIA,BAIXA
}Gravidade;

typedef struct{
    int idOcorrencia;
    Gravidade nivel;
    char ocorrencia[MAXNOME];
    char atendente[MAXNOME];
}Ocorrencia;

char* nomesBairros[] = {"Entidade", "Marupiara", "Industrial", "Rosas", "Aviacao"};
char* nomesUnidades[] = {"Policia", "Hospital", "Bombeiro"};
#endif
