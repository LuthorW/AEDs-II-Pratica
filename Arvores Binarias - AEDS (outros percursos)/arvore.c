/*
/    Atividade - Árvores Binárias - Pré e Pós ordem
/    Disciplina: AEDS II - Prática
/    Letícia Santos Alves // R.A.: 2025.1.08.016
/   ﹒⌗﹒🦇﹒౨ৎ˚₊‧
*/

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// Cria um novo nó na árvore
struct node* novo_no(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->valor = item;
    temp->esquerda = temp->direita = NULL;
    return temp;
}

// Imprime a árvore na ordem: esquerda, raiz, direita
void ordem(struct node* root) {
    if (root != NULL) {
        ordem(root->esquerda);
        printf("%d ", root->valor);
        ordem(root->direita);
    }
}

// Imprime a árvore em pré-ordem: raiz, esquerda, direita
void pre_ordem(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->valor);
        pre_ordem(root->esquerda);
        pre_ordem(root->direita);
    }
}

// Imprime a árvore em pós-ordem: esquerda, direita, raiz
void pos_ordem(struct node* root) {
    if (root != NULL) {
        pos_ordem(root->esquerda);
        pos_ordem(root->direita);
        printf("%d ", root->valor);
    }
}

// Inserir novo nó com determinado
// valor na árvore binária
struct node* inserir(struct node* node, int valor) {
    if (node == NULL) {
        return novo_no(valor);
    }
    if (valor < node->valor) {
        node->esquerda = inserir(node->esquerda, valor);
    } else if (valor > node->valor) {
        node->direita = inserir(node->direita, valor);
    }
    return node;
}

// Procura por um valor na árvore
struct node* buscar(struct node* root, int valor) {
    if (root == NULL || root->valor == valor) {
        return root;
    }
    if (root->valor < valor) {
        return buscar(root->direita, valor);
    }
    return buscar(root->esquerda, valor);
}

// Retorna o nó com o menor valor.
struct node* valor_min(struct node* node) { 
    struct node* atual = node;
    while (atual && atual->esquerda != NULL) {      // Desce pela esquerda até o fim
        atual = atual->esquerda;
    }
    return atual;
}

// Remove um nó da árvore
struct node* remover(struct node* root, int valor) {
    if (root == NULL) {         // Se a árvore estiver vazia
        return root;
    }

    if (valor < root->valor) {           // Se o valor for menor, vai para a esquerda
        root->esquerda = remover(root->esquerda, valor);
    } else if (valor > root->valor) {        // Se o valor for maior, vai para a direita
        root->direita = remover(root->direita, valor);
    } else {
        if (root->esquerda == NULL) {      // Nó com um filho ou nenhum, (na direita)
            struct node* temp = root->direita; 
            free(root);
            return temp;
        } else if (root->direita == NULL) {     // Nó com um filho ou nenhum, (na esquerda)
            struct node* temp = root->esquerda;
            free(root);
            return temp;
        }
        struct node* temp = valor_min(root->direita);    // Pega o menor valor da subarvore direita
        root->valor = temp->valor;  
        root->direita = remover(root->direita, temp->valor);
    }
    return root;
}

int main() {
    struct node* root = NULL;
    int opcao, valor;

    root = inserir(root, 50);
    inserir(root, 30);
    inserir(root, 20);
    inserir(root, 40);
    inserir(root, 70);
    inserir(root, 60);
    inserir(root, 80);

     printf("\nBem-vindo ao sistema de árvores da Luthor Tech!\n");
     printf("\nA principio, já existem alguns valores na árvore,\nmas fique a vontade para modifica-la.");

    while (1) {
        printf("\n\n=================MENU=================\n");     // Menu para remover ou inserir valores. Fica mais fácil o teste
        printf("1- Inserir um valor;\n");   // Adicionado para fazer mais testes com valores diferentes
        printf("2- Remover um valor;\n");
        printf("3- Imprimir árvore (Em ordem);\n");    // Opção para imprimir a árvore em ordem
        printf("4- Imprimir árvore (Pré-ordem);\n");    // Opção para imprimir a árvore em pré-ordem
        printf("5- Imprimir árvore (Pós-ordem);\n");    // Opção para imprimir a árvore em pós-ordem
        printf("6- Imprimir árvore (Todas as ordens);\n");     // Opção para imprimir a árvore em todas as ordens
        printf("7- Sair.\n");
        printf("======================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para ser adicionado: ");
                scanf("%d", &valor);
                root = inserir(root, valor);
                printf("Valor %d inserido.\n", valor); 
                break;
            case 2:
                printf("Digite o valor para ser removido: ");
                scanf("%d", &valor);
                if (buscar(root, valor) != NULL) {
                    root = remover(root, valor);
                    printf("Valor %d removido.\n", valor);
                } else {
                    printf("Valor %d não encontrado.\n", valor);
                }
                break;
             case 3:
                printf("\nÁrvore (em ordem): ");
                ordem(root);
                printf("\n");
                break;
            case 4:
                printf("\nÁrvore (em pré-ordem): ");
                pre_ordem(root);
                printf("\n");
                break;
            case 5:
                printf("\nÁrvore (em pós-ordem): ");
                pos_ordem(root);
                printf("\n");
                break;
            case 6:
                printf("\nEm ordem:      ");
                ordem(root); //
                printf("\nEm pré-ordem:  ");
                pre_ordem(root);
                printf("\nEm pós-ordem:  ");
                pos_ordem(root);
                break;
            case 7:
                printf("\nA Luthor Tech agradece. Finalizando...\n\n");
                return 0; 
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
