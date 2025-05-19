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

    if (count != tam) {
        cerr << "Aviso: Foram lidos " << count << " números, mas eram esperados " << tam << endl;
    }

    // Definir os limiares com base nos testes de custo
    int minTamParticao = determinaLimiarParticao(vetor, tam, limiarCusto, a, b, c);
    int limiarQuebras = determinaLimiarQuebras(vetor, tam, limiarCusto, a, b, c);
    
    // Executar Ordenador Universal com os limiares encontrados
    DadosAlg d;
    OrdenadorUniversal ou;
    //ou.ordenadorUniversal(vetor, tam, minTamParticao, limiarQuebras, d);

    // Saída dos dados
    cout << ">>> Parâmetros lidos do arquivo:" << endl;
    cout << "Seed: " << seed << endl;
    cout << "Limiar de Custo: " << limiarCusto << endl;
    cout << "Coeficientes: a=" << a << ", b=" << b << ", c=" << c << endl;
    cout << "Tamanho do vetor: " << tam << endl << endl;

    cout << ">>> Resultados:" << endl;
    cout << "Limiar ótimo de Partição: " << minTamParticao << endl;
    cout << "Limiar ótimo de Quebras: " << limiarQuebras << endl;
    cout << "Número de quebras no vetor original: " << calcularQuebras(vetor, tam) << endl;

    d.print();
    cout << "Custo total: " << d.custo(a, b, c) << endl;

    for(int i = 0; i < 50; i++){
        cout << "# " << vetor[i];
    }

    delete[] vetor;
    return 0;
}
