/* 
Trabalho prático II - Palíndromos

Disciplina: Algoritmos e Estruturas de Dados II.
Docente: Iago Augusto de Carvalho.

Integrantes do Grupo: 
- Gustavo de Sousa Zimmermann - 2025.1.08.009; 
- Letícia Santos Alves - 2025.1.08.016;
- Luiz Gustavo Custódio Leite - 2025.1.08.031.

Universidade Federal de Alfenas.
Alfenas, 23 de setembro de 2025.
*/

#include "palindromo.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Cria uma lista vazia
Lista* criar_lista() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->inicio = NULL;
    return l;
}

// Cria uma pilha vazia
Pilha* criar_pilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

// Cria uma fila vazia
Fila* criar_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

// Insere um caractere no começo da lista
void inserir_lista(Lista* l, char c) {
    No* novo_no = (No*) malloc(sizeof(No));
    novo_no->dado = c;
    novo_no->proximo = l->inicio;
    l->inicio = novo_no;
}

// Empilha um caractere no topo
void empilhar(Pilha* p, char c) {
    No* novo_no = (No*) malloc(sizeof(No));
    novo_no->dado = c;
    novo_no->proximo = p->topo;
    p->topo = novo_no;
}

// Enfileira um caractere no final
void enfileirar(Fila* f, char c) {
    No* novo_no = (No*) malloc(sizeof(No));
    novo_no->dado = c;
    novo_no->proximo = NULL;
    if (fila_vazia(f)) {
        f->inicio = f->fim = novo_no;
    } else {
        f->fim->proximo = novo_no;
        f->fim = novo_no;
    }
}

// Retira e retorna o topo da pilha
char desempilhar(Pilha* p) {
    if (pilha_vazia(p)) return '\0';
    No* temp = p->topo;
    char dado = temp->dado;
    p->topo = p->topo->proximo;
    free(temp);
    return dado;
}

// Retira e retorna o primeiro da fila
char desenfileirar(Fila* f) {
    if (fila_vazia(f)) return '\0';
    No* temp = f->inicio;
    char dado = temp->dado;
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) f->fim = NULL;
    free(temp);
    return dado;
}

// Funções pra verificar se pilha ou fila estão vazias
bool pilha_vazia(Pilha* p) { return p->topo == NULL; }
bool fila_vazia(Fila* f) { return f->inicio == NULL; }

// Libera toda a memória da lista.
void destruir_lista(Lista* l) {
    No* atual = l->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(l);
}

//  Libera toda a memória da pilha
void destruir_pilha(Pilha* p) {
    while (!pilha_vazia(p)) desempilhar(p);
    free(p);
}

// Libera toda a memória da fila
void destruir_fila(Fila* f) {
    while(!fila_vazia(f)) desenfileirar(f);
    free(f);
}

// Função que normaliza a string, tirando acentos e deixando tudo minúsculo. 
// Ou seja, tudo fica padronizado.
void norma_string(const char* entrada, char* saida) {  
    int j = 0;
    for (int i = 0; entrada[i] != '\0'; ) {
        unsigned char c = entrada[i];

        if ((unsigned char)c >= 0xC3) {
            unsigned char next = entrada[i+1];
            // Verifica combinações de bytes que representam letras acentuadas
            // á à â ã , Á À Â Ã (em ordem)
            if ((c == 0xC3 && (next == 0xA1 || next == 0xA0 || next == 0xA2 || next == 0xA3 ||
                               next == 0x81 || next == 0x80 || next == 0x82 || next == 0x83))) {
                saida[j++] = 'a';
                i += 2;
                continue;
            }
            //                           é              ê               É               Ê 
            else if (c == 0xC3 && (next == 0xA9 || next == 0xAA || next == 0x89 || next == 0x8A)) {
                saida[j++] = 'e';
                i += 2;
                continue;
            }
            //                          í               Í   
            else if (c == 0xC3 && (next == 0xAD || next == 0x8D)) {
                saida[j++] = 'i';
                i += 2;
                continue;
            }
            // ó ô õ (B3, B4, B5)
            // Ó Ô Õ (93, 94, 95)
            else if (c == 0xC3 && (next == 0xB3 || next == 0xB4 || next == 0xB5 ||
                                   next == 0x93 || next == 0x94 || next == 0x95)) {
                saida[j++] = 'o';
                i += 2;
                continue;
            }
            //                          ú               Ú
            else if (c == 0xC3 && (next == 0xBA || next == 0x9A)) {
                saida[j++] = 'u';
                i += 2;
                continue;
            }
            //                          ç               Ç 
            else if (c == 0xC3 && (next == 0xA7 || next == 0x87)) {
                saida[j++] = 'c';
                i += 2;
                continue;
            }
        }
        // Se for letra ou número normal, copia para saída em minúsculo
        if (isalnum((unsigned char)c)) {
            saida[j++] = tolower((unsigned char)c);
        }
        i++;
    }
    saida[j] = '\0';
}

// Função principal que checa se uma linha é palíndromo
int eh_palindromo(const char* linha) {
    char texto_limpo[1024];
    norma_string(linha, texto_limpo); // limpa a string original

    if (strlen(texto_limpo) == 0) {
        return 1;
    }

    // Cria lista, pilha e fila para armazenar os caracteres
    Lista* lista = criar_lista();
    Pilha* pilha = criar_pilha();
    Fila* fila = criar_fila();
    for (int i = 0; texto_limpo[i] != '\0'; i++) {
        inserir_lista(lista, texto_limpo[i]);
        empilhar(pilha, texto_limpo[i]);
        enfileirar(fila, texto_limpo[i]);
    }

    // Compara retirando da pilha (inverso) e da fila (normal)
    bool resultado = true;
    while (!fila_vazia(fila)) {
        if (desempilhar(pilha) != desenfileirar(fila)) {
            resultado = false;
            break;
        }
    }

    destruir_lista(lista);
    destruir_pilha(pilha);
    destruir_fila(fila);

    return resultado ? 1 : 0;
}

int main() {
    char linha[1024];
    FILE* arquivo; // Variável com o nome "arquivo" que deve ser aberta, no caso é a "entrada.txt"

    arquivo = fopen("entrada.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo.");
        return 1;
    }

    while (1) {
        int i = 0;
        int c;

        // Lê caractere por caractere até achar \n ou EOF
        while (i < 1024 - 1) {
            c = fgetc(arquivo);

            if (c == EOF) break;
            if (c == '\n') break;

            linha[i++] = c;
        }
        linha[i] = '\0'; 

        // Se chegou no fim do arquivo, sai do loop
        if (i == 0 && c == EOF) {
            break;
        }

        // Chama a função que verifica palíndromos
        int resultado = eh_palindromo(linha);
        printf("%d\n", resultado);

        // Se o último caractere lido foi o fim do arquivo, sai do loop
        if (c == EOF) { 
            break;
        }
    }

    fclose(arquivo);
    return 0;
}
