/*
/     Atividade - AVL - Remoção
/     Disciplina: AEDS II - Prática
/     Letícia Santos Alves // R.A.: 2025.1.08.016
/   ﹒⌗﹒🦇﹒౨ৎ˚₊‧
*/

#include<stdio.h> 
#include<stdlib.h> 
#include "avl.h"
  
// Obtem a altura da AVL
int altura(struct Node *N) { 
    if (N == NULL) {
        return 0; 
    }
    return N->altura; 
} 
  
// Obtem o máximo entre dois inteiros
int max(int a, int b)  { 
    if (a < b) {
        return (b);
    } 
    return (a); 
} 
  
/* Cria um novo nó com apontadores esquerda e direita nulos */
struct Node* newNode(int valor) { 
    struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
    node->valor     = valor; 
    node->esquerda  = NULL; 
    node->direita   = NULL; 
    node->altura    = 1;  // Novo nó é adicionado como folha
    return(node); 
} 
  
// Faz a rotação a direita na raiz y
struct Node *direitaRotate(struct Node *y) { 
    struct Node *x = y->esquerda; 
    struct Node *T2 = x->direita; 
  
    // Realiza a rotação
    x->direita = y; 
    y->esquerda = T2; 
  
    // Atualiza as alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1; 
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1; 
  
    // Retorna a nova raiz
    return x; 
} 
  
// Faz a rotação a esquerda na raiz x
struct Node *esquerdaRotate(struct Node *x) { 
    struct Node *y = x->direita; 
    struct Node *T2 = y->esquerda; 

    // Realiza a rotação
    y->esquerda = x; 
    x->direita = T2; 

    // Atualiza as alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1; 
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1; 
  
    // Retorna a nova raiz
    return y; 
} 
  
// Obtem o fator de balanceamento para o nó N
int balanceamento(struct Node *N) { 
    if (N == NULL) {
        return 0; 
    }
    return (altura(N->esquerda) - altura(N->direita)); 
} 
  
// Função recursiva para inserir um novo item na árvore com raiz
// *Node e retorna a nova raiz da subárvore
struct Node* inserir(struct Node* node, int valor) { 
    /* 1.  Realiza a inserção normal de árvore binária */
    if (node == NULL) {
        return(newNode(valor)); 
    }
  
    if (valor < node->valor) {
        node->esquerda  = inserir(node->esquerda, valor); 
    } else if (valor > node->valor){ 
        node->direita = inserir(node->direita, valor); 
    } else { 
        // Valores duplicados não são permitidos na AVL
        return node; 
    }

    /* 2. Atualiza a altura de seu antecessor */
    node->altura = 1 + max(altura(node->esquerda), 
                        altura(node->direita)); 
  
    /* 3. Obtem o fator de balanceamento da raiz 
    para observar se a árvore continua balanceada */
    int balance = balanceamento(node); 
  
    // Se a árvore está desbalanceada, então existem quatro casos possíveis
  
    /* Caso esquerda esquerda
        T1, T2, T3 e T4 são sub-árvores.
          z                                      y 
         / \                                   /   \
        y   T4     Rotação direita (z)        x      z
       / \          - - - - - - - - ->      /  \    /  \ 
      x   T3                               T1  T2  T3  T4
     / \
    T1   T2                                              */
    if (balance > 1 && valor < node->esquerda->valor) {
        return direitaRotate(node); 
    }
  
    /* Caso direita direita
      z                                y
     /  \                            /   \ 
    T1   y   Rotação esquerda (z)   z      x
        /  \   - - - - - - - ->    / \    / \
       T2   x                     T1  T2 T3  T4
           / \
         T3  T4                                  */
    if (balance < -1 && valor > node->direita->valor) {
        return esquerdaRotate(node); 
    }

    /* Caso esquerda direita
         z                               z                              x
        / \                            /   \                           /  \ 
       y   T4  Rotação esquerda (y)   x    T4  Rotação direita (z)   y      z
      / \      - - - - - - - - ->    /  \       - - - - - - - ->    / \    / \
    T1   x                          y    T3                       T1  T2 T3  T4
        / \                        / \
      T2   T3                    T1   T2                                     */
    if (balance > 1 && valor > node->esquerda->valor) { 
        node->esquerda =  esquerdaRotate(node->esquerda); 
        return direitaRotate(node); 
    } 
  
    /* Caso direita esquerda
       z                            z                            x
      / \                          / \                          /  \ 
    T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
        / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
       x   T4                      T2   y                  T1  T2  T3  T4
      / \                              /  \
    T2   T3                           T3   T4                             */
    if (balance < -1 && valor < node->direita->valor) { 
        node->direita = direitaRotate(node->direita); 
        return esquerdaRotate(node); 
    } 
  
    /* retorna o ponteiro (não-atualizado) para a raiz */
    return node; 
} 

struct Node* valormin(struct Node* node) {
    struct Node* current = node;
 
    while (current->esquerda != NULL) {    // Loop para encontrar a folha mais à esquerda 
        current = current->esquerda;
    }
 
    return current;
}
 
// Função recursiva para remover um nó 
struct Node* remover(struct Node* raiz, int valor) {
 
    if (raiz == NULL) {
        printf("Valor %d não encontrado!\n", valor);
        return raiz;
    }
 
    if (valor < raiz->valor) {    // Se o valor for menor, desce pela esquerda
        raiz->esquerda = remover(raiz->esquerda, valor);
    }
    else if (valor > raiz->valor) {    // Se o valor for maior, desce pela direita
        raiz->direita = remover(raiz->direita, valor);
    }
    else {
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {    // Nó com 0 ou 1 filho
            struct Node* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
 
            if (temp == NULL) {    // Sem filhos
                temp = raiz;
                raiz = NULL;
            } else { // Com um filho
                *raiz = *temp; 
            }
            free(temp);
            printf("Valor %d removido!\n", valor);
        } else {
            struct Node* temp = valormin(raiz->direita);    // Nó com 2 filhos

            raiz->valor = temp->valor;
 
            raiz->direita = remover(raiz->direita, temp->valor);    // Remove o nó sucessor
        }
    }
 
    if (raiz == NULL) {    // Se a árvore tinha apenas um nó
        return raiz;
    }
 
    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    int balance = balanceamento(raiz);
 
    if (balance > 1 && balanceamento(raiz->esquerda) >= 0) {
        return direitaRotate(raiz);
    }
 
    if (balance > 1 && balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = esquerdaRotate(raiz->esquerda);
        return direitaRotate(raiz);
    }
 
    if (balance < -1 && balanceamento(raiz->direita) <= 0) {
        return esquerdaRotate(raiz);
    }
 
    if (balance < -1 && balanceamento(raiz->direita) > 0) {
        raiz->direita = direitaRotate(raiz->direita);
        return esquerdaRotate(raiz);
    }
 
    return raiz;
}
  
// Imprime os nós em ordem
void inOrder(struct Node *raiz) { 
    if(raiz != NULL) { 
        inOrder(raiz->esquerda); 
        printf("%d ", raiz->valor); 
        inOrder(raiz->direita); 
    } 
} 

int main() { 
    struct Node *raiz = NULL;
    int opcao, valor;

    raiz = inserir(raiz, 10); 
    raiz = inserir(raiz, 20); 
    raiz = inserir(raiz, 30); 
    raiz = inserir(raiz, 40); 
    raiz = inserir(raiz, 50); 
    raiz = inserir(raiz, 25); 
    
  /* A árvore AVL construída será
            30 
           /  \ 
         20   40 
        /  \    \ 
       10  25    50 
  
  A saida correta em pre-ordem é 30 20 10 25 40 50 */

    printf("\nBem-vindo ao sistema de árvores da Luthor Tech!\n");
    printf("\nA principio, já existem alguns valores na árvore,\nmas fique a vontade para modifica-la.");

    do {
        printf("\n\n============Menu============\n");
        printf("1- Inserir Valor;\n");
        printf("2- Remover Valor;\n");
        printf("3- Imprimir Árvore (Em ordem);\n");
        printf("0- Sair.\n");
        printf("==============================\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1; 
        }

        switch(opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                if (scanf("%d", &valor) != 1) {
                    printf("Entrada inválida!\n");
                    while (getchar() != '\n'); 
                    break;
                }
                raiz = inserir(raiz, valor);
                printf("Valor %d inserido!\n", valor);
                break;

            case 2:
                printf("Digite o valor a ser removido: ");
                if (scanf("%d", &valor) != 1) {
                    printf("Entrada inválida!\n");
                    while (getchar() != '\n'); 
                    break;
                }
                raiz = remover(raiz, valor);
                break;

            case 3:
                printf("\nÁrvore (em ordem): \n");
                if (raiz == NULL) {
                    printf("(Vazia)\n");
                } else {
                    inOrder(raiz);
                    printf("\n");
                }
                break;

            case 0:
                printf("\nA Luthor Tech agradece. Finalizando...\n\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0; 
}