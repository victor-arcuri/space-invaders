#ifndef OVERLAY_H
#define OVERLAY_H

#include <allegro5/allegro5.h>
#include "inicializacao.h"
#include "display.h"


typedef struct {
    ALLEGRO_BITMAP* bitmap;
    int img_w, img_h;
    int tela_w, tela_h;
    int tela_x, tela_y;
} OVERLAY;

typedef struct {
    OVERLAY overlay_original;
} OVERLAYS;

typedef struct DISPLAY DISPLAY;

OVERLAYS* iniciar_overlays();

void desenha_buffer_e_overlay(OVERLAY overlay, struct DISPLAY* display, float zoom_atual, float zoom_max);


void finalizar_overlays(OVERLAYS* overlays);

#endif