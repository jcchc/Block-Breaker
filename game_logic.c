#include "game_logic.h"
#include <stdlib.h>

Player player;
Ball ball;
Bloco *listaBlocos = NULL;

int pontuacao = 0;
int nivel = 1;
int vidas = 3;
GameScreen currentState = MENU;
int fakeRankings[5] = {1200, 950, 700, 400, 100};
bool jogoFinalizado = false;
float roundTimer = 0.0f;
float respawnTimer = 0.0f;

const int LARGURA_TELA = 900;
const int ALTURA_TELA = 650;

void IniciarJogo(Player *p, Ball *b, Bloco **l) {
    p->rect = (Rectangle){ LARGURA_TELA/2 - 50, ALTURA_TELA - 40, 100, 20 };
    p->velocidade = 7.0f;
    p->vidas = 3;

    b->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
    b->velocidade = (Vector2){ 3.2f, -3.2f };
    b->raio = 8.0f;
    b->ativa = true;

    pontuacao = 0;
    nivel = 1;
    vidas = 3;
    jogoFinalizado = false;
    roundTimer = 0.0f;
    respawnTimer = 0.0f;

    if (*l != NULL) destruirLista(*l);
    *l = gerarBlocos(nivel);
}

void AtualizarLogica(Player *p, Ball *b, Bloco **l) {
    if (currentState == MENU) {
        if (IsKeyPressed(KEY_ENTER)) {
            IniciarJogo(p, b, l);
            currentState = GAMEPLAY;
        }
        return;
    }

    if (currentState == GAME_OVER) {
        if (IsKeyPressed(KEY_R)) currentState = MENU;
        return;
    }

    if (roundTimer > 0) {
        roundTimer -= GetFrameTime();
        return;
    }

    if (respawnTimer > 0) {
        respawnTimer -= GetFrameTime();
    }

    if (IsKeyDown(KEY_LEFT)) p->rect.x -= p->velocidade;
    if (IsKeyDown(KEY_RIGHT)) p->rect.x += p->velocidade;
    if (p->rect.x < 0) p->rect.x = 0;
    if (p->rect.x > LARGURA_TELA - p->rect.width) p->rect.x = LARGURA_TELA - p->rect.width;

    float mult = 1.0f + (nivel * 0.1f);

    if (respawnTimer > 0) {
        b->posicao.x += b->velocidade.x * mult * 0.35f;
        b->posicao.y += b->velocidade.y * mult * 0.35f;
    } else {
        b->posicao.x += b->velocidade.x * mult;
        b->posicao.y += b->velocidade.y * mult;
    }

    if (b->posicao.x <= b->raio || b->posicao.x >= LARGURA_TELA - b->raio) b->velocidade.x *= -1;
    if (b->posicao.y <= b->raio) b->velocidade.y *= -1;

    if (CheckCollisionCircleRec(b->posicao, b->raio, p->rect)) {
        b->velocidade.y *= -1;
        b->posicao.y = p->rect.y - b->raio - 1;
    }

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

    if (todosBlocosDestruidos(*l)) {
        nivel++;
        destruirLista(*l);
        *l = gerarBlocos(nivel);

        b->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
        b->velocidade = (Vector2){ 3.2f, -3.2f };

        roundTimer = 3.0f;
        respawnTimer = 1.5f;
    }

    if (b->posicao.y > ALTURA_TELA) {
        p->vidas--;
        vidas = p->vidas;

        if (p->vidas <= 0) currentState = GAME_OVER;
        else {
            b->posicao = (Vector2){ LARGURA_TELA/2, ALTURA_TELA/2 };
            b->velocidade = (Vector2){ 3.2f, -3.2f };
            respawnTimer = 1.5f;
        }
    }
}
