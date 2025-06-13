#ifndef TEXTO_H
#define TEXTO_H
#include <string.h>
#include <ctype.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "sprites.h"
#include "inicializacao.h"

#define FONT_WIDTH 8
#define FONT_HEIGHT 8
#define NUM_TECLAS 43


enum {
    FONTE_TECLA_A = 0,
    FONTE_TECLA_B = 1,
    FONTE_TECLA_C = 2,
    FONTE_TECLA_D = 3,
    FONTE_TECLA_E = 4,
    FONTE_TECLA_F = 5,
    FONTE_TECLA_G = 6,
    FONTE_TECLA_H = 7,
    FONTE_TECLA_I = 8,
    FONTE_TECLA_J = 9,
    FONTE_TECLA_K = 10,
    FONTE_TECLA_L = 11,
    FONTE_TECLA_M = 12,
    FONTE_TECLA_N = 13,
    FONTE_TECLA_O = 14,
    FONTE_TECLA_P = 15,
    FONTE_TECLA_Q = 16,
    FONTE_TECLA_R = 17,
    FONTE_TECLA_S = 18,
    FONTE_TECLA_T = 19,
    FONTE_TECLA_U = 20,
    FONTE_TECLA_V = 21,
    FONTE_TECLA_W = 22,
    FONTE_TECLA_X = 23,
    FONTE_TECLA_Y = 24,
    FONTE_TECLA_Z = 25,
    FONTE_TECLA_0 = 26,
    FONTE_TECLA_1 = 27,
    FONTE_TECLA_2 = 28,
    FONTE_TECLA_3 = 29,
    FONTE_TECLA_4 = 30,
    FONTE_TECLA_5 = 31,
    FONTE_TECLA_6 = 32,
    FONTE_TECLA_7 = 33,
    FONTE_TECLA_8 = 34,
    FONTE_TECLA_9 = 35,
    FONTE_TECLA_MENOR_QUE = 36,
    FONTE_TECLA_MAIOR_QUE = 37,
    FONTE_TECLA_IGUAL = 38,
    FONTE_TECLA_ASTERISCO = 39,
    FONTE_TECLA_INTERROGACAO = 40,
    FONTE_TECLA_HIFEN = 41,
    FONTE_TECLA_ESPACO = 42

};

typedef struct {
    ALLEGRO_BITMAP* teclas[NUM_TECLAS];
} FONTE;

FONTE* iniciar_fonte(SPRITES* sprite);

void finalizar_fonte(FONTE* fonte);

void desenhar_texto(char* texto, FONTE* fonte, int starting_x, int starting_y, int spacing);

bool typewrite(char* texto, FONTE* fonte,  int x, int y, int spacing, int *contador, int *delay_atual, int* delay_max);
#endif