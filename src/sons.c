#include <string.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>


#include <inicializacao.h>
#include <sons.h>

ALLEGRO_AUDIO_STREAM* pegar_audio_stream(char* arquivo){
    char path[200] = "assets/audio/";
    strcat(path, arquivo);
    ALLEGRO_AUDIO_STREAM* audio =  al_load_audio_stream(path, 4, 2048);
    tenta_iniciar(audio, "pegar audio");
    return audio;
}

ALLEGRO_SAMPLE* pegar_audio_sample(char* arquivo){
    char path[200] = "assets/audio/";
    strcat(path, arquivo);
    ALLEGRO_SAMPLE* audio = al_load_sample(path);
    tenta_iniciar(audio, "pegar audio");
    return audio;
}

AUDIO* iniciar_audio(){
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);
    AUDIO* audio = (AUDIO*) malloc(sizeof(AUDIO));
    tenta_iniciar(audio, "audio");

    audio->arcade_ligando = pegar_audio_sample("ligar_arcade.wav");
    audio->arcade_desligando = pegar_audio_sample("desligar_arcade.wav");
    audio->estatica_arcade = pegar_audio_stream("estatica_arcade.wav");
    
    audio -> canhao_tiro = pegar_audio_sample("canhao_tiro.wav");
    audio -> canhao_explosao = pegar_audio_sample("canhao_explosao.wav");

    audio -> nave_misterio = pegar_audio_sample("nave_misterio.wav");
    audio -> nave_explosao = pegar_audio_sample("nave_explosao.wav");
    audio -> nave_movimento = (ALLEGRO_SAMPLE**) malloc(sizeof(ALLEGRO_SAMPLE*)*4);
    audio -> nave_movimento[0] = pegar_audio_sample("nave_movimento_0.wav");
    audio -> nave_movimento[1] = pegar_audio_sample("nave_movimento_1.wav");
    audio -> nave_movimento[2] = pegar_audio_sample("nave_movimento_2.wav");
    audio -> nave_movimento[3] = pegar_audio_sample("nave_movimento_3.wav");

    audio -> nova_vida = pegar_audio_sample("nova_vida.wav");


    
    
    al_set_audio_stream_gain(audio->estatica_arcade, 0.6f);
    al_set_audio_stream_loop_secs(audio->estatica_arcade, 0.0, al_get_audio_stream_length_secs(audio->estatica_arcade));
    al_set_audio_stream_playmode(audio->estatica_arcade, ALLEGRO_PLAYMODE_LOOP);
    return audio;
}

void finalizar_audio(AUDIO* audio){
    al_destroy_sample(audio->arcade_ligando);
    al_destroy_sample(audio->arcade_desligando);

    al_destroy_sample(audio->nave_explosao);
    al_destroy_sample(audio->nave_misterio);
    al_destroy_sample(audio->nave_movimento[0]);
    al_destroy_sample(audio->nave_movimento[1]);
    al_destroy_sample(audio->nave_movimento[2]);
    al_destroy_sample(audio->nave_movimento[3]);
    
    al_destroy_sample(audio->nova_vida);

    free(audio->nave_movimento);

    al_destroy_audio_stream(audio->estatica_arcade);
    
    free(audio);
}