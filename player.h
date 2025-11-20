#ifndef PLAYER_H
#define PLAYER_H

// Precisamos da Raylib porque vamos desenhar o texto do ranking na tela
#include "raylib.h" 

// --- FUNÇÕES DE ARQUIVO (FILE I/O) ---

/**
 * @brief Salva uma nova pontuação no arquivo 'ranking.txt'.
 * Usa o modo "append" (anexar) para não apagar os anteriores.
 * * @param nome O nome do jogador (ex: "Julio")
 * @param score A pontuação final
 */
void salvarRanking(const char *nome, int score);

/**
 * @brief Lê o arquivo 'ranking.txt' e desenha a lista na tela.
 * A Pessoa 2 vai chamar isso na tela de Game Over.
 * * @param x Posição X na tela
 * @param y Posição Y na tela
 */
void exibirRanking(int x, int y);

#endif