#include "ControladorJogadores.hpp"

ControladorJogadores::ControladorJogadores(Temporizador* temporizador, Mapa* mapa) : Controlador(temporizador, mapa){

    this->assistenteMovimento = new AssistenteMovimento(temporizador, mapa);
    this->vitoria = false;
}

void ControladorJogadores::linkar(ControladorBomba* controladorBomba,  ControladorItem* controladorItem){
    this->controladorBomba = controladorBomba;
    this->controladorItem = controladorItem;
}

void ControladorJogadores::adicionarJogador(Jogador jogador){
    jogadores.push_back(jogador);
}

std::vector<Jogador>* ControladorJogadores::getJogadores(){
    return &jogadores;
}

void ControladorJogadores::atualizar(){
    if(!vitoria){
        for(Jogador &jogadorAtual : jogadores){
            interagirComMapa(&jogadorAtual);
            assistenteMovimento->atualizarPosicao(&jogadorAtual);

            if(temporizador->getTempoAtual() - jogadorAtual.getUltimaAtualizacao() > TEMPO_ANIMACAO_MORTE){
                jogadorAtual.setMorrendo(false);
            }
        }
        verificaVitoria();
    }
}

void ControladorJogadores::interagirComMapa(Jogador* jogador){
    switch(mapa->getCelula(jogador->getLinha(), jogador->getColuna())){
        case Celula::EXPLOSAO:
            jogador->setMorrendo(true);
            jogador->setIsMorto(true);
            break;
        case Celula::ITEM:
            switch(controladorItem->pegar(jogador->getLinha(), jogador->getColuna())){
                    case TipoItem::BOMBA:
                        jogador->setMaxBomba(jogador->getMaxBomba() + 1);
                        break;
                    case TipoItem::DETONADOR:
                        jogador->setTemDetonador(true);
                        break;
                    case TipoItem::FOGO:
                        jogador->setForca(jogador->getForca() + 1);
                        break;
                    case TipoItem::PATINS:
                        jogador->setVelocidade(jogador->getVelocidade() + sf::microseconds(500)); 
                        break;
                    default:
                        break;
                }
            break;
        default:

            break;
    }
}

void ControladorJogadores::mover(Jogador* jogador, Direcao direcao){

    jogador->setDirecaoProxima(direcao);

    if(!jogador->isAndando() || assistenteMovimento->isDirecoesOpostas(jogador->getDirecaoAtual(), 
                                                                          direcao)){
        jogador->setDirecaoAtual(jogador->getDirecaoProxima());
    }
    jogador->setIsAndando(true);
}

void ControladorJogadores::parar(Jogador* jogador, Direcao direcao){

    if(direcao == jogador->getDirecaoAtual()){
        if(jogador->getDirecaoAtual() != jogador->getDirecaoProxima()){
            jogador->setDirecaoAtual(jogador->getDirecaoProxima());
        }else{
            jogador->setIsAndando(false);
        }
    }else if(direcao == jogador->getDirecaoProxima()){
        jogador->setDirecaoProxima(jogador->getDirecaoAtual());
        jogador->setIsAndando(false);
    }
}

void ControladorJogadores::detonarBomba(Jogador* jogador){
    if(jogador->getTemDetonador()){
        controladorBomba->detonar(jogador->getId());
    }
}

void ControladorJogadores::colocarBomba(Jogador* jogador){

    if(controladorBomba->getQuantidadeBombas(jogador->getId()) < jogador->getMaxBomba() &&
       controladorBomba->getQuantidadeBombas(jogador->getId()) != -1){

        controladorBomba->adicionar(jogador->getTemDetonador(), jogador->getForca(), 
                                    jogador->getLinha(), jogador->getColuna(), 
                                    jogador->getId());
    }
}

void ControladorJogadores::verificaVitoria(){
    int vivos = 0;
    for(Jogador &jogadorAtual : jogadores){
        if(!jogadorAtual.isMorto()){
            vivos++;
        }
    }
    this->vitoria = (vivos == 1);
}

bool ControladorJogadores::isVitoria(){
    return vitoria;
}


void ControladorJogadores::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    int spriteX;
    int spriteY;

    for(Jogador jogadorAtual : jogadores){


            if(jogadorAtual.isMorrendo()){
                spriteY = 4;

                sf::Time dif = temporizador->getTempoAtual() - jogadorAtual.getUltimaAtualizacao();

                spriteX = dif.asMilliseconds() / (TEMPO_ANIMACAO_MORTE.asMilliseconds()/4);

            }else if(!jogadorAtual.isMorto()){

                if(vitoria){
                    spriteY = 5;

                    sf::Time dif = temporizador->getTempoAtual() - jogadorAtual.getUltimaAtualizacao();

                    spriteX = dif.asMilliseconds() / (TEMPO_VITORIA.asMilliseconds()/10) % 2;
                    
                }else{
                    spriteY = (int)jogadorAtual.getDirecaoAtual();

                    if(jogadorAtual.isAndando()){

                        spriteX = (jogadorAtual.getProxAnimacao() / 18) % 8;

                        if(spriteX % 2 == 0){
                            spriteX = 0;
                        }else{
                            spriteX == 3 ? spriteX = 2 : (spriteX == 5 ? spriteX = 1 : (spriteX == 7 ? spriteX = 2 : spriteX));
                        }

                    }else{
                        spriteX = 0;
                    }             
                }
            }

            sf::Sprite sprite(*jogadorAtual.getTextura());

            sprite.setOrigin(MEIO_CELULA, TAMANHO_JOGADOR - TAMANHO_CELULA);
            sprite.setTextureRect(sf::IntRect(spriteX*TAMANHO_JOGADOR, spriteY*TAMANHO_JOGADOR,
                                            TAMANHO_JOGADOR, TAMANHO_JOGADOR));
            sprite.setPosition(jogadorAtual.getColuna()*TAMANHO_CELULA + jogadorAtual.getPosicaoX()-MEIO_CELULA,
                                jogadorAtual.getLinha()*TAMANHO_CELULA + jogadorAtual.getPosicaoY()-MEIO_CELULA);
            
            target.draw(sprite, states);
    }
}