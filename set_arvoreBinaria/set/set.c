// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#include "set.h"

#include <stdlib.h>

// Define como os elementos do conjunto estão organizados na memória.
struct Node{
  SetType key;
  struct Node* left;  // Nó a esquerda.
  struct Node* right;  // Nó a direita.
  struct Node* parent;  // Nó acima.
};

struct SetStruct{
  // Número de elementos no conjunto.
  int size;
  // Nó raiz.
  // "root == NULL" se o conjunto é vazio.
  // "root->parent == NULL" em qualquer conjunto não vazio.
  iterator root;

};

// Implementação das funções auxiliares sobre os nós da árvore,
// tal como no livro Intruduction to Algorithms, Cormen et al. (2009).
///////////////////////////////////////////////////////////////////////

// Retorna o nó da árvore x cuja chave é k em O(log n),
// ou NULL caso k não esteja na árvore x.
iterator TreeSearch(iterator x, SetType k) {
  while (x != NULL && k != x->key) {
    if (k < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  return x;
}

// Retorna o nó com o menor elemento da árvore x em O(log n).
// Precondição: x não é uma árvore vazia.
iterator TreeMinimum(iterator x) {
  while (x->left != NULL) {
    x = x->left;
  }
  return x;
}

// Retorna o nó com o maior elemento da árvore x em O(log n).
// Precondição: x não é uma árvore vazia.
iterator TreeMaximum(iterator x) {
  while (x->right != NULL) {
    x = x->right;
  }
  return x;
}

// Dado o nó x, retorna o sucessor de x, ou seja,
// o nó cuja chave é o menor elemento maior que a chave de x.
// Caso x seja o maior elemento da árvore,
// retorna NULL.
iterator TreeSuccessor(iterator x) {
  if (x->right != NULL) {
    return TreeMinimum(x->right);
  } else {
    iterator y = x->parent;
    while (y != NULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }
}

// Dado o nó x, retorna o predecessor de x, ou seja, o nó cuja chave é o maior
// elemento menor que a chave de x. Caso x seja o menor elemento da árvore,
// retorna NULL.
iterator TreePredecessor(iterator x) {
  if (x->left != NULL) {
    return TreeMaximum(x->left);
  } else {
    iterator y = x->parent;
    while (y != NULL && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y;
  }
}

// Insere uma FOLHA z na árvore de s de forma consistente.
// NOTA: Esta função NÃO aloca a memória para z.
void TreeInsert(set s, iterator z) {
  // Procura qual vai ser o pai y de z na árvore.
  iterator y = NULL;
  iterator x = s->root;
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
    s->root = z;  // z se torna a raiz da árvore.
  } else if (z->key < y->key) {
    y->left = z;
  } else  {
    y->right = z;
  }
}

// Desconecta o nó z da árvore de forma consistente e depois retorna z.
// NOTA: Esta função NÃO desaloca a memória alocada para z.
iterator TreeDelete(set s, iterator z) {
  iterator y;  // Nó que será desconectado da árvore.
  if (z->left == NULL || z->right == NULL) {
    y = z;
  } else {
    y = TreeSuccessor(z);
  }
  iterator x;  // Nó que vai ser o novo filho do pai de y.
  if (y->left != NULL) {
    x = y->left;
  } else {
    x = y->right;
  }
  if (x != NULL) {
    x->parent = y->parent;
  }
  if (y->parent == NULL) {
    s->root = x;
  } else {
    if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }
  }
  if (y->key != z->key) {
    z->key = y->key;
  }
  return y;
}

// Implementação das funções do TAD set.
////////////////////////////////////////////////////////////////////////

set new_set() {
  set s = malloc(sizeof(struct SetStruct));
  s->size = 0;
  s->root = NULL;
  return s;
}

bool empty(set s) {
  return s->size == 0;
}

int size(set s) {
  return s->size;
}

iterator begin(set s) {
  if (empty(s)) {
    return end(s);
  } else {
    return TreeMinimum(s->root);
  }
}

iterator end(set s) {
  return NULL;
}

iterator next(iterator x) {
  return TreeSuccessor(x);
}

iterator prev(iterator x) {
  return TreePredecessor(x);
}

SetType key(iterator x) {
  return x->key;
}

iterator find(SetType k, set s) {
  return TreeSearch(s->root, k);
}

void insert(SetType k, set s) {
  if (find(k, s) == end(s)) {
    iterator z = malloc(sizeof(struct Node));
    z->key = k;
    z->parent = z->left = z->right = NULL;
    TreeInsert(s, z);
    s->size++;
  }
}

void erase(SetType k, set s) {
  iterator z = find(k, s);
  if (z != end(s)) {
    free(TreeDelete(s, z));
    s->size--;
  }
}

void clear(set s) {
  while (!empty(s)) {
    erase(key(begin(s)), s);
  }
}

void copy(set q, set s) {
  clear(q);
  for (iterator i = begin(s); i != end(s); i = next(i)) {
    insert(key(i), q);
  }
}

void delete_set(set s) {
  clear(s);
  free(s);
}
