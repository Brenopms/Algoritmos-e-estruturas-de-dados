// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#ifndef HASH_SET_H_
#define HASH_SET_H_

#include "set.h"

#include <stdbool.h>

// Tipo de dado hash_set (Conjunto implementado com Tabela Hash).
// Os elementos não estão organizados em uma ordem específica.
// Para garantir o ecapsulamento, 'struct HashSetStruct' só é definido em set.c.
typedef struct HashSetStruct* hash_set;

// Cria um conjunto vazio (composto de 'm' subconjuntos).
hash_set new_hash_set(int m);

// Testa se o cojunto está vazio.
bool hash_empty(hash_set s);

// Retorna o número de elementos no conjunto.
int hash_size(hash_set s);

// Retorna um iterador para o primeiro elemento do conjunto.
// Caso o conjunto esteja vazio, rentorna um iterador para end(s).
iterator hash_begin(hash_set s);

// Retorna um iterador para o "marcador de fim" do conjunto.
iterator hash_end(hash_set s);

// Retorna um iterador para o elemento seguinte ao indicado por x em s.
// Se x aponta para o último elemento do conjunto, retorna end(s);
// Precondição: x aponta para um dos elementos do conjunto.
iterator hash_next(iterator x, hash_set s);

// Retorna um iterador para o elemento k,
// ou um iterador para end(s) caso k não pertença ao conjunto.
// OBS: Note que esta função NÃO retorna 'bool'. Para testar se um elemento 'a'
// pertence a um conjunto 's', você deve escrever "if (find(a, s) != end(s))".
iterator hash_find(SetType k, hash_set s);

// Insere k no conjunto.
// Caso k já pertença ao conjunto, um novo elemento NÃO é inserido.
void hash_insert(SetType k, hash_set s);

// Remove k do conjunto (caso lá ele esteja).
void hash_erase(SetType k, hash_set s);

// Remove todos os elementos do conjunto.
void hash_clear(hash_set s);

// Faz com que o conjunto q contenha exatamente os mesmos elementos
// do cojunto s.
void hash_copy(hash_set q, hash_set s);

// Libera toda a memória alocada para o conjunto.
void delete_hash_set(hash_set s);

#endif  // HASH_SET_H_
