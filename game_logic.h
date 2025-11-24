#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "raylib.h"
#include "game_def.h" // <--- IMPORTANTE: Pega as definições daqui!
#include "blocks.h"   // Pega a definição de Bloco daqui!
#include <stdbool.h>

// --- EXPORTANDO AS GLOBAIS (EXTERN) ---
extern Player player;
extern Ball ball;
extern Bloco *listaBlocos;

extern int pontuacao;
extern int nivel;
extern int vidas;

extern GameScreen currentState;
extern int fakeRankings[5];
extern bool jogoFinalizado;
extern float roundTimer; 

// --- FUNÇÕES ---
void IniciarJogo(Player *p, Ball *b, Bloco **l);
void AtualizarLogica(Player *p, Ball *b, Bloco **l);

#endif