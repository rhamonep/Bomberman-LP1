#include "ControladorItem.hpp"
#include "ControladorBloco.hpp"
#include "Mapa.hpp"
#include "Jogador.hpp"

#include <cstdlib>
#include <stdexcept>
#include <sstream>

ControladorItem::ControladorItem(Temporizador* temporizador, Mapa* mapa) 
: Controlador(temporizador, mapa){
    srand(time(NULL));

    std::string caminho = "sprites/itens1.png";

    if (!textura.loadFromFile(caminho)) {
        std::ostringstream oss;
        oss << "ERRO! ControladorItem::ControladorItem -> Não foi possível carregar o caminho: " << caminho;
        throw std::runtime_error (oss.str());
    }
}

void ControladorItem::gerar(ControladorBloco* controladorBloco, std::vector<int> itens){

    int numBlocos = controladorBloco->getTotalBlocos();

    for(int linha = 0; linha < mapa->getNumLinhas(); linha++){
        for(int coluna = 0; coluna < mapa->getNumCol(); coluna++){
            if(mapa->getCelula(linha, coluna) == Celula::BLOCO){
                int tipoItem = sortear(&numBlocos, &itens);
                if(tipoItem >= 0){
                    controladorBloco->editarItem(linha, coluna, (TipoItem)tipoItem);
                }
            }
        }
    }
}

int ControladorItem::sortear(int* numBlocos, std::vector<int>* itens){
    
    if(*numBlocos == 0){
        return -1;
    }

    int totalItens = 0;

    for(int quantidadeAtual : *itens){
        totalItens += quantidadeAtual;
    }

    int rMax = std::max(totalItens, *numBlocos);
    int random = rand() % rMax;

    int TipoItemRetornado = -1;

    if(totalItens > random){
        totalItens = 0;
        while(totalItens <= random){
            ++TipoItemRetornado;
            totalItens += (*itens)[TipoItemRetornado];
        }
        --(*itens)[TipoItemRetornado];
    }

    *numBlocos-=1;
    return TipoItemRetornado;
}

void ControladorItem::destruir(int linha, int coluna){
    std::list<Item>::iterator it;
    
    for(it = itens.begin(); it != itens.end(); ++it){
        if(it->getLinha() == linha && it->getColuna() == coluna){
            mapa->limparCelula(it->getLinha(), it->getColuna());
            it->setIsExplodindo(true);
            it->setTempoCriacao(temporizador->getTempoAtual());
        }
    }
}

TipoItem ControladorItem::pegar(int linha, int coluna){
    TipoItem tipoItem;
    std::list<Item>::iterator it;
    
    for(it = itens.begin(); it != itens.end(); ++it){
        if(it->getLinha() == linha && it->getColuna() == coluna){
            tipoItem = it->getTipoItem();
            mapa->limparCelula(it->getLinha(), it->getColuna());
            it = itens.erase(it);
            return tipoItem;
        }
    }
    return tipoItem;
}

void ControladorItem::adicionar(int linha, int coluna, TipoItem tipoItem){
    itens.push_back(Item(linha, coluna, temporizador->getTempoAtual(), tipoItem));
    mapa->setCelula(linha, coluna, Celula::ITEM);
}

void ControladorItem::atualizar(){
    std::list<Item>::iterator it = itens.begin();

    while(it != itens.end()){

        if(it->isExplodindo() && temporizador->getTempoAtual() - it->getTempoCriacao() > TEMPO_EXPLOSAO_ITEM){
            it = itens.erase(it);
        }else{
            ++it;
        }
    }
}

void ControladorItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sprite(textura);

    int spriteX;
    int spriteY;
 
    for(Item itemAtual : itens) {

        if(!itemAtual.isExplodindo()){
            spriteX = (temporizador->getTempoAtual().asMilliseconds() / TEMPO_PROXIMA_ANIMACAO.asMilliseconds()) % 2;
            spriteY = (int)itemAtual.getTipoItem();
        }else{
            sf::Time dif = temporizador->getTempoAtual() - itemAtual.getTempoCriacao();
            spriteX = 2;
            spriteY = dif.asMilliseconds()/(TEMPO_EXPLOSAO_ITEM.asMilliseconds()/5);
        }

        sprite.setTextureRect(sf::IntRect(spriteX*TAMANHO_CELULA, spriteY*TAMANHO_CELULA,
                                        TAMANHO_CELULA, TAMANHO_CELULA));
        sprite.setPosition(itemAtual.getColuna()*TAMANHO_CELULA, itemAtual.getLinha()*TAMANHO_CELULA);
        target.draw (sprite, states);

    }
    
}