🧱 BLOCK BREAKER – ARKANOID REMASTERIZADO

Um jogo desenvolvido em C + Raylib, onde seu objetivo é destruir todos os blocos, desviar a bola e sobreviver aos níveis cada vez mais difíceis!
Com diferentes mapas, dificuldade progressiva, ranking local e efeitos visuais, este Arkanoid traz uma jogabilidade rápida e desafiadora!

👨‍💻 Membros da Equipe

Rodrigo
Julio
Joao Luis


✅ Pré-requisitos

Linux (Ubuntu/Debian), macOS ou Windows

GCC

Make (ou mingw32-make no Windows)

Raylib instalada

🛠️ Instalação da Raylib
Linux (Ubuntu/Debian)
sudo apt update
sudo apt install build-essential git libraylib-dev

macOS

Instale o Homebrew (se ainda não tiver):

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"


Depois instale a Raylib:

brew install raylib

🪟 Windows

Recomendado: MinGW + vcpkg

Instale o vcpkg

Configure a variável de ambiente VCPKG_ROOT

Instale a Raylib:

vcpkg install raylib


Se o comando make não funcionar:

Set-Alias -Name make -Value mingw32-make

♟️ Como Rodar o Jogo

Clone o repositório:

git clone https://github.com/jcchc/Block-Breaker--PIF.git


Entre na pasta do projeto:

cd BlockBreaker


Compile e execute:



🕹️ Instruções do Jogo
🎮 Navegação no Menu

Enter- Inicia o Jogo
R- Exibe o ranking
Esc- Fecha o jogo


1️⃣ Modos de Jogo
Modo Normal

10 níveis progressivos

Cada nível possui um layout diferente de blocos

Destrua todos os blocos para avançar

Modo Infinito

(se existir no seu jogo — posso remover se quiser)

Dificuldade aumenta automaticamente

Objetivo: sobreviver o máximo possível

Rankings

Guarda as maiores pontuações

Exibidas no menu de rankings

2️⃣ Gameplay

← — mover para a esquerda

→ — mover para a direita

Rebata a bola

Destrua todos os blocos

Não deixe a bola cair!


3️⃣ Game Over / Vitória

Vitória: destrua todos os blocos

Derrota: bola caiu

Pressione M para voltar ao menu
Pressione R para reiniciar o jogo

