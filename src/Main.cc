#include <iostream>
#include <cstdlib>
#include <fstream>
#include "../include/OrdenadorUniversal.h"
using namespace std;

int main(int argc, char *argv[]) {
    // Verifica se o arquivo foi passado como argumento
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <arquivo.txt>" << endl;
        return 1;
    }

    // Abre o arquivo
    ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    // Variáveis para os parâmetros iniciais
    int seed;
    double limiarCusto, a, b, c;
    int tam;

    // Lendo os 6 primeiros parâmetros
    arquivo >> seed >> limiarCusto >> a >> b >> c >> tam;

    // Verifica se o tamanho declarado é válido

    // Alocando memória para os números
    int* vetor = new int[tam];
    int count = 0;
    
    // Lendo os números restantes
    while (count < tam && arquivo >> vetor[count]) {
        count++;
    }

    // Fecha o arquivo
    arquivo.close();

    // Verifica se leu todos os números esperados
    if (count != tam) {
        cerr << "Aviso: Foram lidos " << count << " números, mas eram esperados " << tam << endl;
    }

    /////////////////////////////////////////////////
    // A partir daqui, implemente a lógica do TP:   //
    // 1. Determinação dos limiares                //
    // 2. Implementação dos algoritmos de ordenação//
    // 3. Lógica do Ordenador Universal            //
    /////////////////////////////////////////////////

    // Exemplo de uso dos parâmetros (apenas para teste)
    cout << "Seed: " << seed << endl;
    cout << "Limiar de Custo: " << limiarCusto << endl;
    cout << "Coeficientes: a=" << a << " b=" << b << " c=" << c << endl;
    cout << "Tamanho do vetor: " << tam << endl;
    cout << "Primeiros 5 números: ";
    for (int i = 0; i < 5 && i < count; i++) {
        cout << vetor[i] << " ";
    }
    cout << endl;
    DadosAlg d = DadosAlg();
    insertionSort(vetor, 0, count - 1, &d);
    d.print();
    cout << "Vetor ordenado: ";     
    for (int i = 0; i < count; i++) {
        cout << vetor[i] << " ";
    }

    // Libera a memória alocada
    delete[] vetor;

    return 0;
}