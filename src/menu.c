#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include "menu.h"
#include "display.h"
#include "overlay.h"
#include "texto.h"
#include "sons.h"

void ligar_arcade_animacao(AUDIO* audio, DISPLAY* disp, OVERLAY overlay, float zoom_atual, float zoom_max) {
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* fila = al_create_event_queue();
    al_register_event_source(fila, al_get_timer_event_source(timer));
    al_start_timer(timer);

    const int largura = al_get_bitmap_width(disp->buffer);
    const int altura = al_get_bitmap_height(disp->buffer);

    const int LARGURA_BLOOM = 5;
    const int DURACAO_PRETA = 30;
    const int DURACAO_ANIMACAO = 15;
    const int DURACAO_FADEOUT = 60;

    // Tela preta no início
    for (int frame = 0; frame < DURACAO_PRETA; frame++) {
        pre_draw_display(disp);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        pos_draw_display(disp, overlay, zoom_atual, zoom_max);
        al_wait_for_event(fila, NULL);
    }
    al_play_sample(audio->arcade_ligando, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    // Linha branca de CTR crescendo
    for (int frame = 0; frame < DURACAO_ANIMACAO; frame++) {
        float t = (float)frame / DURACAO_ANIMACAO;
        float progresso = t * t;           
        float fade_in = t;
        float meio = altura / 2.0f;
        float meio_altura = progresso * altura / 2.0f;
        float linha_alpha = fade_in;

        pre_draw_display(disp);
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Bloom
        for (int i = LARGURA_BLOOM; i > 0; i--) {
            float alpha = 0.05f * i * linha_alpha;
            al_draw_filled_rectangle(
                0, meio - meio_altura - i,
                largura, meio + meio_altura + i,
                al_map_rgba_f(1, 1, 1, alpha)
            );
        }

        // Linha central com fade-in
        al_draw_filled_rectangle(
            0, meio - meio_altura,
            largura, meio + meio_altura,
            al_map_rgba_f(1, 1, 1, linha_alpha)
        );

        pos_draw_display(disp, overlay, zoom_atual, zoom_max);
        al_wait_for_event(fila, NULL);
    }

    // Fade-out para preto
    for (int frame = 0; frame < DURACAO_FADEOUT; frame++) {
        float alpha = 1.0 - (float)frame / DURACAO_FADEOUT;

        pre_draw_display(disp);
        al_clear_to_color(al_map_rgba_f(alpha, alpha, alpha, 1.0));
        pos_draw_display(disp, overlay, zoom_atual, zoom_max);
        al_wait_for_event(fila, NULL);
    }
    al_attach_audio_stream_to_mixer(audio->estatica_arcade, al_get_default_mixer());


    al_destroy_timer(timer);
    al_destroy_event_queue(fila);
}

void typewrite_menu_principal(FONTE* fonte, DISPLAY* display,OVERLAY overlay_atual, float zoom_atual, float zoom_max, bool *completo){
    char logo[20] = "SPACE INVADERS";
    int x = (BUFFER_W - (FONT_WIDTH * strlen(logo))) / 2;
    int y = 60;
    int contador = 0;
    int delay_max = 10;
    int delay_atual = 0;
    while (true){
        if (*completo) break;
        pre_draw_display(display);
        if (typewrite(logo, fonte, x,y,0,&contador,&delay_atual, &delay_max)){
            pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
            break;
        }
        pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
    }

    char jogar_text[] = "<Enter>Jogar";
    int jogar_text_x = (BUFFER_W - (strlen(jogar_text)*FONT_WIDTH))/2;
    int jogar_text_y = 130;
    contador = 0;
    delay_atual = 0;

    while (true){
        if (*completo) break;
        pre_draw_display(display);
        desenhar_texto(logo, fonte,x,y,0);
        if (typewrite(jogar_text, fonte,jogar_text_x,jogar_text_y,0,&contador,&delay_atual, &delay_max)){
            pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
            break;
        }
        pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
    }

    char sair_text[] = "<ESC>Sair";
    int sair_text_x = (BUFFER_W - (strlen(sair_text)*FONT_WIDTH))/2;
    int sair_text_y = jogar_text_y + FONT_HEIGHT + 20;
    contador = 0; 
    delay_atual = 0;

    while (true){
        if (*completo) break;
        pre_draw_display(display);
        desenhar_texto(logo, fonte,x,y,0);
        desenhar_texto(jogar_text, fonte,jogar_text_x,jogar_text_y,0);
        if (typewrite(sair_text, fonte,sair_text_x,sair_text_y,0,&contador,&delay_atual, &delay_max)){
            pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
            break;
        }
        pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
    }
    *completo = true; 


}

void typewrite_game_over(FONTE* fonte, DISPLAY* display,OVERLAY overlay_atual, float zoom_atual, float zoom_max){
    char logo[20] = "GAME OVER";
    int x = (BUFFER_W - (FONT_WIDTH * strlen(logo))) / 2;
    int y = 50;
    int contador = 0;
    int delay_max = 10;
    int delay_atual = 0;
    while (true){
        al_set_target_bitmap(display->buffer);
        if (typewrite(logo, fonte, x,y,0,&contador,&delay_atual, &delay_max)){
            cria_faixas_coloridas();
            pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
            break;
        }
        cria_faixas_coloridas();
        pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
        
    }

    char voltar_menu_texto[] = "<ENTER>MENU";
    int x_menu = (BUFFER_W - (FONT_WIDTH * strlen(voltar_menu_texto))) / 2;
    int y_menu = 80;
    contador = 0;
    delay_max = 10;
    delay_atual = 0;
    while (true){
        al_set_target_bitmap(display->buffer);
        if (typewrite(voltar_menu_texto, fonte, x_menu,y_menu,0,&contador,&delay_atual, &delay_max)){
            cria_faixas_coloridas();
            pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
            break;
        }
        cria_faixas_coloridas();
        pos_draw_display(display, overlay_atual, zoom_atual, zoom_max);
        
    }
}