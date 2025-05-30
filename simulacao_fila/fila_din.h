typedef struct noFila{
    int elem;
    struct noFila *prox;
}noFila;
typedef struct{
    noFila *inicio;
    noFila *fim;
}Fila;
void inicializar(Fila* fila);
int vazia(Fila *fila);
int cheia(Fila *fila);
void inserir(Fila* fila,int elem);
void remover(Fila* fila,int* elem);
void obter_topo(Fila *fila,int* elem);
void num_elem(Fila* fila,int *elem);
void imprimir_fila(Fila* fila);
