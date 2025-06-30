#include "../struct_comum.h"

typedef struct No
{
    Ocorrencia ocorrencia;
    struct No* direita;
    struct No* esquerda;
} No;

void Inicializar_Arvore_AVL(No** raiz);
No* CriarNo(Ocorrencia ocorrencia);
void Inserir_Arvore_AVL(No** raiz, Ocorrencia ocorrencia);
void Remover_Arvore_AVL(No** raiz, int idOcorrencia);
void PreOrdem(No* raiz);
void EmOrdem(No* raiz);
void PosOrdem(No* raiz);
int Altura(No* raiz);
int CalcularFatorBalanceamento(No* raiz);
void RotacaoEsquerda(No** raiz);
void RotacaoDireita(No** raiz);
void BuscarOcorrenciaPrioritaria(No* raiz, Ocorrencia* melhor);