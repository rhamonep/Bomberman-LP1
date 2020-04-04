#include "Bloco.hpp"
#include "Constantes.hpp"

Bloco::Bloco(int linha, int coluna, sf::Time tempoCriacao) : Objeto(linha, coluna, tempoCriacao){
    explodindo = false;
    tipoItem = TipoItem::VAZIO;
}

TipoItem Bloco::getTipoItem(){
    return tipoItem;
}

void Bloco::setTipoItem(TipoItem tipoItem){
    this->tipoItem = tipoItem;
}

bool Bloco::isExplodindo(){
    return explodindo;
}

void Bloco::setIsExplodindo(bool explodindo){
    this->explodindo = explodindo;
}