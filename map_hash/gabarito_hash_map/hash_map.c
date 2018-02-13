// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#include "hash_map.h"

#include <stdlib.h>

struct HashMapStruct{
  map array[1000];  // Vetor de subconjuntos.
  int capacity;  // Número de subconjuntoa.
  int size;  // Número de elementos no conjunto.
};

// Função de espalhamento.
int hash(KeyType key, int m) {
  return (int) key % m;
}

hash_map new_hash_map(int m) {
  hash_map s = malloc(sizeof(struct HashMapStruct));
  s->size = 0;
  s->capacity = m;
  for (int j = 0; j < s->capacity; j++) {
    s->array[j] = new_map();
  }
  return s;
}

bool hash_empty(hash_map s) {
  return s->size == 0;
}

int hash_size(hash_map s) {
  return s->size;
}

iterator hash_begin(hash_map s) {
  // Retorna o primeiro elemento da primeira lista não vazia.
  for (int j = 0; j < s->capacity; j++) {
    if (!empty(s->array[j])) {
      return begin(s->array[j]);
    }
  }
  // O conjunto está vazio.
  return hash_end(s);
}

iterator hash_end(hash_map s) {
  return NULL;
}

iterator hash_next(iterator x, hash_map s) {
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

iterator hash_find(KeyType k, hash_map s) {
  int j = hash(k, s->capacity);
  iterator x = find(k, s->array[j]);
  if (x != end(s->array[j])) {
    return x;
  } else {
    return hash_end(s);
  }
}

void hash_insert(KeyType k, ValueType v, hash_map s) {
  iterator x = hash_find(k, s);
  if (x == hash_end(s)) {
    s->size++;
  }
  int j = hash(k, s->capacity);  // Índice da lista onde k vai entrar.
  insert(k, v, s->array[j]);
}

void hash_erase(KeyType k, hash_map s) {
  iterator x = hash_find(k, s);
  if (x != hash_end(s)) {
    int j = hash(k, s->capacity);  // Índice da lista onde k está.
    erase(k, s->array[j]);
    s->size--;
  }
}

void hash_clear(hash_map s) {
  for (int j = 0; j < s->capacity; j++) {
    clear(s->array[j]);
  }
  s->size = 0;
}

void hash_copy(hash_map q, hash_map s) {
  hash_clear(q);
  for (iterator x = hash_begin(s); x != hash_end(s); x = hash_next(x, s)) {
    hash_insert(key(x), value(x), q);
  }
}

void delete_hash_map(hash_map s) {
  for (int i = 0; i < s->capacity; i++) {
    delete_map(s->array[i]);
  }
  free(s);
}
