#include "../struct_comum.h"

#define MAXNOME 50

// cada no presente na matriz é aliado a uma linha e uma coluna, demonstrando que certo bairro possui um certo servico

typedef struct Ligacao
{
    Bairro infoBairro;
    Unidade infoUnidade;
    int linha; //posicao linha na matriz
    int coluna; //posicao coluna na matriz
    struct Ligacao* proxBairro;
    struct Ligacao* proxUnidade;
} Ligacao;

typedef struct Matriz
{
    Ligacao *listaBairros[MAXBAIRRO];
    Ligacao *listaUnidades[MAXUNIDADE];
} Matriz;

void Inicializar_Matriz(Matriz* matriz);
void RemoverMatrizCruzada(Matriz* matriz, int linha, int coluna);
void ImprimirMatrizCruzada(Matriz *matriz);
bool BuscarUnidadeBairro(Matriz* matriz, int idBairro, int idUnidade);
void GerarMatrizAleatoria(Matriz* matriz);