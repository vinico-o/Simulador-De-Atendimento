#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "fila_din.c"

#define NUM_SERVICOS 3
#define NUM_PESSOAS 1000

typedef struct{
    char nomeBairro[30];
    int id;
    int num_servicos_no_bairro;
    //pensei nos serviços ir de 1 a num_serviços, pq ai teria tipo uma ordem
    // se for 3 teria tudo, 2 teria os 2 primeiros e vai...
}Bairro;
typedef struct{
    char nome[30];
    char email[30];
    Bairro endereco;
    int cpf;
    int servico_desejado;

    //Essa parte de baixo é para dados estatísticos
    int chegada;
    int saida;
    int num_fila;
    int tempEspera;
}Cidadao;
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

    for(int i=0;i<NUM_SERVICOS;i++)
    {
        inicializar(&servicos[i]);
        num_pessoas_fila[i] = 0;
        atendimentos_por_fila[i] = 0;
        tempoEsperaFila[i] = 0;
    }
    for(int i=0;i<NUM_PESSOAS;i++,num_cpf++)
    {
        pessoa[i].chegada = 0;
        pessoa[i].saida = 0;
        pessoa[i].num_fila = 0;
        pessoa[i].tempEspera = 0;
        pessoa[i].servico_desejado = rand()% NUM_SERVICOS + 1;
        pessoa[i].endereco.id = rand()% 30 + 1;
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
        pessoa[i].endereco.num_servicos_no_bairro = rand()% NUM_SERVICOS + 1;
        pessoa[i].cpf = num_cpf;
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
