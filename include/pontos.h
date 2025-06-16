#ifndef PONTOS_H
#define PONTOS_H
#include <stdio.h>
#include "utilidades.h"
#include "sons.h"

typedef struct CANHAO CANHAO;

#define PONTOS_VIDA_NOVA 1000
#define PONTUACAO_MAXIMA 9990
#define PONTOS_ALIEN_1 30
#define PONTOS_ALIEN_2 20 
#define PONTOS_ALIEN_3 10   

typedef struct {
    int highscore;
    int score_atual;
    int proxima_vida;
} PONTOS;

PONTOS * iniciar_pontos();
int criar_highscore();
void pontuar(PONTOS* pontos, int tipo_alien, CANHAO* canhao, AUDIO* audio);
void verificar_highscore(PONTOS* pontos);
void atualizar_highscore(PONTOS* pontos);
void verifica_vida_nova(PONTOS* pontos, CANHAO* canhao, AUDIO* audio);
void finalizar_pontos(PONTOS* pontos);

#endif