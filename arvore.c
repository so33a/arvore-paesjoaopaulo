#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "fila.h"

ARVORE novaArvore() {
  ARVORE a = malloc(sizeof(struct arvore));  
  a->z = malloc(sizeof(struct node));
  a->raiz = a->z;
  a->raiz->left = a->raiz->right = a->z;
  a->z->left = a->z->right = a->z;
  return a;
}

void imprimePreOrdemR(ARVORE a, link h) {
  if (h != a->z) {
    printf ("%d ", h->key);
    imprimePreOrdemR(a, h->left);
    imprimePreOrdemR(a, h->right);
  }
}

int contaNosR (ARVORE a, link h) {
  if(h == a->z)
    return 0;
  return 1 + contaNosR(a, h->left) + contaNosR(a, h->right);
}

int contaParesR (ARVORE a, link h) {
  if(h == a->z) 
    return 0;
  if (h->key %2 == 0) 
    return 1 + contaParesR(a, h->left) + contaParesR(a, h->right);
  else
    return  contaParesR(a, h->left) + contaParesR(a, h->right);
}

void imprimePreOrdem (ARVORE a) {
  imprimePreOrdemR(a, a->raiz);
}
void imprimePosOrdemR(ARVORE a, link h) {
  if (h != a->z) {
    imprimePosOrdemR(a, h->left);
    imprimePosOrdemR(a, h->right);
    printf ("%d ", h->key);
  }
}

void imprimePosOrdem (ARVORE a) {
  imprimePosOrdemR(a, a->raiz);
}


void imprimeEmOrdemR (ARVORE a, link h) {
  if (h != a->z) {
    imprimeEmOrdemR(a, h->left);
    printf("%d ", h->key);
    imprimeEmOrdemR(a, h->right);
  }
}

void imprimeEmOrdem (ARVORE a) {
  imprimeEmOrdemR(a, a->raiz); 
}

link buscaR (ARVORE a, link h, int key) {
  if(h == a->z) return NULL;
  if(h->key == key) return h;
  if( h->key < key) 
    return buscaR(a, h->right, key);
  return buscaR(a, h->left, key);
}


link busca (ARVORE a, int key){
  return buscaR(a, a->raiz, key);
}

link novoNo(int key, link l, link r) {
  link x = malloc(sizeof(struct node));
  x->key = key;
  x->left = l;
  x->right = r;
  return x;
}
link inserirR (ARVORE a, link h, int key) {
  if(h == a->z) 
    return novoNo(key, a->z, a->z); 
  if(h->key == key) return h;
  if(h->key < key) 
    h->right = inserirR(a, h->right, key);
  else 
    h->left = inserirR(a, h->left, key);
  return h;
}
link inserirT (ARVORE a, link h, int key) {
  if(h == a->z) 
    return novoNo(key, a->z, a->z); 
  if(h->key == key) return h;
  if(h->key < key)  {
    h->right = inserirT(a, h->right, key);
    h = rotL(a, h);
  }
  else {
    h->left = inserirT(a, h->left, key);
    h = rotR(a, h);
  }
  return h;
}

void inserirNaRaiz(ARVORE a, int key) {
  a->raiz = inserirT(a, a->raiz, key);
}

void inserir (ARVORE a, int key){
  a->raiz = inserirR(a, a->raiz, key);
}

void imprimeEmLargura (ARVORE a) {
  link aux;
  FILA f = novaFila();
  enfilar(f, a->raiz);
  while (f->primeiro != NULL) {
    aux = desenfilar(f);
    printf ("%d ", aux->key);
    if (aux->left != a->z)  {
      enfilar (f,aux->left);
    }
    if (aux->right != a->z) {
      enfilar (f,aux->right);
    }
  }
  destroiFila(f);
}

link rotL(ARVORE a, link h) {
  link x = h->right;
  h->right = x->left;
  x->left = h;
  return x; 
}

link rotR(ARVORE a, link h) {
  link x = h->left;
  h->left = x->right;
  x->right = h;
  return x;
}

void remover (ARVORE a, int key){
  if(a->raiz != a->z){
    removerNo(a, a->raiz, key);
  }
}

/* Remove o nó recursivamente */
link removerNo(ARVORE a, link h, int key) {
  link aux;
  if(h == a->z) {
    /* O elemento que está sendo procurando não foi encontrado */
    return NULL;
  } else if(key < h->key) {
    /* O valor está a esquerda de h */
    h->left = removerNo(a, h->left, key);
  } else if(key > h->key) {
    /* O valor está a direita de h */
    h->right = removerNo(a, h->right, key);
  } else {
    /* O valor está em um nó não folha */
    if(h->right != a->z && h->left != a->z) {
      /* Guéto o menor valor da subarvore à direita e coloco na raiz */
      aux = buscaMenorR(a, h->right);
      h->key = aux->key; 
      /* Remove o nó que foi passado para h */
      h->right = removerNo(a, h->right,aux->key);
    } else {
      /* O nó a ser removido possui uma subarvore filha */
      aux = h;
      if(h->left == a->z){
      /* Caso a da esquerda esteja vazia, pego a da direita */
        h = h->right;
      } else if(h->right == a->z) {
        /* Caso a da direita esteja vazia, pego a da esquerda */
        h = h->left;
      }
      /* Libera o espaço de memória que armazenava o conteúde de h */
      free(aux);
    }
  }
  return h;
}

link buscaMenorR (ARVORE a, link h) {
  link menor = NULL;
  if (h != a->z)
    buscaMenorR(a, h->left);
  else
    return a->raiz;
  return h; 
}

void destroiArvore(ARVORE a){
  destroiArvoreR(a, a->raiz);
}

void destroiArvoreR(ARVORE a, link h){
  if(h != a->z){
    if(h->left != a->z)
      destroiArvoreR(a, h->left);
    if(h->right != a->z)
      destroiArvoreR(a, h->right);
    removerNo(a, h, h->key);
    free(h);
  }
}


