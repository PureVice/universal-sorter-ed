#include "../include/Util.h"


int calcularQuebras(int V[], int tam)
{
    int quebras = 0;
    for (int i = 1; i < tam; i++)
    {
        if (V[i] < V[i - 1])
            quebras++;
    }
    return quebras;
}

double absDouble(double x)
{
    return (x < 0) ? -x : x;
}