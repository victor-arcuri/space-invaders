# Variáveis
CC = gcc
CFLAGS = -Wall -g -Iinclude
ALLEGRO_FLAGS = $(shell pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)
LIBS = $(ALLEGRO_FLAGS) -lm

SRCDIR = src
BUILDDIR = build
TARGET = "Space Invaders"

# Lista dos arquivos-fonte
SRC = $(wildcard $(SRCDIR)/*.c)

# Cria uma lista com o nome de todos os objetos .o no diretório build/
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

# Regra padrão
all: clean $(BUILDDIR) $(TARGET)

# Criar o diretório build/, caso não exista
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Linkar o executável
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Compilar .c para .o na pasta build
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -rf $(BUILDDIR)/*
	rm -f $(TARGET)

#Executa o jogo após buildar
run: all
	$(TARGET)

# Mostra que all, clean e run são comandos, não arquivos
.PHONY: all clean run

# COMANDOS
# make       - cria uma build nova do jogo, deletando a antiga
# make clean - apaga a build antiga
# make run   - cria uma build nova do jogo, delentando a antiga, e roda ela.
