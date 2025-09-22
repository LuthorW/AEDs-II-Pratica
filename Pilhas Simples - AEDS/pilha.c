#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "pilha.h"

struct no {
    int data;
    struct no* prox; 
};

struct pilha {
    struct no* topo;
};

struct pilha* criar_pilha() {
    struct pilha* pilha = (struct pilha*)malloc(sizeof(struct pilha));
    if (pilha == NULL) {
        printf("\nErro: Falha na alocacao de memoria.");
        return NULL;
    }
    pilha->topo = NULL;

    return pilha;
}

bool ehVazia(struct pilha* pilha) {
    if (pilha == NULL) {
        return true;
    }
    return (pilha->topo == NULL);
}

void push(struct pilha* pilha, int item) {
    if (pilha == NULL) {
        printf("\nErro: Pilha nao inicializada.");
        return;
    }
    
    struct no* no_novo = (struct no*)malloc(sizeof(struct no));
    if (no_novo == NULL) {
        printf("\nErro: Falha na alocacao de memoria.");
        return;
    }
    
    no_novo->data = item;

    no_novo->prox = pilha->topo;

    pilha->topo = no_novo;
    
    printf("\nElemento %d inserido.", item);
}

int pop(struct pilha* pilha) {
    if (ehVazia(pilha)) {
        printf("\nPilha vazia. Impossivel remover elementos.");
        return INT_MIN; 
    }
    
    struct no* no_remov = pilha->topo;
    int valor = no_remov->data;
    
    pilha->topo = no_remov->prox;

    free(no_remov);

    return valor;
}

int obtem_elemento(struct pilha* pilha) {
    if (ehVazia(pilha)) {
        printf("\nPilha vazia. Impossivel obter elementos");
        return INT_MIN; 
    }
    return pilha->topo->data; 
}

void ver(struct pilha* pilha) {
    if (ehVazia(pilha)) {
        printf("\nPilha vazia.\n");
        return;
    }
    
    printf("\n=============Pilha=============\n");
    
    struct no* atual = pilha->topo;
    int cont = 0;
    
    struct no* temp = pilha->topo;
    while (temp != NULL) {
        cont++;
        temp = temp->prox;
    }
    
    int posicao = 0;
    atual = pilha->topo;
    while (atual != NULL) {
        if (posicao == 0) {
            printf("->Topo<-\n");
            printf("%4d\n", atual->data);
        } else {
            printf("%4d\n", atual->data);
        }
        atual = atual->prox;
        posicao++;
    }
    printf("->Base<-\n");
    printf("\nElementos totais: %d", cont);
    printf("\n===============================");
}

void fim_pilha(struct pilha* pilha) {
    if (pilha == NULL) {
        return;
    }
    while (!ehVazia(pilha)) {
        pop(pilha);
    }
    free(pilha);
}

int main() { 
    int val, n;
    bool aux;

    struct pilha* pilha = criar_pilha();     // Cria pilha.
    if (pilha == NULL) {
        printf("\nErro ao criar pilha.");
        return -1;
    }
    
    do {
        printf("\n\n********************MENU*******************");
        printf("\n1- Push;");
        printf("\n2- Pop;");
        printf("\n3- Obter elemento");
        printf("\n4- Pilha vazia?");
        printf("\n5- Ver pilha.");
        printf("\n6- Sair");
        printf("\nDigite sua escolha: ");
        scanf("%d",&n);
        
        switch(n) {
            case 1: 
                printf("\nDigite o valor: ");
                scanf("%d",&val);
                push(pilha, val);
                break;
            case 2: 
                val = pop(pilha);
                if (val != INT_MIN) {
                    printf("\nElemento removido: %d", val);
                }
                break;
            case 3: 
                val = obtem_elemento(pilha);
                if (val != INT_MIN) {
                    printf("\nElemento no topo: %d", val);
                }
                break;
            case 4: 
                aux = ehVazia(pilha);
                printf(aux ? "\nPilha vazia.": "\nPilha não esta vazia");
                break;
            case 5:
                ver(pilha);
                break; 
            case 6:
                fim_pilha(pilha);
                return 0;
            default: 
                printf("\nOpcao invalida.");
                break;
        }
    } while(1);
    
    return 0;
}
