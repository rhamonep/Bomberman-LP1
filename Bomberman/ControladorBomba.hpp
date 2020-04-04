#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

#include <list>
#include <map>

#include "Controlador.hpp"
#include "Constantes.hpp"
#include "Bomba.hpp"
#include "GerenciadorBombas.hpp"

class ControladorExplosao;
class ControladorBomba : public Controlador{

    private:

        ControladorExplosao* controladorExplosao;

        std::list<GerenciadorBombas> gerenciadorBombas;
        std::list<Bomba> listaBombas;

        void draw (sf::RenderTarget &target, sf::RenderStates states) const;

        std::list<Bomba>::iterator transformaEmExplosao(std::list<Bomba>::iterator bomba);
        std::list<GerenciadorBombas>::iterator* buscaJogadorGerenciador(JogadorId jogadorId);
        void RemoveBombaGerenciador(JogadorId jogadorId, Bomba* bomba);
        void AdicionaBombaGerenciador(Bomba* bomba);

    public:

        ControladorBomba(Temporizador* temporizador, Mapa* mapa);
        void linkar(ControladorExplosao* controladorExplosao);

        void adicionar(bool temDetonador, int forca, int linha, int coluna, JogadorId jogadorId);
        void destruir(int linha, int coluna);
        void detonar(JogadorId jogadorId);
        int getQuantidadeBombas(JogadorId jogadorId);

        void atualizar();

        void adicionaListaBombaJogadores(JogadorId jogadorId);
};