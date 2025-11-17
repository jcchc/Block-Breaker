#include "blocks.h"
#include <stdlib.h>

Bloco* gerarBlocos(int level) {
    Bloco *head = NULL; 
    int numLinhas = 5;
    int numColunas = 10;

    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {
            
            Bloco *novoBloco = (Bloco*) malloc(sizeof(Bloco));

            novoBloco->rect.x = j * 80 + 10;  //isso veio implicito na biblioteca raylib
            novoBloco->rect.y = i * 30 + 50; 
            novoBloco->rect.width = 75;
            novoBloco->rect.height = 25;
            novoBloco->ativo = true;
            novoBloco->vida = 1 + level;
            novoBloco->tipo = 1;

      
            novoBloco->prox = head;
            head = novoBloco;
        }
    }
    return head;
}

void destruirLista(Bloco *head) {
    Bloco *temp;
    while (head != NULL) {
        temp = head; 
        head = head->prox;
        free(temp);
    }
}

bool todosBlocosDestruidos(Bloco *head) {
    Bloco *atual = head;
    while (atual != NULL) {
        if (atual->ativo) {
            return false;
        }
        atual = atual->prox;
    }
    return true;
}