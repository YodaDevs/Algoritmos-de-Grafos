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

Já ao Algoritmo de Floyd-Warshall temos:

Introdução dos arquivos solicitados:

Trains.txt

`0 Red`
`1 Green`
`2 Blue`
`3 Purple`
`4 Yellow`

CONTÉM N LINHAS (N CORRESPONDENDO AO NÚMERO DE ESTAÇÕES LIDAS DESDE O PRIMEIRO ARQUIVO)
ONDE CADA LINHA CONTÉM UM NÚMERO E UM NOME. O NÚMERO MAPEIA UM NOME PARA OS IDENIFICADORES
USADOS NO ARQUIVO STATIONS.TXT

estados.txt

`5 6`
`0 1 7`
`3 1 10`
`4 3 12`
`1 4 12`
`4 2 32`
`1 2 3`

A PRIMEIRA LINHA DO ARQUIVO CONTÉM DOIS INTEIROS INDICANDO O NÚMERO DE ESTAÇÕES E ROTAS. 
A SEGUIR A PRIMEIRA LINHA É N (N SENDO IGUAL AO NÚMERO TOTAL DE ROTAS) LINHAS QUE REPRESENTAM
ROTAS DIFERENTES E SEUS PESOS ASSOCIADOS.
Ex.
A LINHA 2 INDICA UMA ROTA DA ESTAÇÃO 0 À ESTAÇÃO 1 COM PESO 10 

## Informações do código (como utilizar)

 O Algoritmo foi desenvolvido em C++, seu arquivo fonte está com o nome de 'main.cpp', e os outros códigos, Kruskal, Prim, Djikstra e Floyd, estão em formato 
 `.h` arquivo header.

 Para o uso dos Algoritmo Kruskal, Prim e Djikstra é necessário adicionar algum grafo localizado nos exemplos da pasta Teste. Já no uso do algoritmo de Floyd-Warshall utilizamos o exemplo na pasta "Teste/Floyd" com os estados e caminhos.