
/*
    Atividade - Listas Simples
    Letícia Santos Alves // R.A.: 2025.1.08.016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

struct node {
    int data;
    struct node *next;
} *p, *tmp, *tmp1;

void inserir_fim(int elemento) {
    tmp = p;
    tmp1 = (struct node*) malloc(sizeof(struct node));
    tmp1->data = elemento;
    tmp1->next = NULL;
    if (p == NULL) {
        p = tmp1;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = tmp1;
    }
}

void inserir_inicio(int elemento) {
    tmp1 = (struct node*) malloc(sizeof(struct node));
    tmp1->data = elemento;
    tmp1->next = p;
    p = tmp1;
}

void apagar(int ele) {
    tmp = p;
    struct node *pre = tmp;
    while (tmp != NULL) {
        if (tmp->data == ele) {
            if (tmp == p) {
                p = tmp->next;
                free(tmp);
                return;
            } else {
                pre->next = tmp->next;
                free(tmp);
                return;
            }
        } else {
            pre = tmp;
            tmp = tmp->next;
        }
    }
    printf("\n Valor não encontrado! ");
}

void apagar_inicio() {
    tmp = p;
    if (p == NULL) {
        printf("\n Nenhum elemento deletado ");
    } else {
        printf("\nElemento deletado - %d", p->data);
        p = p->next;
    }
}

void apagar_fim() {
    tmp = p;
    struct node* pre;
    if (p == NULL) {
        printf("\n Nenhum elemento deletado ");
    } else if (p->next == NULL) {
        printf("\nElemento deletado - %d", p->data);
        p = NULL;
    } else {
        while (tmp->next != NULL) {
            pre = tmp;
            tmp = tmp->next;
        }
        pre->next = NULL;
        printf("\nElemento deletado - %d", tmp->data);
    }
}

bool ehVazia() {
    return (p == NULL);
}

void imprimir() {
    tmp = p;
    while (tmp != NULL) {
        printf("\n %d", tmp->data);
        tmp = tmp->next;
    }
}

int obter_primeiro(void) {
    if (p == NULL) {
        printf("\n Nenhum elemento encontrado ");
        return 0;
    } else {
        return (p->data);
    }
}

int obter_ultimo(void) {
    tmp = p;
    if (p == NULL) {
        printf("\n Nenhum elemento encontrado ");
        return 0;
    } else if (p->next == NULL) {
        return (p->data);
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        return (tmp->data);
    }
}
// Inserir em uma posição especifica.
void inserir_posicao(int valor, int posicao) {
    struct node* novo = (struct node*) malloc(sizeof(struct node));
    novo->data = valor;
    novo->next = NULL;

    if (posicao == 0) {
        novo->next = p;
        p = novo;
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
        free(novo);
        return;
    }

    novo->next = tmp->next;
    tmp->next = novo;
}
// Remover de uma posição especifica.
void remover_posicao(int posicao) {
    if (p == NULL) {
        printf("\nLista vazia!");
        return;
    }

    tmp = p;
    if (posicao == 0) {
        p = p->next;
        free(tmp);
        return;
    }

    int i = 0;
    struct node* pre = NULL;
    while (tmp != NULL && i < posicao) {
        pre = tmp;
        tmp = tmp->next;
        i++;
    }

    if (tmp == NULL) {
        printf("\nPosição inválida!");
        return;
    }

    pre->next = tmp->next;
    free(tmp);
}
// Obter o valor de uma posição especifica.
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
    printf("\nBem-vindo ao sistema de Listas da Luthor Tech!\n");
    do {
        printf("\n=============== MENU =================");
        printf("\n1.Inserir no fim");
        printf("\n2.Inserir no inicio");
        printf("\n3.Apagar um elemento em particular");
        printf("\n4.Apagar do inicio");
        printf("\n5.Apagar do fim");
        printf("\n6.Imprimir lista");
        printf("\n7.É vazia?");
        printf("\n8.Obter primeiro");
        printf("\n9.Obter último");
        printf("\n10.Inserir em posição");
        printf("\n11.Remover de posição");
        printf("\n12.Obter valor de posição");
        printf("\n0.Sair");
        printf("\nEntre sua opção : ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                printf("\nDigite o valor ");
                scanf("%d", &val);
                inserir_fim(val);
                break;
            case 2:
                printf("\nDigite o valor ");
                scanf("%d", &val);
                inserir_inicio(val);
                break;
            case 3:
                printf("\nDigite o valor ");
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
                    printf("\nLista vazia");
                else
                    printf("\nLista não vazia");
                break;
            case 8:
                val = obter_primeiro();
                if (val != 0)
                    printf("%d", val);
                break;
            case 9:
                val = obter_ultimo();
                if (val != 0)
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
                exit(0);
                break;
            default:
                printf("\n Opção errada!");
                break;
        }
    } while (1);
}
