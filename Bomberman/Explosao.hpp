#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

#include <list>
#include <array>

#include "Temporizador.hpp"
#include "ExplosaoRamificacao.hpp"

class Mapa;
class ControladorExplosao;
class Explosao : public sf::Drawable{

    private:

        Temporizador* temporizador;
        ControladorExplosao* controladorExplosao;
        Mapa* mapa;

        int linha;
        int coluna;
        int forca;

        sf::Time ultimaAtualizacao;
        sf::Time primeiraAtualizacao;

        std::array<ExplosaoRamificacao, 4> ramificacoes;
    
        sf::Texture* textura;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool isMaximo();

    public:

        Explosao(Temporizador* temporizador, Mapa* mapa, ControladorExplosao* controladorExplosao, sf::Texture* textura, int linha, int coluna, int forca);

        bool espalhou();
        bool isDeletavel();
        void limparCelulas();
};
