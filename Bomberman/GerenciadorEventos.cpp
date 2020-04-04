#include "GerenciadorEventos.hpp"

GerenciadorEventos::GerenciadorEventos(ControladorJogadores* controladorJogadores, std::vector<Jogador>* jogadores,
                                       Temporizador* temporizador){

    this->jogadores = jogadores;                                           
    this->controladorJogadores = controladorJogadores;
    this->temporizador = temporizador;
}

void GerenciadorEventos::gerenciar(sf::Event* evento){
    switch(evento->type){
        case sf::Event::KeyPressed:
            if(evento->key.code == sf::Keyboard::Pause){
                if(temporizador->isPausado()){
                    temporizador->resumir();
                }else{
                    temporizador->pausar();
                }
                return;
            }
            break;
        default:
            break;
    }

    if(temporizador->isPausado()){
        return;
    }

    gerenciarJogadores(evento);
}

void GerenciadorEventos::gerenciarJogadores(sf::Event* evento){

    for(Jogador &jogadorAtual : *jogadores){

        switch(evento->type){
            case sf::Event::KeyReleased:
            
                if(jogadorAtual.getControle()->isSetaDirecao(evento->key.code)){

                    controladorJogadores->parar(&jogadorAtual, jogadorAtual.getControle()->getDirecao(evento->key.code));
                }
                break;
            case sf::Event::KeyPressed:

                if(jogadorAtual.getControle()->isSetaDirecao(evento->key.code)){

                    controladorJogadores->mover(&jogadorAtual, jogadorAtual.getControle()->getDirecao(evento->key.code));

                }else if(evento->key.code == jogadorAtual.getControle()->getColocaBomba()){

                    controladorJogadores->colocarBomba(&jogadorAtual);

                }else if(evento->key.code == jogadorAtual.getControle()->getDetonaBomba()){

                    controladorJogadores->detonarBomba(&jogadorAtual);
                }
                break;
            default:
                break;
        }
    }
}