// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#ifndef QUEUE_H_
#define QUEUE_H_

// Tipo dos elementos na fila.
typedef int QueueType;

// Tipo de dado queue (fila).
// Para garantir o ecapsulamento, 'struct QueueStruct' só é definido em queue.c.
typedef struct QueueStruct* queue;

// Cria uma fila vazia.
queue new_queue();

// Testa se a fila está vazia.
int empty(queue q);

// Retorna o número de elementos na fila.
int size(queue q);

// Retorna o elemento que está no início da fila.
// Precondição: a fila não pode estar vazia.
QueueType front(queue q);

// Retorna o elemento que está no final da fila.
// Precondição: a fila não pode estar vazia.
QueueType back(queue q);

// Insere k no final da fila.
void push(QueueType k, queue q);

// Remove o elemento que está no início da fila.
// Precondição: a fila não pode estar vazia.
void pop(queue q);

// Faz a fila p ficar igual a q.
void copy(queue p, queue q);

// Troca o conteúdo da fila p com o da fila q.
void swap(queue p, queue q);

// Libera a memória alocada para a fila.
void delete_queue(queue q);

#endif  // QUEUE_H_
