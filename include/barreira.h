#ifndef BARREIRA_H
#define BARREIRA_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "utilidades.h"
#include "inicializacao.h"
#include "display.h"
#include "sprites.h"

#define LINHA_VARREDURA_Y 233

#define BARREIRA_1_X 31
#define BARREIRA_1_Y 192

#define BARREIRA_2_X 76
#define BARREIRA_2_Y 192

#define BARREIRA_3_X 121
#define BARREIRA_3_Y 192

#define BARREIRA_4_X 166
#define BARREIRA_4_Y 192

#define BARREIRA_WIDTH 24
#define BARREIRA_HEIGHT 16
typedef struct {
    ALLEGRO_BITMAP* bitmap;
    ALLEGRO_BITMAP* bitmap_editavel;
} LINHA;


typedef struct {
    ALLEGRO_BITMAP* bitmap_original;
    ALLEGRO_BITMAP* bitmap_editavel;
    int x,y;
    HITBOX hitbox;

} BARREIRA;

LINHA* iniciar_linha_varredura();

void draw_linha(LINHA* linha);

BARREIRA* iniciar_barreiras(SPRITES* sprites);
void finalizar_barreiras(BARREIRA* barreiras);
void draw_barreiras(BARREIRA* barreiras);
void danificar_barreira(ALLEGRO_BITMAP* bitmask, BARREIRA barreira, int local_x, int local_y);

bool checa_integridade_posicao(BARREIRA barreira, int x, int y);
void danificar_linha(int x, LINHA* linha);
#endif