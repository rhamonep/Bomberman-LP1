#include "Jogo.hpp"

#include "Constantes.hpp"

#include <SFML/Graphics/Image.hpp>
#include <stdexcept>
#include <sstream>

Jogo::Jogo(std::string caminho){

    sf::Image imagemMapa;
    
    if(!imagemMapa.loadFromFile(caminho)){
        std::ostringstream oss;
        oss << "ERRO! Jogo::jogo -> Não foi possível encontrar o caminho: " << caminho;
        throw std::runtime_error(oss.str());
    }

    numLinhas = imagemMapa.getSize().y;
    numColunas = imagemMapa.getSize().x;

    temporizador = new Temporizador();

    this->mapa = new Mapa(&imagemMapa);    
    
    this->controladorItem = new ControladorItem(temporizador, mapa);
    this->controladorBloco = new ControladorBloco(temporizador, mapa);
    this->controladorExplosao = new ControladorExplosao(temporizador, mapa);
    this->controladorBomba = new ControladorBomba(temporizador, mapa);
    this->controladorJogadores = new ControladorJogadores(temporizador, mapa);

    this->gerenciadorEventos = new GerenciadorEventos(controladorJogadores, controladorJogadores->getJogadores(), temporizador);
    this->ultimaAtualizacao = temporizador->getTempoAtual();
    this->emJogo = true;

    conectarControladores();

    JogadorControle* controle_1 = new JogadorControle(sf::Keyboard::A,
                                                (sf::Keyboard::W),
                                                (sf::Keyboard::D),
                                                (sf::Keyboard::S),
                                                (sf::Keyboard::Q),
                                                (sf::Keyboard::E));


    controladorJogadores->adicionarJogador(Jogador(1, temporizador->getTempoAtual(), controle_1, "sprites/player1.png", 
                                            1, 1));
    controladorBomba->adicionaListaBombaJogadores(1);

    JogadorControle* controle_2 = new JogadorControle(sf::Keyboard::Left,
                                                    (sf::Keyboard::Up),
                                                    (sf::Keyboard::Right),
                                                    (sf::Keyboard::Down),
                                                    (sf::Keyboard::RShift),
                                                    (sf::Keyboard::RControl));

    controladorJogadores->adicionarJogador(Jogador(2, temporizador->getTempoAtual(), controle_2, "sprites/player2.png",
                                mapa->getNumLinhas()-2, mapa->getNumCol()-2));
                                
    controladorBomba->adicionaListaBombaJogadores(2);

    std::vector<int> itens(4,0);

    itens[(int)(TipoItem::BOMBA)] = TOTAL_BOMBAS;
    itens[(int)(TipoItem::FOGO)] = TOTAL_FOGOS;
    itens[(int)(TipoItem::DETONADOR)] = TOTAL_DETONADORES;
    itens[(int)(TipoItem::PATINS)] = TOTAL_PATINS;

    mapa->gerarMapa(&imagemMapa);
    controladorBloco->gerar(&imagemMapa);
    controladorItem->gerar(controladorBloco, itens);
}

void Jogo::conectarControladores(){
 
    controladorBloco->linkar(controladorItem);
    controladorBomba->linkar(controladorExplosao);
    controladorJogadores->linkar(controladorBomba, controladorItem);
    controladorExplosao->linkar(controladorBomba, controladorItem, controladorBloco);
}

int Jogo::alturaEmPixels(){
    return numColunas * TAMANHO_CELULA;
}

int Jogo::larguraEmPixels(){
    return numLinhas * TAMANHO_CELULA;
}

void Jogo::atualizar(){

    controladorJogadores->atualizar();

    controladorBloco->atualizar();

    controladorItem->atualizar();

    controladorBomba->atualizar();

    controladorExplosao->atualizar();

    if(!controladorJogadores->isVitoria()){
        ultimaAtualizacao = temporizador->getTempoAtual();
    }

    if(temporizador->getTempoAtual() - ultimaAtualizacao > TEMPO_VITORIA){
        emJogo = false;
    }
}

void Jogo::gerenciaEventos(sf::Event* evento){
    if(!controladorJogadores->isVitoria()){
        gerenciadorEventos->gerenciar(evento);
    }
}

bool Jogo::isEmJogo(){
    return emJogo;
}

void Jogo::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(*mapa, states);
    target.draw(*controladorItem, states);
    target.draw(*controladorBloco, states);
    target.draw(*controladorBomba, states);
    target.draw(*controladorExplosao, states);
    target.draw(*controladorJogadores, states);
}