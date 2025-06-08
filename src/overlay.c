#include <allegro5/allegro5.h>
#include "inicializacao.h"
#include "display.h"
#include "overlay.h"
#include "utilidades.h"

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
void desenha_buffer_e_overlay(OVERLAY overlay, DISPLAY* display, float zoom_atual, float zoom_max)
{   
    // Calcula o zoom e suaviza
    float zoom_min = 1.0f;
    float progresso_zoom = (zoom_atual - zoom_min) / (zoom_max - zoom_min); 
    if (progresso_zoom < 0) progresso_zoom = 0;
    if (progresso_zoom > 1) progresso_zoom = 1;

    float curva_senoidal = ease_in_out_sine(progresso_zoom);
    float zoom = zoom_min + (zoom_max - zoom_min) * curva_senoidal;

    // Tamanho da Tela
    int screen_w = al_get_display_width(display->display);
    int screen_h = al_get_display_height(display->display);

    // Escala do overlay após aumentar a proporção
    float escala_overlay_base = fmin((float)screen_w / overlay.img_w, (float)screen_h / overlay.img_h);
    float escala_overlay_zoom = escala_overlay_base * zoom;

    // Tamamho do overlay após aplicar escala
    int overlay_w = overlay.img_w * escala_overlay_zoom;
    int overlay_h = overlay.img_h * escala_overlay_zoom;

    // Posiciona a tela na posição correta em relação ao overlay e realiza a escala correta
    int tela_x = overlay.tela_x * escala_overlay_zoom;
    int tela_y = overlay.tela_y * escala_overlay_zoom;
    int tela_w = overlay.tela_w * escala_overlay_zoom;
    int tela_h = overlay.tela_h * escala_overlay_zoom;

    // Pega as coordenadas do centro da tela escalada
    int tela_cx = tela_x + tela_w / 2;
    int tela_cy = tela_y + tela_h / 2;

    // Offset mínimo (overlay centralizado)
    int offset_min_x = (screen_w - overlay_w) / 2;
    int offset_min_y = (screen_h - overlay_h) / 2;

    // Offset máximo (tela do jogo centralizada)
    int offset_max_x = screen_w / 2 - tela_cx;
    int offset_max_y = screen_h / 2 - tela_cy;

    int offset_x = offset_min_x + (offset_max_x - offset_min_x) * curva_senoidal;
    int offset_y = offset_min_y + (offset_max_y - offset_min_y) * curva_senoidal;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Desenha buffer do jogo
    float escala_jogo = fmin((float)tela_w / BUFFER_W, (float)tela_h / BUFFER_H);
    int draw_w = BUFFER_W * escala_jogo;
    int draw_h = BUFFER_H * escala_jogo;
    int draw_x = offset_x + tela_x + (tela_w - draw_w) / 2;
    int draw_y = offset_y + tela_y + (tela_h - draw_h) / 2;

    al_draw_scaled_bitmap(display->buffer, 0, 0, BUFFER_W, BUFFER_H, draw_x, draw_y, draw_w, draw_h, 0);

    // Desenha overlay
    al_draw_scaled_bitmap(overlay.bitmap, 0, 0, overlay.img_w, overlay.img_h, offset_x, offset_y, overlay_w, overlay_h, 0);

}

// Finaliza os overlays, liberando espaço na memória HEAP
void finalizar_overlays(OVERLAYS* overlays){
    al_destroy_bitmap(overlays->overlay_original.bitmap);
    free(overlays);
}