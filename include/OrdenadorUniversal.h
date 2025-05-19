#ifndef ORDENADOR_UNIVERSAL_H
#define ORDENADOR_UNIVERSAL_H
#include "Ordenacao.h"
#include <iostream>



void registraEstatisticas(double custo);
void imprimeEstatisticas(double custo);
// Declaração das funções de ordenação

int determinaLimiarParticao(int V[], int tam, double limiarCusto, double a, double b, double c);
int determinaLimiarQuebras(int V[], int tam, double limiarCusto, double a, double b, double c);
void calculaNovaFaixa(int limParticao, int &minMPS, int &maxMPS, int &passoMPS);
int menorCusto(double custos[], int tamanho);
int calcularQuebras(int V[], int tam);


// Classe principal do Ordenador Universal
class OrdenadorUniversal {
public:
    void ordenadorUniversal(int V[], int tam, int minTamParticao, int limiarQuebras, DadosAlg* d);
    
private:
    
};

#endif