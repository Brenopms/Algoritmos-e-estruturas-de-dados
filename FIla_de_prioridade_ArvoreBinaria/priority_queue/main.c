// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)
//
// Lista sobre Fila de Prioridade.
//
// Questão 1.
// Implemente em priority_queue.cc o TAD priority_queue.
//
// Questão 2.
// Implemente uma função "void PriorityQueueSort(int n, float v[])" que ordena
// os elementos de um vetor utilizando uma priority_queue.
//
// Questão 3.
// Escreva um programa para testar a função da questão anterior.

#include <stdio.h>

#include "priority_queue.h"

void Print(int n, float v[]) {
  printf("{");
  for (int i = 0 ; i < n; i++) {
    printf("%.1f", v[i]);
    if (i < n - 1) {
      printf(", ");
    }
  }
  printf("}\n");
}

void PriorityQueueSort(int n, float v[]) {
  priority_queue q = new_priority_queue();
  for (int i = 0; i < n; i++) {
    push(v[i], q);
  }
  for (int i = 0; i < n; i++) {
    v[i] = top(q);
    pop(q);
  }
  delete_priority_queue(q);
}

int main() {
  float v[] = {5, 6, 4, 7, 3, 8, 2, 9, 1, 0};
  Print(10, v);
  PriorityQueueSort(10, v);
  Print(10, v);
  return 0;
}
