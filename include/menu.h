#ifndef MENU_H
#define MENU_H
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include "display.h"
#include "overlay.h"
#include "texto.h"
#include "sons.h"
void ligar_arcade_animacao(AUDIO* audio, DISPLAY* display, OVERLAY overlay, float zoom_atual, float zoom_max);
void typewrite_menu_principal(FONTE* fonte, DISPLAY* display, OVERLAY overlay, float zoom_atual, float zoom_max, bool* completo);
void typewrite_game_over(FONTE* fonte, DISPLAY* display,OVERLAY overlay_atual, float zoom_atual, float zoom_max);
#endif