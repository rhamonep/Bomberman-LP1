#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

#include <list>
#include <vector>

#include "Temporizador.hpp"
#include "Bloco.hpp"
#include "Controlador.hpp"

class ControladorItem;
class ControladorBloco : public Controlador{

    private:
        ControladorItem* controladorItem;
        std::list<Bloco> blocos;
        int totalBlocos;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    public:

        ControladorBloco(Temporizador* temporizador, Mapa* mapa);
        int getTotalBlocos();
        void gerar(sf::Image* imagemMapa);
        void destruir(int linha, int coluna);
        void adicionar(int linha, int coluna);
        void atualizar();
        void editarItem(int linha, int coluna, TipoItem tipoItem);
        void linkar(ControladorItem* controladorItem);
};