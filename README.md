# Algoritmos-de-Grafos
Autores:     João da Silva Muniz Neto 
             Mateus Monteiro Santos
             Engenharia de Computação - UFAL
             Copyright (c) 2021   

Trabalho referente a disciplina de Teoria dos Grafos, do Instituto de Computação (IC) da Universidade Federal de Alagoas (UFAL) ministrada pelo professor Rian Gabriel Pinheiro. Trabalho com o objetivo de implementar os conhecimentos vistos em sala sobre grafos, valendo a nota da AB2. A implementação consiste em aprensentar 4 códigos, são eles: Dijkstra, Floyd-Warshall, Kruskal e Prim.

## Exemplo

Exemplo de grafo que pode ser lido pelos algoritmos Kruskal, Djikstra e Prim: (Existem alguns exemplos na pasta 'Testes')

`5` - `(Número de Vertices)`

`V01`

`V02`

`V03`

`V04`

`V05`

`7` - `(Número de Arestas)`

`A01 V01 V02 23`

`A02 V02 V04 22`

`A03 V04 V01 123`

`A04 V03 V01 1`

`A05 V02 V03 44`

`A06 V03 V05 18`

`A07 V01 V05 99`

## Informações do código (como utilizar)

 O Algoritmo foi desenvolvido em C++, seu arquivo fonte está com o nome de 'main.cpp', e os outros códigos, Kruskal, Prim, Djikstra e Floyd, estão em formato 
 `.h` arquivo header.

 Para o uso dos Algoritmo Kruskal, Prim e Djikstra é necessário adicionar algum grafo localizado nos exemplos da pasta Teste. Já no uso do algoritmo de Floyd-Warshall utilizamos o exemplo na pasta "Teste/Floyd" com os estados e caminhos.