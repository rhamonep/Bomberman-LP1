#pragma once

#include "Controlador.hpp"
#include "Constantes.hpp"
#include "Item.hpp"

#include <list>

class ControladorBloco;
class ControladorItem : public Controlador{

    private:

        std::list<Item> itens;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        int sortear(int* numBlocos, std::vector<int>* itens);

    public:

        ControladorItem(Temporizador* temporizador, Mapa* mapa);
        void gerar(ControladorBloco* controladorBloco, std::vector<int> itens);
        void destruir(int linha, int coluna);
        void adicionar(int linha, int coluna, TipoItem tipoItem);
        TipoItem pegar(int linha, int coluna);
        void atualizar();
};