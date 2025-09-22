/*
/    Atividade - Filas com Apontadores
/    Disciplina: AEDS II - Prática
/    Letícia Santos Alves // R.A.: 2025.1.08.016
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "fila_apontadores.h"

Fila* criar_fila() {  // Cria uma nova fila.
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (!fila) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }
    fila->frente = NULL;
    fila->fundo = NULL;
    fila->tam_atual = 0;
    printf("\nFila criada.");
    return fila;
}

bool ehCheia(Fila* fila) { // Filas com apontadores geralemnte nao ficam cheias.
    return false;
}

bool ehVazia(Fila* fila) { 
    return (fila->frente == NULL);
}

void enfileirar(Fila* fila, int item) { // Adiciona um elemento na fila.
    No* novo_no = (No*)malloc(sizeof(No));
    if (!novo_no) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    novo_no->valor = item;
    novo_no->proximo = NULL;
    
    if (ehVazia(fila)) {
        fila->frente = novo_no;     // Se a fila tá vazia, frente e fundo apontam para o novo no.
        fila->fundo = novo_no;
    } else {
        fila->fundo->proximo = novo_no;     // se n tá vazia, adiciona no final e vai atualizar o fundo.
        fila->fundo = novo_no;
    }
    
    fila->tam_atual++;
    printf("\nElemento %d enfileirado", item);
}

void desenfileirar(Fila* fila) {    // Remove um elemento da fila.
    if (ehVazia(fila)) {
        printf("\nFila vazia. Impossível remover elementos.");
        return;
    }
    No* temp = fila->frente;
    printf("\nElemento retirado: %d", temp->valor);
    fila->frente = fila->frente->proximo;
    if (fila->frente == NULL) {
        fila->fundo = NULL;
    }
    free(temp);
    fila->tam_atual--;
}

int obtem_elemento(Fila* fila) {   // Obtém o elemento que tá na frente.
    if (ehVazia(fila)) {
        printf("\nFila vazia. Impossível obter elementos.");
        return INT_MIN;
    }
    return fila->frente->valor;
}

void ver_fila(Fila* fila) { // Mostra a fila.
    if (ehVazia(fila)) {
        printf("\nFila vazia.");
        return;
    }
    
    printf("\nFila: ");
    No* atual = fila->frente;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\nTamanho: %d", fila->tam_atual);
}

void liberar_fila(Fila* fila) {
    if (fila) {
        No* atual = fila->frente;       // Libera todos os nos da fila.
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        free(fila);
    }
}

int main() {
    int val, n;
    bool aux;
    
    printf("\nBem-vindo ao sistema de filas da Luthor Tech!\n");
    
    Fila* fila = criar_fila();
    if (!fila) {
        printf("Erro ao criar a fila\n");
        return 1;
    }
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
                enfileirar(fila, val);
                break;
            case 2:
                desenfileirar(fila);
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
                liberar_fila(fila);
                return 0;
            default:
                printf("\nOpção inválida.");
                break;
        }
    } while(1);

    return 0;
}