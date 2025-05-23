#include "../include/Util.hpp"
#include <cstdlib>

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

static void shuffleVector(int *vet, int size, int numShuffle, int seed) {
    srand48(seed);
    int p1 = 0, p2 = 0, temp;
    for (int t = 0; t < numShuffle; t++) {
        while (p1 == p2) {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }
        temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;
        p1 = p2 = 0;
    }
}