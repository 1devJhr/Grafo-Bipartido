# Verificador de Grafo Bipartido

Trabalho de **Teoria dos Grafos**: programa em C/C++ que lê um grafo (ou dígrafo) a partir de uma matriz de adjacência em arquivo `.txt` e informa se ele é **bipartido**. Se for, exibe os dois grupos de vértices.

## O que é um grafo bipartido?

Um grafo é bipartido quando seus vértices podem ser divididos em dois conjuntos disjuntos, de modo que toda aresta liga um vértice de um conjunto a um vértice do outro. Em outras palavras: é possível colorir o grafo com **2 cores** sem que dois vértices vizinhos tenham a mesma cor. Isso equivale a dizer que o grafo **não possui ciclos de comprimento ímpar** (nem laços).

## Como funciona

A função principal é `executafuncao()`, apoiada por `pinta_vertices()` e `mostrar_gp()`.

1. Todos os vértices começam sem grupo (`-1`).
2. Para cada vértice ainda não visitado, é iniciada uma **busca em profundidade (DFS)** em `pinta_vertices(v, gp)`, começando pelo grupo `0`. Isso garante que grafos **desconexos** também sejam tratados.
3. Na DFS, cada vizinho sem grupo recebe o grupo **oposto** (`1 - gp`).
4. Se um vizinho já tem o **mesmo grupo** do vértice atual (inclusive um laço), há conflito e o grafo **não é bipartido**.
5. Sem conflitos, os grupos são impressos.

**Dígrafos:** o sentido das arestas é ignorado. Existe ligação entre `v` e `w` se `matriz_adj[v][w] != 0` **ou** `matriz_adj[w][v] != 0`. Valores diferentes de zero (rótulos, pesos, inclusive negativos) contam como aresta.

## Complexidade

| Etapa | Custo |
|---|---|
| Leitura do arquivo (contar linhas) | O(n) |
| Leitura da matriz | O(n²) |
| Verificação de dígrafo | O(n²) |
| Contagem de arestas (M) | O(n²) |
| DFS sobre a matriz (cada vértice visitado uma vez, percorrendo sua linha) | O(n²) |

**Total: O(n²)**

## Formato do arquivo de entrada

Arquivo `.txt` com a matriz de adjacência `n x n`, valores separados por espaço, uma linha por vértice. Exemplo (`grafo-estrela-nb.txt`):

```
0 0 0 1 1
0 0 1 0 1
0 1 0 1 0
1 0 1 0 0
1 1 0 0 0
```

Limite: no máximo **100 vértices** (`MAX 101`, índices a partir de 1).

## Como compilar e executar

O código usa `system("cls")`, `gets` e `fflush(stdin)`, portanto foi feito para **Windows**.

```bash
g++ Grafo_bipartido.cpp -o Grafo_bipartido
./Grafo_bipartido
```

Ao executar, digite o nome do arquivo **sem** o `.txt` (ex.: `trivial`). O programa mostra a matriz, `N` (vértices), `M` (arestas) e o resultado. Digite `0` para sair.

## Arquivos de teste

| Arquivo | Tipo | Resultado esperado |
|---|---|---|
| `trivial.txt` | Grafo trivial (1 vértice) | Bipartido (Grupo 1: V1, Grupo 2: vazio) |
| `digrafo-bipartido.txt` | Dígrafo | Bipartido (Grupo 1: V1 V3 V5, Grupo 2: V2 V4) |
| `grafo-estrela-nb.txt` | Grafo com ciclo ímpar (comprimento 5) | Não bipartido |
| `digrafo-nao-bipartido.txt` | Dígrafo com ciclo 1→2→3→1 | Não bipartido |
| `rotulado.txt` | Grafo com triângulo (V3, V4, V5) e laços | Não bipartido |
| `valorado.txt` | Dígrafo valorado com triângulo e laço | Não bipartido |

## Exemplo de saída

```
N = 5 e M = 4

SIM, o grafo e bipartido.
Grupo 1: V1 V3 V5
Grupo 2: V2 V4
```

## Estrutura do repositório

```
├── Grafo_bipartido.cpp   # código-fonte
├── Grafo_bipartido.exe   # executável (Windows)
└── *.txt                 # arquivos de teste
```
