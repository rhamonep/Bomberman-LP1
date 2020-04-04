#pragma once

#include "Objeto.hpp"

class Item : public Objeto{

    private:

        TipoItem tipoItem;
        bool explodindo;

    public:

        Item(int linha, int coluna, sf::Time tempoCriacao, TipoItem tipoItem);

        TipoItem getTipoItem();
        bool isExplodindo();

        void setTipoItem(TipoItem tipoItem);
        void setIsExplodindo(bool explodindo);
};