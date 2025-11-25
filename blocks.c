#include "blocks.h"
#include <stdlib.h>

int calcX(int col) {
    // Diminuímos de 60 para 50 para o desenho ficar mais "fechado" no centro
    int larguraBloco = 50; 
    int espaco = 5;
    
    // Calcula a largura total do grid
    int larguraTotalGrid = (12 * (larguraBloco + espaco)); 
    
    // A mágica da centralização acontece aqui:
    return ((800 - larguraTotalGrid) / 2) + (col * (larguraBloco + espaco));
}

Bloco* criarDoMapa(Bloco *head, char *desenho[10], int level) {
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            
            if (desenho[i][j] == '1') {
                Bloco *novoBloco = (Bloco*) malloc(sizeof(Bloco));
                
                novoBloco->rect = (Rectangle){ calcX(j), i * 30 + 40, 60, 20 };
                novoBloco->vida = 1;
                novoBloco->ativo = true;
                novoBloco->tipo = (level % 6) + 1;
                
                novoBloco->prox = head;
                head = novoBloco;
            }
        }
    }
    return head;
}

Bloco* gerarBlocos(int level) {
    Bloco *head = NULL;

    // ========================================
    // NÍVEIS DESENHADOS (2 até 6)
    // ========================================
    if (level >= 2 && level <= 6) {

        if (level == 2) { // ALIEN 👾
            char *mapa[] = {
                "000100001000", // Antenas
                "000010010000",
                "000111111000", // Cabeça
                "001101101100", // Olhos
                "011111111110", // Braços
                "101111111101", 
                "101000000101", // Pernas abertas
                "000110011000",
                "000000000000",
                "000000000000"
            };
            head = criarDoMapa(head, mapa, level);
        }
        else if (level == 3) { // FANTASMA 👻
            char *mapa[] = {
                "000011110000",
                "000111111000",
                "001111111100",
                "001101101100",
                "001111111100",
                "001111111100",
                "001111111100",
                "001101101100",
                "001001001000",
                "000000000000"
            };
            head = criarDoMapa(head, mapa, level);
        }
        else if (level == 4) { // EMOJI 🙂
            char *mapa[] = {
                "001111111100",
                "011111111110",
                "110111111011",
                "111111111111",
                "111111111111",
                "111000000111",
                "110111111011",
                "011011110110",
                "001111111100",
                "000000000000"
            };
            head = criarDoMapa(head, mapa, level);
        }
        else if (level == 5) { // CORAÇÃO ❤️
            char *mapa[] = {
                "000000000000",
                "011000000110",
                "111100001111",
                "111110011111",
                "011111111110",
                "001111111100",
                "000111111000",
                "000011110000",
                "000001100000",
                "000000000000"
            };
            head = criarDoMapa(head, mapa, level);
        }
        else if (level == 6) { // SETA ⬆️
            char *mapa[] = {
                "000001100000",
                "000011110000",
                "000111111000",
                "001111111100",
                "000001100000",
                "000001100000",
                "000001100000",
                "000001100000",
                "000001100000",
                "000000000000"
            };
            head = criarDoMapa(head, mapa, level);
        }

    } 
    // ========================================
    // MODO SOBREVIVÊNCIA E TUTORIAL (Nível 1 ou 7+)
    // ========================================
    else {
        int numLinhas;
        int alturaInicial = 40; // Padrão (no teto)
        int numColunas = 10;    // Padrão (tela cheia)
        int paddingX = 25;      // Margem esquerda padrão

        // --- MUDANÇA NO NÍVEL 1 ---
        if (level == 1) {
            numLinhas = 2;       // Pedido: 2 linhas
            numColunas = 8;      // Pedido: Menos colunas (era 10)
            alturaInicial = 250; // Pedido: Aproximar (mais pra baixo)
            paddingX = 100;      // Ajuste para centralizar as 8 colunas
        }
        // Nível 7+: Sobrevivência
        else {
            numLinhas = 4 + (level - 6);
            if (numLinhas > 9) numLinhas = 9;
        }

        // Loop de Geração
        for (int i = 0; i < numLinhas; i++) {
            for (int j = 0; j < numColunas; j++) { // Agora usamos 'numColunas'
                Bloco *novoBloco = (Bloco*) malloc(sizeof(Bloco));
                
                // Usamos 'paddingX' e 'alturaInicial' para posicionar
                novoBloco->rect = (Rectangle){ j * 75 + paddingX, i * 30 + alturaInicial, 70, 20 };
                
                novoBloco->vida = 1;
                novoBloco->ativo = true;
                novoBloco->tipo = (i % 5) + 1;
                novoBloco->prox = head;
                head = novoBloco;
            }
        }
    }

    return head;
}

void destruirLista(Bloco *head) {
    Bloco *atual = head;
    Bloco *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

bool todosBlocosDestruidos(Bloco *head) {
    Bloco *atual = head;
    while (atual != NULL) {
        if (atual->ativo == true) return false;
        atual = atual->prox;
    }
    return true;
}