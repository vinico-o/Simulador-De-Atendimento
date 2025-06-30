#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Lista_Cruzada.c"
#include "../struct_comum.h"

int main ()
{
    srand(time(NULL));
    Matriz matriz;

    Inicializar_Matriz(&matriz);

    GerarMatrizAleatoria(&matriz);

    ImprimirMatrizCruzada(&matriz);

    return 0;
}