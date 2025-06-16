#ifndef SONS_H
#define SONS_H
#include <string.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>


#include <inicializacao.h>

typedef struct{
    ALLEGRO_SAMPLE* arcade_ligando;
    ALLEGRO_SAMPLE* arcade_desligando;

    ALLEGRO_SAMPLE* canhao_tiro;
    ALLEGRO_SAMPLE* canhao_explosao;

    ALLEGRO_SAMPLE* nave_misterio;
    ALLEGRO_SAMPLE* nave_explosao;
    ALLEGRO_SAMPLE** nave_movimento;
    
    ALLEGRO_SAMPLE* nova_vida;

    ALLEGRO_AUDIO_STREAM* estatica_arcade;

} AUDIO;

ALLEGRO_SAMPLE* pegar_audio_sample(char* arquivo);

AUDIO* iniciar_audio();

void finalizar_audio(AUDIO* audio);

ALLEGRO_AUDIO_STREAM* pegar_audio_stream(char* arquivo);
#endif