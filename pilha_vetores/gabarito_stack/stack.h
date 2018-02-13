// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#ifndef STACK_H_
#define STACK_H_

// Tipo dos elementos na pilha.
typedef char StackType;

// Tipo de dado stack (Pilha).
// Para garantir o ecapsulamento, 'struct StackStruct' só é definido em stack.c.
typedef struct StackStruct* stack;

// Cria uma pilha vazia.
stack new_stack();

// Testa se a pilha está vazia.
int empty(stack s);

// Retorna o número de elementos na pilha.
int size(stack s);

// Retorna o elemento que está no topo da pilha.
// Precondição: a pilha não pode estar vazia.
StackType top(stack s);

// Insere k no topo da pilha.
void push(StackType k, stack s);

// Remove o elemento que está no topo da pilha.
// Precondição: a pilha não pode estar vazia.
void pop(stack s);

// Faz a pilha s ficar igual a p.
void copy(stack s, stack p);

// Troca o conteúdo da pilha s com o da pilha p.
void swap(stack s, stack p);

// Libera a memória alocada para a pilha.
void delete_stack(stack s);

#endif  // STACK_H_
