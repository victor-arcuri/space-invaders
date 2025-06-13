#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "inicializacao.h"
#include "display.h"
#include "barreira.h"
#include "sprites.h"

// Cria o bitmap da linha de varredura
LINHA* iniciar_linha_varredura(){
    ALLEGRO_BITMAP* linha_bitmap = al_create_bitmap(BUFFER_W, 1);
    al_set_target_bitmap(linha_bitmap);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    LINHA* linha = (LINHA*) malloc(sizeof(LINHA));
    linha->bitmap = linha_bitmap;
    ALLEGRO_BITMAP* linha_bitmap_editavel = al_clone_bitmap(linha_bitmap);
    linha->bitmap_editavel = linha_bitmap_editavel;
    tenta_iniciar(linha, "linha");
    return linha;
}

//Desenha a linha
void draw_linha(LINHA* linha){
    //al_draw_bitmap(linha->bitmap_editavel, 0, LINHA_VARREDURA_Y, 0);
}

BARREIRA* iniciar_barreiras(SPRITES* sprites){
    BARREIRA* barreiras = (BARREIRA*) malloc(sizeof(BARREIRA) * 4);
    barreiras[0].bitmap_original = sprites->barreira.bitmap;
    barreiras[1].bitmap_original = sprites->barreira.bitmap;
    barreiras[2].bitmap_original = sprites->barreira.bitmap;
    barreiras[3].bitmap_original = sprites->barreira.bitmap;

    barreiras[0].bitmap_editavel = al_clone_bitmap(barreiras[0].bitmap_original);
    barreiras[1].bitmap_editavel = al_clone_bitmap(barreiras[1].bitmap_original);
    barreiras[2].bitmap_editavel = al_clone_bitmap(barreiras[2].bitmap_original);
    barreiras[3].bitmap_editavel = al_clone_bitmap(barreiras[2].bitmap_original);

    barreiras[0].x = BARREIRA_1_X;
    barreiras[0].y = BARREIRA_1_Y;

    barreiras[1].x = BARREIRA_2_X;
    barreiras[1].y = BARREIRA_2_Y;

    barreiras[2].x = BARREIRA_3_X;
    barreiras[2].y = BARREIRA_3_Y;

    barreiras[3].x = BARREIRA_4_X;
    barreiras[3].y = BARREIRA_4_Y;
    
    barreiras[0].hitbox.x1 = BARREIRA_1_X;
    barreiras[0].hitbox.y1 = BARREIRA_1_Y;
    barreiras[0].hitbox.x2 = BARREIRA_1_X + BARREIRA_WIDTH;
    barreiras[0].hitbox.y2 = BARREIRA_1_Y + BARREIRA_HEIGHT;

    barreiras[1].hitbox.x1 = BARREIRA_2_X;
    barreiras[1].hitbox.y1 = BARREIRA_2_Y;
    barreiras[1].hitbox.x2 = BARREIRA_2_X + BARREIRA_WIDTH;
    barreiras[1].hitbox.y2 = BARREIRA_2_Y + BARREIRA_HEIGHT;

    barreiras[2].hitbox.x1 = BARREIRA_3_X;
    barreiras[2].hitbox.y1 = BARREIRA_3_Y;
    barreiras[2].hitbox.x2 = BARREIRA_3_X + BARREIRA_WIDTH;
    barreiras[2].hitbox.y2 = BARREIRA_3_Y + BARREIRA_HEIGHT;

    barreiras[3].hitbox.x1 = BARREIRA_4_X;
    barreiras[3].hitbox.y1 = BARREIRA_4_Y;
    barreiras[3].hitbox.x2 = BARREIRA_4_X + BARREIRA_WIDTH;
    barreiras[3].hitbox.y2 = BARREIRA_4_Y + BARREIRA_HEIGHT;
    return barreiras;
}

void finalizar_barreiras(BARREIRA* barreiras){
    free(barreiras);
}

void draw_barreiras(BARREIRA* barreiras){
    for (int i = 0; i < 4; i++){
        al_draw_bitmap(barreiras[i].bitmap_editavel, barreiras[i].x, barreiras[i].y, 0);
    }
}

void danificar_barreira(ALLEGRO_BITMAP* bitmap, BARREIRA barreira, int x, int y) {
    ALLEGRO_BITMAP* bitmask = gerar_mask_com_alpha(bitmap);
    ALLEGRO_BITMAP* bitmap_anterior = al_get_target_bitmap();

    int mask_w = al_get_bitmap_width(bitmask);
    int mask_h = al_get_bitmap_height(bitmask);

    int local_x = x - barreira.x;
    int local_y = y - barreira.y;

    // Calcular retângulo de interseção entre a máscara e a barreira
    int src_x = 0;
    int src_y = 0;
    int dest_x = local_x;
    int dest_y = local_y;
    int draw_w = mask_w;
    int draw_h = mask_h;

    // Ajustar se estiver parcialmente fora à esquerda ou acima
    if (dest_x < 0) {
        src_x = -dest_x;
        draw_w -= src_x;
        dest_x = 0;
    }
    if (dest_y < 0) {
        src_y = -dest_y;
        draw_h -= src_y;
        dest_y = 0;
    }

    // Ajustar se estiver parcialmente fora à direita ou abaixo
    if (dest_x + draw_w > BARREIRA_WIDTH) {
        draw_w = BARREIRA_WIDTH - dest_x;
    }
    if (dest_y + draw_h > BARREIRA_HEIGHT) {
        draw_h = BARREIRA_HEIGHT - dest_y;
    }

    // Garantir que ainda há algo a desenhar
    if (draw_w > 0 && draw_h > 0) {
        al_set_target_bitmap(barreira.bitmap_editavel);
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ZERO, ALLEGRO_INVERSE_ALPHA);

        al_draw_bitmap_region(bitmask, src_x, src_y, draw_w, draw_h, dest_x, dest_y, 0);

        al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
        al_set_target_bitmap(bitmap_anterior);
    }

    al_destroy_bitmap(bitmask); 
}
// Checa se o ponto passado possui pixel ativo com alpha transparente ou não. Se estiver visível, retorna true, caso contrário, false
bool checa_integridade_posicao(BARREIRA barreira, int x, int y){
    int local_x = x - barreira.x;
    int local_y = y - barreira.y;
    if (local_x > BARREIRA_WIDTH || local_x < 0 || local_y > BARREIRA_HEIGHT || local_y < 0) return false;
    
    ALLEGRO_BITMAP *bitmap_anterior = al_get_target_bitmap();

    al_set_target_bitmap(barreira.bitmap_editavel);

    ALLEGRO_COLOR cor = al_get_pixel(barreira.bitmap_editavel, local_x, local_y);

    al_set_target_bitmap(bitmap_anterior);

    unsigned char r, g, b, a;
    al_unmap_rgba(cor, &r, &g, &b, &a);

    return a == 255;

}

void danificar_linha(int x, LINHA* linha) {
    ALLEGRO_BITMAP* bitmap_anterior = al_get_target_bitmap();

    al_set_target_bitmap(linha->bitmap_editavel);
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ZERO, ALLEGRO_INVERSE_ALPHA);

    if (x < 0) x = 0;
    if (x > BUFFER_W - 2) x = BUFFER_W - 2;

    al_draw_filled_rectangle(x, 0, x + 2, 1, al_map_rgba(0, 0, 0, 255));

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
    al_set_target_bitmap(bitmap_anterior);
}