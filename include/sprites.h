#ifndef SPRITE_H
#define SPRITE_H

#include <allegro5/allegro5.h>
#include "inicializacao.h"


typedef struct {
    ALLEGRO_BITMAP* _og_sheet;
    
    ALLEGRO_BITMAP* canhao;

} SPRITES;

ALLEGRO_BITMAP* pegar_sprite(ALLEGRO_BITMAP* spritesheet, int x, int y, int w, int h);

SPRITES* iniciar_sprites();

void finalizar_sprites(SPRITES* sprites);

#endif