/*/ =================================================================

                        Programa: Grafo com Dijkstra, Prim e Kruskal em C++
                    Descri��o:  Perunta ao usu�rio um diretorio e cria o Grafo
                                            Bruno de Almeida Zampirom
                                                    158788@upf.br

                                        Ci�ncias da Computa��o - UPF
                                Estrura de Dados II - Evandro Luis Viapiana
                                                Copyright (c) 2017

==================================================================== /*/

#include <iostream>
#include <list>
#include <fstream>                       // I/O de streams

#define ORDENADO    <
//#define ORDENADO  !=
#define INFINITO  100000000     // Valor para auxiliar programa��o

struct Vertice;

struct Aresta
{
    bool viszdo=false;
    std::string rotulo;
    double custo;
    Vertice *v;
};

struct Vertice
{
    std::string rotulo;
    std::list<Aresta> arestas;
    bool viszdo;
    double dist=INFINITO;
    std::string ant="";
};

struct Grafo
{
    std::list<Vertice> vertices;
};

Grafo grafo;

//===========================================PROCURA VERTICE===========================================
bool procura_vertice( Grafo &grafo, std::string &rotulo, std::list<Vertice>::iterator &it )
{
    for( it=grafo.vertices.begin() ; (it != grafo.vertices.end() && it->rotulo ORDENADO rotulo) ; ++it );

    return ( it != grafo.vertices.end() && it->rotulo == rotulo );
}

//===========================================PROCURA ARESTA===========================================
bool procura_aresta( Vertice &vertice, std::string &rotulo, std::list<Aresta>::iterator &it)
{
    for( it=vertice.arestas.begin() ; (it != vertice.arestas.end() && it->rotulo ORDENADO rotulo) ; ++it );

    return ( it != vertice.arestas.end() && it->rotulo == rotulo );
}

//===========================================INSERE VERTICE===========================================
bool inserir_vertice( Grafo &grafo, std::string rotulo )
{
    std::list<Vertice>::iterator it;
    Vertice aux;

    if( procura_vertice( grafo, rotulo, it ) )
    {
        std::cout << std::endl << "*** Erro na insercao de vertice : vertice ja existente";
        return false;
    }

    aux.rotulo     = rotulo;
    aux.viszdo = false;

    grafo.vertices.insert( it, aux );

    return true;
}

//===========================================INSERE===========================================
bool inserir( Grafo &grafo, std::string v1, std::string v2, std::string aresta_rotulo, double aresta_custo )
{
    std::list<Vertice>::iterator vaux1,vaux2;
    std::list<Aresta> ::iterator aresta;
    Aresta aux;

    if( !procura_vertice( grafo, v1, vaux1 ) ||
            !procura_vertice( grafo, v2, vaux2 ) )
        return false;

    procura_aresta( *vaux1, aresta_rotulo, aresta );

    aux.rotulo    = aresta_rotulo;
    aux.custo    = aresta_custo;
    aux.v          = &*vaux2;

    vaux1->arestas.insert( aresta, aux );

    return true;
}

//===========================================INSERE ARESTA===========================================
bool inserir_aresta( Grafo &grafo, std::string v1, std::string v2, std::string aresta_rotulo, double aresta_custo)
{
    std::list<Vertice>::iterator vaux1;

    if ( v1 == v2 )
    {
        std::cout << std::endl << "*** Erro na insercao de aresta : grafo simples nao acez lacos";
        return false;
    }
    procura_vertice( grafo, v1, vaux1 );
    for( auto z : vaux1->arestas)
        if( z.v->rotulo == v2 )
        {
            std::cout << std::endl << "*** Erro na insercao de aresta : grafo simples nao arestas paralelas";
            return false;
        }

    if ( !inserir( grafo, v1, v2, aresta_rotulo, aresta_custo ) )
    {
        std::cout << std::endl << "*** Erro na insercao de aresta : vertice inexistente";
        return false;
    }
    inserir( grafo, v2, v1, aresta_rotulo, aresta_custo);

    return true;
}

//===========================================LEITURA DO ARQUIVO===========================================
bool leitura(Grafo &grafo)
{
    std::string namefile;
    std::cout<<" Informe o nome da arquivo: ";
    std::cin>>namefile;                                             //   lendo o nome do arquivo
    if(namefile=="0")return false;
    std::ifstream open("Testes/"+namefile+".txt");                     //    abrindo
    if (!open.is_open())                                      //    caso encontre o arquivo com esse nome
    {
        std::cout << "\n Erro : nao pode abrir o arquivo "<<namefile<<".txt"<<std::endl;
        return false;
    }

    std::string vertice, rotulo, v1, v2;
    int num;
    double custo;
    open>>num;
    for( int i = 0 ; i < num ; i++ )
    {
        open >>vertice;
        inserir_vertice( grafo, vertice );
    }
    open >> num ;
    for( int i = 0 ; i < num ; i++ )
    {
        open>>rotulo>>v1>>v2>>custo;
        inserir_aresta( grafo, v1, v2, rotulo, custo );
    }
    open.close();
}
