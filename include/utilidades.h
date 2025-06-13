#ifndef UTILIDADES_H
#define UTILIDADES_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
typedef struct {
    int x1, y1, x2, y2;
} HITBOX;


float ease_in_out_sine(float t);

float ease_in_quad(float t);

bool colisao(HITBOX hitbox1, HITBOX hitbox2);

int intervalo_aleatorio(int min, int max);

float intervalo_aleatorio_float(float min, float max);
ALLEGRO_BITMAP* gerar_mask_com_alpha(ALLEGRO_BITMAP* bitmap_original);

#endif