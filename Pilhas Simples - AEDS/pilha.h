#ifndef _H_PILHA
#define _H_PILHA

#include <stdbool.h>

struct pilha* criar_pilha();
bool ehVazia(struct pilha* pilha);
void push(struct pilha* pilha, int item);
int pop(struct pilha* pilha);
int obtem_elemento(struct pilha* pilha);
void ver(struct pilha* pilha);
void fim_pilha(struct pilha* pilha);

#endif // _H_PILHA