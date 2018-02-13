// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)
//
// Lista sobre Conjuntos.
//
// Questão 1.
// Implemente em hash_set.h e hash_set.c o TAD set.
//
// Questão 2.
// Escreva uma função "void Imprimir(hash_set s)" que recebe
// como parâmetro um conjunto s e imprime os elementos de s na tela.

#include "hash_set.h"

#include <stdio.h>
#include <stdlib.h>

// Questão 2.
void Imprimir(hash_set s) {
  printf("{ ");
  for (iterator i = hash_begin(s); i != hash_end(s); i = hash_next(i, s)) {
    printf("%.1f ", key(i));
  }
  printf("}#%d", hash_size(s));
}

int main() {
  hash_set s = new_hash_set(1);
  hash_set p = new_hash_set(1);
  for (int i = 0; i < 10; i++) {
    hash_insert(i, s);
  }
  for (int i = 1; i < 10; i = i + 2) {
    hash_erase(i, s);
  }
  hash_copy(p, s);
  hash_clear(s);
  if (hash_empty(s)) {
    printf("O conjunto s está vazio.\n");
  }
  if (hash_find(4, p) != hash_end(p)) {
    printf("O número 4 pertence ao conjunto.\n");
  }
  if (hash_find(5, p) == hash_end(p)) {
    printf("O número 5 não pertence ao conjunto.\n");
  }
  Imprimir(p);
  printf("\n");
  delete_hash_set(p);
  delete_hash_set(s);
  return 0;
}
