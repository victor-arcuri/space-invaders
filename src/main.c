// Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>

// Bibliotecas Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

// Módulos customizados
#include "inicializacao.h"

int main(){

    // Define constantes do código
    float const FPS = 60;

    // Tenta inicializar recursos da engine
    tenta_iniciar(al_init(), "allegro");
    tenta_iniciar(al_install_keyboard(), "teclado");

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    tenta_iniciar(timer, "timer");
}