// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#include "set.h"

#include <stdlib.h>

// Define como os elementos do conjunto serão organizados na memória.
typedef struct node{
  SetType key;
  struct node* prev;
  struct node* next;
} Node;

struct SetStruct{
  Node* end;  // Ponteiro para o sentinela.
  int size;  // Número de elementos no conjunto.
};

set new_set() {
  set s = malloc(sizeof(struct SetStruct));
  s->size = 0;
  s->end = malloc(sizeof(Node));
  s->end->next = s->end;
  s->end->prev = s->end;
  return s;
}

int empty(set s) {
  return s->size == 0;
}

int size(set s) {
  return s->size;
}

iterator begin(set s) {
  return s->end->next;
}

iterator end(set s) {
  return s->end;
}

iterator next(iterator x) {
  Node* ptr = x;
  return ptr->next;
}

iterator prev(iterator x) {
  Node* ptr = x;
  return ptr->prev;
}

SetType key(iterator x) {
  Node* ptr = x;
  return ptr->key;
}

iterator find(SetType k, set s) {
  for (iterator i = begin(s); i != end(s); i = next(i)) {
    if (key(i) == k) {
      return i;
    } else if (key(i) > k) {
      return end(s);
    }
  }
  return end(s);  // k é maior que todos os elementos contidos no conjunto.
}

void insert(SetType k, set s) {
  // Encontra o primeiro elemento que não é menor que k na lista encadeada.
  Node* x = begin(s);
  while (x != end(s) && key(x) < k) {
    x = next(x);
  }
  // Caso k já não esteja no conjunto, cria um novo nó para armazenar k.
  if (x == end(s) || key(x) != k) {
    // Cria um novo nó e define o valor dos seus campos.
    Node* node = malloc(sizeof(Node));
    node->key = k;
    node->prev = prev(x);
    node->next = x;
    // Ajusta o valor dos ponteiros dos nós adjacentes ao novo nó.
    x->prev->next = node;
    x->prev = node;
    s->size++;
  }
}

void erase(SetType k, set s) {
  Node* x = find(k, s);
  if (x != end(s)) {
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x);
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
  if (!empty(s)) {
    for (iterator i = begin(s); i != end(s); i = next(i)) {
      insert(key(i), q);
    }
  }
}

void delete_set(set s) {
  clear(s);
  free(s->end);
  free(s);
}
