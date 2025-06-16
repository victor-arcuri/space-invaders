#include <allegro5/allegro5.h>

#include "sprites.h"
#include "display.h"
#include "nave.h"
#include "inicializacao.h"
#include "canhao.h"
#include "utilidades.h"
#include "barreira.h"
#include "pontos.h"
// Inicia o struct NAVES na memória HEAP e posiciona cada nave em suas posições iniciais
NAVES* iniciar_naves(SPRITES* sprites, float velocidade_jogo)
{
    NAVES* naves = (NAVES*) malloc(sizeof(NAVES));
    tenta_iniciar(naves, "naves");
    int x = X_INICIAL;
    int y = Y_INICIAL;
    int width = 16; 
    int height = 8;
    for (int i =0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            TIPO tipo;
            SPRITE sprites_nave[2];
            if (i == 0){
                tipo = NAVE_1;
                sprites_nave[0] = sprites->nave_1[0];
                sprites_nave[1] = sprites->nave_1[1];
            } else if (i <= 2) {
                tipo = NAVE_2;
                sprites_nave[0] = sprites->nave_2[0];
                sprites_nave[1] = sprites->nave_2[1];
            } else {
                tipo = NAVE_3;
                sprites_nave[0] = sprites->nave_3[0];
                sprites_nave[1] = sprites->nave_3[1];
            }
            naves->naves[i][j].tipo = tipo;
            naves->naves[i][j].x = x;
            naves->naves[i][j].y = y;
            naves->naves[i][j].w = width;
            naves->naves[i][j].h = height;
            naves->naves[i][j].sprites[0] = sprites_nave[0];
            naves->naves[i][j].sprites[1] = sprites_nave[1];
            naves->naves[i][j].sprites[2] = sprites->nave_explosao;
            naves->naves[i][j].frame = 0;
            naves->naves[i][j].viva = true;
            naves->naves[i][j].hitbox.x1 = x + 2;
            naves->naves[i][j].hitbox.x2 = x + 2+ width - 4 ;
            naves->naves[i][j].hitbox.y1 = y;
            naves->naves[i][j].hitbox.y2 = y + height;
            naves->vel_x =4;
            naves->vel_y =16;
            naves->min_delay = 5;
            naves->max_delay = 60;
            naves->delay_movimento = naves->max_delay;
            naves->contador_movimento = 0;
            naves->total_vivas = LINHAS * COLUNAS;
            naves->em_movimento = true;
            naves->explosao_contador_max = 15;
            naves->explosao_contador_atual = 0;
            naves->contador_movimento_misterio = 0;
            naves->delay_movimento_misterio = 0;
            NAVE nave_misterio;
            nave_misterio.acertou = false;
            nave_misterio.frame = 0;
            nave_misterio.tipo = MISTERIO;
            nave_misterio.viva = false;
            nave_misterio.sprites[0] = sprites->nave_misterio[0];
            nave_misterio.sprites[1] = sprites->nave_misterio[1];
            nave_misterio.w = 16;
            nave_misterio.h = 8;
            naves->nave_misterio = nave_misterio;
            naves->misterio_explosao_contador_max = 15;
            naves->misterio_explosao_contador = 0;
            naves->velocidade_jogo = velocidade_jogo;
            naves->tiros = iniciar_tiros_nave();
            naves->stun = false;
            naves->audio_movimento_contagem = 0;
            x+=width;
        }
        y+=height+ESPACAMENTO_VERTICAL;
        x = X_INICIAL;
    }

    return naves;
}

// Desenha a nave passada
void draw_nave(NAVE nave)
{
    ALLEGRO_BITMAP* sprite;
    if(!nave.acertou && !nave.viva) return;
    sprite = nave.sprites[nave.frame].bitmap;

    al_draw_bitmap(sprite, nave.x, nave.y, 0);

}

// Desenha todas as naves
void draw_naves(NAVES* naves){
    draw_tiros_nave(naves->tiros);
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            draw_nave(naves->naves[i][j]);
        }
    }
    draw_nave(naves->nave_misterio);
}

// Atualiza a lógica das naves
void atualizar_naves(AUDIO* audio, NAVES* naves, CANHAO* canhao, SPRITES* sprites, BARREIRA* barreiras, LINHA* linha, PONTOS* pontos, bool* perdeu_jogo, bool* venceu_jogo){
    atualizar_nave_misterio(naves, canhao, pontos, audio);
    atualizar_tiros_nave(naves->tiros, canhao, barreiras, linha, audio);
    if (naves->stun) return;

    if (naves->explosao_contador_atual > 0){
        naves->explosao_contador_atual--;
        return;
    }
    if (canhao->tiro.acertou){
        tiro_terminou_colisao(canhao);
        
    }
    // Checa quais naves poderiam atirar nesse frame
    int naves_verificadas[COLUNAS];
    int num_naves_possiveis = 0;
    for (int j = 0; j< COLUNAS; j++){
        int nave_mais_baixa = -1;
        for (int i = 0; i < LINHAS; i++){
            if (naves->naves[i][j].viva) nave_mais_baixa = i;
        }
        naves_verificadas[j] = nave_mais_baixa;
        if (nave_mais_baixa != -1) num_naves_possiveis++;
    }
    NAVE naves_possiveis[num_naves_possiveis];
    int index = 0;
    for (int i = 0; i < COLUNAS; i++){
        if (naves_verificadas[i] != -1) {
            naves_possiveis[index] = naves->naves[naves_verificadas[i]][i];
            index++;
        }
    }

    // Define aleatoriamente qual das naves possíveis vai tentar atirar
    int index_possivel = intervalo_aleatorio(0, num_naves_possiveis);
    tenta_disparar_nave(naves->tiros,naves_possiveis[index_possivel],sprites);

    // Colisão com tiro
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            NAVE* nave = &(naves->naves[i][j]);
            if(nave->acertou){
                nave->acertou = false;
            }
            if (!nave->viva || !canhao->tiro.ativo) continue;
            if (colisao(nave->hitbox, canhao->tiro.hitbox)) {
                nave->viva = false;   
                naves->total_vivas--;
                tiro_colidiu(canhao);
                naves->explosao_contador_atual = naves->explosao_contador_max;
                naves->naves[i][j].acertou = true;
                naves->naves[i][j].frame = 2;
                pontuar(pontos, nave->tipo, canhao, audio);
                al_play_sample(audio->nave_explosao, 0.5f, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }
    }
    // Checa se todas as naves estão mortas
    bool vitoria = true;
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            if (naves->naves[i][j].viva) vitoria = false;
        }
    }
    if(vitoria){
        *venceu_jogo = true;
    }

    // Movimento
    if (!naves->em_movimento) return;
    naves->contador_movimento++;

    if (naves->contador_movimento < naves->delay_movimento) return;
    naves->contador_movimento = 0;

    bool jump = false;
    if (naves->audio_movimento_contagem < 3){
        naves->audio_movimento_contagem++;
    }
    else {
        naves->audio_movimento_contagem = 0;
    }
    al_play_sample(audio->nave_movimento[naves->audio_movimento_contagem], 0.7f, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            NAVE* nave = &(naves->naves[i][j]);
            if(!nave->viva) continue;
            if ((nave->x + nave->w + naves->vel_x > BUFFER_W || nave->x + naves->vel_x < 0) && !jump){
                naves->vel_x*=-1;
                jump = true;
            } 
            // Tocar o Solo
            if (jump && nave->y + naves->vel_y + nave->h > Y_FINAL) {
                naves->em_movimento = false;
                naves->stun = true;
                *perdeu_jogo = true;
                return;
            }
            // Tocar o Canhão
            HITBOX hitbox_temp;
            hitbox_temp.x1 = nave->x + 2 + naves->vel_x;
            hitbox_temp.x2 = nave->x + 2 + nave->w - 4 + naves->vel_x;
            hitbox_temp.y1 = nave->y - 4;
            hitbox_temp.y2 = nave->y + nave->h;

            if (colisao(hitbox_temp, canhao->hitbox)){
                naves->stun = true;
                naves->em_movimento = false;
                *perdeu_jogo = true;
                return;
            }
            
        }
    }
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            NAVE* nave = &(naves->naves[i][j]);
            if (jump) nave->y += naves->vel_y;
            if (nave->frame == 0) nave->frame = 1;
            else if (nave->frame == 1) nave->frame = 0;
            nave->x += naves->vel_x;
            nave->hitbox.x1 = nave->x + 2;
            nave->hitbox.x2 = nave->x + 2 + nave->w - 4;
            nave->hitbox.y1 = nave->y;
            nave->hitbox.y2 = nave->y + nave->h;
        } 
    }

    float fator = (float)naves->total_vivas / (LINHAS * COLUNAS);
    float intensidade = 0.8f * naves->velocidade_jogo; 
    float ease = (1 - intensidade) * fator + intensidade * (fator * fator);
    naves->delay_movimento = naves->min_delay + (naves->max_delay - naves->min_delay) * ease;

}

// Libera o espaço ocupado pelas naves
void finalizar_naves(NAVES* naves)
{
    free(naves);
}

void criar_nave_misterio(NAVES* naves, AUDIO* audio){
    if (naves->nave_misterio.viva) return;
    al_play_sample(audio->nave_misterio, 0.7f, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    int lado = intervalo_aleatorio(0,1);
    int direcao, x, y;
    y = 50;
    if (lado == 0){
        direcao = 1;
        x = -naves->nave_misterio.w;
        
    } else {
        direcao = -1;
        x = BUFFER_W + naves->nave_misterio.w;
    }
    naves->misterio_explosao_contador = 0;
    naves->nave_misterio.frame = 0;
    naves->contador_movimento_misterio = 0;
    naves->nave_misterio.viva = true;
    naves->dir_nave_misterio = direcao;
    naves->nave_misterio.x = x;
    naves->nave_misterio.y = y;
}

void atualizar_nave_misterio(NAVES* naves, CANHAO* canhao, PONTOS* pontos, AUDIO* audio){
    if (naves->misterio_explosao_contador > 0){
        naves->misterio_explosao_contador--;
        return;
    }

    if (naves->nave_misterio.acertou){
        naves->nave_misterio.acertou = false;
        tiro_terminou_colisao(canhao);
    }
    

    // Movimento
    if (!naves->nave_misterio.viva) return;
    if (naves->contador_movimento_misterio < naves->delay_movimento_misterio) {
        naves->contador_movimento_misterio++;
        return;
    }
    naves->nave_misterio.hitbox.x1 = naves->nave_misterio.x;
    naves->nave_misterio.hitbox.x2 = naves->nave_misterio.x + naves->nave_misterio.w;
    naves->nave_misterio.hitbox.y1 = naves->nave_misterio.y;
    naves->nave_misterio.hitbox.y2 = naves->nave_misterio.y + naves->nave_misterio.h;

    
    naves->contador_movimento_misterio = 0;
    naves->nave_misterio.x += ( 1 * naves->dir_nave_misterio);

    if ((naves->nave_misterio.x > BUFFER_W && naves->dir_nave_misterio == 1 )|| (naves->nave_misterio.x+naves->nave_misterio.w < 0 && naves->dir_nave_misterio == -1)){
        naves->nave_misterio.viva = false;
    }

    // Checagem de colisão
    if (!canhao->tiro.ativo || !colisao(naves->nave_misterio.hitbox, canhao->tiro.hitbox)) return;
    naves->nave_misterio.viva = false;
    naves->nave_misterio.acertou = true;
    naves->nave_misterio.frame = 1;
    naves->misterio_explosao_contador = naves->misterio_explosao_contador_max;
    pontuar(pontos, MISTERIO, canhao, audio);
    tiro_colidiu(canhao);
    al_play_sample(audio->nave_explosao, 0.5f, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    
}


TIROS_NAVE* iniciar_tiros_nave(){
    TIROS_NAVE* tiros = (TIROS_NAVE*) malloc(sizeof(TIROS_NAVE));
    tiros->tiros_ativos=0;
    tiros->tiros_max=4;
    tiros->tiros = (TIRO_NAVE*) malloc(sizeof(TIRO_NAVE)*tiros->tiros_max);
    for (int i = 0; i < tiros->tiros_max; i++){
        tiros->tiros[i].ativo = false;
        tiros->tiros[i].h = 8;
        tiros->tiros[i].w = 3;
    }
    return tiros;
}


void finalizar_tiros_nave(TIROS_NAVE* tiros){
    free(tiros->tiros);
    free(tiros);
}

void tenta_disparar_nave(TIROS_NAVE* tiros, NAVE nave, SPRITES* sprites){
    // Checa se tem o número máximo de tiros na tela permitido
    if (tiros->tiros_ativos >= tiros->tiros_max) return;

    // Checa chance do tiro
    if (intervalo_aleatorio(0,1000) > 10) return;

    //Define o sprite do tiro
    SPRITE tiro_sprite[4];
    int tiro_h;
    int tiro_w;
    TIPO_TIRO_NAVE tiro_tipo;

    tiro_tipo = intervalo_aleatorio(1,3);
    int tiro_frame;

    switch(tiro_tipo){
        case TIPO_1:
            tiro_sprite[0] = sprites->tiro_1[0];
            tiro_sprite[1] = sprites->tiro_1[1];
            tiro_sprite[2] = sprites->tiro_1[2];
            tiro_sprite[3] = sprites->tiro_1[3];
            break;
        case TIPO_2:
            tiro_sprite[0] = sprites->tiro_2[0];
            tiro_sprite[1] = sprites->tiro_2[1];
            tiro_sprite[2] = sprites->tiro_2[2];
            tiro_sprite[3] = sprites->tiro_2[3];
            break;
        case TIPO_3:
            tiro_sprite[0] = sprites->tiro_3[0];
            tiro_sprite[1] = sprites->tiro_3[1];
            tiro_sprite[2] = sprites->tiro_3[2];
            tiro_sprite[3] = sprites->tiro_3[3];
            break;
    }

    tiro_h = 8;
    tiro_w = 3;
    tiro_frame = 0;


    // Acha o primeiro tiro disponível em TIROS e o redefine
    for (int i = 0; i < tiros->tiros_max; i++){
        if (tiros->tiros[i].ativo) continue;
        tiros->tiros[i].ativo = true;
        tiros->tiros[i].x = nave.x + (nave.w/2) - tiro_w;
        tiros->tiros[i].y = nave.y + nave.h;
        tiros->tiros[i].h = tiro_h;
        tiros->tiros[i].w = tiro_w;
        tiros->tiros[i].sprites[0] = tiro_sprite[0];
        tiros->tiros[i].sprites[1] = tiro_sprite[1];
        tiros->tiros[i].sprites[2] = tiro_sprite[2];
        tiros->tiros[i].sprites[3] = tiro_sprite[3];
        tiros->tiros[i].sprites[4] = sprites->tiro_explosao;
        tiros->tiros[i].frame = tiro_frame;
        tiros->tiros[i].contador_explosao_atual = 0;
        tiros->tiros[i].contador_explosao_max = 15;
        tiros->tiros[i].acertado = false;
        tiros->tiros[i].hitbox.x1 = tiros->tiros[i].x;
        tiros->tiros[i].hitbox.x2 = tiros->tiros[i].x + tiros->tiros[i].w;
        tiros->tiros[i].hitbox.y1 = tiros->tiros[i].y;
        tiros->tiros[i].hitbox.y2 = tiros->tiros[i].y + tiros->tiros[i].h;

        tiros->tiros_ativos++;
        return;
        
    }
}

void atualizar_tiros_nave(TIROS_NAVE* tiros, CANHAO* canhao, BARREIRA* barreiras, LINHA* linha, AUDIO* audio){
    verifica_colisao_barreira(tiros, barreiras);
    for(int i =0; i<tiros->tiros_max; i++){
        if (tiros->tiros[i].contador_explosao_atual > 0){
            tiros->tiros[i].contador_explosao_atual--;
            continue;
        } else if (tiros->tiros[i].acertado){
            tiros->tiros_ativos--;
            tiros->tiros[i].ativo = false;
            tiros->tiros[i].acertado = false;
            continue;
        }
        if (!tiros->tiros[i].ativo) continue;
        tiros->tiros[i].y+=2;
        tiros->tiros[i].frame++;
        tiros->tiros[i].hitbox.x1 = tiros->tiros[i].x;
        tiros->tiros[i].hitbox.x2 = tiros->tiros[i].x + tiros->tiros[i].w;
        tiros->tiros[i].hitbox.y1 = tiros->tiros[i].y;
        tiros->tiros[i].hitbox.y2 = tiros->tiros[i].y + tiros->tiros[i].h;
        tiros->tiros[i].colisao_x = tiros->tiros[i].x + tiros->tiros[i].w / 2;
        tiros->tiros[i].colisao_y = tiros->tiros[i].y + tiros->tiros[i].h;
        if (tiros->tiros[i].frame >= 3 * 10){
            tiros->tiros[i].frame = 0;
        } 
        
        // Verifica se chegou na linha de varredura
        if (tiros->tiros[i].y+tiros->tiros[i].h >= LINHA_VARREDURA_Y){
            tiros->tiros[i].acertado = true;
            tiros->tiros[i].contador_explosao_atual = tiros->tiros[i].contador_explosao_max;
            tiros->tiros[i].frame = 4 * 10;
            danificar_linha(tiros->tiros[i].x, linha);
        }

        // Verifica colisão com canhão
        if (colisao(tiros->tiros[i].hitbox, canhao->hitbox)){ 
            tiros->tiros[i].acertado = true;
            tiros->tiros[i].contador_explosao_atual = tiros->tiros[i].contador_explosao_max;
            tiros->tiros[i].frame = 4 * 10;
            
            canhao_acertado(canhao, audio);
        }

        // Verifica colisão com tiro do canhão
        if (canhao->tiro.ativo && colisao(tiros->tiros[i].hitbox, canhao->tiro.hitbox)){
            canhao->tiro.ativo = false;
            tiros->tiros[i].acertado = true;
            tiros->tiros[i].contador_explosao_atual = tiros->tiros[i].contador_explosao_max;
            tiros->tiros[i].frame = 4 * 10;
        }

    }
}

void draw_tiros_nave(TIROS_NAVE* tiros){
    for(int i =0; i<tiros->tiros_max; i++){
        if (!tiros->tiros[i].ativo) continue;
        al_draw_bitmap(tiros->tiros[i].sprites[tiros->tiros[i].frame/10].bitmap, tiros->tiros[i].x,tiros->tiros[i].y,0);
    }
}

void verifica_colisao_barreira(TIROS_NAVE* tiros, BARREIRA* barreiras){
    for (int i = 0; i < tiros->tiros_max;i++){
        if(tiros->tiros[i].acertado) continue;
        if (!tiros->tiros[i].ativo) continue;
        for (int j = 0; j < 4; j++){
            // Verifica se tiro entrou na área da hitbox da barreira
            if (!colisao(tiros->tiros[i].hitbox, barreiras[j].hitbox)) continue;

            // Verifica se ponta do tiro está sobre um pixel não danificado da barreira
            if (!checa_integridade_posicao(barreiras[j],tiros->tiros[i].colisao_x, tiros->tiros[i].colisao_y)) continue;
            
            tiros->tiros[i].y+=tiros->tiros[i].h ;


            // Suaviza o tiro
            int base_x = tiros->tiros[i].x;
            int base_y = tiros->tiros[i].y;

            const int offsets[][2] = {
                {0, 0},
                {-1, 0}, {1, 0},
                {0, -1}, {0, 1}
            };

            for (int k = 0; k < 5; k++) {
                int dx = offsets[k][0];
                int dy = offsets[k][1];
                danificar_barreira(tiros->tiros[i].sprites[4].bitmap, barreiras[j], base_x + dx, base_y + dy);
            }
            
            tiros->tiros[i].acertado = true;
            tiros->tiros[i].contador_explosao_atual = tiros->tiros[i].contador_explosao_max;
            tiros->tiros[i].frame = 4 * 10;

        }
    }
}

void naves_animacao_spawn(NAVES* naves, DISPLAY* display, OVERLAY overlay_atual, float zoom_atual, float zoom_max){
    for (int i = LINHAS -1; i >= 0; i--){
        for (int j = 0; j < COLUNAS; j++){
            al_set_target_bitmap(display->buffer);
            al_draw_bitmap(naves->naves[i][j].sprites[0].bitmap, naves->naves[i][j].x, naves->naves[i][j].y, 0);
            pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
            al_rest(0.02f);
        }
    }
    
}