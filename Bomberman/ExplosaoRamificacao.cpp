#include "ExplosaoRamificacao.hpp"

ExplosaoRamificacao::ExplosaoRamificacao(){
    this->maximo = true;
    this->expandiuMaximo = false;
    this->tamanho = 0;
}

ExplosaoRamificacao::ExplosaoRamificacao(int tamanho, bool maximo){
    this->tamanho = tamanho;
    this->maximo = maximo;
    this->expandiuMaximo = false;
}


int ExplosaoRamificacao::getTamanho() const{
    return tamanho;
}

bool ExplosaoRamificacao::isMaximo() const{
    return this->maximo;
}

bool ExplosaoRamificacao::isExpandiuMaximo() const{
    return this->expandiuMaximo;
}

void ExplosaoRamificacao::setTamanho(int tamanho){
    this->tamanho = tamanho;
}

void ExplosaoRamificacao::setIsMaximo(bool maximo){
    this->maximo = maximo;
}

void ExplosaoRamificacao::setExpandiuMaximo(bool expandiu){
    this->expandiuMaximo = expandiu;
}
