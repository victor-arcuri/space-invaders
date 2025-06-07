#ifndef SPRITE_H
#define SPRITE_H

#include <allegro5/allegro5.h>
#include "inicializacao.h"

typedef struct {
    ALLEGRO_BITMAP* bitmap;
    int width, height;
} SPRITE;

typedef struct {
    ALLEGRO_BITMAP* _og_sheet;
    
    SPRITE* canhao;

} SPRITES;

SPRITE* pegar_sprite(ALLEGRO_BITMAP* spritesheet, int x, int y, int w, int h);

SPRITES* iniciar_sprites();

void finalizar_sprites(SPRITES* sprites);

#endif