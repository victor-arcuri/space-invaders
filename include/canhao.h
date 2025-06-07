#ifndef CANHAO_H
#define CANHAO_H

#include <allegro5/allegro5.h>

#include "canhao.h"
#include "display.h"
#include "sprites.h"
#include "teclado.h"

typedef struct {
    int x, y;
    SPRITE* sprite;

} CANHAO;

#endif