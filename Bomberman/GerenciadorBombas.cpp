#include "GerenciadorBombas.hpp"

GerenciadorBombas::GerenciadorBombas(JogadorId jogadorId){
    this->jogadorId = jogadorId;
    this->totalBombas = 0;
}

JogadorId GerenciadorBombas::getJogadorID(){
    return jogadorId;
}

void GerenciadorBombas::setJogadorId(JogadorId jogadorId){
    this->jogadorId = jogadorId;
}

int GerenciadorBombas::getTotalBombas(){
    return totalBombas;
}

void GerenciadorBombas::adicionaBomba(Bomba* bomba){
    listaBombas.push_back(bomba);
    ++totalBombas;
}

Bomba GerenciadorBombas::detonaBomba(){

    if(totalBombas > 0){
    
        Bomba detonada = *listaBombas.front();
        listaBombas.pop_front();

        --totalBombas;

        return detonada;
    }
}

void GerenciadorBombas::removeBomba(Bomba* bomba){
    
    std::list<Bomba*>::iterator it = listaBombas.begin();
    
    while(it != listaBombas.end()){
        if((*it)->getLinha() == bomba->getLinha() && 
           (*it)->getColuna() == bomba->getColuna()){
            it = listaBombas.erase(it);
            --totalBombas;
        }else{
            ++it;
        }
    }
}
