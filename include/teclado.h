#ifndef TECLADO_H

#define TECLADO_H

#include <allegro5/allegro5.h>
#include "inicializacao.h"

typedef struct {
    unsigned char teclas[ALLEGRO_KEY_MAX];
} TECLADO;

TECLADO* iniciar_teclado();

void atualizar_teclado(ALLEGRO_EVENT* evento, TECLADO* teclado);

void finalizar_teclado(TECLADO* teclado);

#endif