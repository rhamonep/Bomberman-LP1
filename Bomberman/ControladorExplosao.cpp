#include "ControladorExplosao.hpp"

#include "Constantes.hpp"
#include "Mapa.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <stdexcept>
#include <sstream>

ControladorExplosao::ControladorExplosao(Temporizador* temporizador, Mapa* mapa) 
: Controlador(temporizador, mapa){

    std::string caminho = "sprites/fire.png";

    if (!textura.loadFromFile(caminho)) {
        std::ostringstream oss;
        oss << "ERRO: ControladorExplosao::ControladorExplosao -> Não foi possível carregador caminho: " << caminho;
        throw std::runtime_error (oss.str());
    }

    bufferTextura.create (mapa->getNumCol()*TAMANHO_CELULA, mapa->getNumLinhas()*TAMANHO_CELULA);
}

void ControladorExplosao::linkar(ControladorBomba* controladorBomba, ControladorItem* controladorItem, ControladorBloco* controladorBloco){
    this->controladorBomba = controladorBomba;
    this->controladorBloco = controladorBloco;
    this->controladorItem = controladorItem;
}

void ControladorExplosao::adicionaExplosao(int linha, int coluna, int forca){
    explosoes.push_back(Explosao(temporizador, mapa, this, &textura, linha, coluna, forca));
    mapa->setCelula(linha, coluna, Celula::EXPLOSAO);
}

void ControladorExplosao::explodeCelula(int linha, int coluna){

    if(linha >= mapa->getNumLinhas() || coluna >= mapa->getNumCol()){
        return;
    }

    switch(mapa->getCelula(linha, coluna)){
        case Celula::BLOCO:
            controladorBloco->destruir(linha, coluna); 
            break; 
        case Celula::BOMBA:
            controladorBomba->destruir(linha, coluna);
            break; 
        case Celula::ITEM:
            controladorItem->destruir(linha, coluna);
            break; 
        case Celula::VAZIO:
            mapa->setCelula(linha, coluna, Celula::EXPLOSAO);
            break; 
        default:
            break;
    }        
}

void ControladorExplosao::atualizar(){

    std::list<Explosao>::iterator it;
    
    for(it = explosoes.begin(); it != explosoes.end(); it++){
        it->espalhou();
    }

    it = explosoes.begin();
    while(it != explosoes.end()){
        if(it->isDeletavel()){
            it->limparCelulas();
            it = explosoes.erase(it);
        }else{
            ++it;
        }
    }

    atualizarBufferTextura();
}


void ControladorExplosao::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Sprite sprite (bufferTextura.getTexture());
    sprite.setScale(1.f, -1.f);
    sprite.setPosition (0.f, bufferTextura.getSize().y);

    target.draw (sprite, states);
}

void ControladorExplosao::atualizarBufferTextura (){

    bufferTextura.clear(sf::Color(255,0,0,0));

    for(Explosao explosaoAtual : explosoes){
        bufferTextura.draw(explosaoAtual);
    }
}
