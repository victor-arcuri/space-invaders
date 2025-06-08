#include <allegro5/allegro5.h>
#include "inicializacao.h"
#include "display.h"
#include "overlay.h"

// Inicializa os overlays, alocando espaço na memória HEAP
OVERLAYS* iniciar_overlays()
{
    OVERLAYS* overlays = (OVERLAYS *) malloc(sizeof(OVERLAYS));
    tenta_iniciar(overlays, "overlays");
    
    overlays->overlay_original.bitmap = al_load_bitmap("assets/img/arcade-overlay.png");
    overlays->overlay_original.img_w = 1920;
    overlays->overlay_original.img_h = 1080;
    overlays->overlay_original.tela_w = 786;
    overlays->overlay_original.tela_h = 538;
    overlays->overlay_original.tela_x = 543;
    overlays->overlay_original.tela_y = 367;

    return overlays;

}

// Desenha o buffer do display redimensionado para o overlay
void desenha_buffer_e_overlay(OVERLAY overlay, DISPLAY* display)
{
    // Descobre as proporções corretas do overlay
    int screen_w = al_get_display_width(display->display);
    int screen_h = al_get_display_height(display->display);

    float escala_overlay = fmin((float)screen_w / overlay.img_w, (float)screen_h / overlay.img_h);

    int overlay_w = overlay.img_w * escala_overlay;
    int overlay_h = overlay.img_h * escala_overlay;

    int overlay_x =(screen_w - overlay_w) / 2;
    int overlay_y = (screen_h - overlay_h )/ 2;

    int tela_x = overlay_x + overlay.tela_x * escala_overlay;
    int tela_y = overlay_y + overlay.tela_y * escala_overlay;
    int tela_w = overlay.tela_w * escala_overlay;
    int tela_h = overlay.tela_h * escala_overlay;

    float escala_jogo = fmin((float)tela_w / BUFFER_W, (float)tela_h / BUFFER_H);
    int draw_w = BUFFER_W * escala_jogo;
    int draw_h = BUFFER_H * escala_jogo;
    int draw_x = tela_x + (tela_w - draw_w) / 2;
    int draw_y = tela_y + (tela_h - draw_h) / 2;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Desenha o buffer do jogo na tela, com a posição correta em relação ao overlay
    al_draw_scaled_bitmap(display->buffer, 0, 0, BUFFER_W, BUFFER_H, draw_x, draw_y, draw_w, draw_h, 0);

    // Desenha o overlay escalado na tela
    al_draw_scaled_bitmap(overlay.bitmap, 0, 0, 1920, 1080, overlay_x, overlay_y, overlay_w, overlay_h, 0);

}

// Finaliza os overlays, liberando espaço na memória HEAP
void finalizar_overlays(OVERLAYS* overlays){
    al_destroy_bitmap(overlays->overlay_original.bitmap);
    free(overlays);
}