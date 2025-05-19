#ifndef ORDENADOR_UNIVERSAL_H
#define ORDENADOR_UNIVERSAL_H

#include <iostream>

class DadosAlg {
public:
    int cmp;
    int mov;
    int calls;
    double custo(double a, double b, double c);
    
    DadosAlg();
    void inccmp(int n);
    void incmov(int n);
    void inccalls(int n);
    void swap(int* a, int* b);
    void reset();
    void print();
};

// Declaração das funções de ordenação
void insertionSort(int v[], int l, int r, DadosAlg *d);
int median(int a, int b, int c);
void partition3(int* A, int l, int r, int* i, int* j, DadosAlg *d);
void quickSort3(int* A, int l, int r, DadosAlg *d);

// Classe principal do Ordenador Universal
class OrdenadorUniversal {
public:
    void ordenadorUniversal(int V[], int tam, int minTamParticao, int limiarQuebras, DadosAlg& d);
    int calcularQuebras(int V[], int tam);
private:
    
};

#endif