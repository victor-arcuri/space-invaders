#include <string.h>
#include <ctype.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "sprites.h"
#include "inicializacao.h"
#include "texto.h"

FONTE* iniciar_fonte(SPRITES* sprites){
    FONTE* fonte = (FONTE*) malloc(sizeof(FONTE));
    for (int i = 0; i < NUM_TECLAS; i++){
        fonte->teclas[i] = sprites->teclas[i].bitmap;
    }
    tenta_iniciar(fonte, "fonte");
    return fonte;
}

void finalizar_fonte(FONTE* fonte){
    free(fonte);
}

void desenhar_texto(char* texto, FONTE* fonte, int starting_x, int starting_y, int spacing){
    int x = starting_x;
    int y = starting_y;
    for (int i = 0; i < strlen(texto); i++){
        char c = texto[i];
        c = tolower(c);
        ALLEGRO_BITMAP* bitmap;
        switch (c){
            case 'a':
                bitmap = fonte->teclas[FONTE_TECLA_A];
                break;
            case 'b':
                bitmap = fonte->teclas[FONTE_TECLA_B];
                break;
            case 'c':
                bitmap = fonte->teclas[FONTE_TECLA_C];
                break;
            case 'd':
                bitmap = fonte->teclas[FONTE_TECLA_D];
                break;
            case 'e':
                bitmap = fonte->teclas[FONTE_TECLA_E];
                break;
            case 'f':
                bitmap = fonte->teclas[FONTE_TECLA_F];
                break;
            case 'g':
                bitmap = fonte->teclas[FONTE_TECLA_G];
                break;
            case 'h':
                bitmap = fonte->teclas[FONTE_TECLA_H];
                break;
            case 'i':
                bitmap = fonte->teclas[FONTE_TECLA_I];
                break;
            case 'j':
                bitmap = fonte->teclas[FONTE_TECLA_J];
                break;
            case 'k':
                bitmap = fonte->teclas[FONTE_TECLA_K];
                break;
            case 'l':
                bitmap = fonte->teclas[FONTE_TECLA_L];
                break;
            case 'm':
                bitmap = fonte->teclas[FONTE_TECLA_M];
                break;
            case 'n':
                bitmap = fonte->teclas[FONTE_TECLA_N];
                break;
            case 'o':
                bitmap = fonte->teclas[FONTE_TECLA_O];
                break;
            case 'p':
                bitmap = fonte->teclas[FONTE_TECLA_P];
                break;
            case 'q':
                bitmap = fonte->teclas[FONTE_TECLA_Q];
                break;
            case 'r':
                bitmap = fonte->teclas[FONTE_TECLA_R];
                break;
            case 's':
                bitmap = fonte->teclas[FONTE_TECLA_S];
                break;
            case 't':
                bitmap = fonte->teclas[FONTE_TECLA_T];
                break;
            case 'u':
                bitmap = fonte->teclas[FONTE_TECLA_U];
                break;
            case 'v':
                bitmap = fonte->teclas[FONTE_TECLA_V];
                break;
            case 'w':
                bitmap = fonte->teclas[FONTE_TECLA_W];
                break;
            case 'x':
                bitmap = fonte->teclas[FONTE_TECLA_X];
                break;
            case 'y':
                bitmap = fonte->teclas[FONTE_TECLA_Y];
                break;
            case 'z':
                bitmap = fonte->teclas[FONTE_TECLA_Z];
                break;
            case '0':
                bitmap = fonte->teclas[FONTE_TECLA_0];
                break;
            case '1':
                bitmap = fonte->teclas[FONTE_TECLA_1];
                break;
            case '2':
                bitmap = fonte->teclas[FONTE_TECLA_2];
                break;
            case '3':
                bitmap = fonte->teclas[FONTE_TECLA_3];
                break;
            case '4':
                bitmap = fonte->teclas[FONTE_TECLA_4];
                break;
            case '5':
                bitmap = fonte->teclas[FONTE_TECLA_5];
                break;
            case '6':
                bitmap = fonte->teclas[FONTE_TECLA_6];
                break;
            case '7':
                bitmap = fonte->teclas[FONTE_TECLA_7];
                break;
            case '8':
                bitmap = fonte->teclas[FONTE_TECLA_8];
                break;
            case '9':
                bitmap = fonte->teclas[FONTE_TECLA_9];
                break;
            case '<': 
                bitmap = fonte->teclas[FONTE_TECLA_MENOR_QUE];
                break;
            case '>':
                bitmap = fonte->teclas[FONTE_TECLA_MAIOR_QUE];
                break;
            case '=':
                bitmap = fonte->teclas[FONTE_TECLA_IGUAL];
                break;
            case '*':
                bitmap = fonte->teclas[FONTE_TECLA_ASTERISCO];
                break;
            case '?':
                bitmap = fonte->teclas[FONTE_TECLA_INTERROGACAO];
                break;
            case '-':
                bitmap = fonte->teclas[FONTE_TECLA_HIFEN];
                break;
            case ' ':
                bitmap = fonte->teclas[FONTE_TECLA_ESPACO];
                break;
                
        }
        //int dx = x - FONT_WIDTH;
        //int dy = y - FONT_HEIGHT / 2;
        int dx = x;
        int dy = y;

        al_draw_bitmap(bitmap, dx,dy,0);
        x+=FONT_WIDTH+spacing;
    }
}

bool typewrite(char* texto, FONTE* fonte,  int x, int y, int spacing, int *contador, int *delay_atual, int* delay_max){
    char substr[strlen(texto)+1];
    for (int i = 0; i < (*contador); i++){
        substr[i] =texto[i];
    }
    substr[*contador] ='\0';
    desenhar_texto(substr, fonte, x, y, spacing);
    if (*delay_atual < *delay_max){
        *delay_atual+=1;
        return false;
    } 
    *delay_atual = 0;
    if (*contador <  strlen(texto)) {
        *contador+=1; 
        return false;
    }
    *delay_atual = 0;
    return true;
}