// Copyright 2015 Universidade Federal de Minas Gerais (UFMG)
//
// Lista de exercícios sobre listas encadeadas - fila.
//
// Questão 1.
// Implemente em queue.h e queue.c o TAD queue, utilizando vetores
// alocados dinamicamente.
//
// Questão 2.
// Escreva uma função "void Imprimir(queue p)" que recebe
// como parâmetro uma fila q e imprime os elemento de q na tela.
// Pós-condição: a fila 'q' não é alterada.
//
// Questão 3.
// Escreva um programa que gerencia uma fila de banco. Ao entrar na fila,
// o cliente dá seu CPF e sua idade. Os clientes são atendidos por ordem de
// chegada. Entretanto, os clientes com 60 anos ou mais tem prioridade sobre
// os outros clientes, ou seja, um cliente com menos de 60 anos só é atendido
// se não houver nenhum cliente com 60 anos ou mais esperando na fila. O sistema
// que você vai implementar deve apresentar duas opções: "(1) Entrar na fila" e
// "(2) Próximo da fila". Na Primeira, o sistema deve cadastrar o CPF e a
// idade do cliente. Já na segunda opção, ele deve imprimir o CPF do
// próximo cliente que está esperando e retirá-lo da fila, ou se for o caso
// imprimir uma mensagem indicando que a fila está vazia.
// DICA: Use duas filas: uma para armazenar os nomes dos clientes
// prioritários e outra para armazenar os nomes dos clientes não prioritários.

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// Questão 2.
////////////////////////////////////////////////////////////////////////////////

// Imprime os elementos da fila q na tela.
void Imprimir(queue q) {
  printf("[ ");
  for (int i = 0; i < size(q); i++) {
    printf("%d ", front(q));
    push(front(q), q);
    pop(q);
  }
  printf("]\n");
}

// Questão 3.
//////////////////////////////////////////////////////////////////////////////

// Insere um cliente na fila do banco.
void Enfileirar(int cpf,
                int idade,
                queue prioritarios,
                queue nao_prioritarios) {
  if (idade >= 60) {
    push(cpf, prioritarios);
  } else {
    push(cpf, nao_prioritarios);
  }
}

// Retira o próximo cliente da fila do banco e retorna o seu cpf.
// Precondição: as duas filas não estão vazias.
int Desenfileirar(queue prioritarios,
                  queue nao_prioritarios) {
  int proximo;
  if (!empty(prioritarios)) {
    proximo = front(prioritarios);
    pop(prioritarios);
    return proximo;
  } else {
    proximo = front(nao_prioritarios);
    pop(nao_prioritarios);
    return proximo;
  }
}

int main() {
  queue prioritarios = new_queue();
  queue nao_prioritarios = new_queue();
  int opcao;
  do {
    // Insiste até que o usuário digite uma opção correta.
    do {
      printf("(1) Entrar na fila\n");
      printf("(2) Proximo da fila\n");
      printf("(3) Imprimir Fila\n");
      printf("(0) Sair\n");
      printf(">> ");
      scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 3);
    // Executa a solicitação do usuário.
    if (opcao == 1) {
      int cpf;
      printf("CPF: ");
      scanf("%d", &cpf);
      int idade;
      printf("Idade: ");
      scanf("%d", &idade);
      Enfileirar(cpf, idade, prioritarios, nao_prioritarios);
    } else if (opcao == 2) {
      if (empty(prioritarios) && empty(nao_prioritarios)) {
        printf("\n\n\nNenhum cliente na fila.\n\n");
      } else {
	printf("\n\n\nProximo: %d\n\n", Desenfileirar(prioritarios, nao_prioritarios));
      }
    } else if (opcao == 3) {
	printf("\n\nLista de espera:\n");
	Imprimir(prioritarios);
	Imprimir(nao_prioritarios);
	printf("\n");
      }
  } while (opcao != 0);
  delete_queue(prioritarios);
  delete_queue(nao_prioritarios);
  return 0;
}
