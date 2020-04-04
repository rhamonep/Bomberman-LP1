#pragma once

#include <SFML/Window/Keyboard.hpp>

#include "Constantes.hpp"

class JogadorControle{

    private:

        sf::Keyboard::Key esquerda;
        sf::Keyboard::Key cima;
        sf::Keyboard::Key direita;
        sf::Keyboard::Key baixo;

        sf::Keyboard::Key adicionar;
        sf::Keyboard::Key detonaBomba;

    public:

        JogadorControle(sf::Keyboard::Key esquerda, 
                                        sf::Keyboard::Key cima, 
                                        sf::Keyboard::Key direita, 
                                        sf::Keyboard::Key baixo, 
                                        sf::Keyboard::Key adicionar, 
                                        sf::Keyboard::Key detonaBomba);
        
        sf::Keyboard::Key getEsquerda();
        sf::Keyboard::Key getCima();
        sf::Keyboard::Key getDireita();
        sf::Keyboard::Key getBaixo();
        sf::Keyboard::Key getColocaBomba();
        sf::Keyboard::Key getDetonaBomba();

        void setEsquerda(sf::Keyboard::Key esquerda);
        void setCima(sf::Keyboard::Key cima);
        void setDireita(sf::Keyboard::Key direita);
        void setBaixo(sf::Keyboard::Key baixo);
        void setColocaBomba(sf::Keyboard::Key adicionar);
        void setDetonaBomba(sf::Keyboard::Key detonaBomba);

        bool isSetaDirecao(sf::Keyboard::Key tecla);
        Direcao getDirecao(sf::Keyboard::Key tecla);
};
