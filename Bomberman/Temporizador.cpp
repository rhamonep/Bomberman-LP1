#include "Temporizador.hpp"

#include <iostream>

Temporizador::Temporizador (){
    velocidade = 1.f;
    pausado = false;
}

void Temporizador::setVelocidade(float velocidade){
    if(velocidade > 0.f){
        atualizar();
        this->velocidade = velocidade;
    }else{
        std::cerr << "ERRO! Temporizador::setVelocidade -> Valor Incorreto: " << velocidade << std::endl;
    }
}

void Temporizador::pausar(){
    if (!pausado) {
        pausado = true;
        atualizar();
    }else{
        std::cerr << "ERRO! Temporizador::pausar -> jogo já está pausado " << std::endl;
    }
}

void Temporizador::resumir(){
    if (pausado){
        pausado = false;
        atualizar();
    } else {
        std::cerr << "ERRO Temporizador::resumir -> jogo já está rodando" << std::endl;
    }
}

sf::Time Temporizador::getTempoAtual() const{
    if (pausado)
        return tempoAtual;

    return tempoAtual + clock.getElapsedTime() * velocidade;
}

bool Temporizador::isPausado(){
    return pausado;
}

void Temporizador::atualizar(){
    if (pausado){
        tempoAtual += clock.getElapsedTime() * velocidade;
    }

    clock.restart ();
}
