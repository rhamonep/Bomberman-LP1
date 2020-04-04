#include "ControladorBomba.hpp"

#include "Constantes.hpp"
#include "ControladorExplosao.hpp"
#include "Mapa.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <sstream>
#include <stdexcept>


ControladorBomba::ControladorBomba(Temporizador* temporizador, Mapa* mapa) : Controlador(temporizador, mapa){

    std::string caminho = "sprites/bomb.png";
    if (!textura.loadFromFile(caminho)) {
        std::ostringstream oss;
        oss << "ERRO! ControladorBombas::ControladorBombas -> Não foi posśivel encontrar caminho: " << caminho;
        throw std::runtime_error (oss.str());
    } 
}

void ControladorBomba::linkar(ControladorExplosao* controladorExplosao){
    this->controladorExplosao = controladorExplosao;
}

void ControladorBomba::adicionar(bool temDetonador, int forca, int linha, int coluna, JogadorId jogadorId){
    if(mapa->getCelula(linha, coluna) != Celula::VAZIO)
        return;

    TipoBomba tipo = (temDetonador ? TipoBomba::REMOTA : TipoBomba::NORMAL);
    
    listaBombas.push_back(Bomba(jogadorId, tipo, temporizador->getTempoAtual(), forca, linha, coluna));
    AdicionaBombaGerenciador(&listaBombas.back());
    mapa->setCelula(linha, coluna, Celula::BOMBA);
}

void ControladorBomba::destruir(int linha, int coluna){

    std::list<Bomba>::iterator it;

    for(it = listaBombas.begin(); it != listaBombas.end(); ++it){

        if(it->getLinha() == linha && it->getColuna() == coluna){
            RemoveBombaGerenciador(it->getJogadorId(), &(*it));
            transformaEmExplosao(it);
            return;
        }
    }
}

int ControladorBomba::getQuantidadeBombas(JogadorId jogadorId){
    std::list<GerenciadorBombas>::iterator itGerenciador;

    for(itGerenciador = gerenciadorBombas.begin(); itGerenciador != gerenciadorBombas.end(); ++itGerenciador){
        if(itGerenciador->getJogadorID() == jogadorId){
            return itGerenciador->getTotalBombas();
        }
    }
    return -1;
}

void ControladorBomba::detonar(JogadorId jogadorId){

    std::list<GerenciadorBombas>::iterator itGerenciador;

    for(itGerenciador = gerenciadorBombas.begin(); itGerenciador != gerenciadorBombas.end(); ++itGerenciador){
        if(itGerenciador->getJogadorID() == jogadorId){
            Bomba detonada = itGerenciador->detonaBomba();
            std::list<Bomba>::iterator it = listaBombas.begin();

            while(it != listaBombas.end()){
                if(it->getLinha() == detonada.getLinha() && it->getColuna() == detonada.getColuna()){
                    it = transformaEmExplosao(it);
                }else{
                    ++it;
                }
            }


        }
    }
}

void ControladorBomba::atualizar(){
    
    std::list<Bomba>::iterator it = listaBombas.begin();
    
    while(it != listaBombas.end()){

        bool temDetonador = (it->getTipo() == TipoBomba::REMOTA ? true : false);

        if(!temDetonador && temporizador->getTempoAtual() - it->getTempoCriacao() > TEMPO_BOMBA){
            mapa->limparCelula(it->getLinha(), it->getColuna());
            RemoveBombaGerenciador(it->getJogadorId(), &(*it));
            it = transformaEmExplosao(it);
        }else{
            ++it;
        }
    }
}

void ControladorBomba::adicionaListaBombaJogadores(JogadorId jogadorId){
    gerenciadorBombas.push_back(GerenciadorBombas(jogadorId));
}

void ControladorBomba::draw(sf::RenderTarget &target, sf::RenderStates states) const
{


    sf::Sprite sprite (textura);
    int spriteX = (temporizador->getTempoAtual().asMilliseconds() / TEMPO_PROXIMA_ANIMACAO.asMilliseconds()) % 4;


    for (Bomba bombaAtual : listaBombas) {
        int spriteY = (bombaAtual.getTipo() == TipoBomba::NORMAL ? 0 : 1);

        sprite.setTextureRect (sf::IntRect(spriteX*TAMANHO_CELULA, spriteY*TAMANHO_CELULA, TAMANHO_CELULA, TAMANHO_CELULA));
        sprite.setPosition (bombaAtual.getColuna()*TAMANHO_CELULA, bombaAtual.getLinha()*TAMANHO_CELULA);
        target.draw (sprite, states);
    }
}

void ControladorBomba::RemoveBombaGerenciador(JogadorId jogadorId, Bomba* bomba){
    std::list<GerenciadorBombas>::iterator itGerenciador;

    for(itGerenciador = gerenciadorBombas.begin(); itGerenciador != gerenciadorBombas.end(); ++itGerenciador){
        if(itGerenciador->getJogadorID() == jogadorId){
            itGerenciador->removeBomba(bomba);
        }
    }
}

void ControladorBomba::AdicionaBombaGerenciador(Bomba* bomba){
    std::list<GerenciadorBombas>::iterator it;

    for(it = gerenciadorBombas.begin(); it != gerenciadorBombas.end(); ++it){
        if(it->getJogadorID() == bomba->getJogadorId()){
            it->adicionaBomba(bomba);
        }
    }
}

std::list<Bomba>::iterator ControladorBomba::transformaEmExplosao(std::list<Bomba>::iterator itBomba){

    controladorExplosao->adicionaExplosao(itBomba->getLinha(), itBomba->getColuna(), itBomba->getForca());
    return listaBombas.erase(itBomba);
}
