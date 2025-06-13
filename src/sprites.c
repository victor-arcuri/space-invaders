#include <allegro5/allegro5.h>
#include "inicializacao.h"
#include "sprites.h"

// Cria um sub bitmap para uma spritesheet, que se refere a um único sprite
SPRITE pegar_sprite(ALLEGRO_BITMAP* spritesheet, int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* bitmap = al_create_sub_bitmap(spritesheet, x,y,w,h);
    tenta_iniciar(bitmap, "pegar bitmap");
    SPRITE sprite;
    sprite.bitmap = bitmap;
    sprite.height = h;
    sprite.width = w;
    return sprite;
}

// Inicializa na memória um struct SPRITES com os sprites e as spritesheets e retorna um ponteiro para ele 
SPRITES* iniciar_sprites()
{
    // Cria um struct SPRITES na memória heap e retorna um ponteiro
    SPRITES* sprites = (SPRITES*) malloc(sizeof(SPRITES));
    tenta_iniciar(sprites, "gerenciador de sprites");

    // Carrega as spritesheets
    sprites->_og_sheet = al_load_bitmap("assets/img/space-invaders-og-spritesheet.png");
    tenta_iniciar(sprites->_og_sheet, "spritesheet original");

    // Carrega os sprites
    sprites->canhao =  pegar_sprite(sprites->_og_sheet, CANHAO_X, CANHAO_Y, CANHAO_WIDTH, CANHAO_HEIGHT);

    sprites->nave_1[0] =  pegar_sprite(sprites->_og_sheet, 1, 1, 16, 8);
    sprites->nave_1[1] =  pegar_sprite(sprites->_og_sheet, 1, 11, 16, 8);

    sprites->nave_2[0] =  pegar_sprite(sprites->_og_sheet, 19, 1, 16, 8);
    sprites->nave_2[1] =  pegar_sprite(sprites->_og_sheet, 19, 11, 16, 8);

    sprites->nave_3[0] =  pegar_sprite(sprites->_og_sheet, 37, 1, 16, 8);
    sprites->nave_3[1] =  pegar_sprite(sprites->_og_sheet, 37, 11, 16, 8);

    sprites->tiro_canhao[0] =  pegar_sprite(sprites->_og_sheet, TIRO_CANHAO_X, TIRO_CANHAO_Y, TIRO_CANHAO_WIDTH, TIRO_CANHAO_HEIGHT);
    sprites->tiro_canhao[1] =  pegar_sprite(sprites->_og_sheet, TIRO_CANHAO_EXPLOSAO_X, TIRO_CANHAO_EXPLOSAO_Y, TIRO_CANHAO_EXPLOSAO_WIDTH, TIRO_CANHAO_EXPLOSAO_HEIGHT);
    
    sprites->nave_explosao =  pegar_sprite(sprites->_og_sheet, NAVE_EXPLOSAO_X, NAVE_EXPLOSAO_Y, NAVE_EXPLOSAO_WIDTH, NAVE_EXPLOSAO_HEIGHT);

    sprites->nave_misterio[0] =  pegar_sprite(sprites->_og_sheet, 1, 39, 16, 8);
    sprites->nave_misterio[1] =  pegar_sprite(sprites->_og_sheet, 19, 39, 24, 8);

    sprites->tiro_1[0] = pegar_sprite(sprites->_og_sheet, 1,21,3,8);
    sprites->tiro_1[1] = pegar_sprite(sprites->_og_sheet, 6,21,3,8);
    sprites->tiro_1[2] = pegar_sprite(sprites->_og_sheet, 11,21,3,8);
    sprites->tiro_1[3] = pegar_sprite(sprites->_og_sheet, 16,21,3,8);

    sprites->tiro_2[0] = pegar_sprite(sprites->_og_sheet, 21,21,3,8);
    sprites->tiro_2[1] = pegar_sprite(sprites->_og_sheet, 26,21,3,8);
    sprites->tiro_2[2] = pegar_sprite(sprites->_og_sheet, 31,21,3,8);
    sprites->tiro_2[3] = pegar_sprite(sprites->_og_sheet, 36,21,3,8);

    sprites->tiro_3[0] = pegar_sprite(sprites->_og_sheet, 41,21,3,8);
    sprites->tiro_3[1] = pegar_sprite(sprites->_og_sheet, 46,21,3,8);
    sprites->tiro_3[2] = pegar_sprite(sprites->_og_sheet, 51,21,3,8);
    sprites->tiro_3[3] = pegar_sprite(sprites->_og_sheet, 56,21,3,8);

    sprites->tiro_explosao = pegar_sprite(sprites->_og_sheet, 61, 21, 6,8);

    sprites->barreira = pegar_sprite(sprites->_og_sheet, 45, 31, 24, 16);

    //Tecla A
    sprites->teclas[0] = pegar_sprite(sprites->_og_sheet, 1, 69, 8,8);

    //Tecla B
    sprites->teclas[1] = pegar_sprite(sprites->_og_sheet, 11, 69, 8,8);

    //Tecla C
    sprites->teclas[2] = pegar_sprite(sprites->_og_sheet, 21, 69, 8,8);

    //Tecla D
    sprites->teclas[3] = pegar_sprite(sprites->_og_sheet, 31, 69, 8,8);

    //Tecla E
    sprites->teclas[4] = pegar_sprite(sprites->_og_sheet, 41, 69, 8,8);

    //Tecla F
    sprites->teclas[5] = pegar_sprite(sprites->_og_sheet, 51, 69, 8,8);

    //Tecla G
    sprites->teclas[6] = pegar_sprite(sprites->_og_sheet, 61, 69, 8,8);

    //Tecla H
    sprites->teclas[7] = pegar_sprite(sprites->_og_sheet, 71, 69, 8,8);

    //Tecla I
    sprites->teclas[8] = pegar_sprite(sprites->_og_sheet, 1, 79, 8,8);

    //Tecla J
    sprites->teclas[9] = pegar_sprite(sprites->_og_sheet, 11, 79, 8,8);

    //Tecla K
    sprites->teclas[10] = pegar_sprite(sprites->_og_sheet, 21, 79, 8,8);

    //Tecla L
    sprites->teclas[11] = pegar_sprite(sprites->_og_sheet, 31, 79, 8,8);

    //Tecla M
    sprites->teclas[12] = pegar_sprite(sprites->_og_sheet, 41, 79, 8,8);

    //Tecla N
    sprites->teclas[13] = pegar_sprite(sprites->_og_sheet, 51, 79, 8,8);

    //Tecla O
    sprites->teclas[14] = pegar_sprite(sprites->_og_sheet, 61, 79, 8,8);

    //Tecla P
    sprites->teclas[15] = pegar_sprite(sprites->_og_sheet, 71, 79, 8,8);

    //Tecla Q
    sprites->teclas[16] = pegar_sprite(sprites->_og_sheet, 1, 89, 8,8);

    //Tecla R
    sprites->teclas[17] = pegar_sprite(sprites->_og_sheet, 11, 89, 8,8);

    //Tecla S
    sprites->teclas[18] = pegar_sprite(sprites->_og_sheet, 21, 89, 8,8);

    //Tecla T
    sprites->teclas[19] = pegar_sprite(sprites->_og_sheet, 31, 89, 8,8);

    //Tecla U
    sprites->teclas[20] = pegar_sprite(sprites->_og_sheet, 41, 89, 8,8);

    //Tecla V
    sprites->teclas[21] = pegar_sprite(sprites->_og_sheet, 51, 89, 8,8);

    //Tecla W
    sprites->teclas[22] = pegar_sprite(sprites->_og_sheet, 61, 89, 8,8);

    //Tecla X
    sprites->teclas[23] = pegar_sprite(sprites->_og_sheet, 71, 89, 8,8);

    //Tecla Y
    sprites->teclas[24] = pegar_sprite(sprites->_og_sheet, 1, 99, 8,8);

    //Tecla Z
    sprites->teclas[25] = pegar_sprite(sprites->_og_sheet, 11, 99, 8,8);

    //Tecla 0
    sprites->teclas[26] = pegar_sprite(sprites->_og_sheet, 21, 99, 8,8);

    //Tecla 1
    sprites->teclas[27] = pegar_sprite(sprites->_og_sheet, 31, 99, 8,8);

    //Tecla 2
    sprites->teclas[28] = pegar_sprite(sprites->_og_sheet, 41, 99, 8,8);

    //Tecla 3
    sprites->teclas[29] = pegar_sprite(sprites->_og_sheet, 51, 99, 8,8);

    //Tecla 4
    sprites->teclas[30] = pegar_sprite(sprites->_og_sheet, 61, 99, 8,8);

    //Tecla 5
    sprites->teclas[31] = pegar_sprite(sprites->_og_sheet, 71, 99, 8,8);

    //Tecla 6
    sprites->teclas[32] = pegar_sprite(sprites->_og_sheet, 1, 109, 8,8);

    //Tecla 7
    sprites->teclas[33] = pegar_sprite(sprites->_og_sheet, 11, 109, 8,8);

    //Tecla 8
    sprites->teclas[34] = pegar_sprite(sprites->_og_sheet, 21, 109, 8,8);

    //Tecla 9
    sprites->teclas[35] = pegar_sprite(sprites->_og_sheet, 31, 109, 8,8);

    //Tecla <
    sprites->teclas[36] = pegar_sprite(sprites->_og_sheet, 41, 109, 8,8);

    //Tecla >
    sprites->teclas[37] = pegar_sprite(sprites->_og_sheet, 51, 109, 8,8);

    //Tecla =
    sprites->teclas[38] = pegar_sprite(sprites->_og_sheet, 61, 109, 8,8);

    //Tecla *
    sprites->teclas[39] = pegar_sprite(sprites->_og_sheet, 71, 109, 8,8);

    //Tecla ?
    sprites->teclas[40] = pegar_sprite(sprites->_og_sheet, 1, 119, 8,8);

    //Tecla -
    sprites->teclas[41] = pegar_sprite(sprites->_og_sheet, 11, 119, 8,8);

    //Tecla Espaço
    sprites->teclas[42] = pegar_sprite(sprites->_og_sheet, 21, 119, 8,8);

    

    return sprites;
}

// Destroi os sprites, as spritesheets e libera memória alocada
void finalizar_sprites(SPRITES* sprites)
{
    // Destroi os sprites
    al_destroy_bitmap(sprites->canhao.bitmap);

    // Destroi as spritesheets
    al_destroy_bitmap(sprites->_og_sheet);

    // Libera memória alocada na HEAP
    free(sprites);

}
