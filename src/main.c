// Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Bibliotecas Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

// Módulos customizados
#include "inicializacao.h"
#include "display.h"
#include "sprites.h"
#include "teclado.h"
#include "canhao.h"
#include "overlay.h"
#include "nave.h"
#include "barreira.h"
#include "pontos.h"
#include "texto.h"
#include "hud.h"
#include "menu.h"
#include "sons.h"

//Variáveis globais
long frames;
float zoom_max = 2.0f;
float zoom_min = 1.6;
float const FPS = 60;


void partida(AUDIO* audio, PONTOS* pontos, ALLEGRO_EVENT_QUEUE* queue, DISPLAY* display, SPRITES* sprites, TECLADO* teclado, OVERLAYS* overlays, OVERLAY overlay_atual, FONTE* fonte, float* zoom_atual, float velocidade_jogo, bool* perdeu_jogo, bool* finalizar_jogo){
    CANHAO* canhao = iniciar_canhao(sprites);
    NAVES* naves = iniciar_naves(sprites, velocidade_jogo);    
    LINHA* linha = iniciar_linha_varredura();
    BARREIRA* barreiras = iniciar_barreiras(sprites);
    HUD* hud = iniciar_hud(canhao, pontos, fonte,sprites);

    //Prepara o visual inicial da partida
    pre_draw_display(display);
    draw_barreiras(barreiras);
    draw_linha(linha);
    draw_hud(hud);
    cria_faixas_coloridas();
    pos_draw_display(display, overlay_atual, *zoom_atual, zoom_max);
    naves_animacao_spawn(naves, display, overlay_atual, *zoom_atual, zoom_max);
    
    ALLEGRO_EVENT evento;
    bool finalizar = false;
    bool vitoria = false;
    bool redraw;
    int delay_inicio_max = 120;
    int delay_inicio_atual = 0;

    // Loop principal do jogo
    while (1)
    {
        al_wait_for_event(queue, &evento);

        switch(evento.type)
        {
            case ALLEGRO_EVENT_TIMER:

                // Atualiza a lógica dos elementos do jogo
                if (delay_inicio_atual < delay_inicio_max){
                    delay_inicio_atual++;
                    redraw = true;
                    frames++;
                    break;
                }
                if (teclado->teclas[ALLEGRO_KEY_ESCAPE])
                {
                    finalizar = true;
                }

                atualizar_canhao(audio, canhao, teclado,naves,barreiras,perdeu_jogo);
                atualizar_naves(audio, naves, canhao, sprites, barreiras, linha, pontos,perdeu_jogo,&vitoria);

                redraw = true;
                frames++;
                break;
                

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                finalizar = true;
                break;
        }

        if (finalizar){
            *finalizar_jogo = true;
            break;
        }

        if (*perdeu_jogo){
            break;
        }

        if (vitoria){
            break;
        }
        
        atualizar_teclado(&evento, teclado);

        // Se estivermos em um novo frame sem que o redraw seja feito e todos os eventos tenham sido tratados, faz o redraw
        if (redraw && al_is_event_queue_empty(queue))
        {
            // Preparação do redraw
            pre_draw_display(display);
            al_clear_to_color(al_map_rgb(0,0,0));

            // Funções do redraw
            draw_barreiras(barreiras);
            draw_naves(naves);
            draw_canhao(canhao);
            draw_linha(linha);
            draw_hud(hud);


            // Aplica as faixas de cores
            cria_faixas_coloridas();

            // Finalização do redraw
            pos_draw_display(display,overlay_atual,*zoom_atual,zoom_max);
            redraw = false;
        }
    }

    if (*perdeu_jogo){
        verificar_highscore(pontos);
        pre_draw_display(display);
        draw_barreiras(barreiras);
        draw_naves(naves);
        draw_canhao(canhao);
        draw_linha(linha);
        draw_hud(hud);
        cria_faixas_coloridas();
        typewrite_game_over(fonte,display,overlay_atual,*zoom_atual,zoom_max);
        bool voltar_menu = false;
        while(1){
            al_wait_for_event(queue, &evento);

            switch(evento.type)
            {
                case ALLEGRO_EVENT_TIMER:
                    frames++;
                    break;

                case ALLEGRO_EVENT_KEY_DOWN:
                    // Evita chamadas múltiplas para a função
                    if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                        voltar_menu = true;
                    }
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    finalizar = true;
                    break;
            }
            if (finalizar){
                *finalizar_jogo = true;
                break;
            }
            if (voltar_menu){
                break;
            }
        }
    }
    // Finaliza recursos da partida
    finalizar_canhao(canhao);
    finalizar_naves(naves);
    finalizar_barreiras(barreiras);
    finalizar_hud(hud);
}

void jogar(AUDIO* audio, ALLEGRO_EVENT_QUEUE* queue, DISPLAY* display, SPRITES* sprites, TECLADO* teclado, OVERLAYS* overlays, OVERLAY overlay_atual, FONTE* fonte, float* zoom_atual,bool* finalizar_jogo){
    
    float velocidade_jogo = 1;
    bool perdeu_jogo = false;

    PONTOS* pontos = iniciar_pontos();

    while (*zoom_atual < zoom_min){
        *zoom_atual += 1/FPS;
        pos_draw_display(display, overlay_atual, *zoom_atual, zoom_max);
    }

    while (true){
        if (perdeu_jogo) break;
        partida(audio, pontos, queue, display, sprites, teclado, overlays, overlay_atual, fonte, zoom_atual, velocidade_jogo, &perdeu_jogo, finalizar_jogo);
        velocidade_jogo*=1.5;
        if (*finalizar_jogo) return;
    }

    while (*zoom_atual > 1.0f){
        *zoom_atual -= 1/FPS;
        pos_draw_display(display, overlay_atual, *zoom_atual, zoom_max);
    }

    finalizar_pontos(pontos);
}

void main_menu(AUDIO* audio, ALLEGRO_EVENT_QUEUE* queue, DISPLAY* display, SPRITES* sprites, TECLADO* teclado, OVERLAYS* overlays, OVERLAY overlay_atual, FONTE* fonte, float* zoom_atual, bool* finalizar){
    // Animações iniciais do arcade
    ligar_arcade_animacao(audio, display,overlay_atual, *zoom_atual, zoom_max);
    al_flush_event_queue(queue);
    ALLEGRO_EVENT evento;
    bool redraw = false;
    bool completo = false;
    // Loop principal do menu
    while (true){
        al_wait_for_event(queue, &evento);

        switch(evento.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // Atualiza a lógica dos elementos do menu
                if (teclado->teclas[ALLEGRO_KEY_ESCAPE])
                {
                    *finalizar = true;
                }
                redraw = true;
                frames++;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                // Evita chamadas múltiplas para a função
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    jogar(audio, queue, display, sprites, teclado, overlays, overlay_atual, fonte, zoom_atual, finalizar);
                    completo = false;
                }
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                *finalizar = true;
                break;
        }

        if (redraw && al_event_queue_is_empty(queue)){
            redraw = false;
            pre_draw_display(display);
            typewrite_menu_principal(fonte, display,overlay_atual, *zoom_atual, zoom_max, &completo);
        }

        if(*finalizar){
            // Animação de desligamento do arcade
            al_set_audio_stream_playing(audio->estatica_arcade, false); 
            al_play_sample(audio->arcade_desligando, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            pre_draw_display(display);
            pos_draw_display(display,overlay_atual, *zoom_atual, zoom_max);
            al_rest(2);
            break;

        }

        atualizar_teclado(&evento, teclado);
    }
}

int main(){

    // Define a seed de pseudo-aleatoriedade
    srand(time(NULL));

    // Tenta inicializar recursos da engine
    tenta_iniciar(al_init(), "allegro");
    tenta_iniciar(al_install_keyboard(), "teclado");
    tenta_iniciar(al_init_image_addon(), "imagens");
    tenta_iniciar(al_init_primitives_addon(), "primitives");
 
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    tenta_iniciar(timer, "timer");
 
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    tenta_iniciar(queue, "event queue");
 
     // Tenta incializar recursos customizados
    DISPLAY* display = iniciar_display();
    SPRITES* sprites = iniciar_sprites();
    TECLADO* teclado = iniciar_teclado();
    OVERLAYS* overlays = iniciar_overlays();
    FONTE* fonte = iniciar_fonte(sprites);
    AUDIO* audio = iniciar_audio();

    // Registra fontes de eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display->display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
 
    // Variáveis locais do jogo
    bool finalizar = false;

    float zoom_atual = 1.0;

    // Inicializa o timer do jogo
    al_start_timer(timer);
    
 
    //Define o overlay inicial
    OVERLAY overlay_atual = overlays->overlay_original;
 
    // Loop principal do jogo
    while (1)
    {
        main_menu(audio, queue, display, sprites, teclado, overlays, overlay_atual, fonte, &zoom_atual, &finalizar);
        if (finalizar){
            break;
        }
    }

    // Finaliza funções customizadas
    finalizar_display(display);
    finalizar_sprites(sprites);
    finalizar_teclado(teclado);
    finalizar_overlays(overlays);
    finalizar_fonte(fonte);
    finalizar_audio(audio);

    //Finaliza recursos da engine
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}   