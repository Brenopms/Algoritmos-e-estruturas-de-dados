// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#include "stack.h"

#include<stdlib.h>

// Define como os elementos da pilha serão organizados na memória.
typedef struct node{
  StackType key;
  struct node* prev;
  struct node* next;
} Node;

struct StackStruct{
  Node* end;  // Ponteiro para o sentinela.
  int size;  // Número de elementos na pilha.
};

stack new_stack() {
  stack s = malloc(sizeof(struct StackStruct));
  s->size = 0;
  s->end = malloc(sizeof(Node));
  s->end->next = s->end;
  s->end->prev = s->end;
  return s;
}

int empty(stack s) {
  return s->size == 0;
}

int size(stack s) {
  return s->size;
}

StackType top(stack s) {
  return s->end->next->key;
}

void push(StackType k, stack s) {
  // Ponteiro para o primeiro elemento na pilha.
  Node* first = s->end->next;
  // Cria um novo nó e define o valor dos seus campos.
  Node* node = malloc(sizeof(Node));
  node->key = k;
  node->prev = first->prev;
  node->next = first;
  // Ajusta o valor dos ponteiros dos nós adjacentes ao novo nó.
  first->prev->next = node;
  first->prev = node;
  s->size++;
}

void pop(stack s) {
  Node* first = s->end->next;  // Ponteiro para o primeiro elemento na pilha.
  first->prev->next = first->next;
  first->next->prev = first->prev;
  free(first);
  s->size--;
}

void copy(stack s, stack p) {
  // Apaga todos os elementos de s.
  while (!empty(s)) {
    pop(s);
  }
  // Insere os elementos de p de trás para frente na pilha corrente.
  for (Node* i = p->end->prev; i != p->end; i = i->prev) {
    push(i->key, s);
  }
}

void swap(stack s, stack p) {
  struct StackStruct aux = *s;
  *s = *p;
  *p = aux;
}

void delete_stack(stack s) {
  while (!empty(s)) {
    pop(s);  // A função pop() libera a memórima de cada nó removido da pilha.
  }
  free(s->end);
  free(s);
}
