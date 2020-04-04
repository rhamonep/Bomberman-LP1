#include "GeradorItem.hpp"

#include <iostream>
#include <cstdlib>


int GeradorItem::gerar(int numBlocos, std::vector<int> itens){
    if(numBlocos == 0){
        return -1;
    }

    int totalItens = 0;

    for(int quantidadeAtual : itens){
        totalItens += quantidadeAtual;
    }

    int rMax = std::max(totalItens, numBlocos);
    int random = rand() % rMax;

    int TipoItemRetornado = -1;

    if(totalItens > random){
        totalItens = 0;
        while(totalItens <= random){
            ++TipoItemRetornado;
            totalItens += itens[TipoItemRetornado];
        }
        --itens[TipoItemRetornado];
    }

    --numBlocos;
    return TipoItemRetornado;
}
