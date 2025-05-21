#include "../include/OrdenadorUniversal.h"
#include "../include/Ordenacao.h"
#include "../include/Util.h"
#include <iostream>
#include <iomanip>
#define MAX_CUSTOS 100
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
    return minMPS + (index * passoMPS);
}
int newMin, newMax;
// Calcula nova faixa de busca em torno da melhor partição encontrada
void calculaNovaFaixa(int limParticao, int numMPS, int &minMPS, int &maxMPS, int &passoMPS)
{

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

    // Store original values before modification
    int originalMin = minMPS;
    int originalPasso = passoMPS;

    minMPS = getMPS(newMin, minMPS, passoMPS);
    maxMPS = getMPS(newMax, originalMin, originalPasso); // Use original values

    // Calculate new passoMPS
    //int oldPasso = passoMPS;
    passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0)
    {
        passoMPS = 1;
    }
}

// Função principal para determinar o melhor minTamParticao
int determinaLimiarParticao(int *V, int tam, double limiarCusto, double a, double b, double c)
{
    std::cout << std::fixed;
    int minMPS = 2;
    int maxMPS = tam;
    int numMPS = 5;
    int passoMPS = (maxMPS - minMPS) / 5;
    int iter = 0;

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
        std::fill(custo, custo + MAX_CUSTOS, 0.0);

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
            std::cout << "mps " << t << " cost " << std::setprecision(9) << custo[numMPS] << " cmp " << d.cmp << " move " << d.mov << " calls " << d.calls << std::endl;
            numMPS++;
        }

        menorCustoAlt(mpses, tam);
        maiorCustoAlt(mpses, tam);
        limParticao = menorCusto(custo, numMPS);
        calculaNovaFaixa(limParticao, numMPS, minMPS, maxMPS, passoMPS);

        // Calcula diferença entre custos extremos

        
        diffCusto = std::abs(custo[newMax] - custo[newMin]);

        // Corrige flutuações numéricas muito pequenas
        const double EPSILON = 1e-9;
        if (diffCusto < EPSILON)
        {
            diffCusto = 0.0;
        }

        iter++;
        
        std::cout << std::setprecision(6);
        
        std::cout << "nummps " << numMPS << " limParticao " << menorCustoAlt(mpses, tam) << " mpsdiff " << diffCusto << std::endl;
    }

    // Retorna o tamanho ótimo de partição
    return minMPS + limParticao * passoMPS; /*  */
}
/* 
são 6 faixas, igual lim particao
lq = t do lim particao
calculamos a faixa do mesmo jeito 
vamos tentar imprimir, depois fazer o resto



*/
int determinaLimiarQuebras(int V[], int tam, double limiarCusto, double a, double b, double c)
{
    std::cout << std::fixed;
    int minQ = 1;
    int maxQ = calcularQuebras(V, tam);
    int numQ = 5;
    int passoQ = (maxQ - minQ) / 5;
    int iter = 0;

    double custo[MAX_CUSTOS];
    int limQuebras = 0;
    DadosAlg d;
    OrdenadorUniversal U;
    double quebs[tam];
    for (int i = 0; i < tam; i++)
    {
        quebs[i] = 0;
    }

    double diffCusto = limiarCusto + 1; // Garante entrada no loop

    while ((diffCusto > limiarCusto) && (numQ >= 5))
    {

        numQ = 0;
        std::cout << "iter " << iter << std::endl;
        std::fill(custo, custo + MAX_CUSTOS, 0.0);

        for (int t = minQ; t <= maxQ && numQ < MAX_CUSTOS; t += passoQ)
        {
            int V_copia[tam];

            for (int i = 0; i < tam; i++)
            {
                V_copia[i] = V[i]; // copia o vetor original para os testes 
            }
            d.reset();

            //daqui fica diferente, temos que fazer o tal shufflevector usando a copia, o tmanho e o numero de quebras (t) como parametro
            U.ordenadorUniversal(V_copia, tam, t, 0, &d);

            // Armazena
            custo[numQ] = d.setCusto(a, b, c);
            quebs[t] = custo[numQ];
            std::cout << "lq " << t << " cost " << std::setprecision(9) << custo[numQ] << " cmp " << d.cmp << " move " << d.mov << " calls " << d.calls << std::endl;
            numQ++;
        }

        menorCustoAlt(quebs, tam);
        maiorCustoAlt(quebs, tam);
        limQuebras = menorCusto(custo, numQ);
        calculaNovaFaixa(limQuebras, numQ, minQ, maxQ, passoQ);

        // Calcula diferença entre custos extremos

        
        diffCusto = std::abs(custo[newMax] - custo[newMin]);

        // Corrige flutuações numéricas muito pequenas
        const double EPSILON = 1e-9;
        if (diffCusto < EPSILON)
        {
            diffCusto = 0.0;
        }

        iter++;
        
        std::cout << std::setprecision(6);
        
        std::cout << "numlq " << numQ << " limQuebras " << menorCustoAlt(quebs, tam) << " mpsdiff " << diffCusto << std::endl;
    }

    // Retorna o tamanho ótimo de partição
    return minQ + limQuebras * passoQ; /*  */
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
