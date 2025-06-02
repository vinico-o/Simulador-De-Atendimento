#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Lista_Cruzada.c"

int main ()
{
    srand(time(NULL));
    Matriz matriz;
    Bairro bairro;
    Unidade unidade;
    int linha, coluna;
    int numGeracao = 20;

    Inicializar_Matriz(&matriz);

    for(int i = 0; i < numGeracao; i++)
    {   
        GerarBairroAleatorio(&bairro, &linha);
        GerarUnidadeAleatoria(&unidade, &coluna);
        InserirMatrizCruzada(&matriz, linha, coluna, bairro, unidade);
    }

    ImprimirMatrizCruzada(&matriz);

    return 0;
}