#include <allegro5/allegro5.h>
#include "display.h"
#include "inicializacao.h"

// Cria e retorna um ponteiro para um display com o tamanho da tela
DISPLAY * iniciar_display()
{
    // Display temporário para descobrir o tamanho máximo da tela
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY* disp = al_create_display(1,1);
    tenta_iniciar(disp, "display temporario");

    int screen_w = al_get_display_width(al_get_current_display());
    int screen_h = al_get_display_height(al_get_current_display());
    al_destroy_display(disp);

    // Display a ser retornado
    disp = al_create_display(screen_w, screen_h);
    tenta_iniciar(disp, "display");

    ALLEGRO_BITMAP* buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    tenta_iniciar(buffer, "buffer de bitmap");

    // Incializa um struct DISPLAY na heap, com referência para o display e o buffer, e o retorna
    DISPLAY* display = (DISPLAY *) malloc(sizeof(DISPLAY));
    display->display = disp;
    display->buffer = buffer;

    return display;
}

// Destroi o buffer e o display de um struct DISPLAY
void finalizar_display(DISPLAY *display)
{
    al_destroy_bitmap(display->buffer);
    al_destroy_display(display->display);
    free(display);
}

// Chamada antes de fazer modificações visuais para definir que devem ser feitas antes no buffer
void pre_draw_display(DISPLAY *display)
{
    al_set_target_bitmap(display->buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

// Chamada após fazer alterações visuais para passá-las do buffer para o display visual, mantendo a proporção definida
void pos_draw_display(DISPLAY *display)
{
    al_set_target_backbuffer(display->display);

    int screen_w = al_get_display_width(display->display);
    int screen_h = al_get_display_height(display->display);

    float escala = fmin((float) screen_w / BUFFER_W, (float)screen_h / BUFFER_H);
    int draw_w = BUFFER_W * escala;
    int draw_h = BUFFER_H * escala;
    int draw_x = (screen_w - draw_w) / 2;
    int draw_y = (screen_h - draw_h) / 2;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_scaled_bitmap(display-> buffer, 0, 0, BUFFER_W, BUFFER_H, draw_x, draw_y, draw_w, draw_h, 0);

    al_flip_display();
    
}


