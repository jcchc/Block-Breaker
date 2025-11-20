#include "player.h"
#include <stdio.h>  // OBRIGATÓRIO: É aqui que vivem fopen, fprintf, fclose

// Função para SALVAR (Escrever no arquivo)
void salvarRanking(const char *nome, int score) {
    // 1. Abrir o arquivo
    // "a" = append (adicionar no fim). Se não existir, ele cria.
    FILE *arquivo = fopen("ranking.txt", "a");

    // Verificação de segurança
    if (arquivo == NULL) {
        TraceLog(LOG_WARNING, "Nao foi possivel salvar o ranking.");
        return;
    }

    // 2. Escrever no arquivo
    // Formato: Nome Pontuacao (ex: "Julio 500")
    // O \n no final pula para a próxima linha
    fprintf(arquivo, "%s %d\n", nome, score);

    // 3. Fechar o arquivo (MUITO IMPORTANTE para salvar de verdade)
    fclose(arquivo);
}

// Função para LER e DESENHAR
void exibirRanking(int x, int y) {
    // 1. Abrir o arquivo para leitura
    // "r" = read (ler)
    FILE *arquivo = fopen("ranking.txt", "r");

    DrawText("--- HALL DA FAMA ---", x, y, 20, GOLD);
    y += 30; // Desce um pouco para a próxima linha

    // Se o arquivo não existir (ninguém jogou ainda)
    if (arquivo == NULL) {
        DrawText("Nenhum recorde ainda.", x, y, 20, GRAY);
        return;
    }

    char nomeLeitura[50];
    int scoreLeitura;
    int contador = 1;

    // 2. Loop de Leitura
    // fscanf lê linha por linha. Enquanto conseguir ler 2 coisas (nome e score)...
    while (fscanf(arquivo, "%s %d", nomeLeitura, &scoreLeitura) == 2) {
        
        // Desenha na tela (usando Raylib)
        DrawText(TextFormat("%d. %s .... %d", contador, nomeLeitura, scoreLeitura), x, y, 20, WHITE);
        
        y += 25; // Desce para a próxima linha na tela
        contador++;
        
        // Limite para não encher a tela (mostra só os primeiros 10, por exemplo)
        if (contador > 10) break; 
    }

    // 3. Fechar o arquivo
    fclose(arquivo);
}