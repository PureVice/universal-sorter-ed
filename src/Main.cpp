#include <iostream>
#include <cstdlib>
#include <fstream>
#include "../include/OrdenadorUniversal.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (freopen(argv[1], "r", stdin) == nullptr)
    {
        cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    // Parâmetros de entrada
    int seed;
    double limiarCusto, a, b, c;
    int tam;

    cin >> seed >> limiarCusto >> a >> b >> c >> tam;

    if (tam <= 0)
    {
        cerr << "Tamanho do vetor inválido!" << endl;
        return 1;
    }

    // Alocar e ler vetor
    int *vetor = new int[tam];
    for (int i = 0; i < tam; i++)
    {
        cin >> vetor[i];
    }
    cout << "size " << tam
         << " seed " << seed
         << " breaks " << calcularQuebras(vetor, tam)
         << endl;

    // Definir os limiares com base nos testes de custo
    int minTamParticao = determinaLimiarParticao(vetor, tam, limiarCusto, a, b, c);
    determinaLimiarQuebras(vetor, tam, limiarCusto, a, b, c, seed, minTamParticao + 1);

    delete[] vetor;
    return 0;
}
