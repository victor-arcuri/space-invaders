#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utilidades.h"

float ease_in_out_sine(float t) {
    return -(cos(M_PI * t) - 1) / 2;
}

float ease_in_quad(float t) {
    return t * t;
}

bool colisao(HITBOX hitbox1, HITBOX hitbox2){
    if(hitbox1.x1 > hitbox2.x2) return false;
    if(hitbox1.x2 < hitbox2.x1) return false;
    if(hitbox1.y1 > hitbox2.y2) return false;
    if(hitbox1.y2 < hitbox2.y1) return false;
    return true;
}

int intervalo_aleatorio(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

float intervalo_aleatorio_float(float min, float max)
{
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

ALLEGRO_BITMAP* gerar_mask_com_alpha(ALLEGRO_BITMAP* bitmap_original) {
    int largura = al_get_bitmap_width(bitmap_original);
    int altura = al_get_bitmap_height(bitmap_original);

    ALLEGRO_BITMAP* bitmap_alpha = al_create_bitmap(largura, altura);
    ALLEGRO_BITMAP* anterior = al_get_target_bitmap();
    
    al_set_target_bitmap(bitmap_alpha);
    al_lock_bitmap(bitmap_original, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
    al_lock_bitmap(bitmap_alpha, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            ALLEGRO_COLOR cor = al_get_pixel(bitmap_original, x, y);
            unsigned char r, g, b, a;
            al_unmap_rgba(cor, &r, &g, &b, &a);

            // A cor final será branca com alpha proporcional à intensidade (assumindo imagem em tons de cinza)
            float intensidade = (r + g + b) / 3.0f / 255.0f;
            ALLEGRO_COLOR cor_com_alpha = al_map_rgba(255, 255, 255, (int)(intensidade * 255));

            al_put_pixel(x, y, cor_com_alpha);
        }
    }

    al_unlock_bitmap(bitmap_original);
    al_unlock_bitmap(bitmap_alpha);
    al_set_target_bitmap(anterior);

    return bitmap_alpha;
}