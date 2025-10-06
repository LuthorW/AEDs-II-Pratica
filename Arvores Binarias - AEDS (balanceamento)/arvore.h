#ifndef _H_ARVORE
#define _H_ARVORE

struct node {
    int valor;
    struct node *esquerda, *direita;
};

struct node* novo_no(int item);
struct node* inserir(struct node* node, int valor);
struct node* buscar(struct node* root, int valor);
struct node* remover(struct node* root, int valor);
void ordem(struct node* root);
void pre_ordem(struct node* root);
void pos_ordem(struct node* root);
int contar_nos(struct node* root);
void armazenar(struct node* no, int vetor[], int* indice);
struct node* construir(int vetor[], int inicio, int fim);
struct node* balancear(struct node* root);

#endif // _H_ARVORE