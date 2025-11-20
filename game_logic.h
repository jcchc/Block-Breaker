#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "raylib.h"
#include <stdbool.h>
#include "blocks.h" // <--- AQUI O SEGREDO: Incluímos o seu arquivo!

// --- Enumerações ---
typedef enum {
    MENU = 0,
    GAMEPLAY,
    RANKINGS,
    GAME_OVER
} GameScreen;

// --- Estruturas (Bola e Player ficam aqui pois são da lógica) ---

typedef struct {
    Rectangle rect;   // Posição e tamanho da raquete
    float velocidade;
    int vidas;
} Player;

typedef struct {
    Vector2 posicao;
    Vector2 velocidade;
    float raio;
    bool ativa;
} Ball;

// OBS: Não definimos "Bloco" aqui porque já veio do "blocks.h"

// --- Variáveis Globais Compartilhadas ---
extern int pontuacao;
extern int nivel;
extern bool jogoFinalizado;

// --- Protótipos das Funções LÓGICAS (Sem desenho) ---

// Inicializadores
void IniciarJogo(Player *player, Ball *ball, Bloco **listaBlocos);

// Atualizador (O Cérebro do Jogo)
// Recebe ponteiros para poder modificar os valores
void AtualizarLogica(Player *player, Ball *ball, Bloco **listaBlocos);

#endif