#ifndef _H_FILA
#define _H_FILA

#include <stdbool.h>
#include <limits.h>

typedef struct no {
    int valor;
    struct no* proximo;
} No;

typedef struct fila {
    No* frente;
    No* fundo;
    int tam_atual;
} Fila;

Fila* criar_fila();
bool ehCheia(Fila* fila);
bool ehVazia(Fila* fila);
void enfileirar(Fila* fila, int item);
void desenfileirar(Fila* fila);
int obtem_elemento(Fila* fila);
void ver_fila(Fila* fila);
void liberar_fila(Fila* fila);

#endif  // _H_FILA