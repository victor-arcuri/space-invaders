#include <allegro5/allegro5.h>

#include "canhao.h"
#include "display.h"
#include "sprites.h"
#include "teclado.h"

// Inicia o struct CANHAO, criando-o na memória HEAP
CANHAO* iniciar_canhao(SPRITE sprite)
{
    CANHAO * canhao = (CANHAO *) malloc(sizeof(CANHAO));
    canhao->sprite = sprite;
    canhao->x = (BUFFER_W - sprite.width) / 2;
    canhao->y = BUFFER_H - 40;
    return canhao;

}

// Atualiza a lógica do canhão
void atualizar_canhao(CANHAO* canhao, TECLADO* teclado)
{
    
}


// Desenha o visual do canhão
void draw_canhao(CANHAO* canhao)
{
    al_draw_bitmap(canhao->sprite.bitmap, canhao->x, canhao->y, 0);
}

// Libera o espaço ocupado pelo canhão na memória HEAP
void finalizar_canhao(CANHAO* canhao)
{
    free(canhao);
}