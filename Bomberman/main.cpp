#include <SFML/Graphics.hpp>

#include <stdexcept>
#include <iostream>

#include "Jogo.hpp"

enum class Estado{
    MENU,
    JOGO,
    CRIANDO_MENU,
    CRIANDO_JOGO,
};

int main(){

        Jogo* jogo;
        Estado estado = Estado::MENU;
        sf::RenderWindow janela(sf::VideoMode(500, 300),"SERIA O MENU... APERTE ESPACO PARA CONTINUAR");

        janela.setFramerateLimit(60);

        while (janela.isOpen()) {
 
            sf::Event evento;
            while (janela.pollEvent(evento)) {

                switch(estado){
                    case Estado::JOGO:
                        jogo->gerenciaEventos(&evento);
                        break;
                    case Estado::MENU:
                        if(sf::Event::KeyPressed){
                            if(evento.key.code == sf::Keyboard::Space){
                                estado = Estado::CRIANDO_JOGO;
                            }
                        }
                        break;
                }

                if (evento.type == sf::Event::Closed){
                    janela.close();
                }
            }

            switch(estado){
                case Estado::CRIANDO_JOGO:
                    jogo = new Jogo("sprites/grid.bmp");
                    janela.create(sf::VideoMode(jogo->alturaEmPixels(), jogo->larguraEmPixels()), 
                                                "Bomberman");
                    estado = Estado::JOGO;
                    break;
                case Estado::CRIANDO_MENU:
                    janela.create(sf::VideoMode(200, 300),"SERIA O MENU... APERTE ESPACO PARA CONTINUAR");

                    estado = Estado::MENU;
                    break;
                case Estado::JOGO:
                    jogo->atualizar();

                    janela.clear();
                    janela.draw(*jogo);
                    janela.display();

                    if(!jogo->isEmJogo()){
                        delete(jogo);
                        estado = Estado::CRIANDO_MENU;
                    }
                    break;
                case Estado::MENU:
                    break;
            }
        }
    
    return 0;
}