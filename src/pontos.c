#include <stdio.h>
#include "utilidades.h"
#include "canhao.h"
#include "sons.h"

PONTOS * iniciar_pontos()
{
    PONTOS* pontos = (PONTOS*) malloc(sizeof(PONTOS));
    pontos->highscore = criar_highscore();
    pontos->score_atual = 0;
    pontos->proxima_vida = PONTOS_VIDA_NOVA;
    return pontos;
}

int criar_highscore()
{
    FILE* arquivo;
    arquivo = fopen("highscore.txt","r");
    if (arquivo == NULL){
        arquivo = fopen("highscore.txt","w");
        fprintf(arquivo, "%d", 0);
    }
    int highscore;
    fscanf(arquivo, "%d", &highscore);
    fclose(arquivo);
    return highscore;
}

void pontuar(PONTOS* pontos, int tipo_alien, CANHAO* canhao, AUDIO* audio){
    int pontuacao;
    if (tipo_alien == TIPO_1) pontuacao = PONTOS_ALIEN_1;
    else if (tipo_alien == TIPO_2) pontuacao = PONTOS_ALIEN_2;
    else if (tipo_alien == TIPO_3) pontuacao = PONTOS_ALIEN_3;
    else {
        int r = intervalo_aleatorio(1,100);
        // 1 a 10 - 10% de chance
        if (r <= 10) pontuacao = 300;
        //11 a 30 - 20% de chance
        else if (r <= 30) pontuacao = 150;
        //31 a 60 - 30% de chance
        else if (r <= 60) pontuacao = 100; 
        //61 a 100 = 40% de chance
        else pontuacao = 50;   
    }
    pontos->score_atual+=pontuacao;
    verifica_vida_nova(pontos, canhao, audio);
}

void verificar_highscore(PONTOS* pontos){
    if (pontos->score_atual <= pontos->highscore) return;
    pontos->highscore = pontos->score_atual;
    atualizar_highscore(pontos);
}

void atualizar_highscore(PONTOS* pontos){
    FILE* arquivo;
    arquivo = fopen("highscore.txt","w");
    fprintf(arquivo, "%d", pontos->highscore);
    fclose(arquivo);
}

void verifica_vida_nova(PONTOS* pontos, CANHAO* canhao, AUDIO* audio){
    if (pontos->score_atual < pontos->proxima_vida) return;
    pontos->proxima_vida += PONTOS_VIDA_NOVA;
    if (canhao->vidas >= MAX_VIDAS) return;
    al_play_sample(audio->nova_vida, 0.7f, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    canhao->vidas++; 
}

void finalizar_pontos(PONTOS* pontos)
{
    free(pontos);
}
