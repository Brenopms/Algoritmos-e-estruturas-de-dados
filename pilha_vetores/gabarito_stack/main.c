// Copyright 2014 Universidade Federal de Minas Gerais (UFMG)
//
// Lista de exercícios sobre listas encadeadas - pilha.
//
// Questão 1.
// Implemente em stack.h e stack.c o TAD stack, utilizando vetores
// alocados dinamicamente.
//
// Questão 2.
// Escreva uma função "void ImprimirInfixado(stack* exp)" que recebe
// como parâmetro uma pilha 'exp' que representa uma expressão em notação
// pré-fixada e remove os operadores e operandos de 'exp', imprimindo-os em
// notação infixada totalmente parametrizada.
// Para simplicar sua implementação,
// assuma que todos os números da expressão são de 0 a 9.
// Por exemplo: para para a pilha contendo a expressão "- / + 4 * 3 4 2 1",
// A função deve imprimir "( ( ( 4 + ( 3 * 4 ) ) / 2 ) - 1 )".
//
// Questão 3.
// Escreva um programa que (i) lê de um arquivo uma expressão em notação
// pré-fixada, (ii) imprime na tela a mesma expressão em notação infixada
// totalmente parametrizada.
// Por exemplo: para o arquivo contendo a expressão "- / + 5 * 4 3 2 1",
// O programa deve imprimir "( ( ( 5 + ( 4 * 3 ) ) / 2 ) - 1 )".

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// Retorna 1 (true) se a string s é um operador e false se s é um número.
int EhUmOperador(char s) {
  return s == '+' || s == '-' || s == '*' || s == '/';
}

// Questão 2.
void ImprimirInfixado(stack exp) {
  char t = top(exp);
  pop(exp);
  if (EhUmOperador(t)) {
    printf("( ");
    ImprimirInfixado(exp);
    printf("%c ", t);
    ImprimirInfixado(exp);
    printf(") ");
  } else {
    printf("%c ", t);
  }
}

// Questão 3.
int main() {
  // Lê uma expressão em notação pré-fixada de um arquivo.
  // A ordem dos elementos do arquivo vai estar invertida na pilha 'aux'.
  char x;
  FILE* f = fopen("input.txt", "r");
  stack aux = new_stack();

  while (fscanf(f, "%c ", &x) == 1) {
    push(x, aux);
  }

  // Inverte a ordem dos elementos da pilha 'aux'.
  stack expressao = new_stack();
  while (!empty(aux)) {
    push(top(aux), expressao);
    pop(aux);
  }
  delete_stack(aux);

  // Imprime a expressão em notação infixada.
  ImprimirInfixado(expressao);
  printf("\n");
  delete_stack(expressao);
  return 0;
}
