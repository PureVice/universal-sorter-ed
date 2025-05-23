#ifndef UTIL_H
#define UTIL_H


class Util 
{
    public:
        int calcularQuebras(int V[], int tam);
        double absDouble(double x);
        static void shuffleVector(int *vet, int size, int numShuffle, int seed);
};

#endif