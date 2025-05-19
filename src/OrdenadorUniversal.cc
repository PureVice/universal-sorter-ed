#include "../include/OrdenadorUniversal.h"
#include <iostream>

// Implementação dos métodos da classe DadosAlg
DadosAlg::DadosAlg() : cmp(0), mov(0), calls(0) {}

void DadosAlg::inccmp(int n) {
    cmp += n;
}

void DadosAlg::incmov(int n) {
    mov += n;
}

void DadosAlg::inccalls(int n) {
    calls += n;
}

void DadosAlg::swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    incmov(3);
}

void DadosAlg::reset() {
    cmp = 0;
    mov = 0;
    calls = 0;
}

void DadosAlg::print() {
    std::cout << "Comparações: " << cmp << ", Movimentações: " << mov << ", Chamadas: " << calls << std::endl;
}

// Implementação das funções de ordenação
void insertionSort(int v[], int l, int r, DadosAlg *d) {
    d->inccalls(1);
    int i, j, key;
    for (i = l + 1; i <= r; i++) {
        d->inccmp(1);
        key = v[i];
        d->incmov(1);
        j = i - 1;
        while (j >= 0 && v[j] > key) {
            d->inccmp(1);
            d->incmov(1);
            v[j + 1] = v[j];
            j--;
        }
        d->incmov(1);
        v[j + 1] = key;
    }
}

int median(int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;
    if ((a <= c) && (c <= b)) return c;
    if ((b <= a) && (a <= c)) return a;
    if ((b <= c) && (c <= a)) return c;
    if ((c <= a) && (a <= b)) return a;
    return b;
}

void partition3(int *A, int l, int r, int *i, int *j, DadosAlg d) {
    int x;
    int m = (l + r) / 2;
    *i = l;
    *j = r;
    x = median(A[l], A[m], A[r]);
    d.inccalls(1);

    do {
        while (A[*i] < x) {
            (*i)++;
            d.inccmp(1);
        }
        d.inccmp(1);
        while (A[*j] > x) {
            (*j)--;
            d.inccmp(1);
        }
        d.inccmp(1);
        if (*i <= *j) {
            d.swap(&A[*i], &A[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void quickSort3(int *A, int l, int r, DadosAlg d) {
    d.inccalls(1);
    if (l < r) {
        int i, j;
        partition3(A, l, r, &i, &j, d);
        if (l < j) quickSort3(A, l, j, d);
        if (i < r) quickSort3(A, i, r, d);
    }
}


int OrdenadorUniversal::calcularQuebras(int V[], int tam) {
    int quebras = 0;
    for (int i = 1; i < tam; i++) {
        if (V[i] < V[i-1]) quebras++;
    }
    return quebras;
}
// Implementação do método da classe OrdenadorUniversal
void OrdenadorUniversal::ordenadorUniversal(int V[], int tam, int minTamParticao, int limiarQuebras, DadosAlg& d) {
    int quebras = calcularQuebras(V, tam);
    if (quebras < limiarQuebras) {
        insertionSort(V, 0, tam-1, &d);
    } else {
        if (tam > minTamParticao) {
            quickSort3(V, 0, tam-1, d);
        } else {
            insertionSort(V, 0, tam-1, &d);
        }
    }
}



//void OrdenadorUniversal :: ordenadorUniversal( int V[], int tam, int minTamParticao, int limiarQuebras) {
//	if (numeroQuebras < limiarQuebras) {
//		insertionSort(V, tam);
//	} else {
//		if (tam > minTamParticao) {
//			quickSort3(V, tam);
//		} else {
//			insertionSort(V, tam);
//		}
//	}
//}