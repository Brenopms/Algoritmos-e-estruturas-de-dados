// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)
//
// Lista sobre Conjuntos.
//
// Questão 1.
// Implemente em set.h e set.c o TAD set, utilizando vetores.
//
// Questão 2.
// Escreva uma função "void Imprimir(set s)" que recebe
// como parâmetro um conjunto s e imprime os elementos de s na tela.

#include "set.h"

#include <stdio.h>
#include <stdlib.h>

// Questão 2.
void Imprimir(set s) {
  printf("{ ");
  for (iterator i = begin(s); i != end(s); i = next(i)) {
    printf("%f ", key(i));
  }
  printf("}#%d", size(s));
}

int main() {
  set s = new_set();
  set p = new_set();
  for (int i = 0; i < 10; i++) {
    insert(i, s);
  }
  for (int i = 1; i < 10; i = i + 2) {
    erase(i, s);
  }
  copy(p, s);
  clear(s);

  if (empty(s)) {
    printf("O conjunto s está vazio.\n");
  }
  if (find(4, p) != end(p)) {
    printf("O número 4 pertence ao conjunto.\n");
  }
  if (find(5, p) == end(p)) {
    printf("O número 5 não pertence ao conjunto.\n");
  }
  Imprimir(p);
  printf("\n");
  delete_set(p);
  delete_set(s);
  return 0;
}
