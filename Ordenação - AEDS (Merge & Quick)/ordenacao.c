/*
/     Atividade - Ordenação - Merge Sort e Quick Sort
/     Disciplina: AEDS II - Prática
/     Letícia Santos Alves // R.A.: 2025.1.08.016
/   ﹒⌗﹒🦇﹒౨ৎ˚₊‧
*/

#include<stdio.h> 
#include<stdlib.h> 
#include "ordenacao.h"
  
// Imprime um vetor de inteiros
void imprimir(int *vetor) {
    int i;
    for (i = 0; i < 50; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void bubble(int *vetor) {
    int i, j, temp;
    int n = 50; 

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j+1]) {
                temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
    imprimir(vetor);
    return;
}

void selection(int *vetor) {
    int i, j, min, temp;
    int n = 50;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[min]) { 
                min = j; 
            }
        }
        
        if (min != i) {     // Troca o menor elemento
            temp = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = temp;
        }
    }
    imprimir(vetor);
    return;
}

void insertion(int *vetor) {
    int i, j, valor;
    int n = 50;

    for (i = 1; i < n; i++) {
        valor = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > valor) {    // Move os elementos maiores para frente
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        vetor[j + 1] = valor;
    }

    imprimir(vetor);
    return;
}

void merge_vet(int *V, int inicio, int meio, int fim) {
    int tamanho = fim - inicio + 1;
    int *temp = (int *)malloc(tamanho * sizeof(int));

    int p1 = inicio;
    int p2 = meio + 1;
    int fim1 = 0, fim2 = 0;
    int i;

    for (i = 0; i < tamanho; i++) {
        if (!fim1 && !fim2) {
            if (V[p1] < V[p2]) {
                temp[i] = V[p1];
                p1++;
            } else {
                temp[i] = V[p2];
                p2++;
            }

            if (p1 > meio) fim1 = 1;
            if (p2 > fim) fim2 = 1;
        } else {
            if (!fim1) {      // Copia o que sobrar
                temp[i] = V[p1];
                p1++;
            } else {
                temp[i] = V[p2];
                p2++;
            }
        }
    }

    for (i = 0; i < tamanho; i++) {
        V[inicio + i] = temp[i];
    }

    free(temp);
}

void merge_rec(int *V, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        // Chama a função para as duas metades
        merge_rec(V, inicio, meio);
        merge_rec(V, meio + 1, fim);

        merge_vet(V, inicio, meio, fim);    // Combina as duas metades
    }
}

void merge(int *vetor) {
    merge_rec(vetor, 0, 49);
    imprimir(vetor);
    return;
}

int particiona(int *V, int inicio, int fim) {
    int esq = inicio;
    int dir = fim;
    int pivo = V[inicio];
    int aux;

    while (esq < dir) {
        while (esq <= fim && V[esq] <= pivo) esq++;    // Avança posição da esquerda

        while (V[dir] > pivo) dir--;

        if (esq < dir) {    // Troca esquerda e direita
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        }
    }

    V[inicio] = V[dir];
    V[dir] = pivo;

    return dir; // Retorna índice
}

void quick_rec(int *V, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(V, inicio, fim);    // Divide os dados em duas partições

        quick_rec(V, inicio, pivo - 1);
        quick_rec(V, pivo + 1, fim);
    }
}

void quick(int *vetor) {
    quick_rec(vetor, 0, 49);
    imprimir(vetor);
    return;
}

int main() { 
  // Vetor aleatório de 50 posições
  
  int n;
  do {
    int vetor[50] = {40, 32, 24, 25,  1, 48, 38,  7, 17,  8, 42,  4, 44, 45, 27, 49, 30, 18,  6, 23,  5, 41, 33, 26, 28,  3, 37, 19, 11, 43, 39, 16, 36, 21,  9,  2, 47, 12, 50, 20, 14, 29, 35, 46, 13, 34, 31, 15, 10, 2};
    printf("\n\n\n******************** Escolha seu algoritmo *******************");
	printf("\n1- Bubble sort;");
	 printf("\n2- Selection sort;");
	 printf("\n3- Insertion sort;");
     printf("\n4- Merge sort;");
     printf("\n5- Quick sort;");
     printf("\n0- Sair.");
	 printf("\nEntre sua opção : ");
	 scanf("%d",&n);
	 switch(n) {
        case 1: bubble(vetor);
			    break;
		case 2: selection(vetor);
			    break;
		case 3: insertion(vetor);
			    break;
        case 4: merge(vetor);
			    break;
        case 5: quick(vetor);
			    break;
        case 0: exit(0);
		 	    break;
		default: printf("\n Opção errada!");
		 	    break;
		}
	} while(1);

  return 0; 
} 