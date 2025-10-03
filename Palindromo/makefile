# Define o compilador que será usado (geralmente gcc)
CC = gcc

# Define as flags de compilação
# -Wall: Ativa todos os avisos (warnings), o que é uma boa prática
# -g:    Inclui informações de depuração no executável
# -o:    É usado na regra de compilação para especificar o nome do arquivo de saída
CFLAGS = -Wall -g

# Define o nome do arquivo executável que será gerado
EXEC = verificador_palindromo

# Define o nome do seu arquivo de código-fonte .c
SRCS = teste.c

# Define o nome do arquivo de entrada padrão para o teste
INPUT_FILE = entrada.txt

#
# REGRAS DO MAKEFILE
#

# Regra 'all': é a regra padrão, executada quando você digita apenas "make"
# Ela compila o programa.
all: $(EXEC)

# Regra de compilação: ensina ao make como criar o executável a partir do código-fonte
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

# Regra 'clean': remove o arquivo executável e outros arquivos temporários
# Útil para limpar o diretório antes de enviar o projeto.
clean:
	rm -f $(EXEC)

# Regra 'run': um atalho para compilar e executar o programa com o arquivo de entrada
# Muito útil para testar rapidamente.
run: all
	./$(EXEC) $(INPUT_FILE)

# Declara que 'all', 'clean' e 'run' não são nomes de arquivos
.PHONY: all clean run