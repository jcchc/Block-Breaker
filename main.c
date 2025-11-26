#include "raylib.h"
#include "game_def.h"
#include "game_logic.h"
#include "graphics.h"
#include "blocks.h"

int main(void) {
    // 1. Inicia a janela com tamanho FIXO (900x650)
   
    InitWindow(900, 650, "Block Breaker Final");
    
    // 2. Configurações Importantes
    SetExitKey(KEY_NULL); 
    SetTargetFPS(60);    

    InitGraphics();
    
    // 3. Inicia o Jogo
    IniciarJogo(&player, &ball, &listaBlocos); 
    currentState = MENU; 

    while (!WindowShouldClose()) {
        
        // Se estiver no MENU e apertar ESC, aí sim fecha a janela
        if (currentState == MENU && IsKeyPressed(KEY_ESCAPE)) {
            break; 
        }

        // 4. Atualiza Lógica
        AtualizarLogica(&player, &ball, &listaBlocos);

        // 5. Desenha (Simples e Direto)
        BeginDrawing();
            ClearBackground((Color){10, 10, 15, 255}); // Fundo escuro para bordas se houver
            
            // Desenha o jogo exatamente no tamanho da janela
            DrawGameFrame(); 
        EndDrawing();
    }

    // 6. Limpeza de Memória
    destruirLista(listaBlocos);
    UnloadGraphics();
    CloseWindow();
    
    return 0;
}
