#include "game_logic.h"
#include <stdlib.h> // Para NULL

// =========================================================
// 1. CRIAÇÃO DAS VARIÁVEIS GLOBAIS
// (Sem 'extern' aqui. Aqui elas nascem.)
// =========================================================
Player player;
Ball ball;
Bloco *listaBlocos = NULL;

int pontuacao = 0;
int nivel = 1;
int vidas = 3;
GameScreen currentState = MENU;
int fakeRankings[5] = {1200, 950, 700, 400, 100};
bool jogoFinalizado = false;
float roundTimer = 0.0f; // <--- O Timer nasce aqui!

// Constantes locais
const int LARGURA_TELA = 900;
const int ALTURA_TELA = 650;

// =========================================================
// 2. FUNÇÕES LÓGICAS
// =========================================================

void IniciarJogo(Player *p, Ball *b, Bloco **l) {
    p->rect = (Rectangle){ LARGURA_TELA/2 - 50, ALTURA_TELA - 40, 100, 20 };
    p->velocidade = 7.0f;
    p->vidas = 3;

    b->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
    b->velocidade = (Vector2){ 4.0f, -4.0f };
    b->raio = 8.0f;
    b->ativa = true;

    pontuacao = 0;
    nivel = 1;
    vidas = 3;
    jogoFinalizado = false;
    roundTimer = 0.0f;
    
    // NÃO mudamos currentState aqui. O Menu decide quando mudar.

    if (*l != NULL) destruirLista(*l);
    *l = gerarBlocos(nivel); 
}

void AtualizarLogica(Player *p, Ball *b, Bloco **l) {
    
    // --- LÓGICA DO MENU ---
    if (currentState == MENU) {
        if (IsKeyPressed(KEY_ENTER)) {
            IniciarJogo(p, b, l);
            currentState = GAMEPLAY; // Começa o jogo!
        }
        return;
    }

    // --- LÓGICA DO GAME OVER ---
    if (currentState == GAME_OVER) {
        if (IsKeyPressed(KEY_R)) currentState = MENU;
        return;
    }

    // --- PAUSA PARA AVISO DE ROUND ---
    if (roundTimer > 0) {
        roundTimer -= GetFrameTime();
        return; // Congela o jogo
    }

    // --- LÓGICA DE JOGO (Gameplay) ---
    
    // Movimento Raquete
    if (IsKeyDown(KEY_LEFT)) p->rect.x -= p->velocidade;
    if (IsKeyDown(KEY_RIGHT)) p->rect.x += p->velocidade;
    if (p->rect.x < 0) p->rect.x = 0;
    if (p->rect.x > LARGURA_TELA - p->rect.width) p->rect.x = LARGURA_TELA - p->rect.width;

    // Movimento Bola (Mais rápido a cada nível)
    float mult = 1.0f + (nivel * 0.1f);
    b->posicao.x += b->velocidade.x * mult;
    b->posicao.y += b->velocidade.y * mult;

    // Colisões Parede
    if (b->posicao.x <= b->raio || b->posicao.x >= LARGURA_TELA - b->raio) b->velocidade.x *= -1;
    if (b->posicao.y <= b->raio) b->velocidade.y *= -1;

    // Colisão Raquete
    if (CheckCollisionCircleRec(b->posicao, b->raio, p->rect)) {
        b->velocidade.y *= -1;
        b->posicao.y = p->rect.y - b->raio - 1;
    }

    // Colisão Blocos (Sua Lista)
    Bloco *atual = *l;
    while (atual != NULL) {
        if (atual->ativo) {
            if (CheckCollisionCircleRec(b->posicao, b->raio, atual->rect)) {
                b->velocidade.y *= -1;
                atual->vida--;
                if (atual->vida <= 0) {
                    atual->ativo = false;
                    pontuacao += 100;
                }
                break;
            }
        }
        atual = atual->prox;
    }

    // Passar de Fase
    if (todosBlocosDestruidos(*l)) {
        nivel++;
        destruirLista(*l);
        *l = gerarBlocos(nivel);
        
        // Reseta bola
        b->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
        b->velocidade = (Vector2){ 4.0f, -4.0f };
        
        // Ativa o aviso de Round por 3 segundos
        roundTimer = 3.0f; 
    }

    // Perder Vida
    if (b->posicao.y > ALTURA_TELA) {
        p->vidas--;
        vidas = p->vidas;
        if (p->vidas <= 0) currentState = GAME_OVER;
        else {
            b->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
            b->velocidade = (Vector2){ 4.0f, -4.0f };
        }
    }
}