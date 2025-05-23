#include <iostream>
#include <cstdlib>
#include <fstream>
#include "../include/OrdenadorUniversal.h"


using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <arquivo.txt>" << endl;
        return 1;
    }

    ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    // Parâmetros de entrada
    int seed;
    double limiarCusto, a, b, c;
    int tam;

    arquivo >> seed >> limiarCusto >> a >> b >> c >> tam;

    if (tam <= 0) {
        cerr << "Tamanho do vetor inválido!" << endl;
        return 1;
    }

    // Alocar e ler vetor
    int* vetor = new int[tam];
    int count = 0;
    while (count < tam && arquivo >> vetor[count]) {
        count++;
    }
    arquivo.close();
        cout << "size " << tam
         << " seed " << seed 
         << " breaks " << calcularQuebras(vetor, tam)
         << endl;

    // Definir os limiares com base nos testes de custo
    int minTamParticao = determinaLimiarParticao(vetor, tam, limiarCusto, a, b, c);
    determinaLimiarQuebras(vetor, tam, limiarCusto, a, b, c, seed, minTamParticao+1);



    delete[] vetor;
    return 0;
}
