#include "../include/OrdenadorUniversal.h"
#include "../include/Ordenacao.h"
#include "../include/Util.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#define MAX_CUSTOS 100
// Função auxiliar para embaralhar o vetor introduzindo quebras
void shuffleVector(int *vet, int size, int numShuffle)
{

    int p1 = 0, p2 = 0, temp;

    for (int t = 0; t < numShuffle; t++)
    {

        // Garante que p1 e p2 sejam diferentes
        while (p1 == p2)
        {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }

        // Troca os valores
        temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;

        // Reseta os índices
        p1 = p2 = 0;
    }
}

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
   

    // Cálculo de newMin e newMax
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

    // Valores originais
    int originalMin = minMPS;
    int originalPasso = passoMPS;
   
    // Atualização de minMPS e maxMPS
    minMPS = getMPS(newMin, minMPS, passoMPS);
    maxMPS = getMPS(newMax, originalMin, originalPasso);
   
    // Ajuste do passo
    int oldPasso = passoMPS;
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

    float diffCusto = limiarCusto + 1; // Garante entrada no loop

    // Função local para encontrar índice do menor custo

    while ((diffCusto > limiarCusto) && (numMPS >= 5))
    {

        numMPS = 0;
        std::cout << "\niter " << iter << std::endl;
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

        std::cout << "nummps " << numMPS << " limParticao " << menorCustoAlt(mpses, tam) << " mpsdiff " << diffCusto << std::endl; //ababa
    }

    // Retorna o tamanho ótimo de partição
    return minMPS + limParticao * passoMPS; /*  */
}




int idMenorCustoQuebras(int numMPS, double custo[2][100] ){

  int idMenorCusto;
  double custoQs, custoIn, custoAbs, menorCusto;

  for(int i = 0; i < numMPS; i++){
    
    custoQs = custo[0][i];
    custoIn = custo[1][i];
    custoAbs = std::abs(custoQs - custoIn);
    if(i == 0 || menorCusto > custoAbs){
      menorCusto = custoAbs; 
      idMenorCusto = i;
    }
  }

  return idMenorCusto;
}
class EstatisticasAlg
{
private:
    int ql;
    double cost, cmp, mov, calls;
public:
    EstatisticasAlg(/* args */);
    EstatisticasAlg(int ql, double cost, double cmp, double mov, double calls);
    ~EstatisticasAlg();
};

EstatisticasAlg::EstatisticasAlg()
{
    ql = 0;
    cost = cmp = mov = calls = 0.0;
}
EstatisticasAlg::EstatisticasAlg(int ql, double cost, double cmp, double mov, double calls)
{
    this->ql = ql;
    this->cost = cost;
    this->cmp = cmp;
    this->mov = mov;
    this->calls = calls;
}

EstatisticasAlg::~EstatisticasAlg()
{
}

int determinaLimiarQuebras(int V[], int tam, double limiarCusto, double a, double b, double c, int seed, int optimalMinTamParticao) {
    std::cout << std::fixed;
    int minQ = 1;
    int maxQ = tam / 2;
    int numQ = 5;
    int passoQ = (maxQ - minQ) / 5;
    int iter = 0;

    double custos[2][MAX_CUSTOS]; // [0] -> quick, [1] -> insertion
    int lqs[MAX_CUSTOS];
    int limQuebras = 0;
    DadosAlg d;
    OrdenadorUniversal U;
    double quebs[tam];
    for (int i = 0; i < tam; i++)
    {
        quebs[i] = 0;
    }

    float diffCusto = limiarCusto + 1;

    while ((diffCusto > limiarCusto) && (numQ >= 5))
    {   
        
        std::cout << "\niter " << iter << std::endl;
        numQ = 0;

        for (int i = 0; i < MAX_CUSTOS; i++)
        {
            custos[0][i] = custos[1][i] = 0.0;
        }

        for (int t = minQ; t <= maxQ && numQ < MAX_CUSTOS; t += passoQ)
        {

            int V_ordenado[tam];
            int V_ordenado2[tam];

            for (int i = 0; i < tam; i++)
            {

                V_ordenado[i] = V[i];
                V_ordenado2[i] = V[i];
            }
            DadosAlg temp = DadosAlg(); // criado para ordenar o vetor antes do shuffle
            U.fakeOrdenadorUniversal(V_ordenado, tam, t, 0, &temp, 0);//ignora
            
            d.reset();
            srand48(seed);
            shuffleVector(V_ordenado, tam, t);
            U.fakeOrdenadorUniversal(V_ordenado, tam, optimalMinTamParticao, 0, &d, 0);
            
            custos[0][numQ] = d.setCusto(a, b, c);
            
            lqs[numQ] = t;
            std::cout << "qs lq " << t << " cost " << std::setprecision(9) << custos[0][numQ]
                      << " cmp " << d.cmp << " move " << d.mov << " calls " << d.calls << std::endl;

            temp.reset();
            U.fakeOrdenadorUniversal(V_ordenado2, tam, t, 0, &temp, 0);//ignora

            d.reset();
            srand48(seed);
            shuffleVector(V_ordenado2, tam, t);
            U.fakeOrdenadorUniversal(V_ordenado2, tam, t, 0, &d, 1);//provavalmente aqui 

            custos[1][numQ] = d.setCusto(a, b, c);
            quebs[t] = custos[0][numQ];
            std::cout << "in lq " << t << " cost " << std::setprecision(9) << custos[1][numQ]
                      << " cmp " << d.cmp << " move " << d.mov << " calls " << d.calls << std::endl;

            numQ++;
        }

        menorCustoAlt(quebs, tam);
        maiorCustoAlt(quebs, tam);

        limQuebras = menorCustoAlt(quebs, numQ);

        calculaNovaFaixa(limQuebras, numQ, minQ, maxQ, passoQ);
        
        diffCusto = std::abs(custos[1][newMax] - custos[1][newMin]);

        const double EPSILON = 1e-9;
        if (diffCusto < EPSILON)
        {
            diffCusto = 0.0;
        }

        std::cout << std::endl;
        int idxMenor = idMenorCustoQuebras(numQ, custos);
    
        std::cout << std::setprecision(6);
        std::cout << "numlq " << numQ << " limQuebras " << lqs[idxMenor]// ababa
                  << " lqdiff " << diffCusto << std::endl;

        iter++;
    }

    int resultado = minQ + limQuebras * passoQ;
    return resultado;
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

void OrdenadorUniversal::fakeOrdenadorUniversal(int V[], int tam, int minTamParticao, int limiarQuebras, DadosAlg *d, int alg)
{

    if (alg != 0)
    {
        insertionSort(V, 0, tam - 1, d);
    }
    if (alg == 0)
    {
        quickSort3(V, 0, tam - 1, minTamParticao, d);
    }
}