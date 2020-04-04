#include "Item.hpp"

Item::Item(int linha, int coluna, sf::Time tempoCriacao, TipoItem tipoItem) : Objeto (linha, coluna, tempoCriacao) {
    this->tipoItem = tipoItem;
    this->explodindo = false;
}

TipoItem Item::getTipoItem(){
    return tipoItem;
}

void Item::setTipoItem(TipoItem tipoItem){
    this->tipoItem = tipoItem;
}

bool Item::isExplodindo(){
    return explodindo;
}

void Item::setIsExplodindo(bool explodindo){
    this->explodindo = explodindo;
}