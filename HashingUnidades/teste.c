#include <stdio.h>
#include "Tabela_Hash.c"

int main()
{
    TabHashUnidade tabela;
    UnidadeHash *busca;

    InicializarTabelaHashUnidades(&tabela);
    InserirTabelaUnidades("vinicius", &tabela);
    InserirTabelaUnidades("cauan", &tabela);
    InserirTabelaUnidades("igor", &tabela);
    InserirTabelaUnidades("unesp", &tabela);
    InserirTabelaUnidades("vinicius", &tabela);

    busca = BuscarTabelaHashUnidades("vinicius", &tabela);
    printf("%d\n%s", busca->unidade.id, busca->unidade.nome);

    ImprimirTabelaHashUnidades(&tabela);

    return 0;
}