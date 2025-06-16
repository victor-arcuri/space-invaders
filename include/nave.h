#ifndef NAVE_H
#define NAVE_H

#include <allegro5/allegro5.h>

#include "sprites.h"
#include "display.h"
#include "inicializacao.h"
#include "utilidades.h"
#include "barreira.h"
#include "pontos.h"
#include "sons.h"

#define LINHAS 5
#define COLUNAS 11
#define X_INICIAL 24
#define Y_INICIAL 64
#define Y_FINAL (BUFFER_H - 17)
#define ESPACAMENTO_VERTICAL 8

struct CANHAO;
typedef struct CANHAO CANHAO;


typedef enum {
    TIPO_1 = 1,
    TIPO_2 = 2,
    TIPO_3 = 3
} TIPO_TIRO_NAVE;

typedef struct {
    int x,y,w,h;
    bool ativo;
    HITBOX hitbox;
    SPRITE sprites[5];
    int frame;
    int contador_explosao_max;
    int contador_explosao_atual;
    bool acertado;
    int colisao_x, colisao_y;
} TIRO_NAVE;


typedef struct {
    int tiros_ativos;
    int tiros_max;
    TIRO_NAVE* tiros;
} TIROS_NAVE;



typedef enum {
    NAVE_1 = 1,
    NAVE_2 = 2,
    NAVE_3 = 3,
    MISTERIO = 4,
} TIPO;

typedef struct {
    int x,y,w,h;
    int frame;
    TIPO tipo;
    SPRITE sprites[3];
    bool viva;
    HITBOX hitbox;
    bool acertou;
} NAVE;

typedef struct {
    int vel_x, vel_y;
    NAVE naves[5][11];
    NAVE nave_misterio;
    int delay_movimento;
    int contador_movimento;
    int total_vivas;
    int min_delay, max_delay;
    int explosao_contador_atual,explosao_contador_max;
    bool em_movimento;
    int delay_movimento_misterio;
    int contador_movimento_misterio;
    int dir_nave_misterio;
    int misterio_explosao_contador, misterio_explosao_contador_max;
    float velocidade_jogo;
    bool stun;
    TIROS_NAVE* tiros;
    int audio_movimento_contagem;

} NAVES;

NAVES* iniciar_naves(SPRITES* sprites, float velocidade_jogo);

void draw_nave(NAVE nave);

void draw_naves(NAVES* naves);

void atualizar_naves(AUDIO* audio, NAVES* naves, CANHAO* canhao, SPRITES* sprites, BARREIRA* barreiras, LINHA* linha, PONTOS* pontos, bool* perdeu_jogo, bool* venceu_jogo);

void finalizar_naves(NAVES* naves);

void criar_nave_misterio(NAVES* naves, AUDIO* audio);

void atualizar_nave_misterio(NAVES* naves, CANHAO* canhao, PONTOS* pontos, AUDIO* audio);


TIROS_NAVE* iniciar_tiros_nave();

void finalizar_tiros_nave(TIROS_NAVE* tiros);

void tenta_disparar_nave(TIROS_NAVE* tiros, NAVE nave, SPRITES* sprites);

void atualizar_tiros_nave(TIROS_NAVE* tiros, CANHAO* canhao, BARREIRA* barreira, LINHA* linha,AUDIO* audio);

void draw_tiros_nave(TIROS_NAVE* tiros);

void verifica_colisao_barreira(TIROS_NAVE* tiros, BARREIRA* barreiras);

void naves_animacao_spawn(NAVES* naves, DISPLAY* display, OVERLAY overlay_atual, float zoom_atual, float zoom_max);

#endif