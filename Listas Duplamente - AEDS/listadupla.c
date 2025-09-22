/*
    Atividade - Listas Duplamente Encadeadas
    Letícia Santos Alves // R.A.: 2025.1.08.016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listadupla.h"

struct node {   // Estrutura do no.
    int data;
    struct node *prev; // Ponteiro para o anterior.
    struct node *next; // Ponteiro para o próximo.
} *p, *tmp, *tmp1;

void inserir_fim(int elemento) {
    tmp = p;
    tmp1 = (struct node*) malloc(sizeof(struct node));
    tmp1->data = elemento;
    tmp1->next = NULL;
    tmp1->prev = NULL; 

    if (p == NULL) {
        p = tmp1;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = tmp1;       // O próximo do antigo último no é o novo.
        tmp1->prev = tmp;       // O anterior do novo nó é o antigo ultimo.
    }
}

void inserir_inicio(int elemento) {
    tmp1 = (struct node*) malloc(sizeof(struct node));
    tmp1->data = elemento;
    tmp1->prev = NULL;      // O primeiro elemnto sempre tem prev nulo.
    tmp1->next = p;

    if (p != NULL) {
        p->prev = tmp1;
    }
    p = tmp1;   // O ponteiro p aponta para o novo primeiro nó.
}

void apagar(int ele) {
    tmp = p;
    while (tmp != NULL) {
        if (tmp->data == ele) {
            if (tmp->prev == NULL) { 
                p = tmp->next;
                if (p != NULL) {
                    p->prev = NULL;
                }
            } else {
                tmp->prev->next = tmp->next;
                if (tmp->next != NULL) {
                    tmp->next->prev = tmp->prev;
                }
            }
            free(tmp);
            return;
        }
        tmp = tmp->next;
    }
    printf("\nValor não encontrado!");
}

void apagar_inicio() {
    if (p == NULL) {
        printf("\nNenhum elemento deletado.");
        return;
    }

    tmp = p;
    printf("\nElemento deletado - %d", p->data);
    p = p->next;
    if (p != NULL) {
        p->prev = NULL; 
    }
    free(tmp);
}

void apagar_fim() {
    if (p == NULL) {
        printf("\nNenhum elemento deletado.");
        return;
    }

    tmp = p;
    while (tmp->next != NULL) {
        tmp = tmp->next;    // Vai at o último no.
    }

    printf("\nElemento deletado - %d", tmp->data);
    if (tmp->prev == NULL) { 
        p = NULL;
    } else {
        tmp->prev->next = NULL;     // O próximo do penultimo nó agora é nulo.
    }
    free(tmp);
}

bool ehVazia() { 
    return (p == NULL);
}

void imprimir() {
    tmp = p;
    if (tmp == NULL) {
        printf("\nLista vazia!");
        return;
    }
    while (tmp != NULL) {
        printf("\n %d", tmp->data);
        tmp = tmp->next;    // Vai para o proximo no
    }
}

int obter_primeiro(void) {
    if (p == NULL) {
        printf("\nNenhum elemento encontrado.");
        return 0;
    } else {
        return (p->data);
    }
}

int obter_ultimo(void) {
    if (p == NULL) {
        printf("\nNenhum elemento encontrado.");
        return 0;
    }
    tmp = p;
    while (tmp->next != NULL) {
        tmp = tmp->next;   // Vai ate o ultimo nó.
    }
    return (tmp->data);
}

void inserir_posicao(int valor, int posicao) {
    if (posicao == 0) {
        inserir_inicio(valor);
        return;
    }

    tmp = p;
    int i = 0;
    while (tmp != NULL && i < posicao - 1) {
        tmp = tmp->next; 
        i++;
    }

    if (tmp == NULL) {
        printf("\nPosição inválida!");
        return;
    }

    struct node* novo = (struct node*) malloc(sizeof(struct node));
    novo->data = valor;
        // Ajusta os ponteiros para colocar o novo no na nova posiçao.
    novo->next = tmp->next;    
    novo->prev = tmp;
    tmp->next = novo;

    if (novo->next != NULL) {
        novo->next->prev = novo;
    }
}

void remover_posicao(int posicao) {
    if (p == NULL) {
        printf("\nLista vazia!");
        return;
    }
    if (posicao == 0) {
        apagar_inicio();
        return;
    }

    tmp = p;
    int i = 0;
    while (tmp != NULL && i < posicao) {
        tmp = tmp->next;
        i++;
    }

    if (tmp == NULL) {
        printf("\nPosição inválida!");
        return;
    }
        // Ajusta os ponteiros para remover o no.
    tmp->prev->next = tmp->next;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp->prev;
    }
    free(tmp);
}

int obter_posicao(int posicao) {
    tmp = p;
    int i = 0;
    while (tmp != NULL && i < posicao) {
        tmp = tmp->next;
        i++;
    }

    if (tmp == NULL) {
        printf("\nPosição inválida!");
        return -1;
    }

    return tmp->data;
}

int main() {
    int val, n, pos;
    p = NULL;
    printf("\nBem-vindo ao sistema de Listas Encadeadas da Luthor Tech!\n");
    do {
        printf("\n\n==========================MENU==========================\n");
        printf("\n1- Inserir no fim;");
        printf("\n2- Inserir no inicio;");
        printf("\n3- Apagar um elemento em particular;");
        printf("\n4- Apagar do inicio;");
        printf("\n5- Apagar do fim;");
        printf("\n6- Imprimir lista;");
        printf("\n7- É vazia?");
        printf("\n8- Obter primeiro;");
        printf("\n9- Obter último;");
        printf("\n10- Inserir em posição;");
        printf("\n11- Remover de posição;");
        printf("\n12- Obter valor de posição;");
        printf("\n0- Sair.");
        printf("\nDigite a sua opção: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                printf("\nDigite o valor: ");
                scanf("%d", &val);
                inserir_fim(val);
                break;
            case 2:
                printf("\nDigite o valor: ");
                scanf("%d", &val);
                inserir_inicio(val);
                break;
            case 3:
                printf("\nDigite o valor: ");
                scanf("%d", &val);
                apagar(val);
                break;
            case 4:
                apagar_inicio();
                break;
            case 5:
                apagar_fim();
                break;
            case 6:
                imprimir();
                break;
            case 7:
                if (ehVazia())
                    printf("\nLista está vazia.");
                else
                    printf("\nLista não está vazia.");
                break;
            case 8:
                val = obter_primeiro();
                if (val != 0 || (p != NULL && p->data == 0))
                    printf("%d", val);
                break;
            case 9:
                val = obter_ultimo();
                if (val != 0 || (p != NULL && p->data == 0))
                    printf("%d", val);
                break;
            case 10:
                printf("\nDigite o valor: ");
                scanf("%d", &val);
                printf("\nDigite a posição: ");
                scanf("%d", &pos);
                inserir_posicao(val, pos);
                break;
            case 11:
                printf("\nDigite a posição: ");
                scanf("%d", &pos);
                remover_posicao(pos);
                break;
            case 12:
                printf("\nDigite a posição: ");
                scanf("%d", &pos);
                val = obter_posicao(pos);
                if (val != -1)
                    printf("\nValor na posição %d = %d", pos, val);
                break;
            case 0:
                printf("\nA Luthor Tech agradece. Finalizando...\n\n");
                return 0;
            default:
                printf("\n Opção errada!");
                break;
        }
    } while (1);
}
