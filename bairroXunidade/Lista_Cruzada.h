#define MAXBAIRRO 5 //linha da matriz indica os bairros
#define MAXUNIDADE 4 //coluna da matriz indica os servicos 
#define MAXNOME 50

// cada no presente na matriz é aliado a uma linha e uma coluna, demonstrando que certo bairro possui um certo servico

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
void Inserir(Matriz* matriz, int linha, int coluna, Bairro bairro, Unidade unidade);
void Remover(Matriz* matriz, int linha, int coluna);
void Imprimir(Matriz *matriz);
void GerarBairroAleatorio(Bairro* bairro, int* indice);
void GerarUnidadeAleatoria(Unidade* unidade, int* indice);