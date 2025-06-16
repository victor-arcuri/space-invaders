#ifndef CANHAO_H
#define CANHAO_H

#include <allegro5/allegro5.h>

#include "canhao.h"
#include "display.h"
#include "sprites.h"
#include "teclado.h"
#include "utilidades.h"
#include "nave.h"
#include "sons.h"

#define LIMITE_TIRO 35
#define MAX_VIDAS 6
typedef struct {
    int x, y;
    SPRITE sprite[2];
    int frame;
    bool ativo;
    int vel_y;
    bool explodindo;
    int count;
    int count_max;
    HITBOX hitbox;
    bool acertou;
    int contagem_tiros;
    int tiro_colisao_x;
    int tiro_colisao_y;
} TIRO;

typedef struct CANHAO {
    int x, y;
    SPRITE sprite;
    TIRO tiro;
    HITBOX hitbox;
    int vidas;
    bool ativo;
    bool acertado;
    SPRITE acertado_sprites[2];
    int acertado_frame;
    int acertado_contador_max;
    int acertado_contador_atual;
    int acertado_ciclos;

} CANHAO;

#define CANHAO_VEL 1
#define CANHAO_MAX_X (BUFFER_W - CANHAO_WIDTH)


CANHAO* iniciar_canhao(SPRITES* sprites);
void atualizar_canhao(AUDIO* audio, CANHAO* canhao, TECLADO* teclado, NAVES* naves,BARREIRA* barreiras, bool* perdeu_jogo);
void draw_canhao(CANHAO* canhao);
void finalizar_canhao(CANHAO* canhao);
void disparar_tiro_canhao(CANHAO* canhao, AUDIO* audio);
void atualizar_tiro_canhao(CANHAO* canhao);
void tiro_colidiu(CANHAO* canhao);
void tiro_terminou_colisao(CANHAO* canhao);
void draw_tiro_canhao(CANHAO* canhao);

void checa_nave_misterio(CANHAO* canhao, NAVES* naves, AUDIO* audio);

void canhao_acertado(CANHAO* canhao,AUDIO* audio);
void verifica_colisao_barreira_tiro_canhao(CANHAO* canhao, BARREIRA* barreiras);
#endif