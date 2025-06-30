#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "../FilaDinamica/fila_din.c"
#include "../PilhaDinamica/pilha.c"
#include "../ArvoreBinariaBusca/ArvBB.c"
#include "../HashingUnidades/Tabela_Hash.c"
#include "../bairroEcidadaoHash/BairrosCidadao.c"
#include "../bairroXunidade/Lista_Cruzada.c"
#include "../ArvoreAVL/Arvore_Ocorrencias.c"
#include "../struct_comum.h"

#define NUM_SERVICOS 3
#define NUM_PESSOAS 1000
#define MAXNOME 50
#define MAXBAIRRO 5

//TODO - fazer a struct de ocorrencias

//TODO - adicionar a AVL para atender chamadas de acordo com a gravidade




typedef struct{
    Bairro bairro;
    Fila servicos[NUM_SERVICOS];
    NoAVL* arvoreOcorrencias[NUM_SERVICOS];
    //Estatisticas referentes a fila
    int tempoEsperaFila[NUM_SERVICOS];
    int num_pessoas_fila[NUM_SERVICOS];
    int atendimentos_por_fila[NUM_SERVICOS];
    int tempChegadaFila[NUM_SERVICOS];
    int tempSaidaFila[NUM_SERVICOS];
}BairroSimulacao;


typedef struct{
    Cidadao *cidadao;
    int servico_desejado;
    Ocorrencia atendimento;
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
Gravidade gravidadePolicia[] = {
    ALTA, MEDIA, ALTA, BAIXA,
    MEDIA, ALTA, MEDIA, BAIXA
};

char* ocorrenciaHospital[] = {
    "Queda", "Ferimento", "Febre","Dor",
    "Desmaio", "Convulcao", "Infeccao", "Alergia",
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


void GerarOcorrenciaAleatorio(CidadaoSimulacao* pessoa)
{

    int indice = rand() % qntOcorrencia;
    //se o serviço for o 1, entao sua ocorrencia é policial
    if(pessoa->servico_desejado == 1)
    {
        strcpy(pessoa->atendimento.ocorrencia, ocorrenciaPolicia[indice]);
        pessoa->atendimento.nivel = gravidadePolicia[indice];
    }
    //se o serviço for o 2, entao sua ocorrencia é hospitalar
    if(pessoa->servico_desejado == 2)
    {
        strcpy(pessoa->atendimento.ocorrencia, ocorrenciaHospital[indice]);
        pessoa->atendimento.nivel = gravidadeHospital[indice];
    }
    //se o serviço for o 3, entao sua ocorrencia é de bombeiro
    if(pessoa->servico_desejado == 3)
    {
        strcpy(pessoa->atendimento.ocorrencia, ocorrenciaBombeiro[indice]);
        pessoa->atendimento.nivel = gravidadeBombeiro[indice];
    }

}

const char* gravidadeNome(Gravidade g) {
    switch (g) {
        case ALTA: return "ALTA";
        case MEDIA: return "MEDIA";
        case BAIXA: return "BAIXA";
        default: return "DESCONHECIDA";
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
    strcpy(pessoa->cidadao->nome,nomesAleatorios[*indice]);
}
void GerarNomeAleatorioAtendente(CidadaoSimulacao *pessoa)
{
    int indice = rand() % qntNomes;
    strcpy(pessoa->atendimento.atendente,nomesAleatorios[indice]);
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
    strcpy(pessoa->cidadao->email,emailAleatorio[indice]);
}

// gerando indice para aleatorizar o bairro do cidadao
int AleatorizarBairro()
{
    return rand() % MAXBAIRRO;
}


int main()
{
    setlocale(LC_ALL,"Portuguese");
    srand(time(NULL));

    int tempTotal = 200;
    int tempAtual = 0;
    int chegada = 0;
    int tempAtendimento = 0;
    int num_pessoa = 1;
    int num_cpf = 1000000;

    CidadaoSimulacao pessoa[NUM_PESSOAS];
    BairroSimulacao bairro[MAXBAIRRO];
    Pilha historico_atendimento[NUM_SERVICOS];
    noArvBB *ArvOcorrencia;
    tabelaBairros tabelaBairro;
    tabelaCidadaos tabelaCidadao;
    TabHashUnidade TabelaUnidade;
    Unidade unidadeTemp;
    Matriz matrizBairroUnidade; 

    //Inicalizando BST e tabelas hash
    inicializanoArvBB(&ArvOcorrencia);
    InicializarTabelaHashUnidades(&TabelaUnidade);
    inicializarTabelaBairros (&tabelaBairro);
    inicializarTabelaCidadaos (&tabelaCidadao);
    Inicializar_Matriz(&matrizBairroUnidade);

    //Gerar Relacao Bairro-Unidade Aleatoria
    GerarMatrizAleatoria(&matrizBairroUnidade);

    //Instruções para Pilha
    for(int i=0;i<NUM_SERVICOS;i++)
    {
        inicializa_pilha(&historico_atendimento[i]);
    }
    // inicializando cada bairro
    for(int i=0;i<MAXBAIRRO;i++)
    {
        for(int j=0;j<NUM_SERVICOS;j++)
        {
            inicializar(&bairro[i].servicos[j]);
            Inicializar_Arvore_AVL(&bairro[i].arvoreOcorrencias[j]);
            bairro[i].atendimentos_por_fila[j] = 0;
            bairro[i].num_pessoas_fila[j] = 0;
            bairro[i].tempoEsperaFila[j] = 0;
            bairro[i].tempChegadaFila[j] = 0;
            bairro[i].tempSaidaFila[j] = 0;
        }
        bairro[i].bairro.id = i+1;
        strcpy(bairro[i].bairro.nome,nomesBairros[i]);
    }

    int idUnidade = 1;

    // gerando bairros
    inserirTabelaBairros ("Entidade",&tabelaBairro);
    inserirTabelaBairros ("Marupiara",&tabelaBairro);
    inserirTabelaBairros ("Industrial",&tabelaBairro);
    inserirTabelaBairros ("Rosas",&tabelaBairro);
    inserirTabelaBairros ("Aviacao",&tabelaBairro);

    //Inicializando pessoas
    for(int i=0;i<NUM_PESSOAS;i++,num_cpf++)
    {

        pessoa[i].chegada = 0;
        pessoa[i].saida = 0;
        pessoa[i].num_fila = 0;
        pessoa[i].tempEspera = 0;
        pessoa[i].cidadao = malloc(sizeof(Cidadao));
        pessoa[i].cidadao->id = i+1;
        pessoa[i].servico_desejado = rand()% NUM_SERVICOS + 1; //gera aleatoriamente o serviço de cada pessoa
        pessoa[i].cidadao->cpf = num_cpf;
        pessoa[i].atendimento.idOcorrencia = i+1;
    

        // aleatoriza um numero para escolher o nome do bairro
        int bairroAleatorio = AleatorizarBairro();

        // linka o bairro da tabela hash com o bairro do cidadao
        pessoa[i].cidadao->endereco = buscarBairro(nomesBairros[bairroAleatorio], &tabelaBairro);
        
        //Gerando nomes,email e ocorrencias para cada pessoa
        int indicetempNome;
        GerarNomeAleatorio(&pessoa[i],&indicetempNome);
        GerarEmailAleatorio(&pessoa[i],indicetempNome);
        GerarNomeAleatorioAtendente(&pessoa[i]);
        GerarOcorrenciaAleatorio(&pessoa[i]);

        // inserindo na tabela
        inserirTabelaCidadaos(pessoa[i].cidadao, &tabelaCidadao);
    }

    //aletorizando a chegada e a saida
    chegada += rand()%2 + 1;
    tempAtendimento += chegada + rand()%16 + 1;

    while(tempTotal)
    {
        //Quando a chegada acontece
        //No if a pessoas que tem um bairro é inserida em uma das filas do seu bairro com base na ocorrência
        if(chegada == tempAtual && num_pessoa < NUM_PESSOAS)
        {
            //Qual fila vai ser inserido
            int fila_inserido = pessoa[num_pessoa].servico_desejado - 1;
            //Pega o id do bairro da pessoa para inserir na fila do bairro
            int idTempBairro = pessoa[num_pessoa].cidadao->endereco->id -1;
            //Insere na fila respectiva
            
            //A busca verifica se aquele unidade existe do bairro da pessoa, se existir ela e inserida na fila
            if(BuscarUnidadeBairro(&matrizBairroUnidade, idTempBairro, fila_inserido))
            {
                inserir(&bairro[idTempBairro].servicos[fila_inserido],num_pessoa);
                Inserir_Arvore_AVL(&bairro[idTempBairro].arvoreOcorrencias[fila_inserido], pessoa[num_pessoa].atendimento);                
            }
            //Caso nao exista, procura o primeiro bairro que possuir aquela unidade
            else
            {
                int menorFila = 999999;
                int melhorBairro = -1;

                for(int i=0;i<MAXBAIRRO;i++)
                {
                    if(BuscarUnidadeBairro(&matrizBairroUnidade,i,fila_inserido))
                    {
                        int tam_fila = tamanhoFila(&bairro[i].servicos[fila_inserido]);
                        if(tam_fila<menorFila)
                        {
                            menorFila = tam_fila;
                            melhorBairro = i;
                        }
                    }
                }
                if(melhorBairro!=-1)
                {
                    Inserir_Arvore_AVL(&bairro[melhorBairro].arvoreOcorrencias[fila_inserido],pessoa[num_pessoa].atendimento);
                    idTempBairro = melhorBairro;
                }
                else
                {
                    printf("Nenhum bairro disponível para o servico %d\n",pessoa[num_pessoa].atendimento.idOcorrencia);
                }
            }
            //Atualiza os dados da pessoa referentes a tempo na fila e em qual fila ela estava
            pessoa[num_pessoa].chegada = tempAtual;
            pessoa[num_pessoa].num_fila = fila_inserido;
            bairro[idTempBairro].num_pessoas_fila[fila_inserido]++;
            bairro[idTempBairro].tempChegadaFila[fila_inserido] += tempAtual;
            //Incrementa para a proxima pessoa
            num_pessoa++;
            //Gera o tempo da nova chegada
            chegada += rand()%2 + 1;

        }
        //If para a saida da fila
        //Aqui ele tira uma pessoa de cada fila de cada bairro
        if(tempAtendimento == tempAtual)
        {
            //Laço referente ao bairro (são 5)
            for(int j=0;j<MAXBAIRRO;j++)
            {
                //Laço referente a cada fila de um bairro j
                for(int i=0;i<NUM_SERVICOS;i++)
                {
                    if(!vazia(&bairro[j].servicos[i]) && !Arvore_AVL_Vazia(&bairro[i].arvoreOcorrencias[j]))
                    {
                        Ocorrencia buscaOcorrencia;
                        ObterOcorrenciaPrioritaria(bairro[i].arvoreOcorrencias[j], &buscaOcorrencia);
                        //Pega o numero da pessoa para poder analisar seus dados referentes ao atendimento
                        int pessoa_ = buscaOcorrencia.idOcorrencia;
                        //remove a pessoa de uma fila especifica de um bairro j
                        remover(&bairro[j].servicos[i],&pessoa_);
                        Remover_Arvore_AVL(&bairro[j].arvoreOcorrencias[i], buscaOcorrencia.idOcorrencia);
                        
                        //Comando referentes a inserção da unidade utilizada na tabela hash de Unidades
                        unidadeTemp.id = idUnidade++;
                        strcpy(unidadeTemp.nome,nomesUnidades[pessoa[pessoa_].servico_desejado-1]);
                        InserirTabelaUnidades(unidadeTemp.id, unidadeTemp.nome, &TabelaUnidade);
    
                        
                        //Print dos dados da pessoa que foi retirada de sua fila
                        //Cada pessoa tem um id referente a sua ocorrencia, a partir dele conseguimos recuperar a pessoa referente a esse id, como tambem sua ocorrência
                        //Adiciona esse id em um BST
                        printf("\t\t=========================================\n");
                        printf("\t\t     Pessoa Atendida com Sucesso\n");
                        printf("\t\t=========================================\n");
                        printf("\t\t  Pessoa ID:  %d\n", pessoa_);
                        printf("\t\t   CPF:       %d\n", pessoa[pessoa_].cidadao->cpf);
                        printf("\t\t   Nome:      %s\n", pessoa[pessoa_].cidadao->nome);
                        printf("\t\t   E-mail:    %s\n", pessoa[pessoa_].cidadao->email);
                        printf("\t\t-----------------------------------------\n");
                        printf("\t\t  Ocorrencia Atendida:\n");
                        printf("\t\t   ID:        %d\n", pessoa[pessoa_].atendimento.idOcorrencia);
                        printf("\t\t   Tipo:      %s\n", pessoa[pessoa_].atendimento.ocorrencia);
                        printf("\t\t   Gravidade: %s\n", gravidadeNome(pessoa[pessoa_].atendimento.nivel));
                        printf("\t\t=========================================\n\n");
                        inserirnoArvBB(&ArvOcorrencia,pessoa[pessoa_].atendimento.idOcorrencia);
                        
                        Ocorrencia atendPilha = pessoa[pessoa_].atendimento;


                        push(&historico_atendimento[i],atendPilha);

                        //Dado para saber o tempo de espera da pessoa na fila
                        pessoa[pessoa_].saida = tempAtual;

                        //Contabiliza o número de atendimentos por fila
                        bairro[j].atendimentos_por_fila[i]++;
                        bairro[j].tempSaidaFila[i] += tempAtual;
                    }
                }
            }
            //Gera um novo tempo para atendimento
            tempAtendimento += rand()%16 + 1;
        }


        tempTotal--;
        //Printa as filas de cada tempo
        printf("Tempo %d\n",tempAtual);
        for (int i = 0; i < MAXBAIRRO; i++)
        {
            printf("\t Bairro: %s\n", bairro[i].bairro.nome);

            for (int j = 0; j < 3; j++)
            {
                printf("\t  -> %-10s: ", nomesUnidades[j]); // Alinha os nomes dos serviços
                imprimir_fila(&bairro[i].servicos[j]);
            }
            printf("\n");
        }
        tempAtual++;
    }

    //printf("Pessoas que tiveram ocorrencias: \n");
    //imprimirEmOrdem(&ArvOcorrencia);
    //ImprimirTabelaHashUnidades(&TabelaUnidade);
    //imprimirTabelaDeBairros(&tabelaBairro);
    //imprimirTabelaCidadaos (&tabelaCidadao);

    //Salvar a BST de ocorrencias
    FILE *bst = fopen("OcorrenciasBST.txt", "w");
    if (bst) {
        fprintf(bst, "------- Ocorrencias na BST -------\n\n");

        for (int i = 0; i < num_pessoa; i++) {
            noArvBB *temp = buscanoArvBB(&ArvOcorrencia, i);
            if (temp) {
                for (int j = 0; j < NUM_PESSOAS; j++) {
                    if (pessoa[j].atendimento.idOcorrencia == temp->elem) {
                        fprintf(bst, "Dados da ocorrência %d:\n", temp->elem);
                        fprintf(bst, "\tID: %d\n", pessoa[j].atendimento.idOcorrencia);
                        fprintf(bst, "\tNivel: %s\n", gravidadeNome(pessoa[j].atendimento.nivel));
                        fprintf(bst, "\tOcorrência: %s\n", pessoa[j].atendimento.ocorrencia);
                        fprintf(bst, "\tNome atendente: %s\n\n\n",pessoa[j].atendimento.atendente);
                    }
                }
            }
        }

        fclose(bst);
    }
    //Salvar a Tabela de Unidades
    FILE *hash_unidades = fopen("HashUnidades.txt", "w");
    if(hash_unidades)
    {
        freopen("HashUnidades.txt", "w", stdout);
        ImprimirTabelaHashUnidades(&TabelaUnidade);
        freopen("/dev/tty", "w", stdout);
        fclose(hash_unidades);
    }

    //Salvar a Tabela de Bairros
    FILE *bairros = fopen("HashBairros.txt", "w");
    if(bairros)
    {
        freopen("HashBairros.txt", "w", stdout);
        imprimirTabelaDeBairros(&tabelaBairro);
        freopen("/dev/tty", "w", stdout);
        fclose(bairros);
    }

    // Salvar a Tabela de Cidadãos
    FILE *cidadaos = fopen("HashCidadaos.txt", "w");
    if (cidadaos) {
        freopen("HashCidadaos.txt", "w", stdout);
        imprimirTabelaCidadaos(&tabelaCidadao);
        freopen("/dev/tty", "w", stdout);
        fclose(cidadaos);
    }

    //Salvar as pilhas de aterndimento das unidades
    FILE *pilha = fopen("PilhaAtendimentos.txt","w");
    if(pilha)
    {
        fprintf(bst, "------- Histórico de Atendimentos -------\n\n");
        for(int i=0;i<NUM_SERVICOS;i++)
        {
            noPilha *aux = historico_atendimento[i].topo;
            fprintf(pilha,"=======Histórico de %s: \n\n",nomesUnidades[i]);
            while(aux)
            {
                fprintf(pilha, "Dados da ocorrência %d:\n", aux->atendimento.idOcorrencia);
                fprintf(pilha, "\tID: %d\n", aux->atendimento.idOcorrencia);
                fprintf(pilha, "\tNivel: %s\n", gravidadeNome(aux->atendimento.nivel));
                fprintf(pilha, "\tOcorrência: %s\n", aux->atendimento.ocorrencia);
                fprintf(pilha, "\tNome atendente: %s\n\n\n",aux->atendimento.atendente);
                aux = aux->prox;
            }
        }


    }

    FILE *matrizCruzada = fopen("MatrizCruzada.txt", "w");
    if(matrizCruzada)
    {
        freopen("MatrizCruzada.txt", "w", stdout);
        ImprimirMatrizCruzada(&matrizBairroUnidade);
        freopen("/dev/tty", "w", stdout);
        fclose(matrizCruzada);
    }
    
    for(int i=0;i<num_pessoa;i++)
    {
        if (pessoa[i].saida > pessoa[i].chegada)
        {
            pessoa[i].tempEspera = pessoa[i].saida - pessoa[i].chegada;
        }
        else
        {
            pessoa[i].tempEspera = 0;  
        }
    }
    int maiorTempoPessoa = pessoa[0].tempEspera;
    int indicedapessoa = 0;
    for(int i=0;i<num_pessoa;i++)
    {
        if(maiorTempoPessoa<pessoa[i].tempEspera)
        {
            maiorTempoPessoa = pessoa[i].tempEspera;
            indicedapessoa = i;
            
        }
    }


    for(int i=0;i<MAXBAIRRO;i++)
    {
        for(int j=0;j<num_pessoa;j++)
        {
            if(pessoa[j].cidadao->endereco->id == i+1)
            {
                if(pessoa[j].num_fila == 0)
                {
                    bairro[i].tempoEsperaFila[0] += pessoa[j].tempEspera;
                }
                if(pessoa[j].num_fila == 1)
                {
                    bairro[i].tempoEsperaFila[1] += pessoa[j].tempEspera;
                }
                if(pessoa[j].num_fila == 2)
                {
                    bairro[i].tempoEsperaFila[2] += pessoa[j].tempEspera;
                }
            }
        }
    }
    int pessoas_atendidas =0;


    
    FILE *arq = fopen("estatisticas.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return 1;
    }

    fprintf(arq, "------- ESTATÍSTICAS DA SIMULAÇÃO -------\n\n");

    for (int i = 0; i < MAXBAIRRO; i++) {
        fprintf(arq, "Atendimentos referentes ao bairro %s\n\n", bairro[i].bairro.nome);
        for (int j = 0; j < NUM_SERVICOS; j++) {
            fprintf(arq, "\tPessoas que entraram na fila %s: %d\n", nomesUnidades[j], bairro[i].num_pessoas_fila[j]);
            fprintf(arq, "\tAtendimentos da fila de %s: %d\n", nomesUnidades[j], bairro[i].atendimentos_por_fila[j]);

            if (bairro[i].atendimentos_por_fila[j] > 0) {
                fprintf(arq, "\tTempo de espera médio da %s: %.2f\n", nomesUnidades[j], (float)bairro[i].tempoEsperaFila[j] / bairro[i].atendimentos_por_fila[j]);
            } else {
                fprintf(arq, "\tTempo de espera médio da %s: N/A\n", nomesUnidades[j]);
            }

            if (bairro[i].num_pessoas_fila[j] > 0) {
                fprintf(arq, "\tTempo médio de chegada da %s: %.2f\n", nomesUnidades[j], (float)bairro[i].tempChegadaFila[j] / bairro[i].num_pessoas_fila[j]);
            } else {
                fprintf(arq, "\tTempo médio de chegada da %s: N/A\n", nomesUnidades[j]);
            }

            if (bairro[i].atendimentos_por_fila[j] > 0) {
                fprintf(arq, "\tTempo médio de saída da %s: %.2f\n", nomesUnidades[j], (float)bairro[i].tempSaidaFila[j] / bairro[i].atendimentos_por_fila[j]);
            } else {
                fprintf(arq, "\tTempo médio de saída da %s: N/A\n", nomesUnidades[j]);
            }

            fprintf(arq, "\n");
            pessoas_atendidas+=bairro[i].atendimentos_por_fila[j];
        }
        fprintf(arq, "\n");
    }

    fprintf(arq, "Numero de clientes atendidos: %d\n", pessoas_atendidas);

    for (int i = 0; i <= pessoas_atendidas; i++) {
        if (pessoa[i].tempEspera >= 0) {
            fprintf(arq, "\nTempo de espera da pessoa %s: %d", pessoa[i].cidadao->nome, pessoa[i].tempEspera);
        }
    }

    fprintf(arq, "\n\nMaior tempo de espera foi do %s com %d unidades de tempo\n",pessoa[indicedapessoa].cidadao->nome, maiorTempoPessoa);

    fclose(arq);
    return 0;
}
