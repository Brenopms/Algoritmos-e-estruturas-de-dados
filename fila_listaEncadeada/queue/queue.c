// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#include "queue.h"

#include <stdlib.h>

// Define como os elementos da fila serão organizados na memória.
typedef struct node{
  QueueType key;
  struct node* prev;
  struct node* next;
} Node;

struct QueueStruct{
  Node* end;  // Ponteiro para o sentinela.
  int size;  // Número de elementos na fila.
};

queue new_queue() {
  queue q = malloc(sizeof(struct QueueStruct));
  q->size = 0;
  q->end = malloc(sizeof(Node));
  q->end->next = q->end;
  q->end->prev = q->end;
  return q;
}

int empty(queue q) {
  return q->size == 0;
}

int size(queue q) {
  return q->size;
}

QueueType front(queue q) {
  return q->end->next->key;
}

QueueType back(queue q) {
  return q->end->prev->key;
}

void push(QueueType k, queue q) {
  // Cria um novo nó e define o valor dos seus campos.
  Node* node = malloc(sizeof(Node));
  node->key = k;
  node->prev = q->end->prev;
  node->next = q->end;
  // Ajusta o valor dos ponteiros dos nós adjacentes ao novo nó.
  node->prev->next = node;
  node->next->prev = node;
  q->size++;
}

void pop(queue q) {
  Node* first = q->end->next;  // Ponteiro para o primeiro elemento na fila.
  first->prev->next = first->next;
  first->next->prev = first->prev;
  free(first);
  q->size--;
}

void copy(queue p, queue q) {
  // Apaga todos os elementos em p.
  while (!empty(p)) {
    pop(p);
  }
  // Insere os elementos de q em p.
  for (Node* i = q->end->next; i != q->end; i = i->next) {
    push(i->key, p);
  }
}

void swap(queue s, queue p) {
  struct QueueStruct aux = *s;
  *s = *p;
  *p = aux;
}

void delete_queue(queue q) {
  // Primeiramente, remove todos os elementos da fila.
  while (!empty(q)) {
    pop(q);  // A função pop() libera a memórima de cada nó removido da fila;
  }
  // Em seguida, libera a memória alocada ao sentinela.
  free(q->end);
  free(q);
}
