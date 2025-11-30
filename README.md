# 📊 Universal Sorter (Ordenador Universal)

Este projeto implementa um **Ordenador Universal** em C++, desenvolvido no âmbito da disciplina de Estruturas de Dados. O objetivo do sistema é encontrar, de forma adaptativa, a melhor estratégia de ordenação para um determinado vetor de inteiros, baseando-se em parâmetros de custo e nas características dos dados (como o nível de desordem).

## 📂 Estrutura do Projeto

A organização das diretorias segue o padrão definido no `Makefile`:

```text
universal-sorter-ed/
│
├── bin/              # Executáveis gerados (ex: tp1.out)
├── include/          # Ficheiros de cabeçalho (.hpp)
│   ├── Ordenacao.hpp
│   ├── OrdenadorUniversal.hpp
│   └── Util.hpp
├── obj/              # Ficheiros objeto (.o) gerados durante a compilação
├── src/              # Código fonte (.cpp)
│   ├── Main.cpp                # Ponto de entrada e leitura de parâmetros
│   ├── Ordenacao.cpp           # Implementação do QuickSort e InsertionSort
│   └── OrdenadorUniversal.cpp  # Lógica de otimização e escolha de limiares
├── Makefile          # Script de automação de compilação
└── arquivo.txt       # Exemplo de ficheiro de entrada
```

## 🚀 Funcionalidades e Algoritmos

O sistema utiliza uma abordagem híbrida combinando dois algoritmos clássicos:

1. **QuickSort (Mediana de 3):** Utilizado para grandes conjuntos de dados. O pivô é escolhido pela mediana entre o primeiro, o meio e o último elemento.
2. **Insertion Sort:** Utilizado para pequenas partições ou vetores quase ordenados.

### 🧠 Lógica Adaptativa

O diferencial deste ordenador é a capacidade de "afinar" os parâmetros de ordenação com base numa função de custo personalizada:

```
Custo = a × comparações + b × movimentações + c × chamadas
```

Onde `a, b, c` são pesos fornecidos pelo utilizador. O programa calcula:

- **Limiar de Partição (`minTamParticao`):** O tamanho mínimo de um subvetor no QuickSort a partir do qual se deve alternar para o Insertion Sort para minimizar o custo.
- **Limiar de Quebras (`limiarQuebras`):** Determina se o vetor está suficientemente ordenado para usar apenas o Insertion Sort, ou se deve ser ordenado via QuickSort.

## 🛠️ Compilação e Instalação

O projeto utiliza um `Makefile` para gerir a compilação. Certifique-se de ter o `g++` instalado.

Para compilar todo o projeto e gerar o executável `bin/tp1.out`:

```bash
make all
```

Para limpar os ficheiros objeto e binários gerados:

```bash
make clean
```

## 💻 Como Utilizar

### Formato de Entrada

O programa espera receber os dados através da entrada padrão (`stdin`) ou redirecionados de um ficheiro. O formato esperado em `src/Main.cpp` é:

```text
<seed> <limiarCusto> <a> <b> <c> <tamanho_vetor>
<elemento_1> <elemento_2> ... <elemento_n>
```

- **seed:** Semente para geração de números aleatórios.
- **limiarCusto:** Valor de paragem para a otimização dos limiares.
- **a, b, c:** Pesos para comparações, movimentações e chamadas de função, respetivamente.
- **tamanho_vetor:** Quantidade de inteiros a ordenar.
- **elementos:** A sequência de números inteiros.

### Execução

Para executar com um ficheiro de teste (ex: `arquivo.txt`):

```bash
./bin/tp1.out arquivo.txt
```

Ou utilizando o atalho do Makefile:

```bash
make run
```

### Saída Esperada

O programa imprimirá na saída padrão informações sobre o vetor e o processo de otimização, incluindo:

- Tamanho e Semente utilizada.
- Número de "Quebras" (inversões) no vetor original.
- Iterações para encontrar o melhor tamanho de partição (`mps`).
- Custos calculados para diferentes estratégias (QuickSort vs Insertion Sort).

---

*Desenvolvido no contexto académico da Universidade Federal de Minas Gerais (UFMG).*
