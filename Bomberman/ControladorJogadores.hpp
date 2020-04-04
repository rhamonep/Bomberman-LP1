#pragma once

#include "Jogador.hpp"
#include "ControladorBomba.hpp"
#include "ControladorItem.hpp"
#include "AssistenteMovimento.hpp"

#include <vector>

class ControladorJogadores : public Controlador{

    private:

        AssistenteMovimento* assistenteMovimento;
        ControladorBomba* controladorBomba;
        ControladorItem* controladorItem;
        std::vector<Jogador> jogadores;

        bool vitoria;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void interagirComMapa(Jogador* jogador);
        void verificaVitoria();

    public:

        ControladorJogadores(Temporizador* temporizador, Mapa* mapa);
        void linkar(ControladorBomba* controladorBomba,  ControladorItem* controladorItem);
        bool isVitoria();
        void atualizar();
        void adicionarJogador(Jogador jogador);
        std::vector<Jogador>* getJogadores();

        void mover(Jogador* jogador, Direcao direcao);
        void parar(Jogador* jogador, Direcao direcao);
        void detonarBomba(Jogador* jogador);
        void colocarBomba(Jogador* jogador);
};