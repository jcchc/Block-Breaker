#include "blocks.h"
#include <stdlib.h>

Bloco* gerarBlocos(int level) {
    Bloco *head = NULL;

    int numLinhas = 3 + (level - 1);
    if (numLinhas > 9) numLinhas = 9;

    int numColunas = 10;

    for (int i = 0; i < numLinhas; i++) {
        for (int j = 0; j < numColunas; j++) {

            Bloco *novoBloco = (Bloco*) malloc(sizeof(Bloco));

            novoBloco->rect = (Rectangle){
                j * 80 + 5,
                i * 30 + 40,
                75,
                20
            };

            novoBloco->vida = 1;
            novoBloco->ativo = true;
            novoBloco->tipo = (i % 5) + 1;

            novoBloco->prox = head;
            head = novoBloco;
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
        if (atual->ativo == true) {
            return false;
        }
        atual = atual->prox;
    }

    return true;
}
