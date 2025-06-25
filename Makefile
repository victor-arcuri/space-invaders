# Variáveis
CC = gcc
CFLAGS = -Wall -g -Iinclude

# [WIN] Configurações específicas para MinGW + Allegro 5.0.10
ifeq ($(OS),Windows_NT)
    TARGET = invaders.exe                    # [WIN] Nome do executável no Windows
    RM = del /Q                              # [WIN] Comando para deletar arquivos
    MKDIR = if not exist $(BUILDDIR) mkdir $(BUILDDIR)
    SEP = \

    ALLEGRO_VERSION = 5.0.10
    MINGW_VERSION = 4.7.0
    FOLDER = C:
    FOLDER_NAME = \allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
    PATH_ALLEGRO = $(FOLDER)$(FOLDER_NAME)
    LIB_ALLEGRO = \lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
    INCLUDE_ALLEGRO = \include

    ALLEGRO_FLAGS = -I$(PATH_ALLEGRO)$(INCLUDE_ALLEGRO)
    LIBS = $(PATH_ALLEGRO)$(LIB_ALLEGRO)
else
    TARGET = Space\ Invaders                # [LINUX] Nome do executável no Linux com espaço (usando barra invertida)
    RM = rm -f
    MKDIR = mkdir -p $(BUILDDIR)
    SEP = /

    ALLEGRO_FLAGS = $(shell pkg-config --cflags allegro-5 allegro_font-5 allegro_primitives-5 \
        allegro_image-5 allegro_audio-5 allegro_acodec-5)
    LIB_LINKS = $(shell pkg-config --libs allegro-5 allegro_font-5 allegro_primitives-5 \
        allegro_image-5 allegro_audio-5 allegro_acodec-5)
    LIBS = $(LIB_LINKS) -lm
endif

SRCDIR = src
BUILDDIR = build

# Lista dos arquivos-fonte
SRC = $(wildcard $(SRCDIR)$(SEP)*.c)

# Cria uma lista com o nome de todos os objetos .o no diretório build/
OBJ = $(patsubst $(SRCDIR)$(SEP)%.c, $(BUILDDIR)$(SEP)%.o, $(SRC))

# Regra padrão
all: clean $(BUILDDIR) $(TARGET)

# Criar o diretório build/, caso não exista
$(BUILDDIR):
	$(MKDIR)

# Linkar o executável
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Compilar .c para .o na pasta build
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(ALLEGRO_FLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	-$(RM) $(BUILDDIR)$(SEP)*.o
	-$(RM) $(TARGET)

#Executa o jogo após buildar
run: all
	./$(TARGET)

# Mostra que all, clean e run são comandos, não arquivos
.PHONY: all clean run

# COMANDOS
# make       - cria uma build nova do jogo, deletando a antiga
# make clean - apaga a build antiga
# make run   - cria uma build nova do jogo, deletando a antiga, e roda ela.
