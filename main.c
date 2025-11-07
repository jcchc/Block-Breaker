#include "raylib.h"

int main(void) {
    // Inicialização da Janela
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Block Breaker PIF - TESTE");

    SetTargetFPS(60); // Define o FPS (Frames por Segundo)

    // Loop Principal do Jogo
    while (!WindowShouldClose()) { // Detecta se o usuário fechou a janela
        // --- Seção de Desenho (Draw) ---
        BeginDrawing();

        ClearBackground(RAYWHITE); // Limpa a tela com branco

        DrawText("PARABENS, A JANELA ABRIU!", 190, 200, 20, DARKGRAY);
        DrawCircleV((Vector2){ screenWidth/2, screenHeight/2 }, 50, MAROON); // Desenha um círculo

        EndDrawing();
    }

    // Finalização
    CloseWindow(); // Fecha a janela
    return 0;
}