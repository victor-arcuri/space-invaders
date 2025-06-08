#ifndef DISPLAY_H
#define DISPLAY_H

#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "inicializacao.h"
#include "overlay.h"

#define BUFFER_W 224
#define BUFFER_H 256

typedef struct DISPLAY   {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* buffer;
} DISPLAY;

DISPLAY* iniciar_display();

void finalizar_display(DISPLAY *display);

void pre_draw_display(DISPLAY *display);

void pos_draw_display(DISPLAY *display, OVERLAY overlay);

void cria_faixas_coloridas();

#endif