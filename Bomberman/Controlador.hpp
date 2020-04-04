#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Temporizador.hpp"
#include "Constantes.hpp"

class Mapa;
class Controlador : public sf::Drawable{

    protected:

        Temporizador* temporizador;
        Mapa* mapa;
        sf::Texture textura;

        virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const =0;

    public:

        Controlador(Temporizador* temporizador, Mapa* mapa);

        virtual void atualizar() =0;

};