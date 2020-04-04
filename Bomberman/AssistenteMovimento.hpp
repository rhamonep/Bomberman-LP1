#pragma once

#include "Jogador.hpp"

class AssistenteMovimento{

    private:

        Temporizador* temporizador;
        Mapa* mapa;

        void centraliza(Jogador* jogador, int* faltando);
        void atualizaPosicaoMapa(Jogador* jogador);

    public:

        AssistenteMovimento(Temporizador* temporizador, Mapa* mapa);

        void atualizarPosicao(Jogador* jogador);
        bool isDirecoesOpostas (Direcao d1, Direcao d2);
};
