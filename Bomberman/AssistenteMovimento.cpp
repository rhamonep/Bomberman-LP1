#include "AssistenteMovimento.hpp"

AssistenteMovimento::AssistenteMovimento(Temporizador* temporizador, Mapa *mapa){
    this->temporizador = temporizador;
    this->mapa = mapa;
}

void AssistenteMovimento::atualizarPosicao(Jogador* jogador){

    if(jogador->isMorto() || jogador->isMorrendo()){
        return;
    }

    if(!jogador->isAndando()){
        jogador->setUltimaAtualizacao(temporizador->getTempoAtual());
        return;
    }

    sf::Time dif = temporizador->getTempoAtual() - jogador->getUltimaAtualizacao();

    int totalPixelsAndados = dif.asMilliseconds() / jogador->getVelocidade().asMilliseconds();

    jogador->setUltimaAtualizacao(jogador->getUltimaAtualizacao() + 
                                  jogador->getVelocidade() * (sf::Int64)totalPixelsAndados);
    jogador->setProxAnimacao(jogador->getProxAnimacao() + totalPixelsAndados); 
    
    
    while(totalPixelsAndados > 0){
        
        bool esquerda = mapa->isAndavel(jogador->getLinha()+0, jogador->getColuna()-1);
        bool cimaEsquerda = mapa->isAndavel(jogador->getLinha()-1, jogador->getColuna()-1);
        bool baixoEsquerda = mapa->isAndavel(jogador->getLinha()+1, jogador->getColuna()-1);
        bool direita = mapa->isAndavel(jogador->getLinha()+0, jogador->getColuna()+1);
        bool cimaDireita = mapa->isAndavel(jogador->getLinha()-1, jogador->getColuna()+1);
        bool baixoDireita = mapa->isAndavel(jogador->getLinha()+1, jogador->getColuna()+1);
        bool cima = mapa->isAndavel(jogador->getLinha()-1, jogador->getColuna()+0);
        bool baixo = mapa->isAndavel(jogador->getLinha()+1, jogador->getColuna()+0);
        
        switch(jogador->getDirecaoAtual()){

            case Direcao::ESQUERDA:
            
                if(jogador->getPosicaoY() < MEIO_CELULA){
                    if(esquerda){
                        jogador->setDirecaoAtual(Direcao::BAIXO);
                    }else if(cimaEsquerda){
                        jogador->setDirecaoAtual(Direcao::CIMA);
                    }else{
                        totalPixelsAndados = 0;
                    }
                }else if(jogador->getPosicaoY() > MEIO_CELULA){
                    if(esquerda){
                        jogador->setDirecaoAtual(Direcao::CIMA);
                    }else if(baixoEsquerda){
                        jogador->setDirecaoAtual(Direcao::BAIXO);
                    }else{
                        totalPixelsAndados = 0;
                    }
                }else{
                    if(jogador->getPosicaoX() == MEIO_CELULA){
                        if(esquerda){
                            jogador->setDirecaoAtual(Direcao::ESQUERDA);
                        }else{
                            totalPixelsAndados = 0;
                        }
                    }else{
                        jogador->setDirecaoAtual(Direcao::ESQUERDA);
                    }
                }
                break;
            case Direcao::CIMA:
                if(jogador->getPosicaoX() < MEIO_CELULA){
                    if(cima){
                        jogador->setDirecaoAtual(Direcao::DIREITA);
                    }else if(cimaEsquerda){
                        jogador->setDirecaoAtual(Direcao::ESQUERDA);
                    }else{
                        totalPixelsAndados = 0;
                    }
                }else if(jogador->getPosicaoX() > MEIO_CELULA){
                    if(cima){
                        jogador->setDirecaoAtual(Direcao::ESQUERDA);
                    }else if(cimaDireita){
                        jogador->setDirecaoAtual(Direcao::DIREITA);
                    }else{
                        totalPixelsAndados = 0;
                    }
                }else{
                    if(jogador->getPosicaoY() == MEIO_CELULA){
                        if(cima){
                            jogador->setDirecaoAtual(Direcao::CIMA);
                        }else{
                            totalPixelsAndados = 0;
                        }
                    }else{
                        jogador->setDirecaoAtual(Direcao::CIMA);
                    }
                }
                break;
            case Direcao::DIREITA:
                if(jogador->getPosicaoY() < MEIO_CELULA){
                    if(direita){
                        jogador->setDirecaoAtual(Direcao::BAIXO);
                    }else if(cimaDireita){
                        jogador->setDirecaoAtual(Direcao::CIMA);
                    }else{
                        totalPixelsAndados = 0;
                    }
                }else if(jogador->getPosicaoY() > MEIO_CELULA){
                    if(direita){
                        jogador->setDirecaoAtual(Direcao::CIMA);
                    }else if(baixoDireita){
                        jogador->setDirecaoAtual(Direcao::BAIXO);
                    }else{
                        totalPixelsAndados = 0;
                    }
                }else{
                    if(jogador->getPosicaoX() == MEIO_CELULA){
                        if(direita){
                            jogador->setDirecaoAtual(Direcao::DIREITA);
                        }else{
                            totalPixelsAndados = 0;
                        }
                    }else{
                        jogador->setDirecaoAtual(Direcao::DIREITA);
                    }
                }
                break;
            case Direcao::BAIXO:
                if(jogador->getPosicaoX() < MEIO_CELULA){
                    if(baixo){
                        jogador->setDirecaoAtual(Direcao::DIREITA);
                    }else if(baixoEsquerda){
                        jogador->setDirecaoAtual(Direcao::ESQUERDA);
                    }else{
                        totalPixelsAndados = 0;
                    }
                }else if(jogador->getPosicaoX() > MEIO_CELULA){
                    if(baixo){
                        jogador->setDirecaoAtual(Direcao::ESQUERDA);
                    }else if(baixoDireita){
                        jogador->setDirecaoAtual(Direcao::DIREITA);
                    }else{
                        totalPixelsAndados = 0;
                    }
                }else{
                    if(jogador->getPosicaoY() == MEIO_CELULA){
                        if(baixo){
                            jogador->setDirecaoAtual(Direcao::BAIXO);
                        }else{
                            totalPixelsAndados = 0;
                        }
                    }else{
                        jogador->setDirecaoAtual(Direcao::BAIXO);
                    }
                }
                break;
            default:
                break;
        }
        centraliza(jogador, &totalPixelsAndados);
        if(jogador->getPosicaoX() == MEIO_CELULA && jogador->getPosicaoY() == MEIO_CELULA){

            std::array<bool, 4> direcoesLivres = {esquerda, cima, direita, baixo};
            
            if(direcoesLivres[(int)jogador->getDirecaoProxima()]){
                jogador->setDirecaoAtual(jogador->getDirecaoProxima());
            }
        }
    }
}

void AssistenteMovimento::centraliza(Jogador* jogador, int* totalPixelsAndados){
    int novaPosicaoY = jogador->getPosicaoY();
    int novaPosicaoX = jogador->getPosicaoX();

    switch(jogador->getDirecaoAtual()){
        case Direcao::ESQUERDA:
            if(jogador->getPosicaoX() <= MEIO_CELULA){
                novaPosicaoX = -MEIO_CELULA;
            }else{
                novaPosicaoX = MEIO_CELULA;
            }
            break;
        case Direcao::CIMA:
            if(jogador->getPosicaoY() <= MEIO_CELULA){
                novaPosicaoY = -MEIO_CELULA;
            }else{
                novaPosicaoY = MEIO_CELULA;
            }
            break;
        case Direcao::DIREITA:
            if(jogador->getPosicaoX() >= MEIO_CELULA){
                novaPosicaoX = TAMANHO_CELULA+MEIO_CELULA;
            }else{
                novaPosicaoX = MEIO_CELULA;
            }
            break;
        case Direcao::BAIXO:
            if(jogador->getPosicaoY() >= MEIO_CELULA){
                novaPosicaoY = TAMANHO_CELULA+MEIO_CELULA;
            }else{
                novaPosicaoY = MEIO_CELULA;
            }
            break;
        default:
            *totalPixelsAndados = 0;
            return;
            break;
    } 
    
    int iDir = (int)(jogador->getDirecaoAtual());
    while(*totalPixelsAndados > 0 && (jogador->getPosicaoY() != novaPosicaoY ||
                            jogador->getPosicaoX() != novaPosicaoX)){

        jogador->setPosicaoY(jogador->getPosicaoY() + D_LINHA[iDir]); 
        jogador->setPosicaoX(jogador->getPosicaoX() + D_COLUNA[iDir]);
        *totalPixelsAndados -= 1;                   
    }

    atualizaPosicaoMapa(jogador);
}

void AssistenteMovimento::atualizaPosicaoMapa(Jogador* jogador){

    while(jogador->getPosicaoY() < 0){
        jogador->setPosicaoY(jogador->getPosicaoY() + TAMANHO_CELULA);
        jogador->setLinha(jogador->getLinha() - 1);
    }

    while(jogador->getPosicaoY() >= TAMANHO_CELULA){
        jogador->setPosicaoY(jogador->getPosicaoY() - TAMANHO_CELULA);
        jogador->setLinha(jogador->getLinha() + 1);
    }
 
    while(jogador->getPosicaoX() < (0)){
        jogador->setPosicaoX(jogador->getPosicaoX() + TAMANHO_CELULA);
        jogador->setColuna(jogador->getColuna() - 1);
    }

    while(jogador->getPosicaoX() >= (TAMANHO_CELULA)){
        jogador->setPosicaoX(jogador->getPosicaoX() - TAMANHO_CELULA);
        jogador->setColuna(jogador->getColuna() + 1);
    }
}

bool AssistenteMovimento::isDirecoesOpostas (Direcao d1, Direcao d2){

    if ((d1 == Direcao::ESQUERDA && d2 == Direcao::DIREITA) || (d1 == Direcao::DIREITA && d2 == Direcao::ESQUERDA)){
        return true;
    }

    if ((d1 == Direcao::CIMA && d2 == Direcao::BAIXO) || (d1 == Direcao::BAIXO && d2 == Direcao::CIMA)){
        return true;
    }

    return false;
}