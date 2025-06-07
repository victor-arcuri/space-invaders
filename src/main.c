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

int main(){

    // Define constantes do código
    float const FPS = 60;

    // Tenta inicializar recursos da engine
    tenta_iniciar(al_init(), "allegro");
    tenta_iniciar(al_install_keyboard(), "teclado");
    tenta_iniciar(al_init_image_addon(), "imagens");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    tenta_iniciar(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    tenta_iniciar(queue, "event queue");

    // Tenta incializar recursos customizados
    DISPLAY* display = iniciar_display();
    SPRITES* sprites = iniciar_sprites();


    // Inicializa o timer do jogo
    al_start_timer(timer);

    al_rest(2);

    // Finaliza funções customizadas
    finalizar_display(display);
    finalizar_sprites(sprites);

    //Finaloza recursos da engine
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

}