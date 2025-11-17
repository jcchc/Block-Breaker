#include "raylib.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Block Breaker PIF - TESTE");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("PARABENS, A JANELA ABRIU!", 190, 200, 20, DARKGRAY);
        DrawCircleV((Vector2){ screenWidth/2, screenHeight/2 }, 50, MAROON); // Desenha um círculo

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}