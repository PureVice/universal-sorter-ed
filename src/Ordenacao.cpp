#include "../include/Ordenacao.hpp"
#include <iostream>

DadosAlg::DadosAlg() : cmp(0), mov(0), calls(0) {}



double DadosAlg::setCusto(double a, double b, double c)
{
    this->custo = a * cmp + b * mov + c * calls;
    return this->custo;
}
void DadosAlg::inccmp(int n)
{
    cmp += n;
}

void DadosAlg::incmov(int n)
{
    mov += n;
}

void DadosAlg::inccalls(int n)
{
    calls += n;
}

void DadosAlg::swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    incmov(3);
}

void DadosAlg::reset()
{
    cmp = 0;
    mov = 0;
    calls = 0;
    custo = 0;
}

void DadosAlg::print()
{
    std::cout << "Comparações: " << cmp << ", Movimentações: " << mov << ", Chamadas: " << calls << std::endl;
}

// Implementação das funções de ordenação
void insertionSort(int v[], int l, int r, DadosAlg *d)
{
    d->inccalls(1);
    int i, j, key;
    for (i = l + 1; i <= r; i++)
    {
        d->inccmp(1);
        key = v[i];
        d->incmov(1);
        j = i - 1;
        while (j >= 0 && v[j] > key)
        {
            d->inccmp(1);
            d->incmov(1);
            v[j + 1] = v[j];
            j--;
        }
        d->incmov(1);
        v[j + 1] = key;
    }
}

int median(int a, int b, int c)
{
    if ((a <= b) && (b <= c))
        return b;
    if ((a <= c) && (c <= b))
        return c;
    if ((b <= a) && (a <= c))
        return a;
    if ((b <= c) && (c <= a))
        return c;
    if ((c <= a) && (a <= b))
        return a;
    return b;
}

void partition3(int *A, int l, int r, int *i, int *j, DadosAlg *d)
{
    int x;
    int m = (l + r) / 2;
    *i = l;
    *j = r;
    x = median(A[l], A[m], A[r]);
    d->inccalls(1);

    do
    {
        while (A[*i] < x)
        {
            (*i)++;
            d->inccmp(1);
        }
        d->inccmp(1);
        while (A[*j] > x)
        {
            (*j)--;
            d->inccmp(1);
        }
        d->inccmp(1);
        if (*i <= *j)
        {
            d->swap(&A[*i], &A[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void quickSort3(int *A, int l, int r, int minTamParticao, DadosAlg *d)
{
    
        if (r - l + 1 <= minTamParticao) {
        insertionSort(A, l, r, d);
        return;
    }
    d->inccalls(1);
    if (l < r)
    {
        int i, j;
        partition3(A, l, r, &i, &j, d);
        if (l < j)
            quickSort3(A, l, j, minTamParticao, d);
        if (i < r)
            quickSort3(A, i, r, minTamParticao, d);
    }
}
