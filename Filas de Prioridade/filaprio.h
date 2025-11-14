#ifndef FILAPRIO_H
#define FILAPRIO_H

#define MAX_SIZE 8000

typedef struct {
    char nome[50];
    int idade; 
} Jog;

typedef struct { // Vetor Ordenado
    Jog jogs[MAX_SIZE]; 
    int n;
} PqVO; 

void init_vo(PqVO* q);
void insert_vo(PqVO* q, Jog j);
Jog remover_vo(PqVO* q);

typedef struct No { // Lista Encadeada Ordenada
    Jog jog; 
    struct No* prox;
} No;

typedef No* PqLO; 

void init_lo(PqLO* q); 
void insert_lo(PqLO* q, Jog j);
Jog remover_lo(PqLO* q); 

typedef struct { // Vetor Não Ordenado
    Jog jogs[MAX_SIZE]; 
    int n;
} PqVN; 

void init_vn(PqVN* q); 
void insert_vn(PqVN* q, Jog j);
Jog remover_vn(PqVN* q); 


#endif // FILAPRIO_H