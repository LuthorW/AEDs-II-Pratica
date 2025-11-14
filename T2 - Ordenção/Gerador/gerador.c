#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

#define GIGABYTE (1024ULL * 1024 * 1024)

#define FILE_SIZE_BYTES (200ULL * 1024 * 1024) // TESTE: 200MB
//#define FILE_SIZE_BYTES (4ULL * GIGABYTE)

const char* NOME_ARQUIVO = "dados_desordenados.txt";

int main() {
    // "w" = write, modo texto
    FILE *arq_saida = fopen(NOME_ARQUIVO, "w"); 
    if (!arq_saida) {
        perror("Eita, não consegui criar o arquivo de saida.");
        return 1;
    }

    srand((unsigned int)time(NULL));    // Semente para os números aleatórios

    // Etimativa de quantos números
    unsigned long long total_nums = FILE_SIZE_BYTES / sizeof(long long);
    
    printf("Gerando ~%llu numeros aleatorios...\n", total_nums);
    printf("Arquivo de saida: %s\n", NOME_ARQUIVO);

    // Um buffer na RAM
    const size_t TAM_BUFFER = 1024 * 1024 / sizeof(long long); // ~1MB
    long long *buffer = (long long*)malloc(TAM_BUFFER * sizeof(long long));
    
    if (!buffer) {
        printf("Ih, faltou memoria pro buffer.\n");
        fclose(arq_saida);
        return 1;
    }

    for (unsigned long long i = 0; i < total_nums; ) {
        size_t nums_no_buffer = 0;
        for (size_t j = 0; j < TAM_BUFFER && i < total_nums; j++, i++, nums_no_buffer++) {
            long long num_aleatorio = ((long long)rand() << 32) | rand();
            buffer[j] = num_aleatorio;
        }

        for (size_t k = 0; k < nums_no_buffer; k++) {
            fprintf(arq_saida, "%lld\n", buffer[k]);    // %lld é o 'long long'
        }

        // Feedback de progresso
        if (i > 0 && (i % (total_nums / 100) == 0)) {
            printf("Progresso: %.1f%%\r", (double)i / total_nums * 100.0);
            fflush(stdout);
        }
    }

    free(buffer);
    fclose(arq_saida);
    printf("\nArquivo .txt gerado! Amo!\n");
    return 0;
}