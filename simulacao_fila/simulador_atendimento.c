#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "fila_din.c"
#include "pilha.c"
#include "ArvBB.c"
#include "../HashingUnidades/Tabela_Hash.c"

#define NUM_SERVICOS 3
#define NUM_PESSOAS 1000
#define MAXNOME 50
#define MAXBAIRRO 5



typedef struct{
    char nome[MAXNOME];
    int id;
}Bairro;

typedef struct{
    Bairro bairrin;
    Fila servicos[NUM_SERVICOS];
}BairroSimulacao;

typedef struct{
    int id;
    int cpf;
    char nome[MAXNOME];
    char email[MAXNOME];
    Bairro *endereco;
}Cidadao;

typedef struct{
    Cidadao cidadao;
    int servico_desejado;
    char ocorrencia[MAXNOME];
    int idOcorrencia;
    //Essa parte de baixo � para dados estat�sticos
    int chegada;
    int saida;
    int num_fila;
    int tempEspera;
}CidadaoSimulacao;

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


void GerarOcorrenciaAleatorio(CidadaoSimulacao* pessoa)
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

void GerarNomeAleatorio(CidadaoSimulacao* pessoa,int *indice)
{
    *indice = rand() % qntNomes;
    strcpy(pessoa->cidadao.nome,nomesAleatorios[*indice]);
}

char* emailAleatorio[] = {
    "laura.silva@example.com", "bruno.oliveira@example.org", "carla.souza@example.net", "diego.lima@example.com",
    "eduarda.alves@example.org", "felipe.costa@example.net", "luciana.martins@example.com", "henrique.gomes@example.org",
    "bianca.rocha@example.net", "joao.mendes@example.com", "katia.pereira@example.org", "lucas.santana@example.net",
    "mariana.dias@example.com", "nicolas.campos@example.org", "olivia.barbosa@example.net", "paulo.ribeiro@example.com",
    "silvia.ferreira@example.org", "rafael.nogueira@example.net", "sofia.teixeira@example.com", "tiago.freitas@example.org",
    "andre.ferreira@example.org", "gabriel.nogueira@example.net", "daniel.teixeira@example.com", "jose.freitas@example.org",
    "fernando.ferreira@example.org", "gustavo.nogueira@example.net", "hugo.teixeira@example.com", "igor.freitas@example.org"
};

void GerarEmailAleatorio(CidadaoSimulacao* pessoa,int indice)
{
    strcpy(pessoa->cidadao.email,emailAleatorio[indice]);
}

char* nomesBairros[] = {"Ipanema", "Marupiara", "Industrial", "Rosas", "Aviacao"};
char* nomesUnidades[] = {"Policia", "Hospital", "Bombeiro"};

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

    CidadaoSimulacao pessoa[NUM_PESSOAS];
    BairroSimulacao bairro[MAXBAIRRO];
    int tempoEsperaFila[NUM_SERVICOS];


    int num_pessoas_fila[NUM_SERVICOS];

    int atendimentos_por_fila[NUM_SERVICOS];

    int tempChegadaFila[NUM_SERVICOS];
    int tempSaidaFila[NUM_SERVICOS];

    Pilha historico_atendimento[NUM_SERVICOS];
    noArvBB *ArvOcorrencia;
    inicializanoArvBB(&ArvOcorrencia);

    for(int i=0;i<NUM_SERVICOS;i++)
    {
        //Instruções para Fila
        
        num_pessoas_fila[i] = 0;
        atendimentos_por_fila[i] = 0;
        tempoEsperaFila[i] = 0;

        //Instruções para Pilha
        inicializa_pilha(&historico_atendimento[i]);
    }
    
    for(int i=0;i<MAXBAIRRO;i++)
    {
        // inicializando cada bairro
        inicializar(&bairro->servicos[i]);
        bairro->bairrin.id = i;
        strcpy(bairro->bairrin.nome,nomesBairros[i-1]);
    }
    TabHashUnidade TabelaUnidade;
    Unidade unidadeTemp;
    InicializarTabelaHashUnidades(&TabelaUnidade);
    for(int i=0;i<NUM_PESSOAS;i++,num_cpf++)
    {

        pessoa[i].chegada = 0;
        pessoa[i].saida = 0;
        pessoa[i].num_fila = 0;
        pessoa[i].tempEspera = 0;
        pessoa[i].cidadao.id = i+1;
        pessoa[i].servico_desejado = rand()% NUM_SERVICOS + 1; //gera aleatoriamente o serviço de cada pessoa
        pessoa[i].cidadao.endereco = malloc(sizeof(Bairro));
        pessoa[i].cidadao.endereco->id= rand()% MAXBAIRRO + 1; //isso aqui vai depender do numero de bairros que vai ter
        
        //peguei de exemplo o cod da função GerarBArirroAleatorio da Lista_Cruzada.c
        int indicetemp = pessoa[i].cidadao.endereco->id;
        strcpy(pessoa[i].cidadao.endereco->nome,nomesBairros[indicetemp-1]);
        

        pessoa[i].cidadao.cpf = num_cpf;
        pessoa[i].idOcorrencia = i+1;
        int indicetempNome;
        GerarNomeAleatorio(&pessoa[i],&indicetempNome);
        GerarEmailAleatorio(&pessoa[i],indicetempNome);
    }

    chegada += rand()%4 + 1;
    tempAtendimento += chegada + rand()%16 + 1;

    while(tempTotal)
    {
        if(chegada == tempAtual && num_pessoa < NUM_PESSOAS)
        {
            int fila_inserido = pessoa[num_pessoa].servico_desejado - 1;
            inserir(&bairro->servicos[fila_inserido],num_pessoa);
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
                if(!vazia(&bairro->servicos[i]))
                {
                    int pessoa_;
                    remover(&bairro->servicos[i],&pessoa_);

                    unidadeTemp.id = pessoa[pessoa_].servico_desejado;
                    strcpy(unidadeTemp.nome,nomesUnidades[pessoa[pessoa_].servico_desejado-1]);
                    InserirTabelaUnidades(unidadeTemp.nome,&TabelaUnidade);

                    printf("\tPessoa %d atendida!\n",pessoa_);
                    printf("\tcpf: %d \tnome: %s \tocorrencia: %s \temail:%s\n",pessoa[pessoa_].cidadao.cpf,pessoa[pessoa_].cidadao.nome,pessoa[pessoa_].ocorrencia,pessoa[pessoa_].cidadao.email);
                    inserirnoArvBB(&ArvOcorrencia,pessoa[pessoa_].idOcorrencia);
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
            imprimir_fila(&bairro->servicos[i]);
        }
        printf("\n");
        tempAtual++;
    }
    for (int i=0;i<NUM_PESSOAS;i++)
    {
        free(pessoa[i].cidadao.endereco);
    }
    ImprimirTabelaHashUnidades(&TabelaUnidade);
    //Arrumar a parte de BST
    printf("Pessoas que tiveram ocorrencias: ");
    imprimirEmOrdem(&ArvOcorrencia);
return 0;
}
