#include "Explosao.hpp"

#include "Constantes.hpp"
#include "Temporizador.hpp"
#include "Mapa.hpp"
#include "ControladorExplosao.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

Explosao::Explosao(Temporizador* temporizador, Mapa* mapa, ControladorExplosao* controladorExplosao,
                  sf::Texture* textura, int linha, int coluna, int forca){

    this->controladorExplosao = controladorExplosao;
    this->temporizador = temporizador;
    this->mapa = mapa;
    this->linha = linha;
    this->coluna = coluna;
    this->forca = forca;
    this->ultimaAtualizacao = temporizador->getTempoAtual();
    this->primeiraAtualizacao = temporizador->getTempoAtual();
    this->textura = textura;

    ramificacoes.fill(ExplosaoRamificacao(0, forca==0));
}

bool Explosao::espalhou(){
    bool espalhou = false;

    while(!isMaximo() && temporizador->getTempoAtual() - ultimaAtualizacao > TEMPO_VELOCIDADE_EXPLOSAO){
        for(int iDirecao = 0; iDirecao < 4; ++iDirecao){
            
            ExplosaoRamificacao* ramificacaoAtual = &ramificacoes[iDirecao];

            if(ramificacaoAtual->isMaximo()){
                continue;
            }
            
            int linhaRamificacao = linha + D_LINHA[iDirecao] * (ramificacaoAtual->getTamanho()+1);
            int colunaRamificacao = coluna + D_COLUNA[iDirecao] * (ramificacaoAtual->getTamanho()+1);


            if(mapa->getCelula(linhaRamificacao, colunaRamificacao) != Celula::VAZIO &&
               mapa->getCelula(linhaRamificacao, colunaRamificacao) != Celula::EXPLOSAO){
                
                ramificacaoAtual->setIsMaximo(true);

                if(mapa->getCelula(linhaRamificacao, colunaRamificacao) != Celula::PEDRA){
                    controladorExplosao->explodeCelula(linhaRamificacao, colunaRamificacao);
                }
            }else{ 
                if(mapa->getCelula(linhaRamificacao, colunaRamificacao) != Celula::PEDRA){
                    controladorExplosao->explodeCelula(linhaRamificacao, colunaRamificacao);
                }
                
                ramificacaoAtual->setTamanho(ramificacaoAtual->getTamanho()+1);

                if(ramificacaoAtual->getTamanho() == forca){
                    ramificacaoAtual->setIsMaximo(true);
                    ramificacaoAtual->setExpandiuMaximo(true);
                } 
                espalhou = true; 
            }
        }
        ultimaAtualizacao += TEMPO_VELOCIDADE_EXPLOSAO;
    }
    
    return espalhou;
}

void Explosao::limparCelulas(){
    
   mapa->limparCelula(linha, coluna);

        int linhaRamificacao;
        int colunaRamificacao;

        for(int iDirecao = 0; iDirecao < 4; ++iDirecao){
            
            ExplosaoRamificacao* ramificacaoAtual = &ramificacoes[iDirecao];

            for(int tamanho = 1; tamanho <= ramificacaoAtual->getTamanho(); tamanho++){

                linhaRamificacao = linha + D_LINHA[iDirecao] * tamanho;
                colunaRamificacao = coluna + D_COLUNA[iDirecao] * tamanho;

                mapa->limparCelula(linhaRamificacao, colunaRamificacao);
            }
        } 
}

bool Explosao::isDeletavel(){
    if(isMaximo() && temporizador->getTempoAtual() - ultimaAtualizacao > TEMPO_EXPLOSAO){
        return true;
    }
    return false;
}

bool Explosao::isMaximo(){
    for(ExplosaoRamificacao ramificacaoAtual : ramificacoes){
        if(!ramificacaoAtual.isMaximo()){
            return false;
        }
    }
    return true;
}

void Explosao::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite (*textura);

    sf::Time dif = temporizador->getTempoAtual() - primeiraAtualizacao;

    int spriteY = temporizador->getTempoAtual().asMilliseconds()/(TEMPO_EXPLOSAO.asMilliseconds()/4) %3;

    sprite.setTextureRect (sf::IntRect(0, spriteY*TAMANHO_CELULA, TAMANHO_CELULA, TAMANHO_CELULA));
    sprite.setPosition (coluna*TAMANHO_CELULA, linha*TAMANHO_CELULA);   
    target.draw (sprite, states);
    
    for (int iDirecao = 0; iDirecao < 4; iDirecao++) {
        for (int tamanho = 1 ; tamanho <= ramificacoes[iDirecao].getTamanho(); tamanho++) {

            int spriteX = 1+(iDirecao%2);

            if (tamanho == ramificacoes[iDirecao].getTamanho() && ramificacoes[iDirecao].isExpandiuMaximo()){
                spriteX = 3+iDirecao; 
            }
            sprite.setTextureRect(sf::IntRect(spriteX*TAMANHO_CELULA, spriteY*TAMANHO_CELULA,
                                              TAMANHO_CELULA, TAMANHO_CELULA));
            sprite.setPosition ((coluna + D_COLUNA[iDirecao]*tamanho)*TAMANHO_CELULA,
                                (linha + D_LINHA[iDirecao]*tamanho)*TAMANHO_CELULA);
            target.draw (sprite, states);
        }
    }
}
