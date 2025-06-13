#ifndef MENU_H
#define MENU_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "display.h"
#include "overlay.h"
#include "texto.h"
void ligar_arcade_animacao(DISPLAY* display, OVERLAY overlay, int zoom_atual, int zoom_max);
void typewrite_menu_principal(FONTE* fonte, DISPLAY* display, OVERLAY overlay, int zoom_atual, int zoom_max);
#endif