/*/ =======================================================================
    Algoritmo de Djikstra em C++
    Descrição: Perunta ao usuario dois valores, cria a tabela e informa o menor caminho
    Autores: João da Silva Muniz Neto 
             Mateus Monteiro Santos
             Engenharia de Computação - UFAL
             Copyright (c) 2021   
========================================================================== /*/

#include <iostream>
#include "Grafo.h"

//PERCORRE O CAMINHO DO GRAFO DE DIJKSTRA
void Dijkstra_Caminho(Grafo &grafo,std::list<Vertice>::iterator IT,std::list<Vertice>::iterator itO)
{
    if(IT->ant!="") //Percorre o caminho inverso de Pesquisa
    {
        std::cout<<IT->ant;
        if(IT->ant!=itO->rotulo)
            std::cout<<", ";
        std::list<Vertice>::iterator aux;
        procura_vertice(grafo,IT->ant,aux);
        Dijkstra_Caminho(grafo,aux,itO);
    }
}

//MOSTRA O GRAFO DE DIJKSTRA
void Dijkstra_Mostra(Grafo &grafo,std::list<Vertice>::iterator itO)
{
    for(auto it=grafo.vertices.begin() ; it != grafo.vertices.end() ; ++it )
    {
        if(it->dist==INFINITO || it==itO)      //Caso não exista caminho para este valor
            std::cout  <<"  "<< it->rotulo <<" :**\n";
        else
        {
            std::cout  <<"  "<< it->rotulo <<" :"<<it->dist;
            if(it->dist<10)
                std::cout<<" ";
            std::cout<<"  {";
            Dijkstra_Caminho(grafo,it,itO);
            std::cout<<"}"<<std::endl;
        }
    }
}

//CALCULO DO CUSTO DAS DISTANCIAS DO GRAFO DE DIJKSTRA
void Dijkstra_Distancia(Grafo &grafo, std::list<Vertice>::iterator &z, std::list<Vertice>::iterator &ITP, std::list<Aresta>::iterator &AR)
{
    if(ITP->dist > z->dist + AR->custo) //Caso o custo com o anterior seja menor que o atual
    {
        ITP->dist= z->dist + AR->custo; //distancia do vertice anterior + o custo da aresta
        ITP->ant=  z->rotulo;
    }
}

//PERCORRENDO PELO VIZINHOS NO GRAFO DE DIJKSTRA
void Dijkstra_Vizinhos(Grafo &grafo, std::list<Vertice>::iterator IT)
{
    std::list<Vertice>::iterator itPROX;     //para saber em qual vertice seguir apos este
    double maior=INFINITO;
    IT->viszdo=true;                        //marca como viszdo
    for(auto z= IT->arestas.begin() ; z != IT->arestas.end() ; ++z) //   percorrendo os vizinhos
    {
        std::list<Vertice>::iterator ITP;
        procura_vertice(grafo, z->v->rotulo,ITP);  //procurando vertice do vizinho
        Dijkstra_Distancia(grafo, IT, ITP, z);
    }
    for(auto it=grafo.vertices.begin() ; it != grafo.vertices.end() ; ++it ) //proximo vertice a ser pesquisado
        if(!it->viszdo && it->dist<maior) // Procura entre os ainda não vztados o de menor custo
        {
            itPROX=it;
            maior=itPROX->dist;
        }
    if(maior < INFINITO )Dijkstra_Vizinhos(grafo,itPROX); //caso ainda tenha algum não pesquisado
}

//MAIN DO GRAFO DE DIJKTRA

int Dijkstra(Grafo &grafo)
{
    std::list<Vertice>::iterator itO,itD;
    std::string origem, destino;
    std::cout<<" Informe o vertice de origem e o de destino: ";
    std::cin>>origem>>destino;
    if( !procura_vertice( grafo, origem, itO ) ||  !procura_vertice( grafo, destino, itD ))
    {
        std::cout <<"\n *** Erro no algoritmo de Dijkstra: vertice nao encontrado \n";
        return false;
    }
    itO->viszdo=true; //inicializando o vertice de origem
    itO->dist=0;
    Dijkstra_Vizinhos(grafo, itO);  //criando tabela
    Dijkstra_Mostra(grafo,itO);     //mostrando a tabela;
    if(itD->dist<INFINITO)
        std::cout<<"  Melhor caminho entre "<<itO->rotulo<<" e "<<itD->rotulo<<": "<<itD->dist<<std::endl;
    else
        std::cout<<"  Nao existe caminho entre "<<itO->rotulo<<" e "<<itD->rotulo<<std::endl;
    for(auto it=grafo.vertices.begin() ; it != grafo.vertices.end() ; ++it ) //Resetando o grafo
    {
        it->viszdo=false;
        it->dist=INFINITO;
        it->ant="";
    }
}
