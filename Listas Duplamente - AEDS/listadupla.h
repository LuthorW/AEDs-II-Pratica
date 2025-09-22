#ifndef _H_LISTADUPLA
#define _H_LISTADUPLA

#include <stdbool.h>

void inserir_fim(int);
void inserir_inicio(int);
void apagar(int);
void apagar_inicio(void);
void apagar_fim(void);
bool ehVazia(void);
int obter_primeiro(void);
int obter_ultimo(void);
void imprimir();
void inserir_posicao(int valor, int posicao);
void remover_posicao(int posicao);
int obter_posicao(int posicao);

#endif // _H_LISTADUPLA
