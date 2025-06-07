#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inicializacao.h"

// Retorna mensagem de erro e encerra o jogo caso o objeto em análise não tenha sido inicializado corretamente.
void tenta_iniciar(bool teste, const char *descricao){
    if (teste) return;

    printf("Não foi possivel inicializar o(a) %s\n", descricao);
    exit(1);
}