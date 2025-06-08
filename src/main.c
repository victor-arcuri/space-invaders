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

//Variáveis globais
long frames;

int main(){

    // Define constantes do código
    float const FPS = 60;

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
    CANHAO* canhao = iniciar_canhao(sprites->canhao);
    OVERLAYS* overlays = iniciar_overlays();

    // Registra fontes de eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display->display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    // Variáveis locais do jogo
    ALLEGRO_EVENT evento;
    bool finalizar = false;
    bool redraw = true;
    
    float zooming = false;
    float zoom_atual = 1.6f;
    float zoom_max = 2.0f;
    // Inicializa o timer do jogo
    al_start_timer(timer);

    //Define o overlay inicial
    OVERLAY overlay_atual = overlays->overlay_original;

    // Loop principal do jogo
    while (1)
    {
        al_wait_for_event(queue, &evento);

        switch(evento.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if (teclado->teclas[ALLEGRO_KEY_ESCAPE])
                {
                    finalizar = true;
                }
                else if (teclado->teclas[ALLEGRO_KEY_TAB] && !zooming)
                {
                    zooming = true;
                }
                redraw = true;
                frames++;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                finalizar = true;
                break;
        }

        if (finalizar)
            break;
        
        atualizar_teclado(&evento, teclado);

        // Se estivermos em um novo frame sem que o redraw seja feito e todos os eventos tenham sido tratados, faz o redraw
        if (redraw && al_is_event_queue_empty(queue))
        {
            // Preparação do redraw
            pre_draw_display(display);
            al_clear_to_color(al_map_rgb(0,0,0));

            // Funções do redraw
            draw_canhao(canhao);

            // Aplica as faixas de cores
            cria_faixas_coloridas();

            // Finalização do redraw
            pos_draw_display(display,overlay_atual,zoom_atual,zoom_max);
            redraw = false;
        }
    }


    // Finaliza funções customizadas
    finalizar_display(display);
    finalizar_sprites(sprites);
    finalizar_teclado(teclado);
    finalizar_canhao(canhao);
    finalizar_overlays(overlays);

    //Finaloza recursos da engine
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;

}