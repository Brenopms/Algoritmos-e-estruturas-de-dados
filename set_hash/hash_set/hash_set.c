// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#include "hash_set.h"

#include <stdlib.h>

struct HashSetStruct{
  set array[1000];  // Vetor de subconjuntos.
  int capacity;  // Número de subconjuntoa.
  int size;  // Número de elementos no conjunto.
};

// Função de espalhamento.
int hash(SetType key, int m) {
  return (int) key % m;
}

hash_set new_hash_set(int m) {
  hash_set s = malloc(sizeof(struct HashSetStruct));
  s->size = 0;
  s->capacity = m;
  for (int j = 0; j < s->capacity; j++) {
    s->array[j] = new_set();
  }
  return s;
}

bool hash_empty(hash_set s) {
  return s->size == 0;
}

int hash_size(hash_set s) {
  return s->size;
}

iterator hash_begin(hash_set s) {
  // Retorna o primeiro elemento da primeira lista não vazia.
  for (int j = 0; j < s->capacity; j++) {
    if (!empty(s->array[j])) {
      return begin(s->array[j]);
    }
  }
  // O conjunto está vazio.
  return hash_end(s);
}

iterator hash_end(hash_set s) {
  return NULL;
}

iterator hash_next(iterator x, hash_set s) {
  int j = hash(key(x), s->capacity);
  if (next(x) != end(s->array[j])) {
    // Se x não é o último do seu subconjunto,
    // retorna o próximo elemento no subconjunto.
    return next(x);
  } else {
    // Se x é o último do seu subconjunto,
    // retorna o primeiro elemento do próximo subconjunto não vazio.
    for (int i = j + 1; i < s->capacity; i++) {
      if (!empty(s->array[i])) {
        return begin(s->array[i]);
      }
    }
    // Caso x seja o último elemento do conjunto.
    return hash_end(s);
  }
}

iterator hash_find(SetType k, hash_set s) {
  int j = hash(k, s->capacity);
  iterator x = find(k, s->array[j]);
  if (x != end(s->array[j])) {
    return x;
  } else {
    return hash_end(s);
  }
}

void hash_insert(SetType k, hash_set s) {
  if (hash_find(k, s) == hash_end(s)) {
    int j = hash(k, s->capacity);  // Índice da lista onde k vai entrar.
    insert(k, s->array[j]);
    s->size++;
  }
}

void hash_erase(SetType k, hash_set s) {
  iterator x = hash_find(k, s);
  if (x != hash_end(s)) {
    int j = hash(k, s->capacity);  // Índice da lista onde k está.
    erase(k, s->array[j]);
    s->size--;
  }
}

void hash_clear(hash_set s) {
  for (int j = 0; j < s->capacity; j++) {
    clear(s->array[j]);
  }
  s->size = 0;
}

void hash_copy(hash_set q, hash_set s) {
  hash_clear(q);
  for (iterator x = hash_begin(s); x != hash_end(s); x = hash_next(x, s)) {
    hash_insert(key(x), q);
  }
}

void delete_hash_set(hash_set s) {
  for (int i = 0; i < s->capacity; i++) {
    delete_set(s->array[i]);
  }
  free(s);
}
