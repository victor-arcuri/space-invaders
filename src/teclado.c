#include <allegro5/allegro5.h>
#include "inicializacao.h"
#include "teclado.h"

#define TECLA_PROCESSADA      1
#define TECLA_PRESSIONADA     2

// Inicializa uma array que serve para registrar o estado das teclas do teclado e retorna um ponteiro para ela
TECLADO* iniciar_teclado()
{
    TECLADO* teclado = (TECLADO*) malloc(sizeof(TECLADO));
    memset(teclado->teclas, 0, ALLEGRO_KEY_MAX);
    tenta_iniciar(teclado, "teclado");
    return teclado;
}

// Registra o estado de cada tecla pressionável do teclado
void atualizar_teclado(ALLEGRO_EVENT* evento, TECLADO* teclado)
{
    switch(evento->type){
        case ALLEGRO_EVENT_TIMER:
            for (int i = 0; i < ALLEGRO_KEY_MAX; i++){
                teclado->teclas[i] &= ~ TECLA_PROCESSADA;
            }
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            teclado->teclas[evento->keyboard.keycode] = TECLA_PRESSIONADA | TECLA_PROCESSADA;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            teclado->teclas[evento->keyboard.keycode] &= ~TECLA_PRESSIONADA;
            break;
    }
}

// Libera espaço na memória HEAP ocupado pelo teclado
void finalizar_teclado(TECLADO* teclado)
{
    free(teclado);
}



