typedef struct noArvBB
{
    int elem;
    struct noArvBB *esq;
    struct noArvBB *dir;
}noArvBB;
void inicializanoArvBB(noArvBB **abb);
int verif_vazianoArvBB(noArvBB *abb);
noArvBB* buscanoArvBB(noArvBB **abb,int elem);
noArvBB* buscaSubstArvBB(noArvBB **abb,int *elem);
noArvBB* buscaAntecessorArvBB(noArvBB **abb,int elem,noArvBB *antaux);
void inserirnoArvBB(noArvBB **abb,int elem);
void removerNoArvBB(noArvBB **abb,int *elem);
void imprimirPreOrdem(noArvBB **abb);
void imprimirEmOrdem(noArvBB **abb);
void imprimirPosOrdem(noArvBB **abb);
noArvBB* inverter_arv(noArvBB *abb);
