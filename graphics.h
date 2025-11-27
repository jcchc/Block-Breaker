#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "raylib.h"

// --- GERENCIAMENTO DE RECURSOS VISUAIS ---

// Inicializa fontes, texturas, sons e sistemas de partículas
// Deve ser chamada após InitWindow() e InitAudioDevice()
void InitGraphics(void);

// Descarrega todos os recursos da memória (Unload)
// Deve ser chamada antes de CloseWindow()
void UnloadGraphics(void);

// --- RENDERIZAÇÃO ---

// Função principal de desenho (Máquina de Estados de Visualização)
// Seleciona o que desenhar com base no currentState (Menu, Gameplay, etc)
void DrawGameFrame(void);

// Cria um efeito visual de explosão na posição especificada
void SpawnExplosion(Vector2 pos, Color color);

// --- API DE ÁUDIO ---

void TocarSomBloco(void);      // Colisão Bola x Bloco
void TocarSomRebatida(void);   // Colisão Bola x Player
void TocarSomGameOver(void);   // Fim de jogo (Vidas <= 0)
void TocarSomPerderVida(void); // Perda de vida parcial

#endif