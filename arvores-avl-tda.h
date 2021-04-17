#ifndef ARVORES-AVL-TDA_H_INCLUDED
#define ARVORES-AVL-TDA_H_INCLUDED
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux {
    TIPOCHAVE chave;
    struct aux *esq, *dir;
    int h; //atributo altura é definido para fazer balanceamento caso seja necessário
} NO;

typedef NO* PONT;

PONT inicializa();
PONT criaNo(TIPOCHAVE ch);
PONT direita(PONT r);
PONT esquerda(PONT r);
PONT esquerdaDireita(PONT r);
PONT direitaEsquerda(PONT r);
PONT insereNo(PONT raiz, TIPOCHAVE key);
PONT deleteNode(PONT root, TIPOCHAVE key);
PONT contem(TIPOCHAVE ch, PONT raiz);
int numeroNos(PONT raiz);
void exibeArvore(PONT raiz);



#endif // ARVORES-AVL-TDA_H_INCLUDED
