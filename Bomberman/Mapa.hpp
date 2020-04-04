#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <vector>
#include <memory>

#include "Temporizador.hpp"
#include "ControladorBloco.hpp"
#include "ControladorExplosao.hpp"
#include "ControladorBomba.hpp"
#include "ControladorItem.hpp"
#include "Constantes.hpp"

class Mapa : public sf::Drawable{
   
    private:

        int numLinhas;
        int numColunas;

        std::vector<Celula> celulas;
        
        Temporizador* temporizador;

        sf::Texture texturaTerreno;

        sf::RenderTexture bufferTextura;
        std::vector<int> itens;

        int index(int linha, int col) const;
        void atualizarBufferTextura();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void printaMapa();
        void destroiTodosBlocos();
    
    public:

        Mapa(sf::Image* imagemMapa);

        void atualizar();

        int getNumLinhas();
        int getNumCol();
        void gerarMapa(sf::Image* imagemMapa);

        bool isAndavel(int linha, int coluna);

        Celula getCelula(int linha, int coluna);
        void setCelula(int linha, int coluna, Celula conteudo);
        void limparCelula(int linha, int coluna);

};