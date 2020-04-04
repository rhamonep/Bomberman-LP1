# Bomberman-LP1
UFPB - Projeto LP1 - Bomberman

Equipe: Rhamon Espínola Pires e Lucas Bezerra de Oliveira Abreu

Projeto desenvolvido para as cadeiras de Linguagem de Programação I e Laboratório de Linguagem de Programação I, utilizando a biblioteca gráfica SFML, no Ubuntu.

Instalar a biblioteca: sudo apt-get install libsfml-dev

Compilar: g++ *.cpp -o Bomberman -lsfml-graphics -lsfml-window -lsfml-system

Rodar: ./Bomberman

CONTROLES:

Jogador 1 : A, W, S, D (movimento), Q (coloca bomba), E (detona bomba se tiver o item detonador).
Jogador 2 : Setas de direção (movimento), Shift Direito (coloca bomba), Ctrl Direito (detona bomba).

O projeto completo consiste em recriar o jogo SuperBomberman da Nintendo com todas suas mecânicas e interações de jogo, visando implementar novos recursos em futuras atualizaçes.

No momento segue bem incompleto, quando se fala em termos de interações com usuário antes do inicio de uma partida. A intenção primária foi criar e organizar todas as funções do começo até o fim de uma batalha. Segue um video de uma batalha, que visa mostrar parte das mecânicas implementadas.

A organização e estruturação do projeto foi pensando em deixar bem modulado, para facilitar a utlização de threads, futuramente. Projeto será levado adiante para outras disciplinas.
