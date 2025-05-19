#include "../include/OrdenadorUniversal.h"
#include <iostream>

// Implementação dos métodos da classe DadosAlg
DadosAlg::DadosAlg() : cmp(0), mov(0), calls(0) {}

double DadosAlg::custo(double a, double b, double c)
{
    double custo = 0;
    custo = a * cmp + b * mov + c * calls;
    return custo;
}
void DadosAlg::inccmp(int n)
{
    cmp += n;
}

void DadosAlg::incmov(int n)
{
    mov += n;
}

void DadosAlg::inccalls(int n)
{
    calls += n;
}

void DadosAlg::swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    incmov(3);
}

void DadosAlg::reset()
{
    cmp = 0;
    mov = 0;
    calls = 0;
}

void DadosAlg::print()
{
    std::cout << "Comparações: " << cmp << ", Movimentações: " << mov << ", Chamadas: " << calls << std::endl;
}

// Implementação das funções de ordenação
void insertionSort(int v[], int l, int r, DadosAlg *d)
{
    d->inccalls(1);
    int i, j, key;
    for (i = l + 1; i <= r; i++)
    {
        d->inccmp(1);
        key = v[i];
        d->incmov(1);
        j = i - 1;
        while (j >= 0 && v[j] > key)
        {
            d->inccmp(1);
            d->incmov(1);
            v[j + 1] = v[j];
            j--;
        }
        d->incmov(1);
        v[j + 1] = key;
    }
}

int median(int a, int b, int c)
{
    if ((a <= b) && (b <= c))
        return b;
    if ((a <= c) && (c <= b))
        return c;
    if ((b <= a) && (a <= c))
        return a;
    if ((b <= c) && (c <= a))
        return c;
    if ((c <= a) && (a <= b))
        return a;
    return b;
}

void partition3(int *A, int l, int r, int *i, int *j, DadosAlg *d)
{
    int x;
    int m = (l + r) / 2;
    *i = l;
    *j = r;
    x = median(A[l], A[m], A[r]);
    d->inccalls(1);

    do
    {
        while (A[*i] < x)
        {
            (*i)++;
            d->inccmp(1);
        }
        d->inccmp(1);
        while (A[*j] > x)
        {
            (*j)--;
            d->inccmp(1);
        }
        d->inccmp(1);
        if (*i <= *j)
        {
            d->swap(&A[*i], &A[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void quickSort3(int *A, int l, int r, DadosAlg *d)
{
    d->inccalls(1);
    if (l < r)
    {
        int i, j;
        partition3(A, l, r, &i, &j, d);
        if (l < j)
            quickSort3(A, l, j, d);
        if (i < r)
            quickSort3(A, i, r, d);
    }
}

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

// Calcula nova faixa de busca em torno da melhor partição encontrada
void calculaNovaFaixa(int limParticao, int numMPS, int particoes[], int &minMPS, int &maxMPS, int &passoMPS)
{
    int newMinIdx = 0;
    int newMaxIdx = 0;

    // Se o melhor valor está no início da lista
    if (limParticao == 0)
    {
        newMinIdx = 0;
        if (numMPS >= 3)
        {
            newMaxIdx = 2;
        }
        else
        {
            newMaxIdx = numMPS - 1;
        }
    }
    // Se o melhor valor está no fim da lista
    else if (limParticao == numMPS - 1)
    {
        if (numMPS >= 3)
        {
            newMinIdx = numMPS - 3;
        }
        else
        {
            newMinIdx = 0;
        }
        newMaxIdx = numMPS - 1;
    }
    // Se o melhor valor está no meio da lista
    else
    {
        newMinIdx = limParticao - 1;
        newMaxIdx = limParticao + 1;
    }

    minMPS = particoes[newMinIdx];
    maxMPS = particoes[newMaxIdx];
    passoMPS = (maxMPS - minMPS) / 5;

    if (passoMPS == 0)
    {
        passoMPS = 1;
    }
}



// Função principal para determinar o melhor minTamParticao
int determinaLimiarParticao(int V[], int tam, double limiarCusto, double a, double b, double c)
{
    int minMPS = 2;
    int maxMPS = tam;
    int limParticao = minMPS;

    const int MAX_PARTICOES = 100;
    int particoes[MAX_PARTICOES];
    double custos[MAX_PARTICOES];

    int iter = 0;

    while (true)
    {
        int passo = (maxMPS - minMPS) / 5;
        if (passo == 0)
            passo = 1;

        int numMPS = 0;
        DadosAlg * listadados;
        printf("iter %d\n", iter);

        for (int mps = minMPS; mps <= maxMPS && numMPS < MAX_PARTICOES; mps += passo)
        {
            particoes[numMPS] = mps;

            // Copia o vetor original
            int *Vtemp = new int[tam];
            for (int i = 0; i < tam; i++)
            {
                Vtemp[i] = V[i];
            }

            // Executa a ordenação
            DadosAlg d;
            OrdenadorUniversal ou;
            ou.ordenadorUniversal(Vtemp, tam, mps, tam, &d);

           
            
            std::cout << "mps " << mps << d.custo(a,b,c) << " cmp "<<d.cmp << " move "<< d.mov << std::endl;
            //mps 2 cost 118.433083300 cmp 11772 move 7904 calls 1489

            delete[] Vtemp;
            numMPS++;
        }

        // Verifica condições de parada
        double menor = custos[0];
        double maior = custos[0];
        int melhorIndice = 0;

        for (int i = 1; i < numMPS; i++)
        {
            if (custos[i] < menor)
            {
                menor = custos[i];
                melhorIndice = i;
            }
            if (custos[i] > maior)
            {
                maior = custos[i];
            }
        }

        limParticao = particoes[melhorIndice];
        double diffCusto = maior - menor;

        printf("nummps %d limParticao %d mpsdiff %.6f\n", numMPS, limParticao, diffCusto);
        //nummps 6 limParticao 2 mpsdiff 307.698059
        if (diffCusto < limiarCusto || numMPS < 5)
        {
            break;
        }

        // Atualiza faixa para próxima iteração
        int novoMin = particoes[std::max(0, melhorIndice - 1)];
        int novoMax = particoes[std::min(numMPS - 1, melhorIndice + 1)];
        minMPS = novoMin;
        maxMPS = novoMax;

        iter++;
    }

    return limParticao;
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

            custos[numLimiar] = d.custo(a, b, c);

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
    int quebras = calcularQuebras(V, tam);

    if (quebras < limiarQuebras)
    {
        insertionSort(V, 0, tam - 1, d);
    }
    else
    {
        if (tam > minTamParticao)
        {
            quickSort3(V, 0, tam - 1, d);
        }
        else
        {
            insertionSort(V, 0, tam - 1, d);
        }
    }
}
