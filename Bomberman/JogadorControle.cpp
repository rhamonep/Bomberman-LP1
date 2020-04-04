#include "JogadorControle.hpp"

JogadorControle::JogadorControle(sf::Keyboard::Key esquerda, 
                                sf::Keyboard::Key cima, 
                                sf::Keyboard::Key direita, 
                                sf::Keyboard::Key baixo, 
                                sf::Keyboard::Key adicionar, 
                                sf::Keyboard::Key detonaBomba){

    this->esquerda = esquerda;
    this->cima = cima;
    this->direita = direita;
    this->baixo = baixo;
    this->adicionar = adicionar;
    this->detonaBomba = detonaBomba;

}

sf::Keyboard::Key JogadorControle::getEsquerda(){
    return esquerda;
}

sf::Keyboard::Key JogadorControle::getCima(){
    return cima;
}

sf::Keyboard::Key JogadorControle::getDireita(){
    return direita;
}

sf::Keyboard::Key JogadorControle::getBaixo(){
    return baixo;
}

sf::Keyboard::Key JogadorControle::getColocaBomba(){
    return adicionar;
}

sf::Keyboard::Key JogadorControle::getDetonaBomba(){
    return detonaBomba;
}

void JogadorControle::setEsquerda(sf::Keyboard::Key esquerda){
    this->esquerda = esquerda;
}

void JogadorControle::setCima(sf::Keyboard::Key cima){
    this->cima = cima;
}

void JogadorControle::setDireita(sf::Keyboard::Key direita){
    this->direita = direita;
}

void JogadorControle::setBaixo(sf::Keyboard::Key baixo){
    this->baixo = baixo;
}

void JogadorControle::setColocaBomba(sf::Keyboard::Key adicionar){
    this->adicionar = adicionar;
}

void JogadorControle::setDetonaBomba(sf::Keyboard::Key detonaBomba){
    this->detonaBomba = detonaBomba;
}

bool JogadorControle::isSetaDirecao(sf::Keyboard::Key tecla){
    return (tecla == cima) || (tecla == direita) || (tecla == baixo) || (tecla == esquerda);
}

Direcao JogadorControle::getDirecao(sf::Keyboard::Key tecla){
    if(tecla == cima){
        return Direcao::CIMA;
    }
    if(tecla == direita){
        return Direcao::DIREITA;
    }
    if(tecla == baixo){
        return Direcao::BAIXO;
    }
    return Direcao::ESQUERDA;
}
