/* 
Trabalho prático II - Palíndromos
Arquivo .h

Disciplina: Algoritmos e Estruturas de Dados II.
Docente: Iago Augusto de Carvalho.

Integrantes do Grupo: 
- Gustavo de Sousa Zimmermann - 2025.1.08.009; 
- Letícia Santos Alves - 2025.1.08.016;
- Luiz Gustavo Custódio Leite - 2025.1.08.031.

Universidade Federal de Alfenas.
Alfenas, 23 de setembro de 2025.
*/

#ifndef PALINDROMO_H
#define PALINDROMO_H

#include <stdio.h>
#include <stdbool.h>

// --- Definições das estruturas que são utilizadas ---

// Nó para as listas
typedef struct No {
    char dado;
    struct No* proximo;
} No;

// Estrutura da Lista
typedef struct {
    No* inicio;
    int tamanho;
} Lista;

// Estrutura da Pilha
typedef struct {
    No* topo;
} Pilha;

// Estrutura da Fila
typedef struct {
    No* inicio;
    No* fim;
} Fila;

// --- Protótipos das funções que são utilizadas ---

// Funções da Lista
Lista* criar_lista();
void inserir_lista(Lista* l, char c); 
void destruir_lista(Lista* l);

// Funções da Pilha
Pilha* criar_pilha();
void empilhar(Pilha* p, char c);
char desempilhar(Pilha* p);
bool pilha_vazia(Pilha* p);
void destruir_pilha(Pilha* p);

// Funções da Fila
Fila* criar_fila();
void enfileirar(Fila* f, char c);
char desenfileirar(Fila* f);
bool fila_vazia(Fila* f);
void destruir_fila(Fila* f);

// Função principal de verificação de palíndromo
int eh_palindromo(const char* linha); 

#endif // PALINDROMO_H
