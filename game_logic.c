#include "game_logic.h"
#include <stdlib.h> // Para NULL

// Definição das variáveis globais
int pontuacao = 0;
int nivel = 1;
bool jogoFinalizado = false;

// Constantes locais (para saber onde bater)
const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;

void IniciarJogo(Player *player, Ball *ball, Bloco **listaBlocos) {
    // Reseta o Player
    player->rect = (Rectangle){ LARGURA_TELA/2 - 50, ALTURA_TELA - 40, 100, 20 };
    player->velocidade = 7.0f;
    player->vidas = 3;

    // Reseta a Bola
    ball->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
    ball->velocidade = (Vector2){ 4.0f, -4.0f };
    ball->raio = 8.0f;
    ball->ativa = true;

    // Reseta o Jogo
    pontuacao = 0;
    nivel = 1;
    jogoFinalizado = false;

    // Reseta e cria SEUS blocos
    if (*listaBlocos != NULL) destruirLista(*listaBlocos);
    *listaBlocos = gerarBlocos(nivel); // <--- Sua função brilhando aqui
}

void AtualizarLogica(Player *player, Ball *ball, Bloco **listaBlocos) {
    if (jogoFinalizado) return;

    // 1. Movimento da Raquete
    if (IsKeyDown(KEY_LEFT) && player->rect.x > 0) 
        player->rect.x -= player->velocidade;
    if (IsKeyDown(KEY_RIGHT) && player->rect.x < LARGURA_TELA - player->rect.width) 
        player->rect.x += player->velocidade;

    // 2. Movimento da Bola
    // Dificuldade progressiva: Aumenta velocidade com o nível
    float multiplicador = 1.0f + (nivel * 0.1f);
    ball->posicao.x += ball->velocidade.x * multiplicador;
    ball->posicao.y += ball->velocidade.y * multiplicador;

    // 3. Colisão Bola x Paredes
    if (ball->posicao.x <= ball->raio || ball->posicao.x >= LARGURA_TELA - ball->raio)
        ball->velocidade.x *= -1;
    if (ball->posicao.y <= ball->raio)
        ball->velocidade.y *= -1;

    // 4. Colisão Bola x Raquete
    if (CheckCollisionCircleRec(ball->posicao, ball->raio, player->rect)) {
        ball->velocidade.y *= -1;
        ball->posicao.y = player->rect.y - ball->raio - 1; // Desgruda
    }

    // 5. Colisão Bola x SEUS BLOCOS (Lista Encadeada)
    Bloco *atual = *listaBlocos;
    while (atual != NULL) {
        if (atual->ativo) {
            if (CheckCollisionCircleRec(ball->posicao, ball->raio, atual->rect)) {
                ball->velocidade.y *= -1; // Rebate
                atual->vida--;            // Tira vida
                
                if (atual->vida <= 0) {
                    atual->ativo = false; // Mata bloco
                    pontuacao += 100;     // Ganha ponto
                }
                break; // Bateu em um, sai do loop (evita bugs físicos)
            }
        }
        atual = atual->prox; // Vai para o próximo nó da lista
    }

    // 6. Verificar Vitória de Nível
    if (todosBlocosDestruidos(*listaBlocos)) {
        nivel++;
        // Limpa a lista velha e cria a nova (Rounds Infinitos)
        destruirLista(*listaBlocos);
        *listaBlocos = gerarBlocos(nivel);
        
        // Reseta a bola para o meio
        ball->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
        ball->velocidade = (Vector2){ 4.0f, -4.0f }; // Reinicia direção
    }

    // 7. Verificar Derrota (Game Over)
    if (ball->posicao.y > ALTURA_TELA) {
        player->vidas--;
        if (player->vidas <= 0) {
            jogoFinalizado = true;
            // Aqui entraria o salvarRanking() no futuro
        } else {
            // Perdeu vida, reseta bola
            ball->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
            ball->velocidade = (Vector2){ 4.0f, -4.0f };
        }
    }
}