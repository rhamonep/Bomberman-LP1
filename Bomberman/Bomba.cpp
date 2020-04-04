#include "Bomba.hpp"

Bomba::Bomba(JogadorId jogadorId, TipoBomba tipo, sf::Time tempoCriacao, int forca, int linha, int coluna) 
: Objeto(linha, coluna, tempoCriacao){
    this->forca = forca;
    this->tipo = tipo;
    this->jogadorId = jogadorId;
}

int Bomba::getForca(){
    return forca;
}


TipoBomba Bomba::getTipo(){
    return tipo;
}

JogadorId Bomba::getJogadorId(){
    return jogadorId;
}
