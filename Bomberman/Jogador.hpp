#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include <array>
#include <string>

#include "Temporizador.hpp"
#include "JogadorControle.hpp"
#include "Mapa.hpp"
#include "Constantes.hpp"

class Jogador{

    private:

        JogadorId jogadorId;
        JogadorControle* controle;

        sf::Time ultimaAtualizacao;
        sf::Texture textura;

        int proxAnimacao;

        int linha;
        int coluna;

        int posicaoX;
        int posicaoY;

        Direcao dirAtual;
        Direcao dirProxima;

        bool morto;
        bool morrendo;
        bool andando;

        sf::Time velocidade;
        int forca;
        int maxBomba;
        bool temDetonador;

    public:

        Jogador(JogadorId JogadorId, sf::Time ultimaAtualizacao, JogadorControle* controle, std::string caminho, int linha, int coluna);

        JogadorId getId();
        JogadorControle* getControle();
        sf::Time getUltimaAtualizacao();
        sf::Texture* getTextura();
        int getProxAnimacao();
        int getLinha();
        int getColuna();
        int getPosicaoY();
        int getPosicaoX();
        Direcao getDirecaoAtual();
        Direcao getDirecaoProxima();
        bool isMorto();
        bool isMorrendo();
        bool isAndando();
        sf::Time getVelocidade();
        int getForca();
        int getMaxBomba();
        bool getTemDetonador();

        void setId(JogadorId jogadorId);
        void setControle(JogadorControle* controle);
        void setUltimaAtualizacao(sf::Time ultimaAtualizacao);
        void setTextura(sf::Texture textura);
        void setProxAnimacao(int proxAnimacao);
        void setLinha(int linha);
        void setColuna(int coluna);
        void setPosicaoY(int posicaoX);
        void setPosicaoX(int posicaoY);
        void setDirecaoAtual(Direcao dirAtual);
        void setDirecaoProxima(Direcao dirProxima);
        void setIsMorto(bool isMorto);
        void setMorrendo(bool morrendo);
        void setIsAndando(bool isAndando);
        void setVelocidade(sf::Time velocidade);
        void setForca(int forca);
        void setMaxBomba(int maxBomba);
        void setTemDetonador(bool temDetonador);

};