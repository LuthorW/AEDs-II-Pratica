/*
/     Atividade - Filas de Prioridade
/     Disciplina: AEDS II - Prática
/     Letícia Santos Alves // R.A.: 2025.1.08.016
/   ﹒⌗﹒🦇﹒౨ৎ˚₊‧
*/

#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <time.h>     
#include "filaprio.h" 

#define NUM_JOGADORES 8000
#define ARQUIVO_CSV "jogadores.csv"


// ===================================================================
// VETOR ORDENADO 
// ===================================================================

void init_vo(PqVO* q) { 
    q->n = 0;
}

void insert_vo(PqVO* q, Jog j) { 
    if (q->n >= MAX_SIZE) {
        printf("Erro: Fila cheia (VO)\n");
        return;
    }
    int i = q->n - 1;
    while (i >= 0 && q->jogs[i].idade > j.idade) { 
        q->jogs[i + 1] = q->jogs[i];
        i--;
    }
    q->jogs[i + 1] = j;
    q->n++;
}

Jog remover_vo(PqVO* q) { 
    if (q->n <= 0) {
        return (Jog){"Vazio", -1}; 
    }
    q->n--;
    return q->jogs[q->n]; 
}

// ===================================================================
// LISTA ENCADEADA ORDENADA
// ===================================================================

void init_lo(PqLO* q) {
    *q = NULL;
}

void insert_lo(PqLO* q, Jog j) { 
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro: Falha de alocação (LO)\n");
        return;
    }
    novo->jog = j; 

    No *atual = *q, *anterior = NULL;
    
    while (atual != NULL && atual->jog.idade > j.idade) { 
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) { 
        novo->prox = *q;
        *q = novo;
    } else { 
        novo->prox = atual;
        anterior->prox = novo;
    }
}

Jog remover_lo(PqLO* q) { 
    if (*q == NULL) {
        return (Jog){"Vazio", -1}; 
    }
    No* temp = *q;
    Jog j = temp->jog; 
    *q = (*q)->prox; 
    free(temp);
    return j; 
}


// ===================================================================
// VETOR NÃO ORDENADO 
// ===================================================================

void init_vn(PqVN* q) {
    q->n = 0;
}

void insert_vn(PqVN* q, Jog j) { 
    if (q->n >= MAX_SIZE) {
        printf("Erro: Fila cheia (VN)\n");
        return;
    }
    q->jogs[q->n] = j; 
    q->n++;
}

Jog remover_vn(PqVN* q) { 
    if (q->n <= 0) {
        return (Jog){"Vazio", -1};
    }

    int max_idx = 0;
    for (int i = 1; i < q->n; i++) {
        if (q->jogs[i].idade > q->jogs[max_idx].idade) { 
            max_idx = i;
        }
    }
    
    Jog max_jog = q->jogs[max_idx];
    q->jogs[max_idx] = q->jogs[q->n - 1];
    q->n--; 

    return max_jog;
}


int carregar_jogs(Jog* jogs_teste) { 
    FILE* f = fopen("jogadores.csv", "r");
    if (f == NULL) {
        printf("Erro: Não foi possível abrir o arquivo %s.\n", ARQUIVO_CSV);
        return 0;
    }
    char buffer[256];
    int count = 0;
    fgets(buffer, sizeof(buffer), f);

    while (count < NUM_JOGADORES && fgets(buffer, sizeof(buffer), f)) {
        int result = sscanf(buffer, "%49[^,],%*[^,],%*[^,],%*[^,],%d",
               jogs_teste[count].nome,
               &jogs_teste[count].idade);
        if (result == 2) {
            count++;
        }
    }
    fclose(f);
    return 1;
}

int main() {
    Jog* jogs_teste = malloc(NUM_JOGADORES * sizeof(Jog)); 
    if (!jogs_teste || !carregar_jogs(jogs_teste)) { 
        printf("Erro ao carregar dados. Encerrando.\n");
        if (jogs_teste) free(jogs_teste);
        return 1;
    }

    printf("========================================================================\n");
    printf("\nBem-vindo ao sistema de filas de prioridade da Luthor Tech!\n");
    printf("\nA principio, já existem jogadores carregados, mas fique a\nvontade para alterações.\n");

    printf("\nBenchmark iniciado com capacidade para %d jogadores.\nAbrindo o arquivo '%s'...\n\n",
           NUM_JOGADORES, ARQUIVO_CSV);

    clock_t start, end;
    double cpu_time;
    Jog jog_removido; 

    // Teste 1: Vetor Ordenado
    PqVO pq_vo; 
    init_vo(&pq_vo); 
    start = clock();
    for (int i = 0; i < NUM_JOGADORES; i++) {
        insert_vo(&pq_vo, jogs_teste[i]); 
    }
    for (int i = 0; i < NUM_JOGADORES; i++) {
        jog_removido = remover_vo(&pq_vo); 
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo (Vetor Ordenado): \t%f segundos\n", cpu_time);

    // Teste 2: Lista Encadeada Ordenada
    PqLO pq_lo; 
    init_lo(&pq_lo); 
    start = clock();
    for (int i = 0; i < NUM_JOGADORES; i++) {
        insert_lo(&pq_lo, jogs_teste[i]); 
    }
    for (int i = 0; i < NUM_JOGADORES; i++) {
        jog_removido = remover_lo(&pq_lo); 
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo (Lista Ordenada): \t%f segundos\n", cpu_time);

    // Teste 3: Vetor Não Ordenado
    PqVN pq_vn; 
    init_vn(&pq_vn); 
    start = clock();
    for (int i = 0; i < NUM_JOGADORES; i++) {
        insert_vn(&pq_vn, jogs_teste[i]); 
    }
    for (int i = 0; i < NUM_JOGADORES; i++) {
        jog_removido = remover_vn(&pq_vn); 
    }
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo (Vetor Nao Ordenado): \t%f segundos\n", cpu_time);

    printf("\n========================================================================\n");

    free(jogs_teste);
    return 0;
}