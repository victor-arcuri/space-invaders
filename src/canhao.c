#include <allegro5/allegro5.h>

#include "canhao.h"
#include "display.h"
#include "sprites.h"
#include "teclado.h"

CANHAO * iniciar_canhao(SPRITE* sprite)
{
    CANHAO * canhao = (CANHAO *) malloc(sizeof(CANHAO));
    canhao->x = (BUFFER_W - sprite->width) / 2;
    canhao->y = (BUFFER_H - sprite->height) / 2;
    return canhao;

}

void atualizar_canhao(CANHAO* canhao, TECLADO* teclado)
{
    
}

void draw_canhao(CANHAO* canhao)
{
}