#ifndef _H_FILA
#define _H_FILA

#include <stdbool.h>
#include <limits.h>

struct fila;

struct fila criar_fila(int tamanho);
bool ehCheia(struct fila fila);
bool ehVazia(struct fila fila);
struct fila enfileirar(struct fila fila, int item);
struct fila desenfileirar(struct fila fila);
int obtem_elemento(struct fila fila);
void ver_fila(struct fila fila);

#endif
