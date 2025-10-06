/*
/     Atividade - Árvores Binárias - Balanceamento de Árvores
/     Disciplina: AEDS II - Prática
/     Letícia Santos Alves // R.A.: 2025.1.08.016
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

    if (valor < root->valor) {        // Se o valor for menor, vai para a esquerda
        root->esquerda = remover(root->esquerda, valor);
    } else if (valor > root->valor) {     // Se o valor for maior, vai para a direita
        root->direita = remover(root->direita, valor);
    } else {
        if (root->esquerda == NULL) {     // Nó com um filho ou nenhum, (na direita)
            struct node* temp = root->direita;
            free(root);
            return temp;
        } else if (root->direita == NULL) {     // Nó com um filho ou nenhum, (na esquerda)
            struct node* temp = root->esquerda;
            free(root);
            return temp;
        }
        struct node* temp = valor_min(root->direita);   // Pega o menor valor da subarvore direita
        root->valor = temp->valor;
        root->direita = remover(root->direita, temp->valor);
    }
    return root;
}

// Conta os nós da árvore
int contar_nos(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + contar_nos(root->esquerda) + contar_nos(root->direita);
}

// Armazena os valores da árvore em um vetor, em ordem
void armazenar(struct node* no, int vetor[], int* indice) {
    if (no == NULL) {
        return;
    }
    armazenar(no->esquerda, vetor, indice);
    vetor[*indice] = no->valor;
    (*indice)++;
    armazenar(no->direita, vetor, indice);
}

// Constrói uma árvore balanceada a partir de um vetor ordenado
struct node* construir(int vetor[], int inicio, int fim) {
    if (inicio > fim) {
        return NULL;
    }

    int meio = inicio + (fim - inicio) / 2;
    struct node* root = novo_no(vetor[meio]);   // O meio do vetor se torna a raiz

    root->esquerda = construir(vetor, inicio, meio - 1);  // Recursivamente constrói a subárvore esquerda
    root->direita = construir(vetor, meio + 1, fim);  // Recursivamente constrói a subárvore direita

    return root;
}

// Função principal que orquestra o balanceamento
struct node* balancear(struct node* root) {
    if (root == NULL) {
        printf("A árvore está vazia. Nada para balancear.\n");
        return NULL;
    }

    int num_nos = contar_nos(root); // Conta os nós
    
    int* vetor = (int*)malloc(num_nos * sizeof(int));
    int indice = 0;
    armazenar(root, vetor, &indice);

    struct node* nova_raiz = construir(vetor, 0, num_nos - 1); // Constrói a árvore balanceada

    free(vetor); // Libera a memória

    return nova_raiz;
}

int main() {
    struct node* root = NULL;
    int opcao, valor;

    root = inserir(root, 30); // Para ser desbalanceada
    inserir(root, 70);
    inserir(root, 50);
    inserir(root, 40);
    inserir(root, 60);
    inserir(root, 80);
    inserir(root, 20);

    printf("\nBem-vindo ao sistema de árvores da Luthor Tech!\n");
    printf("\nA principio, já existem alguns valores na árvore,\nmas fique a vontade para modifica-la.");

    while (1) {
        printf("\n\n=================MENU=================\n");      // Menu para remover ou inserir valores. Fica mais fácil o teste
        printf("1- Inserir um valor;\n");   // Adicionado para fazer mais testes com valores diferentes
        printf("2- Remover um valor;\n");
        printf("3- Imprimir árvore (Em ordem);\n");     // Opção para imprimir a árvore em ordem
        printf("4- Imprimir árvore (Pré-ordem);\n");     // Opção para imprimir a árvore em pré-ordem
        printf("5- Imprimir árvore (Pós-ordem);\n");     // Opção para imprimir a árvore em pós-ordem
        printf("6- Imprimir árvore (Todas as ordens);\n");      // Opção para imprimir a árvore em todas as ordens
        printf("7- Balancear a árvore;\n");             // Opção para balancear a árvore
        printf("8- Sair.\n");
        printf("======================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nDigite o valor para ser adicionado: ");
                scanf("%d", &valor);
                root = inserir(root, valor);
                printf("Valor %d inserido.", valor);
                break;
            case 2:
                printf("\nDigite o valor para ser removido: ");
                scanf("%d", &valor);
                if (buscar(root, valor) != NULL) {
                    root = remover(root, valor);
                    printf("Valor %d removido.", valor);
                } else {
                    printf("Valor %d não encontrado.", valor);
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
                printf("\nIniciando balanceamento da árvore...\n");
                root = balancear(root);
                printf("Árvore balanceada com sucesso!");
                break;
            case 8:
                printf("\nA Luthor Tech agradece. Finalizando...\n\n");
                return 0;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
