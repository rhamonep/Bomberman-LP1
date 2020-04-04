#pragma once
#include "Bomba.hpp"
#include "Constantes.hpp"

#include <list>

class GerenciadorBombas{

    private:

        JogadorId jogadorId;
        std::list<Bomba*> listaBombas;
        int totalBombas;

    public:
    
        GerenciadorBombas(JogadorId jogadorId);

        JogadorId getJogadorID();
        int getTotalBombas();

        void adicionaBomba(Bomba* bomba);
        void removeBomba(Bomba* bomba);
        Bomba detonaBomba();

        void setJogadorId(JogadorId jogadorId);
};