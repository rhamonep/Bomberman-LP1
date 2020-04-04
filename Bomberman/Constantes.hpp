#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

const int TAMANHO_CELULA = 32;
const int TAMANHO_JOGADOR = 64;
const int MEIO_CELULA = (TAMANHO_CELULA-1) / 2;

const sf::Time TEMPO_PROXIMA_ANIMACAO = sf::milliseconds (130);
const sf::Time TEMPO_ANIMACAO_MORTE = sf::milliseconds(800);


const sf::Time TEMPO_BOMBA = sf::milliseconds(2000);
const sf::Time TEMPO_EXPLOSAO = sf::milliseconds(500);
const sf::Time TEMPO_EXPLOSAO_BLOCO = sf::milliseconds (500);
const sf::Time TEMPO_EXPLOSAO_ITEM = sf::milliseconds (500);
const sf::Time TEMPO_VELOCIDADE_EXPLOSAO= sf::milliseconds(0); 

const sf::Time TEMPO_VITORIA = sf::milliseconds(3000);

const sf::Time TEMPO_MOVIMENTACAO_JOGADOR = sf::milliseconds(7);

const int D_LINHA[4] = {+0, -1, +0, +1};
const int D_COLUNA[4]  = {-1, +0, +1, +0};

const int TOTAL_BOMBAS = 10;
const int TOTAL_FOGOS  = 10;
const int TOTAL_DETONADORES = 5;
const int TOTAL_PATINS = 5;

const sf::Color PEDRA_COR = sf::Color(0,0,0);
const sf::Color BLOCO_COR = sf::Color(128,128,128);

typedef int JogadorId;

enum class TipoBomba{
    NORMAL = 0,
    REMOTA = 1
};

enum class Direcao{
    ESQUERDA, 
    CIMA, 
    DIREITA, 
    BAIXO
};

enum class TipoItem{
    BOMBA = 0, 
    FOGO = 1, 
    DETONADOR = 2, 
    PATINS = 3,
    VAZIO = 4
};

enum class Celula{
    VAZIO,
    PEDRA,
    BLOCO,
    EXPLOSAO,
    BOMBA,
    ITEM
};