#pragma once

#include "Constantes.hpp"

class Objeto{

    protected:
    
        int linha;
        int coluna;

        sf::Time tempoCriacao;

    public:

        Objeto(int linha, int coluna, sf::Time tempoCriacao);

        int getLinha();
        int getColuna();
        sf::Time getTempoCriacao();

        void setLinha(int linha);
        void setColuna(int coluna);
        void setTempoCriacao(sf::Time tempoCriacao);
};