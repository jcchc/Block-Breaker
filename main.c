#include "raylib.h"
#include "game_def.h"
#include "game_logic.h"
#include "graphics.h"
#include "blocks.h"

int main(void) {
    InitWindow(900, 650, "Block Breaker Final");
    SetTargetFPS(60);

    InitGraphics();
    
    // Chama o Iniciar para configurar memória, mas o estado começa como MENU
    IniciarJogo(&player, &ball, &listaBlocos); 
    currentState = MENU; // Garante menu

    while (!WindowShouldClose()) {
        
        // 1. Atualiza (Lógica + Menu)
        AtualizarLogica(&player, &ball, &listaBlocos);

        // 2. Desenha
        BeginDrawing();
        ClearBackground((Color){20, 20, 30, 255});
        DrawGameFrame(); // Desenha Menu, Jogo ou GameOver
        EndDrawing();
    }

    destruirLista(listaBlocos);
    UnloadGraphics();
    CloseWindow();
    return 0;
}