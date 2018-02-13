// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)

#ifndef MAP_H_
#define MAP_H_

#include <stdbool.h>

// Tipo dos elementos no conjunto.
typedef int KeyType;
typedef float ValueType;

// Tipo de dado map (Conjunto Associativo).
// Cada elemento no conjunto está associado a um valor.
// As chaves são únicas, mas valores podem se repetir.
// Os elementos não estão organizados em uma ordem específica.
// Para garantir o ecapsulamento, 'struct MapStruct' só é definido em map.c.
typedef struct MapStruct* map;

// Tipo do iterador de elementos no cojunto.
// Para garantir o ecapsulamento, 'struct NodeStruct' só é definido em map.c.
typedef struct Node* iterator;

// Cria um conjunto vazio.
map new_map();

// Testa se o cojunto está vazio.
bool empty(map s);

// Retorna o número de elementos no conjunto.
int size(map s);

// Retorna um iterador para o primeiro elemento do conjunto.
// Caso o conjunto esteja vazio, rentorna um iterador para end(s).
iterator begin(map s);

// Retorna um iterador para o "marcador de fim" do conjunto.
iterator end(map s);

// Retorna um iterador para o elemento seguinte ao indicado por x.
// Se x aponta para o último elemento do conjunto, retorna end(s);
// Precondição: x aponta para um dos elementos do conjunto.
iterator next(iterator x);

// Retorna a chave do elemento indicado por x.
// Precondição: x aponta para um dos elementos do conjunto.
KeyType key(iterator x);

// Retorna o valor associado ao elemento indicado por x.
// Precondição: x aponta para um dos elementos do conjunto.
ValueType value(iterator x);

// Retorna um iterador para o elemento k,
// ou um iterador para end(s) caso k não pertença ao conjunto.
// OBS: Note que esta função NÃO retorna 'bool'. Para testar se um elemento 'a'
// pertence a um conjunto 's', você deve escrever "if (find(a, s) != end(s))".
iterator find(KeyType k, map s);

// Insere k no conjunto, associado ao valor v.
// Caso k já pertença ao conjunto, o valor associado a ele é atualizado para v.
void insert(KeyType k, ValueType v, map s);

// Remove k do conjunto (caso lá ele esteja).
void erase(KeyType k, map s);

// Remove todos os elementos do conjunto.
void clear(map s);

// Faz com que o conjunto q contenha exatamente os mesmos elementos
// do cojunto s.
void copy(map q, map s);

// Libera toda a memória alocada para o conjunto.
void delete_map(map s);

#endif  // MAP_H_
