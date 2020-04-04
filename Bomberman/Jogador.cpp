#include "Jogador.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <stdexcept>
#include <sstream>
#include <iostream>

Jogador::Jogador(JogadorId jogadorId, sf::Time ultimaAtualizacao, JogadorControle* controle, 
                std::string caminho, int linha, int coluna){

    this->jogadorId = jogadorId;
    this->controle = controle;
    this->ultimaAtualizacao = ultimaAtualizacao;
    this->morto = false;
    this->morrendo = false;
    this->andando = false;
    this->proxAnimacao = 0;
    this->linha = linha;
    this->coluna = coluna;
    this->posicaoX = MEIO_CELULA;
    this->posicaoY = MEIO_CELULA;
    this->dirAtual = Direcao::BAIXO;
    this->dirProxima = Direcao::BAIXO;
    this->forca = 2;
    this->maxBomba = 1;
    this->temDetonador = false;
    this->velocidade = TEMPO_MOVIMENTACAO_JOGADOR;

    if (!textura.loadFromFile(caminho)){
        std::ostringstream oss;
        oss << "ERRO! Jogador::Jogador -> Não foi possível carregar o caminho: " << caminho;
        throw std::runtime_error (oss.str());
    }
}

JogadorId Jogador::getId(){
    return jogadorId;
}

JogadorControle* Jogador::getControle(){
    return controle;
}

sf::Time Jogador::getUltimaAtualizacao(){
    return ultimaAtualizacao;
}

sf::Texture* Jogador::getTextura(){
    return &textura;
}

int Jogador::getProxAnimacao(){
    return proxAnimacao;
}

int Jogador::getLinha(){
    return linha;
}

int Jogador::getColuna(){
    return coluna;
}

int Jogador::getPosicaoY(){
    return posicaoY;
}

int Jogador::getPosicaoX(){
    return posicaoX;
}

Direcao Jogador::getDirecaoAtual(){
    return dirAtual;
}

Direcao Jogador::getDirecaoProxima(){
    return dirProxima;
}

bool Jogador::isMorto(){
    return morto;
}

bool Jogador::isMorrendo(){
    return morrendo;
}

void Jogador::setMorrendo(bool morrendo){
    this->morrendo = morrendo;
}

bool Jogador::isAndando(){
    return andando;
}

sf::Time Jogador::getVelocidade(){
    return velocidade;
}

int Jogador::getForca(){
    return forca;
}

int Jogador::getMaxBomba(){
    return maxBomba;
}

bool Jogador::getTemDetonador(){
    return temDetonador;
}

void Jogador::setId(JogadorId jogadorId){
    this->jogadorId = jogadorId;
}

void Jogador::setControle(JogadorControle* controle){
    this->controle = controle;
}

void Jogador::setUltimaAtualizacao(sf::Time ultimaAtualizacao){
    this->ultimaAtualizacao = ultimaAtualizacao;
}

void Jogador::setTextura(sf::Texture textura){
    this->textura = textura;
}

void Jogador::setProxAnimacao(int proxAnimacao){
    this->proxAnimacao = proxAnimacao;
}

void Jogador::setLinha(int linha){
    this->linha = linha;
}

void Jogador::setColuna(int coluna){
    this->coluna = coluna;
}

void Jogador::setPosicaoY(int posicaoY){
    this->posicaoY = posicaoY;
}

void Jogador::setPosicaoX(int posicaoX){
    this->posicaoX = posicaoX;
}

void Jogador::setDirecaoAtual(Direcao dirAtual){
    this->dirAtual = dirAtual;
}

void Jogador::setDirecaoProxima(Direcao dirProxima){
    this->dirProxima = dirProxima;
}

void Jogador::setIsMorto(bool morto){
    this->morto = morto;
}

void Jogador::setIsAndando(bool andando){
    this->andando = andando;
}

void Jogador::setVelocidade(sf::Time velocidade){
    this->velocidade = velocidade;
}

void Jogador::setForca(int forca){
    this->forca = forca;
}

void Jogador::setMaxBomba(int maxBomba){
    this->maxBomba = maxBomba;
}

void Jogador::setTemDetonador(bool temDetonador){
    this->temDetonador = temDetonador;
}

