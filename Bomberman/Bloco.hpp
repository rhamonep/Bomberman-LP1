#pragma once

#include <SFML/System/Time.hpp>
#include "Constantes.hpp"
#include "Objeto.hpp"

class Bloco : public Objeto{

   private: 

        bool explodindo;
        TipoItem tipoItem;


    public:

        Bloco(int linha, int coluna, sf::Time tempoCriacao);

        TipoItem getTipoItem();
        bool isExplodindo();

        void setTipoItem(TipoItem tipoItem);
        void setIsExplodindo(bool explodindo);
};