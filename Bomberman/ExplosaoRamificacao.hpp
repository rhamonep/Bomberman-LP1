#pragma once

class ExplosaoRamificacao{

    private:

        int tamanho;
        bool maximo;
        bool expandiuMaximo;

    public:

        ExplosaoRamificacao();
        ExplosaoRamificacao(int tamanho, bool maximo);

        int getTamanho() const;
        bool isMaximo() const;
        bool isExpandiuMaximo() const;

        void setTamanho(int tamanho);
        void setIsMaximo(bool maximo);
        void setExpandiuMaximo(bool expandiu);
};