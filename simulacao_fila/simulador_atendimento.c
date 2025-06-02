#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "fila_din.c"
#include "pilha.c"

#define NUM_SERVICOS 3
#define NUM_PESSOAS 1000
#define MAXNOME 50
#define MAXBAIRRO 5

typedef struct{
    char nomeBairro[MAXNOME];
    int id;
    int num_servicos_no_bairro;

    //pensei nos servi�os ir de 1 a num_servi�os, pq ai teria tipo uma ordem
    // se for 3 teria tudo, 2 teria os 2 primeiros e vai...
    //perguntar para o cua (eu acho) se o endereco da struct cidadao seria o nome do bairro
    //e ve com ele se seria bom fazer igual fez com o bairro e deixar uma struct de cidadao generica
    // tb ver com ele oq seria exatamente o id da struct cidadao
}Bairro;
typedef struct{
    int id; //coloquei provisorio pq tem q ver com o caua oq vai fazer com essa struct
    int cpf;
    char nome[MAXNOME];
    char email[MAXNOME];
    Bairro endereco;
    int servico_desejado;
    char ocorrencia[MAXNOME];

    //Essa parte de baixo � para dados estat�sticos
    int chegada;
    int saida;
    int num_fila;
    int tempEspera;
}Cidadao;

int qntOcorrencia = 8;
char* ocorrenciaPolicia[] = {
    "Assalto", "Furto", "Homicidio", "Estelionato", 
    "Ameaca", "Sequestro", "Embriaguez", "Receptacao"
};

char* ocorrenciaHospital[] = {
    "Queda", "Ferimento", "Febre","Dor", 
    "Desmaio", "Convulcao", "Infeccao", "Alergia", 
};

char* ocorrenciaBombeiro[] = {
    "Incendio", "Acidente", "Afogamento", "Deslizamento",
    "Resgate", "Busca", "Vazamento", "Explosao"
};


void GerarOcorrenciaAleatorio(Cidadao* pessoa)
{
    int indice = rand() % qntOcorrencia;
    //se o serviço for o 1, entao sua ocorrencia é policial
    if(pessoa->servico_desejado == 1)
    {
        strcpy(pessoa->ocorrencia, ocorrenciaPolicia[indice]);
    }
    //se o serviço for o 2, entao sua ocorrencia é hospitalar
    if(pessoa->servico_desejado == 2)
    {
        strcpy(pessoa->ocorrencia, ocorrenciaHospital[indice]);
    }
    //se o serviço for o 3, entao sua ocorrencia é de bombeiro
    if(pessoa->servico_desejado == 3)
    {
        strcpy(pessoa->ocorrencia, ocorrenciaBombeiro[indice]);
    }
    
}
int qntNomes = 28;
char* nomesAleatorios[] = {
    "Laura", "Bruno", "Carla", "Diego",
    "Eduarda", "Felipe", "Luciana", "Henrique",
    "Bianca", "João", "Katia", "Lucas",
    "Mariana", "Nicolas", "Olívia", "Paulo",
    "Sílvia", "Rafael", "Sofia", "Tiago",
    "André", "Gabriel", "Daniel", "José",
    "Fernando", "Gustavo", "Hugo", "Igor"
};

void GerarNomeAleatorio(Cidadao* pessoa)
{
    int indice = rand() % qntNomes;
    strcpy(pessoa->nome,nomesAleatorios[indice]);
}

int main()
{
    setlocale(LC_ALL,"Portuguese");
    srand(time(NULL));

    int tempTotal = 500;
    int tempAtual = 0;
    int chegada = 0;
    int tempAtendimento = 0;
    int num_pessoa = 1;
    int num_cpf = 1000000;

    Cidadao pessoa[NUM_PESSOAS];
    int tempoEsperaFila[NUM_SERVICOS];

    Fila servicos[NUM_SERVICOS];
    int num_pessoas_fila[NUM_SERVICOS];

    int atendimentos_por_fila[NUM_SERVICOS];

    int tempChegadaFila[NUM_SERVICOS];
    int tempSaidaFila[NUM_SERVICOS];

    Pilha historico_atendimento[NUM_SERVICOS];


    for(int i=0;i<NUM_SERVICOS;i++)
    {
        //Instruções para Fila
        inicializar(&servicos[i]);
        num_pessoas_fila[i] = 0;
        atendimentos_por_fila[i] = 0;
        tempoEsperaFila[i] = 0;

        //Instruções para Pilha
        inicializa_pilha(&historico_atendimento[i]);
    }
    for(int i=0;i<NUM_PESSOAS;i++,num_cpf++)
    {
        pessoa[i].chegada = 0;
        pessoa[i].saida = 0;
        pessoa[i].num_fila = 0;
        pessoa[i].tempEspera = 0;
        pessoa[i].servico_desejado = rand()% NUM_SERVICOS + 1; //gera aleatoriamente o serviço de cada pessoa
        pessoa[i].endereco.id = rand()% MAXBAIRRO + 1; //isso aqui vai depender do numero de bairros que vai ter

        //esse for seria para definir quais servicos cada bairro tera
        //provavelmente vai mudar por causa da lista cruzada, ver com o vinicius
        /*
        for(int i=0;i<MAXBAIRRO;i++)
        {
            if(i == pessoa[i].enderco.id)
            {
                peguei de exemplo o cod da função GerarBArirroAleatorio da Lista_Cruzada.c
                strcpy(pessoa[i].enderco.nomeBairro,nomesBairros[])
            }

        
        }
        
        
        */
        for(int j=0;j<30;j++)
        {
            if(pessoa[i].endereco.id == j)
            {
                if(j%3==0)
                {
                    pessoa[i].endereco.num_servicos_no_bairro = 1;
                }
                if(j%3==1)
                {
                   pessoa[i].endereco.num_servicos_no_bairro = 2;
                }
                if(j%3==2)
                {
                    pessoa[i].endereco.num_servicos_no_bairro = 3;
                }
            }
        }
        pessoa[i].cpf = num_cpf;
        GerarOcorrenciaAleatorio(&pessoa[i]);
        GerarNomeAleatorio(&pessoa[i]);
    }

    chegada += rand()%4 + 1;
    tempAtendimento += chegada + rand()%16 + 1;

    while(tempTotal)
    {
        if(chegada == tempAtual)
        {
            int fila_inserido = pessoa[num_pessoa].servico_desejado - 1;
            inserir(&servicos[fila_inserido],num_pessoa);
            pessoa[num_pessoa].chegada = tempAtual;
            pessoa[num_pessoa].num_fila = fila_inserido;
            num_pessoa++;
            num_pessoas_fila[fila_inserido]++;
            chegada += rand()%4 + 1;

        }
        if(tempAtendimento == tempAtual)
        {
            for(int i=0;i<NUM_SERVICOS;i++)
            {
                if(!vazia(&servicos[i]))
                {
                    int pessoa_;
                    remover(&servicos[i],&pessoa_);
                    printf("\tPessoa %d atendida!\n",pessoa_);
                    printf("\t%d \t %s \t %s\n",pessoa[pessoa_].cpf,pessoa[pessoa_].nome,pessoa[pessoa_].ocorrencia);
                    printf("\tOcorrencia adicionada ao historico de atendimento\n\n");
                    push(&historico_atendimento[i],pessoa[pessoa_].ocorrencia);
                    pessoa[pessoa_].saida = tempAtual;
                    atendimentos_por_fila[i]++;
                }
            }
            tempAtendimento += rand()%16 + 1;
        }

        tempTotal--;
        printf("Tempo %d\n",tempAtual);
        for(int i=0;i<NUM_SERVICOS;i++)
        {
            imprimir_fila(&servicos[i]);
        }
        printf("\n");
        tempAtual++;
    }

return 0;
}
