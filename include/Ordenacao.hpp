#ifndef ORDENACAO_H
#define ORDENACAO_H

class DadosAlg {
public:
    int cmp;
    int mov;
    int calls;
    double custo;

    double setCusto(double a, double b, double c);
    
    void setAbc();
    DadosAlg();
    void inccmp(int n);
    void incmov(int n);
    void inccalls(int n);
    void swap(int* a, int* b);
    void reset();
    void print();
};


void insertionSort(int v[], int l, int r, DadosAlg *d);
int median(int a, int b, int c);
void partition3(int* A, int l, int r, int* i, int* j, DadosAlg *d);
void quickSort3(int *A, int l, int r, int minTamParticao, DadosAlg *d);





#endif