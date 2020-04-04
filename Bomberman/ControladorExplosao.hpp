#ifndef FIREMANAGER_HPP_INCLUDED
#define FIREMANAGER_HPP_INCLUDED

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Time.hpp>

#include <list>

#include "Temporizador.hpp"
#include "Explosao.hpp"
#include "Controlador.hpp"
#include "ControladorBloco.hpp"
#include "ControladorBomba.hpp"
#include "ControladorItem.hpp"

class ControladorExplosao : public Controlador{

    private:

        std::list<Explosao> explosoes;
        sf::RenderTexture bufferTextura;

        ControladorBomba* controladorBomba;
        ControladorItem* controladorItem;
        ControladorBloco* controladorBloco;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void atualizarBufferTextura();

    public:

        ControladorExplosao(Temporizador* Temporizador, Mapa* mapa);
        void linkar(ControladorBomba* controladorBomba, ControladorItem* controladorItem, ControladorBloco* controladorBloco);

        void explodeCelula(int linha, int coluna);
        void adicionaExplosao(int linha, int coluna, int forca);
        void atualizar();
};

#endif