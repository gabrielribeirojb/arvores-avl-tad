#include <stdio.h>
#include <stdlib.h>
#include "arvores-avl-tda.h"

int main()
{

    PONT raiz = inicializa();
    raiz = criaNo(40);

    PONT no1 = inicializa();
    no1 = criaNo(12);

    PONT no2 = inicializa();
    no2 = criaNo(42);

    PONT no3 = inicializa();
    no3 = criaNo(10);

    insereNo(raiz,no1->chave);
    insereNo(raiz,no2->chave);
    insereNo(raiz,no3->chave);

    exibeArvore(raiz);
    printf("Numero de elementos antes da remocao: %d\n", numeroNos(raiz));

    deleteNode(raiz, no2->chave);

    exibeArvore(raiz);
    printf("Numero de elementos antes da remocao: %d\n", numeroNos(raiz));
}
