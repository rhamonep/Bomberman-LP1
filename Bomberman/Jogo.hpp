#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <memory>
#include <list>

#include "Temporizador.hpp"
#include "Mapa.hpp"
#include "Jogador.hpp"
#include "ControladorJogadores.hpp"
#include "ControladorBloco.hpp"
#include "ControladorExplosao.hpp"
#include "ControladorBomba.hpp"
#include "ControladorItem.hpp"
#include "GerenciadorEventos.hpp"

class Jogo : public sf::Drawable{
    
    private:

        Temporizador* temporizador;
        Mapa* mapa;

        int numLinhas;
        int numColunas;

        bool emJogo;
        sf::Time ultimaAtualizacao;
        
        ControladorJogadores* controladorJogadores;
        ControladorItem* controladorItem;
        ControladorBloco* controladorBloco;
        ControladorExplosao* controladorExplosao;
        ControladorBomba* controladorBomba;
        GerenciadorEventos* gerenciadorEventos;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void conectarControladores();

    public:

        Jogo(std::string caminho);

        int alturaEmPixels();
        int larguraEmPixels();

        bool isEmJogo();

        void atualizar();
        void gerenciaEventos(sf::Event* evento);
};