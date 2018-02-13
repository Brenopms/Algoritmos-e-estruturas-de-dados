// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#include "priority_queue.h"

#include <stdlib.h>

typedef struct Node* iterator;

// Define como os elementos da fila estão organizados na memória.
struct Node{
  PQType key;
  struct Node* left;  // Nó a esquerda.
  struct Node* right;  // Nó a direita.
  struct Node* parent;  // Nó acima.
};

struct PQStruct{
  // Número de elementos na fila.
  int size;
  // Nó raiz.
  // "root == NULL" se a fila é vazia.
  // "root->parent == NULL" em qualquer fila não vazia.
  iterator root;
};

// Implementação das funções auxiliares sobre os nós da árvore,
// tal como no livro Intruduction to Algorithms, Cormen et al. (2009).
///////////////////////////////////////////////////////////////////////

// Retorna o nó com o menor elemento da árvore x em O(log n).
// Precondição: x não é uma árvore vazia.
iterator TreeMinimum(iterator x) {
  while (x->left != NULL) {
    x = x->left;
  }
  return x;
}

// Insere uma FOLHA z na árvore de s de forma consistente.
// NOTA: Esta função NÃO aloca a memória para z.
void TreeInsert(priority_queue q, iterator z) {
  // Procura qual vai ser o pai y de z na árvore.
  iterator y = NULL;
  iterator x = q->root;
  while (x != NULL) {
    y = x;
    if (z->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  // Insere z em baixo do nó y.
  z->parent = y;
  if (y == NULL) {
    q->root = z;  // z se torna a raiz da árvore.
  } else if (z->key < y->key) {
    y->left = z;
  } else  {
    y->right = z;
  }
}

// Implementação das funções do TAD set.
////////////////////////////////////////////////////////////////////////

priority_queue new_priority_queue() {
  priority_queue q = malloc(sizeof(struct PQStruct));
  q->size = 0;
  q->root = NULL;
  return q;
}

bool empty(priority_queue q) {
  return q->size == 0;
}

int size(priority_queue q) {
  return q->size;
}

PQType top(priority_queue q) {
  return TreeMinimum(q->root)->key;
}

void push(PQType k, priority_queue q) {
  iterator z = malloc(sizeof(struct Node));
  z->key = k;
  z->parent = z->left = z->right = NULL;
  TreeInsert(q, z);
  q->size++;
}

// Caso particular de apagar um elemento cuja subárbore esquerda é sempre vazia.
void pop(priority_queue q) {
  iterator x = TreeMinimum(q->root);
  // Conecta o pai de x (se houver) com a subárvore direita de x (se houver).
  if (x->right != NULL) {
    x->right->parent = x->parent;
  }
  if (x->parent != NULL) {
    x->parent->left = x->right;
  } else {
    q->root = x->right;  // O menor elemento era a raiz.
  }
  free(x);
  q->size--;
}

// Função auxiliar de "copy(p, q)".
// Copia todos os elementos de q em p recursivamente.
// Os elementos de q são guardados na pilha de recursão.
void RecursiveCopy(priority_queue p, priority_queue q) {
  if (!empty(q)) {
    // Retira um elemento de p e coloca em q.
    PQType k = top(q);
    push(k, p);
    pop(q);
    // Copia os demais elementos de p em q recursivamente.
    RecursiveCopy(p, q);
    // Devolve o elemento retirado para p.
    push(k, q);
  }
}

void copy(priority_queue p, priority_queue q) {
  // Apaga todos os elementos em p.
  while (!empty(p)) {
    pop(p);
  }
  RecursiveCopy(p, q);
}

void swap(priority_queue q, priority_queue p) {
  struct PQStruct aux = *q;
  *q = *p;
  *p = aux;
}

void delete_priority_queue(priority_queue q) {
  // Primeiramente, remove todos os elementos da fila.
  while (!empty(q)) {
    pop(q);  // A função pop() libera a memórima de cada nó removido da fila;
  }
  // Em seguida, libera a memória alocada para o PQStruct.
  free(q);
}
