// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#ifndef SET_H_
#define SET_H_

#include <stdbool.h>

// Tipo dos elementos no conjunto.
typedef float SetType;

// Tipo de dado set (Conjunto).
// Os elementos não estão organizados em uma ordem específica.
// Para garantir o ecapsulamento, 'struct SetStruct' só é definido em set.c.
typedef struct SetStruct* set;

// Tipo do iterador de elementos no cojunto.
// Para garantir o ecapsulamento, 'struct NodeStruct' só é definido em set.c.
typedef struct Node* iterator;

// Cria um conjunto vazio.
set new_set();

// Testa se o cojunto está vazio.
bool empty(set s);

// Retorna o número de elementos no conjunto.
int size(set s);

// Retorna um iterador para o primeiro elemento do conjunto.
// Caso o conjunto esteja vazio, rentorna um iterador para end(s).
iterator begin(set s);

// Retorna um iterador para o "marcador de fim" do conjunto.
iterator end(set s);

// Retorna um iterador para o elemento seguinte ao indicado por x.
// Se x aponta para o último elemento do conjunto, retorna end(s);
// Precondição: x aponta para um dos elementos do conjunto.
iterator next(iterator x);

// Retorna a chave do elemento indicado por x.
// Precondição: x aponta para um dos elementos do conjunto.
SetType key(iterator x);

// Retorna um iterador para o elemento k,
// ou um iterador para end(s) caso k não pertença ao conjunto.
// OBS: Note que esta função NÃO retorna 'bool'. Para testar se um elemento 'a'
// pertence a um conjunto 's', você deve escrever "if (find(a, s) != end(s))".
iterator find(SetType k, set s);

// Insere k no conjunto.
// Caso k já pertença ao conjunto, um novo elemento NÃO é inserido.
void insert(SetType k, set s);

// Remove k do conjunto (caso lá ele esteja).
void erase(SetType k, set s);

// Remove todos os elementos do conjunto.
void clear(set s);

// Faz com que o conjunto q contenha exatamente os mesmos elementos
// do cojunto s.
void copy(set q, set s);

// Libera toda a memória alocada para o conjunto.
void delete_set(set s);

#endif  // SET_H_
