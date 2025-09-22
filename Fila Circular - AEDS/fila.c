/*
/    Atividade - Filas Circulares
/    Disciplina: AEDS II - Prática
/    Letícia Santos Alves // R.A.: 2025.1.08.016
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "fila.h"

#define MAX 20  // Define um tamanho máximo.

struct fila {   // Estrutura da fila.
    int frente, fundo, tamanho_maximo;
    int tamanho_atual;
    int items[MAX];
};

struct fila criar_fila(int tamanho) {   // Cria uma fila.
    struct fila fila;
    fila.tamanho_maximo = tamanho;
    fila.frente = 0;
    fila.tamanho_atual = 0;
    fila.fundo = tamanho - 1;
    return fila;
}

bool ehCheia(struct fila fila) {
    return (fila.tamanho_atual == fila.tamanho_maximo);
}

bool ehVazia(struct fila fila) {
    return (fila.tamanho_atual == 0);
}

struct fila enfileirar(struct fila fila, int item) {    // Adiciona um elemento à fila.
    if (ehCheia(fila)) {
        printf("\nFila cheia. Impossível inserir elementos");
        return fila;
    }
    fila.fundo = (fila.fundo + 1) % fila.tamanho_maximo;
    fila.items[fila.fundo] = item;
    fila.tamanho_atual++;
    printf("\nElemento %d enfileirado", item);
    return fila;
}

struct fila desenfileirar(struct fila fila) {   // Remove um elemento da fila.
    if (ehVazia(fila)) {
        printf("\nFila vazia. Impossível remover elementos");
        return fila;
    }
    printf("\nElemento retirado: %d", fila.items[fila.frente]);
    fila.frente = (fila.frente + 1) % fila.tamanho_maximo;
    fila.tamanho_atual--;
    return fila;
}

int obtem_elemento(struct fila fila) {  // Obtém o elemento da frente.
    if (ehVazia(fila)) {
        printf("\nFila vazia. Impossível obter elementos");
        return INT_MIN;
    }
    return fila.items[fila.frente];
}

void ver_fila(struct fila fila) {   // Mostra todos os elementos da fila. (pra ficar melhor para testes)
    if (ehVazia(fila)) {
        printf("\nFila vazia.");
        return;
    }
    printf("\nFila: ");
    int i = fila.frente;
    for (int c = 0; c < fila.tamanho_atual; c++) {
        printf("%d ", fila.items[i]);
        i = (i + 1) % fila.tamanho_maximo;
    }
}

int main() {
    int val, n;
    bool aux;
    struct fila fila = criar_fila(10);  // Cria uma fila de tamanho 10 (pode mudar se quiser).

    printf("\nBem-vindo ao sistema de filas da Luthor Tech!");

    do {
        printf("\n\n======================= MENU =======================");
        printf("\n1- Enfileirar;");
        printf("\n2- Desenfileirar;");
        printf("\n3- Obter elemento;");
        printf("\n4- Fila vazia?");
        printf("\n5- Fila cheia?");
        printf("\n6- Ver fila;");
        printf("\n7- Sair.");
        printf("\nDigite sua escolha: ");
        scanf("%d", &n);

        switch(n) {
            case 1:
                printf("\nDigite o valor: ");
                scanf("%d", &val);
                fila = enfileirar(fila, val);
                break;
            case 2:
                fila = desenfileirar(fila);
                break;
            case 3:
                val = obtem_elemento(fila);
                if (val != INT_MIN)
                    printf("\nElemento da frente: %d", val);
                break;
            case 4:
                aux = ehVazia(fila);
                printf("\nFila %s vazia.", aux ? "está" : "não está");
                break;
            case 5:
                aux = ehCheia(fila);
                printf("\nFila %s cheia.", aux ? "está" : "não está");
                break;
            case 6:
                ver_fila(fila);
                break;
            case 7:
                printf("\nA Luthor Tech agradece. Finalizando...\n\n");
                return 0;
            default:
                printf("\nOpção inválida.");
                break;
        }
    } while(1);

    return 0;
}
