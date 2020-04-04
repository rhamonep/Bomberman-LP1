#pragma once

#include <SFML/Window/Event.hpp>

#include <vector>

#include "Jogador.hpp"
#include "Temporizador.hpp"
#include "ControladorJogadores.hpp"

class GerenciadorEventos{

    private:

        ControladorJogadores* controladorJogadores;
        Temporizador* temporizador;
        std::vector<Jogador>* jogadores;
        
        void gerenciarJogadores(sf::Event* evento);

    public:

        GerenciadorEventos(ControladorJogadores* controladorJogadores, std::vector<Jogador>* jogadores, 
                           Temporizador* temporizador);

        void gerenciar(sf::Event* evento);

};