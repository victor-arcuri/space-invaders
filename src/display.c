#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "display.h"
#include "inicializacao.h"
#include "overlay.h"

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
    
    //Define nome do jogo
    al_set_window_title(disp, "Space Invaders");

    //Define o icone do jogo
    ALLEGRO_BITMAP* icone = al_load_bitmap("assets/img/icon.png");
    if (icone)
        al_set_display_icon(disp, icone);
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
void pos_draw_display(DISPLAY *display, OVERLAY overlay, float zoom_atual, float zoom_max)
{
    al_set_target_backbuffer(display->display);

    desenha_buffer_e_overlay(overlay, display,zoom_atual, zoom_max);

    al_flip_display();
    
}

// Simula a coloração em faixas do jogo original
void cria_faixas_coloridas()
{
    // Define o modo de blending como aditivo com transparência
    al_set_blender(ALLEGRO_ADD, ALLEGRO_DEST_COLOR, ALLEGRO_ZERO);

    // Desenha o retângulo inferior verde
    int green_h = 45;
    int green_x1 = 0;
    int green_x2 = BUFFER_W;
    int green_y1 = 190;
    int green_y2 = green_y1+green_h;
    al_draw_filled_rectangle(green_x1, green_y1, green_x2, green_y2, al_map_rgba(0, 255, 0, 255));

    // Desenha o retângulo inferior verde das vidas
    int green_vida_h = 10;
    int green_vida_x1 = 20;
    int green_vida_x2 = BUFFER_W;
    int green_vida_y1 = green_y2;
    int green_vida_y2 = green_vida_y1 + green_vida_h;
    al_draw_filled_rectangle(green_vida_x1, green_vida_y1, green_vida_x2, green_vida_y2, al_map_rgba(0, 255, 0, 255));

    // Desenha o retângulo superior vermelho
    int red_h = 32;
    int red_x1 = 0;
    int red_x2 = BUFFER_W;
    int red_y1 = 32;
    int red_y2 = red_y1 + red_h;
    al_draw_filled_rectangle(red_x1, red_y1, red_x2, red_y2, al_map_rgba(255, 0, 0, 255));

    // Restaura o modo de blending padrão
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}
