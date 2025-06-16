#include <allegro5/allegro5.h>

#include "canhao.h"
#include "display.h"
#include "sprites.h"
#include "teclado.h"
#include "nave.h"
#include "barreira.h"

#define CANHAO_VEL 1
#define CANHAO_MAX_X (BUFFER_W - CANHAO_WIDTH)


// Inicia o struct CANHAO, criando-o na memória HEAP
CANHAO* iniciar_canhao(SPRITES* sprites)
{   
    SPRITE sprite_canhao = sprites->canhao;
    SPRITE sprite_tiro = sprites->tiro_canhao[0];
    SPRITE sprite_explosao = sprites->tiro_canhao[1];
    CANHAO * canhao = (CANHAO *) malloc(sizeof(CANHAO));
    canhao->sprite = sprite_canhao;
    canhao->x = (BUFFER_W - sprite_canhao.width) / 2;
    canhao->y = BUFFER_H - 39;
    canhao->vidas = 3;
    TIRO tiro;
    tiro.ativo = false;
    tiro.sprite[0] = sprite_tiro;
    tiro.sprite[1] = sprite_explosao;
    tiro.vel_y = 4;
    tiro.frame = 0;
    tiro.count_max = 15;
    tiro.count = 0;
    tiro.explodindo = false;
    tiro.acertou = false;
    tiro.x = canhao->x;
    tiro.y = canhao->y;
    tiro.hitbox.x1 = tiro.x;
    tiro.hitbox.x2 = tiro.x + TIRO_CANHAO_EXPLOSAO_WIDTH;
    tiro.hitbox.y1 = tiro.y;
    tiro.hitbox.y2 = tiro.y + TIRO_CANHAO_EXPLOSAO_HEIGHT;
    canhao->tiro = tiro;
    canhao->tiro.contagem_tiros = 0;
    canhao->ativo = true;
    canhao->acertado = false;
    canhao->acertado_frame = 0;
    canhao->acertado_sprites[0] = sprites->canhao_acertado[0];
    canhao->acertado_sprites[1] = sprites->canhao_acertado[1];
    canhao->acertado_contador_atual = 0;
    canhao->acertado_contador_max = 5;
    canhao->acertado_ciclos = 0;
    return canhao;

}

// Atualiza a lógica do canhão
void atualizar_canhao(AUDIO* audio, CANHAO* canhao, TECLADO* teclado, NAVES* naves, BARREIRA* barreiras, bool* perdeu_jogo)
{
    if (!canhao->ativo) return;
    if (canhao->acertado){
        naves->stun = true;
        if(canhao->acertado_ciclos < 6){
            if (canhao->acertado_contador_atual < canhao->acertado_contador_max){
                canhao->acertado_contador_atual++;
            } else {
                if (canhao->acertado_frame == 0){
                    canhao->acertado_frame = 1;
                } else {
                    canhao->acertado_frame = 0;
                    canhao->acertado_ciclos++;
                }
                canhao->acertado_contador_atual = 0;
            }
        } else {
            if (canhao->vidas > 0){
                canhao->acertado = false;
                naves->stun = false;

            } else {
                canhao->ativo = false;
                *perdeu_jogo = true;
            }
        }
        return;
    } 
    if (teclado->teclas[ALLEGRO_KEY_RIGHT])
    {
        canhao->x+=CANHAO_VEL;
    }

    if (teclado->teclas[ALLEGRO_KEY_LEFT])
    {
        canhao->x-=CANHAO_VEL;
    }

    if (teclado->teclas[ALLEGRO_KEY_SPACE] || teclado->teclas[ALLEGRO_KEY_Z])
    {
        disparar_tiro_canhao(canhao, audio);
        checa_nave_misterio(canhao, naves, audio);
    }
    verifica_colisao_barreira_tiro_canhao(canhao, barreiras);
    atualizar_tiro_canhao(canhao);
    if (canhao->x > CANHAO_MAX_X) canhao->x = CANHAO_MAX_X;
    if (canhao->x < 0) canhao->x = 0;

    canhao->hitbox.x1 = canhao->x;
    canhao->hitbox.x2 = canhao->x+CANHAO_WIDTH;
    canhao->hitbox.y1 = canhao->y;
    canhao->hitbox.y2 = canhao->y+CANHAO_HEIGHT;
}



// Desenha o visual do canhão
void draw_canhao(CANHAO* canhao)
{
    if (!canhao->ativo) return;
    if (canhao->acertado){
        al_draw_bitmap(canhao->acertado_sprites[canhao->acertado_frame].bitmap,canhao->x, canhao->y,0);
        return;
    }
    draw_tiro_canhao(canhao);
    al_draw_bitmap(canhao->sprite.bitmap, canhao->x, canhao->y, 0);
}

// Libera o espaço ocupado pelo canhão na memória HEAP
void finalizar_canhao(CANHAO* canhao)
{
    free(canhao);
}

void disparar_tiro_canhao(CANHAO* canhao, AUDIO* audio)
{
    TIRO* tiro = &(canhao->tiro);
    
    if (tiro->ativo || tiro->acertou) return;
    al_play_sample(audio->canhao_tiro, 0.5f, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    tiro->contagem_tiros++;
    tiro->frame = 0;
    tiro->count = 0;
    tiro->ativo = true;
    tiro->x = canhao->x + CANHAO_WIDTH / 2;
    tiro->y = canhao->y - TIRO_CANHAO_HEIGHT / 2;
    tiro->hitbox.x1 = tiro->x;
    tiro->hitbox.x2 = tiro->x + TIRO_CANHAO_EXPLOSAO_WIDTH;
    tiro->hitbox.y1 = tiro->y;
    tiro->hitbox.y2 = tiro->y + TIRO_CANHAO_EXPLOSAO_HEIGHT;
    canhao->tiro.tiro_colisao_x = canhao->tiro.x + TIRO_CANHAO_WIDTH / 2;
    canhao->tiro.tiro_colisao_y = canhao->tiro.y;

}

void atualizar_tiro_canhao(CANHAO* canhao)
{ 
    TIRO* tiro = &(canhao->tiro);

    if (!tiro->ativo) return;

    if (tiro->explodindo) {
        tiro->count++;
        if (tiro->count >= tiro-> count_max){
            tiro->explodindo = false;
            tiro->count = 0;
            tiro->ativo = false;
        }
        return;
    }

    tiro->y -= tiro->vel_y;
    tiro->hitbox.x1 = tiro->x;
    tiro->hitbox.x2 = tiro->x + TIRO_CANHAO_EXPLOSAO_WIDTH;
    tiro->hitbox.y1 = tiro->y;
    tiro->hitbox.y2 = tiro->y + TIRO_CANHAO_EXPLOSAO_HEIGHT;
    canhao->tiro.tiro_colisao_x = canhao->tiro.x + TIRO_CANHAO_WIDTH / 2;
    canhao->tiro.tiro_colisao_y = canhao->tiro.y;


    if (tiro->y <= LIMITE_TIRO) {
        tiro->explodindo = true;
        tiro->frame = 1;
    }

}

// Desabilita o tiro ao colidir
void tiro_colidiu(CANHAO* canhao)
{

    canhao->tiro.ativo = false;
    canhao->tiro.acertou = true;
}

// Reabilita o tiro ao término da colisao
void tiro_terminou_colisao(CANHAO* canhao)
{
    canhao->tiro.acertou = false;
}

void draw_tiro_canhao(CANHAO* canhao)
{
    TIRO* tiro = &(canhao->tiro);
    
    if (!tiro->ativo) return;

    al_draw_bitmap(tiro->sprite[tiro->frame].bitmap, tiro->x, tiro->y, 0);

}

void checa_nave_misterio(CANHAO* canhao, NAVES* naves, AUDIO* audio){
    if (naves->nave_misterio.viva) canhao->tiro.contagem_tiros = 0;
    if (canhao->tiro.contagem_tiros % 15 == 0 && canhao->tiro.contagem_tiros != 0){
        criar_nave_misterio(naves, audio);
    }
}

void canhao_acertado(CANHAO* canhao, AUDIO* audio){
    if (canhao->vidas > 0){
        canhao->vidas--;
        canhao->acertado = true;
        canhao->acertado_ciclos = 0;
        canhao->acertado_contador_atual = 0;
        canhao->acertado_frame = 0;
        al_play_sample(audio->canhao_explosao, 0.5f, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        return;
    }
    
}


void verifica_colisao_barreira_tiro_canhao(CANHAO* canhao, BARREIRA* barreiras){
    TIRO tiro = canhao->tiro;
    if (!tiro.ativo) return;
    for (int i =0; i < 4; i++){
        // Verifica se o tiro do canhão está sobrepondo a hitbox da barreira
        if (!colisao(tiro.hitbox, barreiras[i].hitbox)) continue;

        // Verifica se o tiro do canhão está sobre um pixel visivel
        if(!checa_integridade_posicao(barreiras[i], tiro.tiro_colisao_x, tiro.tiro_colisao_y)) continue;

        canhao->tiro.y-=2;


        // Suaviza o tiro
        int base_x = tiro.x;
        int base_y = canhao->tiro.y;

        const int offsets[][2] = {
            {0, 0},
            {-1, 0}, {1, 0},
            {0, -1}, {0, 1}
        };

        for (int k = 0; k < 5; k++) {
            int dx = offsets[k][0];
            int dy = offsets[k][1];
            danificar_barreira(tiro.sprite[1].bitmap, barreiras[i], base_x + dx, base_y + dy);
        }

        canhao->tiro.explodindo = true;
        canhao->tiro.frame = 1;

    }
}