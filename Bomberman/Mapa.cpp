#include "Mapa.hpp"

#include "GeradorItem.hpp"
#include "Constantes.hpp"

#include <stdexcept>
#include <cassert>
#include <sstream>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

Mapa::Mapa(sf::Image* imagemMapa) : celulas(imagemMapa->getSize().x * imagemMapa->getSize().y, Celula()){

    numLinhas = imagemMapa->getSize().y;
    numColunas = imagemMapa->getSize().x;

    std::string caminho = "sprites/tile.png";

    if (!texturaTerreno.loadFromFile(caminho)) {
        std::ostringstream oss;
        oss << "ERRO! Mapa::Mapa -> Não foi possível carregar caminho: " << caminho;
        throw std::runtime_error (oss.str());
    }

    if (!bufferTextura.create (TAMANHO_CELULA*numColunas, TAMANHO_CELULA*numLinhas)){
        throw std::runtime_error("ERRO!: Mapa::Mapa -> Não foi possível inicializar buffer textura");
    }
}

int Mapa::index(int linha, int col) const{
    return linha*numColunas + col;
}

void Mapa::gerarMapa(sf::Image* imagemMapa){

    for(int linha = 0; linha < numLinhas; linha++){
        for(int coluna = 0; coluna < numColunas; coluna++){
            if(imagemMapa->getPixel(coluna, linha) == PEDRA_COR){
                celulas[index(linha, coluna)] = Celula::PEDRA;
            }
        }
    }
    atualizarBufferTextura();
}

void Mapa::atualizarBufferTextura(){

    bufferTextura.clear(sf::Color::Green);

    sf::Sprite sprite(texturaTerreno);

    for(int linha = 0; linha < numLinhas; ++linha){
        for(int coluna = 0; coluna < numColunas; ++coluna){
            int tipo = celulas[index(linha, coluna)] == Celula::PEDRA ? 0 : 1;

            sprite.setTextureRect(sf::IntRect(0, tipo*TAMANHO_CELULA, 
                                              TAMANHO_CELULA, TAMANHO_CELULA));

            sprite.setPosition(TAMANHO_CELULA*coluna, TAMANHO_CELULA*linha);
            bufferTextura.draw(sprite);
        }
    }
}

void Mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    sf::Sprite spriteMapa (bufferTextura.getTexture());
    spriteMapa.setScale(1.f, -1.f);
    spriteMapa.setPosition (0.f, bufferTextura.getSize().y);
    target.draw (spriteMapa, states);
}

int Mapa::getNumLinhas(){
    return numLinhas;
}

int Mapa::getNumCol(){
    return numColunas;
}

Celula Mapa::getCelula(int linha, int coluna){
    return celulas[index(linha, coluna)];
}

void Mapa::setCelula(int linha, int coluna, Celula conteudo){
    celulas[index(linha, coluna)] = conteudo;
}

void Mapa::limparCelula(int linha, int coluna){
    celulas[index(linha, coluna)] = Celula::VAZIO;
}

bool Mapa::isAndavel(int linha, int coluna){
    return !(celulas[index(linha, coluna)] == Celula::PEDRA) &&
           !(celulas[index(linha, coluna)] == Celula::BOMBA) &&
           !(celulas[index(linha, coluna)] == Celula::BLOCO);
}
