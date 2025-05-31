#include <stdio.h>
#include "Tabela_Hash.c"

int main()
{
    TabHashUnidade tabela;

    Inicializar(&tabela);
    InserirTabelaUnidades("vinicius", &tabela);
    InserirTabelaUnidades("cauan", &tabela);
    InserirTabelaUnidades("igor", &tabela);
    InserirTabelaUnidades("unesp", &tabela);
    InserirTabelaUnidades("vinicius", &tabela);

    ImprimirTabela(&tabela);

    return 0;
}