#ifndef HUD_H
#define HUD_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "texto.h"
#include "canhao.h"
#include "pontos.h"
#include "sprites.h"

#define VIDAS_TEXTO_X 8
#define VIDAS_TEXTO_Y 234

#define SCORE_TEXTO_X 25
#define SCORE_TEXTO_Y 15


typedef struct HUD{
    int* score_atual;
    int* highscore;
    int* vidas;
    FONTE* fonte;
    SPRITE* sprite_canhao;
} HUD;

HUD* iniciar_hud(CANHAO* canhao, PONTOS* pontos, FONTE* fonte,SPRITES* sprites);
void finalizar_hud(HUD* hud);

void draw_hud(HUD* hud);

#endif