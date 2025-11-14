# Automatizando o makefile

# Nome do projeto (nosso executável final)
PROJ_NAME=trabalho2

# --- Arquivos ---
C_SOURCE=trab.c
H_SOURCE=trab.h
OBJ=$(C_SOURCE:.c=.o)

# --- Compilador e Flags ---
CC=gcc

CC_FLAGS= -c \
          -Wall \
          -g \
          -pedantic \
          -O2

#########################
# Compilação e linkagem #
#########################

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	# $@ é o alvo (sorter)
	# $^ são os pré-requisitos (trab.o)
	$(CC) -o $@ $^

%.o: %.c $(H_SOURCE)
	# $< é o primeiro pré-requisito (trab.c)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~ bloco_*.txt dados_ordenados.txt