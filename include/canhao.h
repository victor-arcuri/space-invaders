#ifndef CANHAO_H
#define CANHAO_H

#include <allegro5/allegro5.h>

#include "canhao.h"
#include "display.h"
#include "sprites.h"
#include "teclado.h"

typedef struct {
    int x, y;
    SPRITE sprite;

} CANHAO;

CANHAO* iniciar_canhao(SPRITE sprite);

void atualizar_canhao(CANHAO* canhao, TECLADO* teclado);

void draw_canhao(CANHAO* canhao);

void finalizar_canhao(CANHAO* canhao);

#endif