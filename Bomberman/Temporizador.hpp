#pragma once

#include <SFML/System/Clock.hpp>

class Temporizador{

    private:
        
        float velocidade;
        bool pausado;

        sf::Clock clock;
        sf::Time tempoAtual;

        void atualizar();

    public:

        Temporizador();

        void setVelocidade (float velocidade);
        sf::Time getTempoAtual() const;

        bool isPausado();

        void pausar();
        void resumir();
};
