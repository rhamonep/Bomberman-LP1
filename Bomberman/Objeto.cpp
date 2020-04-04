#include "Objeto.hpp"

Objeto::Objeto(int linha, int coluna, sf::Time tempoCriacao){
    this->linha = linha;
    this->coluna = coluna;
    this->tempoCriacao = tempoCriacao;
}

int Objeto::getLinha(){
    return linha;
}

int Objeto::getColuna(){
    return coluna;
}

sf::Time Objeto::getTempoCriacao(){
    return tempoCriacao;
}

void Objeto::setLinha(int linha){
    this->linha = linha;
}

void Objeto::setColuna(int coluna){
    this->coluna = coluna;
}

void Objeto::setTempoCriacao(sf::Time tempoCriacao){
    this->tempoCriacao = tempoCriacao;
}
