#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "texto.h"
#include "canhao.h"
#include "pontos.h"
#include "hud.h"
#include "sprites.h"
HUD* iniciar_hud(CANHAO* canhao, PONTOS* pontos, FONTE* fonte, SPRITES* sprites){
    HUD* hud = (HUD*) malloc(sizeof(HUD));
    hud->highscore = &pontos->highscore;
    hud->score_atual = &pontos->score_atual;
    hud->vidas = &canhao->vidas;
    hud->fonte = fonte;
    hud->sprite_canhao = &sprites->canhao;
    return hud;
}

void finalizar_hud(HUD* hud){
    free(hud);
}

void draw_hud(HUD* hud){
    int highscore = *hud->highscore;
    int vidas = *hud->vidas;
    int score_atual = *hud->score_atual;

    // Vidas
    char vidas_vetor[3];
    sprintf(vidas_vetor, "%d", vidas);
    desenhar_texto(vidas_vetor,hud->fonte, VIDAS_TEXTO_X, VIDAS_TEXTO_Y,0);
    int x = VIDAS_TEXTO_X + (FONT_WIDTH*2);
    int y = VIDAS_TEXTO_Y;
    for (int i = 0; i < vidas -1; i++){
        al_draw_bitmap(hud->sprite_canhao->bitmap, x,y,0);
        x+=hud->sprite_canhao->width;
    }

    // Scores
    char score_text[10] = "Score<1>";
    char score_value[5];
    int score_value_x =  SCORE_TEXTO_X; 
    int score_value_y =  SCORE_TEXTO_Y + FONT_HEIGHT + 1; 
    sprintf(score_value, "%04d", score_atual);
    desenhar_texto(score_text, hud->fonte, SCORE_TEXTO_X, SCORE_TEXTO_Y, 0);
    desenhar_texto(score_value, hud->fonte, score_value_x, score_value_y, 0);

    char highscore_text[10] = "HI-Score";
    char highscore_value[5];
    int highscore_text_x = BUFFER_W - (strlen(highscore_text) * FONT_WIDTH) - SCORE_TEXTO_X;
    int highscore_text_y = SCORE_TEXTO_Y;
    int highscore_value_x =  BUFFER_W - (4 * FONT_WIDTH) - SCORE_TEXTO_X; 
    int highscore_value_y =  SCORE_TEXTO_Y + FONT_HEIGHT + 1; 
    sprintf(highscore_value, "%04d", highscore);
    desenhar_texto(highscore_text, hud->fonte, highscore_text_x, highscore_text_y, 0);
    desenhar_texto(highscore_value, hud->fonte, highscore_value_x, highscore_value_y, 0);
    
}