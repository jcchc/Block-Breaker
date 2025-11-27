#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "raylib.h"
#include "game_def.h" // Importa as definições de Player, Ball, etc.
#include "blocks.h"   // Importa a definição de Bloco
#include <stdbool.h>

// --- VARIÁVEIS GLOBAIS COMPARTILHADAS (EXTERN) ---
// O 'extern' avisa ao compilador que essas variáveis 
// estão definidas no game_logic.c, mas podem ser usadas aqui.

extern Player player;
extern Ball ball;
extern Bloco *listaBlocos;

extern int pontuacao;
extern int nivel;
extern int vidas;

extern GameScreen currentState; // Estado atual do jogo

// Ranking Real (Lido do arquivo)
extern int topScores[5]; 

// Timers para controle de fluxo
extern float roundTimer; 

// --- PROTÓTIPOS DE FUNÇÕES ---
// Funções principais da lógica do jogo
void IniciarJogo(Player *p, Ball *b, Bloco **l);
void AtualizarLogica(Player *p, Ball *b, Bloco **l);

#endif