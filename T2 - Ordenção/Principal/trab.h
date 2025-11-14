/* 
Trabalho prático II - Ordenação

Disciplina: Algoritmos e Estruturas de Dados II.
Docente: Iago Augusto de Carvalho.

Integrantes do Grupo: 
- Beatriz Flausino Machado - 2024.2.08.005;
- Gustavo de Sousa Zimmermann - 2025.1.08.009; 
- Letícia Santos Alves - 2025.1.08.016;
- Luiz Gustavo Custódio Leite - 2025.1.08.031.

Universidade Federal de Alfenas.
Alfenas, 03 de novembro de 2025.

            ﹒⌗﹒🦇﹒౨ৎ˚₊‧
*/

#ifndef TRAB_H
#define TRAB_H

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <inttypes.h> 
#include <limits.h> 

typedef long long ItemType;

int comparar(const void *a, const void *b);

int dividir(const char* arq_entrada, int tam_bloco);

void intercalar(int qtd_blocos, const char* arq_saida);


#endif // TRAB_H