#include <stdio.h>
#include "Tabela_Hash.c"

int main()
{
    TabHashUnidade tabela;
    UnidadeHash *busca;

    Inicializar(&tabela);
    InserirTabelaUnidades("vinicius", &tabela);
    InserirTabelaUnidades("cauan", &tabela);
    InserirTabelaUnidades("igor", &tabela);
    InserirTabelaUnidades("unesp", &tabela);
    InserirTabelaUnidades("vinicius", &tabela);

    busca = BuscarTabela("vinicius", &tabela);
    printf("%d\n%s", busca->unidade.id, busca->unidade.nome);

    ImprimirTabela(&tabela);

    return 0;
}