#include <stdio.h>
#include <stdlib.h>
#include "arvores-avl-tda.h"

PONT inicializa(){
    return (NULL);
}

PONT criaNo(TIPOCHAVE ch){
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    novoNo->h = 0;
    return (novoNo);
}

//Método auxiliar para retornar o nó mais distante
int max(int a, int b){
    if(a>b) return a;
    return b;
}

//Método auxiliar que calcula a altura do nó
int altura(PONT r){
    if(r == NULL) return (0);
    return (r->h);
}

//Rotação à direita
PONT direita(PONT r){
    PONT aux;
    aux = r->esq;
    r->esq = aux->dir;
    aux->dir = r;
    r->h = max(altura(r->dir),altura(r->esq)) + 1;
    aux->h = max(altura(aux->esq), r->h) + 1;
    return (aux);
}

//Rotação à esquerda
PONT esquerda(PONT r){
    PONT aux;
    aux = r->dir;
    r->dir = aux->esq;
    aux->esq = r;
    r->h = max(altura(r->dir), altura(r->esq)) + 1;
    aux->h = max(altura(aux->dir), r->h) + 1;
    return (aux);
}

//Rotações duplas

PONT esquerdaDireita(PONT r){
    r->esq = esquerda(r->esq);
    return (direita(r));
}

PONT direitaEsquerda(PONT r){
    r->dir = direita(r->dir);
    return (esquerda(r));
}

PONT insereNo(PONT raiz, TIPOCHAVE chave)
{
    if (raiz == NULL)
        return(criaNo(chave));

    if (chave < raiz->chave)
        raiz->esq  = insereNo(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = insereNo(raiz->dir, chave);
    else
        return raiz;

    /* Atualiza a altura do nó */
    raiz->h = 1 + max(altura(raiz->esq),
                           altura(raiz->dir));

    // Pega o fator de balancemento do nó ancestral e checa se está desbalanceado
    int balance = getBalance(raiz);

    // Se estiver desbalanceado, há 4 casos

    // Esquerda Esquerda
    if (balance > 1 && chave < raiz->esq->chave)
        return direita(raiz);

    // Direita Direita
    if (balance < -1 && chave > raiz->dir->chave)
        return esquerda(raiz);

    // Esquerda Direita
    if (balance > 1 && chave > raiz->esq->chave)
    {
        return esquerdaDireita(raiz);
    }

    // Direita Esquerda
    if (balance < -1 && chave < raiz->dir->chave)
    {
        return direitaEsquerda(raiz);
    }

    return (raiz);
}

//Método auxiliar que retorna o filho de um nó com o menor valor
PONT minValueNode(PONT no){
    PONT atual = no;
    while(atual->esq != NULL)
        atual = atual->esq;

    return (atual);
}

//Método auxiliar que retorna o fator de balanceamento de um nó
int getBalance(PONT r){
    if(r == NULL)
        return (0);
    return altura(r->dir) - altura(r->esq);
}

PONT deleteNode(PONT root, TIPOCHAVE key){

    if (root == NULL)
        return root;

    if ( key < root->chave )
        root->esq = deleteNode(root->esq, key);

    else if( key > root->chave )
        root->dir = deleteNode(root->dir, key);

    else
    {
        // Nó com apenas um fiho ou sem
        if( (root->esq == NULL) || (root->dir == NULL) ){
            PONT temp = root->esq ? root->esq : root->dir;

            // Sem filho
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // Um filho
             *root = *temp;
             free(temp);
        }
        else
        {
            // Nó com dois filhos: pega-se o menor filho desse nó (menor valor da subárvore da direita)
            PONT temp = minValueNode(root->dir);

            // Copiar o dado do nó sucessor
            root->chave = temp->chave;

            // Deletar o nó sucessor
            root->dir = deleteNode(root->dir, temp->chave);
        }
    }

    if (root == NULL)
      return root;

    // Atualizar a altura do nó atual
    root->h = 1 + max(altura(root->esq),altura(root->dir));

    // Pegar o fator de balanceamento do nó e ver se ficou desbalanceado
    int balance = getBalance(root);

    // Se tiver desbalanceado, há 4 casos

    // Esquerda esquerda
    if (balance > 1 && getBalance(root->esq) >= 0)
        return direita(root);

    // Esquerda Direita
    if (balance > 1 && getBalance(root->esq) < 0)
    {
        return esquerdaDireita(root);
    }

    // Direita Direita
    if (balance < -1 && getBalance(root->dir) <= 0)
        return esquerda(root);

    // Direita Esquerda
    if (balance < -1 && getBalance(root->dir) > 0)
    {
        return direitaEsquerda(root);
    }

    return (root);
}

PONT contem(TIPOCHAVE ch, PONT raiz){
    if(raiz == NULL){
        return (NULL);
    }

    if(raiz->chave == ch){
        return (raiz);
    }

    if(raiz->chave > ch){
        return contem(ch, raiz->esq);
    }

    return (contem(ch, raiz->dir));
}

int numeroNos(PONT raiz){
    if(!raiz){
        return 0;
    }
    else {
         return(numeroNos(raiz->esq)
           +1
           +numeroNos(raiz->dir));
    }
}

void exibeArvore(PONT raiz){
    if(raiz != NULL){
        printf("%i", raiz->chave);
        printf("(");
        exibeArvore(raiz->esq);
        exibeArvore(raiz->dir);
        printf(")");
    }
}




