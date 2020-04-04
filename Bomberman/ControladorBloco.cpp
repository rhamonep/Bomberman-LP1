#include "ControladorBloco.hpp"
#include "Constantes.hpp"
#include "GeradorItem.hpp"
#include "ControladorItem.hpp"
#include "Mapa.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <stdexcept>
#include <sstream>

ControladorBloco::ControladorBloco(Temporizador* temporizador, Mapa* mapa) : Controlador(temporizador, mapa){
    this->totalBlocos = 0;

    std::string caminho = "sprites/brick.png";

    if (!textura.loadFromFile(caminho)) {
        std::ostringstream oss;
        oss << "ERRO! ControladorExplosaoBloco::ControladorExplosaoBloco -> Não foi possível carregar o caminho: " << caminho;
        throw std::runtime_error (oss.str());
    }
}

void ControladorBloco::linkar(ControladorItem* controladorItem){
    this->controladorItem = controladorItem;
}

void ControladorBloco::gerar(sf::Image* imagemMapa){

    for(int linha = 0; linha < imagemMapa->getSize().y; linha++){
        for(int coluna = 0; coluna < imagemMapa->getSize().x; coluna++){
           if(imagemMapa->getPixel(coluna, linha) == BLOCO_COR){
               adicionar(linha, coluna);           
            }
        }
    }
}

int ControladorBloco::getTotalBlocos(){
    return totalBlocos;
}
       
void ControladorBloco::adicionar(int linha, int coluna){
    blocos.push_back(Bloco(linha, coluna, temporizador->getTempoAtual()));
    mapa->setCelula(linha, coluna, Celula::BLOCO);
    ++totalBlocos;
}

void ControladorBloco::destruir(int linha, int coluna){

    std::list<Bloco>::iterator it;

    for(it = blocos.begin(); it != blocos.end(); ++it){
        if(it->getLinha() == linha && it->getColuna() == coluna){
            it->setIsExplodindo(true);
            it->setTempoCriacao(temporizador->getTempoAtual());
        }
    }
}

void ControladorBloco::editarItem(int linha, int coluna, TipoItem tipoitem){
    std::list<Bloco>::iterator it;

    for(it = blocos.begin(); it != blocos.end(); ++it){
        if(it->getLinha() == linha && it->getColuna() == coluna){
            it->setTipoItem(tipoitem);
        }
    }
}

void ControladorBloco::atualizar(){

    std::list<Bloco>::iterator it = blocos.begin();

    while(it != blocos.end()){

        if(it->isExplodindo() &&
            temporizador->getTempoAtual() - it->getTempoCriacao() > TEMPO_EXPLOSAO_BLOCO){

                mapa->limparCelula(it->getLinha(), it->getColuna());
                
                if(it->getTipoItem() != TipoItem::VAZIO){
                    controladorItem->adicionar(it->getLinha(), it->getColuna(), it->getTipoItem());
                }
                it = blocos.erase(it);
                --totalBlocos;
        }else{
            ++it;
        }
    }
}

void ControladorBloco::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sprite(textura);

    int spriteX;

    for(Bloco blocoAtual : blocos){

        if(blocoAtual.isExplodindo()){
            sf::Time dif = temporizador->getTempoAtual() - blocoAtual.getTempoCriacao();

            spriteX = 1 + (dif.asMilliseconds()/(TEMPO_EXPLOSAO_BLOCO.asMilliseconds()/6));
        }else{
            spriteX = 0;
        }

        sprite.setTextureRect(sf::IntRect(spriteX*TAMANHO_CELULA, 0, TAMANHO_CELULA, TAMANHO_CELULA));
        sprite.setPosition (blocoAtual.getColuna()*TAMANHO_CELULA, blocoAtual.getLinha()*TAMANHO_CELULA);
        target.draw (sprite, states);

    }
}
