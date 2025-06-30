#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Arvore_Ocorrencias.c"
#include "../struct_comum.h"

#define QNT_OCORRENCIAS 24
#define TOTAL_OCORRENCIAS 24

// Função para imprimir uma ocorrência formatada
void ImprimirOcorrencia(Ocorrencia o) {
    const char* gravidadeStr[] = { "ALTA", "MEDIA", "BAIXA" };
    printf("ID: %02d | Gravidade: %5s | Ocorrencia: %-s\n", o.idOcorrencia, gravidadeStr[o.nivel], o.ocorrencia);
}

// Impressão em ordem com detalhes
void ImprimirEmOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        ImprimirEmOrdem(raiz->esquerda);
        ImprimirOcorrencia(raiz->ocorrencia);
        ImprimirEmOrdem(raiz->direita);
    }
}

int main() {
    NoAVL* raiz;
    Ocorrencia resultado;
    Inicializar_Arvore_AVL(&raiz);
    srand(time(NULL)); // inicializa gerador de aleatórios

    // Dados agrupados
    char* ocorrenciaPolicia[] = {
        "Assalto", "Furto", "Homicidio", "Estelionato",
        "Ameaca", "Sequestro", "Embriaguez", "Receptacao"
    };
    Gravidade gravidadePolicia[] = {
        ALTA, MEDIA, ALTA, BAIXA,
        MEDIA, ALTA, MEDIA, BAIXA
    };

    char* ocorrenciaHospital[] = {
        "Queda", "Ferimento", "Febre", "Dor",
        "Desmaio", "Convulcao", "Infeccao", "Alergia"
    };
    Gravidade gravidadeHospital[] = {
        BAIXA, MEDIA, ALTA, BAIXA,
        ALTA, MEDIA, BAIXA, ALTA
    };

    char* ocorrenciaBombeiro[] = {
        "Incendio", "Acidente", "Afogamento", "Deslizamento",
        "Resgate", "Busca", "Vazamento", "Explosao"
    };
    Gravidade gravidadeBombeiro[] = {
        ALTA, BAIXA, MEDIA, ALTA,
        MEDIA, BAIXA, MEDIA, ALTA
    };

    int id = 1;

    // Geração aleatória de ocorrências
    for (int i = 0; i < TOTAL_OCORRENCIAS; i++) {
        int tipo = rand() % 3; // 0 = Policia, 1 = Hospital, 2 = Bombeiro
        int indice = rand() % 8; // índice dentro do vetor

        Ocorrencia o;
        o.idOcorrencia = id++;

        if (tipo == 0) {
            o.nivel = gravidadePolicia[indice];
            strcpy(o.ocorrencia, ocorrenciaPolicia[indice]);
        } else if (tipo == 1) {
            o.nivel = gravidadeHospital[indice];
            strcpy(o.ocorrencia, ocorrenciaHospital[indice]);
        } else {
            o.nivel = gravidadeBombeiro[indice];
            strcpy(o.ocorrencia, ocorrenciaBombeiro[indice]);
        }

        Inserir_Arvore_AVL(&raiz, o);
    }

    printf("=== Arvore de Ocorrencias (Em Ordem): ===\n");
    ImprimirEmOrdem(raiz);

    printf("\n=== Remocao de IDs 5, 12, 17 ===\n");
    Remover_Arvore_AVL(&raiz, 5);
    Remover_Arvore_AVL(&raiz, 12);
    Remover_Arvore_AVL(&raiz, 17);

    printf("\n=== Ocorrencias Apos Remocoes: ===\n");
    ImprimirEmOrdem(raiz);

    printf("\nAltura final da arvore: %d\n", Altura(raiz));

    printf("\n=== Ocorrencia Mais Prioritaria ===\n");
    ObterOcorrenciaPrioritaria(raiz, &resultado);
    ImprimirOcorrencia(resultado);

    return 0;
}
