#include <stdio.h>
#include "BairrosCidadao.h"



int main ()
{

    tabelaBairros tabelaB;
    tabelaCidadaos tabelaC;

    inicializarTabelaBairros(&tabelaB);
    inicializarTabelaCidadaos(&tabelaC);

    inserirTabelaBairros ("aam", &tabelaB);
    inserirTabelaBairros ("aad", &tabelaB);


    return 0;
}