#include "../include/OrdenadorUniversal.h"
#include "../include/Ordenacao.h"
#include "../include/Util.h"
#include <iostream>

int menorCustoAlt(double custos[], int tamanho)
{
    int idxMin = 0;
    double minCusto = 100000000.0;

    for (int i = 1; i < tamanho; i++)
    {
        if (custos[i] < minCusto && custos[i] != 0)
        {
            minCusto = custos[i];
            idxMin = i;
        }
    }
    
    return idxMin;
}
int maiorCustoAlt(double custos[], int tamanho)
{
    // Verificação de segurança
    if (tamanho <= 0)
        return -1;

    int idxMax = 0;
    double maxCusto = custos[0]; // Inicializa com o primeiro elemento

    for (int i = 1; i < tamanho; i++)
    {
        if (custos[i] > maxCusto)
        { // Comparação invertida para maior valor
            maxCusto = custos[i];
            idxMax = i;
        }
    }

    std::cout << "idxMax: " << idxMax << std::endl;
    return idxMax;
}

// Retorna o índice do menor custo no vetor
int menorCusto(double custos[], int tamanho)
{
    int idxMin = 0;
    double minCusto = custos[0];

    for (int i = 1; i < tamanho; i++)
    {
        if (custos[i] < minCusto)
        {
            minCusto = custos[i];
            idxMin = i;
        }
    }

    return idxMin;
}

int getMPS(int index, int minMPS, int passoMPS)
{
    return minMPS + index * passoMPS;
}

// Calcula nova faixa de busca em torno da melhor partição encontrada
void calculaNovaFaixa(int limParticao, int numMPS, int &minMPS, int &maxMPS, int &passoMPS)
{
    int newMin, newMax;

    if (limParticao == 0)
    {
        newMin = 0;
        newMax = 2;
    }
    else if (limParticao == numMPS - 1)
    {
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    }
    else
    {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }

    // Converte índices para tamanhos reais de partição
    minMPS = getMPS(newMin, minMPS, passoMPS);

    maxMPS = getMPS(newMax, minMPS, passoMPS);
    std::cout << "minMPS " << minMPS << std::endl;
    std::cout << "maxMPS " << maxMPS << std::endl;

    // Garante que minMPS não seja menor que 2
    if (minMPS < 2)
        minMPS = 2;

    passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0)
        passoMPS = 1;
}

struct estatisticas
{
};

// Função principal para determinar o melhor minTamParticao
int determinaLimiarParticao(int *V, int tam, double limiarCusto, double a, double b, double c)
{
    std::cout << "entrou no determinaLimiar" << std::endl;
    int minMPS = 2;
    int maxMPS = tam;
    int numMPS = 5;
    int passoMPS = (maxMPS - minMPS) / 5;
    int iter = 0;
#define MAX_CUSTOS 100
    double custo[MAX_CUSTOS];
    int limParticao = 0;
    DadosAlg d;
    OrdenadorUniversal U;
    double mpses[tam];
    for (int i = 0; i < tam; i++)
    {
        mpses[i] = 0;
    }

    double diffCusto = limiarCusto + 1; // Garante entrada no loop

    // Função local para encontrar índice do menor custo

    while ((diffCusto > limiarCusto) && (numMPS >= 5))
    {

        numMPS = 0;
        std::cout << "iter " << iter << std::endl;
        for (int t = minMPS; t <= maxMPS && numMPS < MAX_CUSTOS; t += passoMPS)
        {
            int V_copia[tam];

            for (int i = 0; i < tam; i++)
            {
                V_copia[i] = V[i]; // copia o vetor original para os testes mps
            }
            d.reset();
            U.ordenadorUniversal(V_copia, tam, t, 0, &d);

            // Armazena
            custo[numMPS] = d.setCusto(a, b, c);
            mpses[t] = custo[numMPS];
            std::cout << "mps " << t << " cost " << custo[numMPS] << " cmp " << d.cmp << " move " << d.mov << " calls " << d.calls << std::endl;
            numMPS++;
        }
        menorCustoAlt(mpses, tam);
        maiorCustoAlt(mpses, tam);
        limParticao = menorCusto(custo, numMPS);
        calculaNovaFaixa(limParticao, numMPS, minMPS, maxMPS, passoMPS);
        
        // Calcula diferença entre custos extremos
        double custoMin = custo[0];
        double custoMax = custo[0];
        for (int i = 1; i < numMPS; i++)
        {
            if (custo[i] < custoMin)
                custoMin = custo[i];
            if (custo[i] > custoMax)
                custoMax = custo[i];
        }
        diffCusto = (custoMax - custoMin) > 0 ? custoMax - custoMin : custoMin - custoMax;
        iter++;
        std::cout << "nummps " << numMPS << " limParticao " << menorCustoAlt(mpses, tam) << " mpsdiff " << diffCusto << std::endl;
    }

    // Retorna o tamanho ótimo de partição
    return minMPS + limParticao * passoMPS; /*  */
}

int determinaLimiarQuebras(int V[], int tam, double limiarCusto, double a, double b, double c)
{
    int minQ = 0;
    int maxQ = tam - 1;
    int passoQ = (maxQ - minQ) / 5;

    if (passoQ == 0)
    {
        passoQ = 1;
    }

    double diffCusto = 1000000000.0; // Valor inicial grande
    int limQuebras = minQ;

    const int MAX_LIMIARES = 100;
    int limiares[MAX_LIMIARES];
    double custos[MAX_LIMIARES];

    while (diffCusto > limiarCusto)
    {
        int numLimiar = 0;

        for (int q = minQ; q <= maxQ && numLimiar < MAX_LIMIARES; q += passoQ)
        {
            limiares[numLimiar] = q;

            // Cópia manual do vetor original
            int *Vtemp = new int[tam];
            for (int i = 0; i < tam; i++)
            {
                Vtemp[i] = V[i];
            }

            DadosAlg d;
            OrdenadorUniversal ou;
            ou.ordenadorUniversal(Vtemp, tam, tam, q, &d); // minTamParticao = tam, força Quicksort

            custos[numLimiar] = d.setCusto(a, b, c);

            delete[] Vtemp;
            numLimiar++;
        }

        if (numLimiar < 5)
        {
            break;
        }

        limQuebras = menorCusto(custos, numLimiar);
        diffCusto = custos[0] - custos[numLimiar - 1];
        if (diffCusto < 0)
        {
            diffCusto = -diffCusto;
        }

        int newMinIdx = 0;
        int newMaxIdx = 0;

        if (limQuebras == 0)
        {
            newMinIdx = 0;
            newMaxIdx = (numLimiar >= 3) ? 2 : numLimiar - 1;
        }
        else if (limQuebras == numLimiar - 1)
        {
            newMinIdx = (numLimiar >= 3) ? numLimiar - 3 : 0;
            newMaxIdx = numLimiar - 1;
        }
        else
        {
            newMinIdx = limQuebras - 1;
            newMaxIdx = limQuebras + 1;
        }

        minQ = limiares[newMinIdx];
        maxQ = limiares[newMaxIdx];
        passoQ = (maxQ - minQ) / 5;
        if (passoQ == 0)
        {
            passoQ = 1;
        }
    }

    return limiares[limQuebras];
}

// Implementação do método da classe OrdenadorUniversal
void OrdenadorUniversal::ordenadorUniversal(int V[], int tam, int minTamParticao, int limiarQuebras, DadosAlg *d)
{
    // std::cout << "tamanho: " << tam << std::endl;
    int quebras = calcularQuebras(V, tam);
    // std::cout << "quebras: " << quebras << std::endl;
    if (quebras < limiarQuebras)
    {
        insertionSort(V, 0, tam - 1, d);
    }
    else
    {
        if (tam > minTamParticao)
        {
            quickSort3(V, 0, tam - 1, minTamParticao, d);
        }
        else
        {
            insertionSort(V, 0, tam - 1, d);
        }
    }
}
