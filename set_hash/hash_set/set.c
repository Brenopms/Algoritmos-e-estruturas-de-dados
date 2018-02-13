// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#include "set.h"

#include <stdlib.h>

// Os elementos do conjunto estão distribuídos sequencialmente em uma
// lista duplamente encadeada com sentinela.
struct Node{
  SetType key;
  struct Node* prev;  // Nó a esquerda.
  struct Node* next;  // Nó a direita.
};

struct SetStruct{
  iterator end;  // Nó sentinela.
  int size;  // Número de elementos no conjunto.
};

set new_set() {
  set s = malloc(sizeof(struct SetStruct));
  iterator x = malloc(sizeof(struct Node));
  x->next = x;
  x->prev = x;
  s->end = x;
  s->size = 0;
  return s;
}

bool empty(set s) {
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
  return x->next;
}

SetType key(iterator x) {
  return x->key;
}

iterator find(SetType k, set s) {
  for (iterator x = begin(s); x != end(s); x = next(x)) {
    if (key(x) == k) {
      return x;
    }
  }
  return end(s);  // k não pertence ao conjunto.
}

void insert(SetType k, set s) {
  if (find(k, s) == end(s)) {
    // Cria um novo nó e insere ele depois do sentinela.
    struct Node* node = malloc(sizeof(struct Node));
    node->key = k;
    node->prev = s->end;
    node->next = s->end->next;
    // Ajusta o valor dos ponteiros dos nós adjacentes ao novo nó.
    node->prev->next = node;
    node->next->prev = node;
    s->size++;
  }
}

void erase(SetType k, set s) {
  iterator x = find(k, s);
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
  for (iterator x = begin(s); x != end(s); x = next(x)) {
    insert(key(x), q);
  }
}

void delete_set(set s) {
  clear(s);
  free(s->end);
  free(s);
}
