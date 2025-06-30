#include "../struct_comum.h"

typedef struct NoAVL
{
    Ocorrencia ocorrencia;
    struct NoAVL* direita;
    struct NoAVL* esquerda;
} NoAVL;

void Inicializar_Arvore_AVL(NoAVL** raiz);
NoAVL* CriarNo(Ocorrencia ocorrencia);
void Inserir_Arvore_AVL(NoAVL** raiz, Ocorrencia ocorrencia);
void Remover_Arvore_AVL(NoAVL** raiz, int idOcorrencia);
void PreOrdem(NoAVL* raiz);
void EmOrdem(NoAVL* raiz);
void PosOrdem(NoAVL* raiz);
int Altura(NoAVL* raiz);
int CalcularFatorBalanceamento(NoAVL* raiz);
void RotacaoEsquerda(NoAVL** raiz);
void RotacaoDireita(NoAVL** raiz);
void BuscarOcorrenciaPrioritaria(NoAVL* raiz, Ocorrencia* melhor);