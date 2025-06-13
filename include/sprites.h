#ifndef SPRITE_H
#define SPRITE_H

#include <allegro5/allegro5.h>
#include "inicializacao.h"

#define CANHAO_X 1
#define CANHAO_Y 49
#define CANHAO_WIDTH 16
#define CANHAO_HEIGHT 8

#define TIRO_CANHAO_X 55
#define TIRO_CANHAO_Y 49
#define TIRO_CANHAO_WIDTH 1
#define TIRO_CANHAO_HEIGHT 8

#define TIRO_CANHAO_EXPLOSAO_X 58
#define TIRO_CANHAO_EXPLOSAO_Y 49
#define TIRO_CANHAO_EXPLOSAO_WIDTH 8
#define TIRO_CANHAO_EXPLOSAO_HEIGHT 8

#define NAVE_EXPLOSAO_X 55
#define NAVE_EXPLOSAO_Y 1
#define NAVE_EXPLOSAO_WIDTH 16
#define NAVE_EXPLOSAO_HEIGHT 8
typedef struct {
    ALLEGRO_BITMAP* bitmap;
    
    int width, height;

} SPRITE;

typedef struct {
    ALLEGRO_BITMAP* _og_sheet;
    
    SPRITE canhao;

    SPRITE nave_1[2];
    SPRITE nave_2[2];
    SPRITE nave_3[2];

    SPRITE nave_misterio[2];

    SPRITE tiro_canhao[2];

    SPRITE nave_explosao;

    SPRITE tiro_1[4];
    SPRITE tiro_2[4];
    SPRITE tiro_3[4];
    SPRITE tiro_explosao;

    SPRITE barreira;

    SPRITE teclas[43];


} SPRITES;

SPRITE pegar_sprite(ALLEGRO_BITMAP* spritesheet, int x, int y, int w, int h);

SPRITES* iniciar_sprites();

void finalizar_sprites(SPRITES* sprites);

#endif