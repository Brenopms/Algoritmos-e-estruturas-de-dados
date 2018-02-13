// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include "map.h"

#include <stdbool.h>

// Tipo de dado hash_map (Conjunto Associativo implementado com Tabela Hash).
// Os elementos não estão organizados em uma ordem específica.
// Para garantir o ecapsulamento, 'struct HashMapStruct' só é definido em map.c.
typedef struct HashMapStruct* hash_map;

// Cria um conjunto vazio (composto de 'm' subconjuntos).
hash_map new_hash_map(int m);

// Testa se o cojunto está vazio.
bool hash_empty(hash_map s);

// Retorna o número de elementos no conjunto.
int hash_size(hash_map s);

// Retorna um iterador para o primeiro elemento do conjunto.
// Caso o conjunto esteja vazio, rentorna um iterador para end(s).
iterator hash_begin(hash_map s);

// Retorna um iterador para o "marcador de fim" do conjunto.
iterator hash_end(hash_map s);

// Retorna um iterador para o elemento seguinte ao indicado por x em s.
// Se x aponta para o último elemento do conjunto, retorna end(s);
// Precondição: x aponta para um dos elementos do conjunto.
iterator hash_next(iterator x, hash_map s);

// Retorna um iterador para o elemento k,
// ou um iterador para end(s) caso k não pertença ao conjunto.
// OBS: Note que esta função NÃO retorna 'bool'. Para testar se um elemento 'a'
// pertence a um conjunto 's', você deve escrever "if (find(a, s) != end(s))".
iterator hash_find(KeyType k, hash_map s);

// Insere k no conjunto, associado ao valor v.
// Caso k já pertença ao conjunto, o valor associado a ele é atualizado para v.
void hash_insert(KeyType k, ValueType v, hash_map s);

// Remove k do conjunto (caso lá ele esteja).
void hash_erase(KeyType k, hash_map s);

// Remove todos os elementos do conjunto.
void hash_clear(hash_map s);

// Faz com que o conjunto q contenha exatamente os mesmos elementos
// do cojunto s.
void hash_copy(hash_map q, hash_map s);

// Libera toda a memória alocada para o conjunto.
void delete_hash_map(hash_map s);

#endif  // HASH_MAP_H_
