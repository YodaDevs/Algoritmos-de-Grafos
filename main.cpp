/*/ =================================================================

    Implementação de 4 algoritmos de grafos com Dijkstra, Prim, Kruskal e Floyd-Warshall em C++
    Descrição: Menu inicial do trabalho de Grafos, chame a função pelo algoritmo selecionado pelo usuário
    Autores: João da Silva Muniz Neto 
             Mateus Monteiro Santos
             Engenharia de Computação - UFAL
             Copyright (c) 2021
==================================================================== /*/

#include "Kruskal.h"
#include "Floyd.h"

using namespace std;

//==============================================================================
int main()
{
    cout<<" Implementacao de Joao da Silva Muniz Neto e Mateus Monteiro Santos\n";
    while(1)
    {
        cout<<"\n L - Ler grafo pelo txt (Para opcoes D,P e K) "<<endl;
        cout<<" D - Dijkstra"<<endl;
        cout<<" F - Floyd-Warshall"<<endl; 
        cout<<" K - Kruskal"<<endl;
        cout<<" P - Prim"<<endl;
        cout<<" E - Encerrar"<<endl;
        cout<<" ";
        char a;
        cin>>a;
        switch(a)
        {
        case 'L':
            leitura(grafo);
            break;
        case 'D':
            if(grafo.vertices.size()>0)Dijkstra(grafo);
            break;
        case 'P':
            if(grafo.vertices.size()>0)Prim(grafo);
            break;
        case 'K':
            if(grafo.vertices.size()>0)Kruskal(grafo);
            break;
        case 'F':
            Floyd();
            break;
        case 'E':
            return 0;
        }
    }
}
