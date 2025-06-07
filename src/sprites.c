#include <allegro5/allegro5.h>
#include "inicializacao.h"
#include "sprites.h"

#define CANHAO_X 3
#define CANHAO_Y 49
#define CANHAO_W 13
#define CANHAO_H 8


// Cria um sub bitmap para uma spritesheet, que se refere a um único sprite
ALLEGRO_BITMAP* pegar_sprite(ALLEGRO_BITMAP* spritesheet, int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(spritesheet, x,y,w,h);
    tenta_iniciar(sprite, "pegar sprite");
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
    sprites->canhao =  al_create_sub_bitmap(sprites->_og_sheet, CANHAO_X, CANHAO_Y, CANHAO_W, CANHAO_H);

    
    return sprites;
}

// Destroi os sprites, as spritesheets e libera memória alocada
void finalizar_sprites(SPRITES* sprites)
{
    // Destroi os sprites
    al_destroy_bitmap(sprites->canhao);

    // Destroi as spritesheets
    al_destroy_bitmap(sprites->_og_sheet);

    // Libera memória alocada na HEAP
    free(sprites);

}
