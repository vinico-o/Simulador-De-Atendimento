#include <stdio.h>
#include "BairrosCidadao.c"


int main ()
{

    tabelaBairros tabelaB;
    tabelaCidadaos tabelaC;

    inicializarTabelaBairros(&tabelaB);
    inicializarTabelaCidadaos(&tabelaC);

    inserirTabelaBairros ("aad", &tabelaB);
    inserirTabelaBairros ("aam", &tabelaB);
    inserirTabelaBairros ("Guanabara", &tabelaB);
    inserirTabelaBairros ("Rosas", &tabelaB);
    inserirTabelaBairros ("Aguas Claras", &tabelaB);
    
    inserirTabelaCidadaos ("Junior", &tabelaC, &tabelaB);
    inserirTabelaCidadaos ("Pedro", &tabelaC, &tabelaB);
    inserirTabelaCidadaos ("Lucas", &tabelaC, &tabelaB);
    inserirTabelaCidadaos ("Ana", &tabelaC, &tabelaB);
    inserirTabelaCidadaos ("Ona", &tabelaC, &tabelaB);


    imprimirTabelaDeBairros(&tabelaB);
    imprimirTabelaCidadaos(&tabelaC);

    return 0;
}