#pragma once

#include "Constantes.hpp"
#include "Objeto.hpp"

class Bomba : public Objeto{

    private:

        JogadorId jogadorId;

        TipoBomba tipo;
        int forca;

    public:

       Bomba(JogadorId jogador, TipoBomba tipo, sf::Time tempoCriacao, int forca, int linha, int coluna); 

       int getForca();
       TipoBomba getTipo();
       JogadorId getJogadorId();

};