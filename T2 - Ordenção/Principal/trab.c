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

#include "trab.h"

int comparar(const void *a, const void *b) {

    // Converte os ponteiros genéricos
    ItemType item_a = *(const ItemType *)a;
    ItemType item_b = *(const ItemType *)b;
    
    if (item_a < item_b) return -1; // a vem antes de b
    if (item_a > item_b) return 1;  // a vem depois de b
    return 0;
}

int dividir(const char* arq_entrada, int tam_bloco) { // Tamanho do bloco em número de itens
    FILE* arq_in = fopen(arq_entrada, "r");
    if (!arq_in) {
        perror("Não foi possível abrir o arquivo de entrada.");
        return 0;
    }

    ItemType* buffer = (ItemType*)malloc(tam_bloco * sizeof(ItemType)); 
    if (!buffer) {
        printf("Faltou memoria pro buffer (%d items).\n", tam_bloco);
        fclose(arq_in);
        return 0;
    }

    int idx_bloco = 0;
    int nums_lidos = 0;
    ItemType num;

    while (fscanf(arq_in, "%lld", &num) == 1) {     // Lê número por número
        buffer[nums_lidos] = num;
        nums_lidos++;

        if (nums_lidos == tam_bloco) {
            idx_bloco++;
            printf("Criando bloco %d (com %d items)...\n", idx_bloco, nums_lidos);
            
            qsort(buffer, nums_lidos, sizeof(ItemType), comparar); // Ordena o bloco lido

            char nome_bloco[50];
            sprintf(nome_bloco, "bloco_%d.txt", idx_bloco); // Salva como .txt

            FILE* arq_bloco = fopen(nome_bloco, "w");
            if (!arq_bloco) {
                printf("Erro ao criar arquivo %s!\n", nome_bloco);
                break;
            }

            for (int i = 0; i < nums_lidos; i++) {
                fprintf(arq_bloco, "%lld\n", buffer[i]); 
            }
            fclose(arq_bloco);
            
            nums_lidos = 0;
        }
    }

    if (nums_lidos > 0) { 
        idx_bloco++;
        printf("Criando ultimo bloco %d (com %d items)...\n", idx_bloco, nums_lidos);
        
        qsort(buffer, nums_lidos, sizeof(ItemType), comparar); // Ordena o bloco restante

        char nome_bloco[50];
        sprintf(nome_bloco, "bloco_%d.txt", idx_bloco); // Salva como .txt

        FILE* arq_bloco = fopen(nome_bloco, "w"); 
        if (arq_bloco) {
            for (int i = 0; i < nums_lidos; i++) {
                fprintf(arq_bloco, "%lld\n", buffer[i]);
            }
            fclose(arq_bloco);
        }
    }

    free(buffer);
    fclose(arq_in);

    printf("Total de blocos criados: %d\n", idx_bloco);
    return idx_bloco;
}

void intercalar(int qtd_blocos, const char* arq_saida) {
    // Vetor de ponteiros pros arquivos (um pra cada bloco)
    FILE** arqs_blocos = (FILE**)malloc(qtd_blocos * sizeof(FILE*));
    // Vetor pra guardar o número do topo de cada arquivo
    ItemType* nums_topo = (ItemType*)malloc(qtd_blocos * sizeof(ItemType));
    // Vetor pra saber se o bloco ainda tem números (1) ou já acabou (0)
    int* bloco_ativo = (int*)malloc(qtd_blocos * sizeof(int)); 

    if (!arqs_blocos || !nums_topo || !bloco_ativo) {
        printf("Erro de memoria na intercalacao.\n");
        return;
    }

    // Abre todos os blocos e lê o primeiro número de cada um
    for (int i = 0; i < qtd_blocos; i++) {
        char nome_bloco[50];
        sprintf(nome_bloco, "bloco_%d.txt", i + 1);
        arqs_blocos[i] = fopen(nome_bloco, "r");

        if (arqs_blocos[i] && fscanf(arqs_blocos[i], "%lld", &nums_topo[i]) == 1) {
            bloco_ativo[i] = 1; 
        } else {
            bloco_ativo[i] = 0;
            if(arqs_blocos[i]) fclose(arqs_blocos[i]);
        }
    }

    FILE* arq_final = fopen(arq_saida, "w"); // Arquivo final de saída
    if (!arq_final) {
        printf("Erro ao criar o arquivo de saida.\n"); // Caso dê erro
        return;
    }
    
    printf("Intercalando %d blocos de texto...\n", qtd_blocos);

    while (1) {
        ItemType menor_num = LLONG_MAX;
        int idx_menor = -1;

        // Acha o menor número entre todos os blocos ATIVOS
        for (int i = 0; i < qtd_blocos; i++) {
            if (bloco_ativo[i] && nums_topo[i] < menor_num) {
                menor_num = nums_topo[i];
                idx_menor = i;
            }
        }

        if (idx_menor == -1) {
            break; 
        }

        // Escreve o menor número no arquivo final
        fprintf(arq_final, "%lld\n", menor_num);

        // Puxa o próximo número do bloco que a gente tirou
        if (fscanf(arqs_blocos[idx_menor], "%lld", &nums_topo[idx_menor]) != 1) {
            bloco_ativo[idx_menor] = 0; 
            fclose(arqs_blocos[idx_menor]);
        }
    }

    fclose(arq_final);
    printf("Arquivo final ordenado salvo em: %s\n", arq_saida);

    for (int i = 0; i < qtd_blocos; i++) {
        char nome_bloco[50];
        sprintf(nome_bloco, "bloco_%d.txt", i + 1);
        remove(nome_bloco);
    }

    free(arqs_blocos);
    free(nums_topo);
    free(bloco_ativo);
}

int main() {
    const char* arq_entrada = "dados_desordenados.txt";
    const char* arq_saida = "dados_ordenados.txt";

    int tam_bloco = 6553600; 

    printf("\n\nBem-vindo ao ordenador externo da Luthor Corp!\n\n\n");
    
    printf("Lendo arquivo: %s\n", arq_entrada);
    printf("Usando blocos de %d numeros (%.2f MB de RAM por bloco)\n", 
            tam_bloco, (double)tam_bloco * sizeof(ItemType) / (1024*1024));
    
    clock_t inicio = clock();
    
    int qtd_blocos = dividir(arq_entrada, tam_bloco);
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nFase 1 (texto + qsort) concluida em %.2f segundos.\n\n", tempo);

    if (qtd_blocos > 0) {
        inicio = clock();
        
        intercalar(qtd_blocos, arq_saida);
        
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("\nFase 2 (texto) concluida em %.2f segundos.\n", tempo);
    }

    printf("\n\nProcesso concluído com sucesso!\nA Luthor Corp agradece.\n\n");
    return 0;
}
