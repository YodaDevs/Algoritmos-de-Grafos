/*/ =======================================================================

                                        Programa: Grafo com Dijkstra, Prim e Kruskal em C++
                    Descri��o:  Perunta ao usu�rio dois valor, cria tabela e informa o menor caminho
                                                            Bruno de Almeida Zampirom
                                                                    158788@upf.br

                                                        Ci�ncias da Computa��o - UPF
                                            Estrura de Dados II - Evandro Luis Viapiana
                                                                Copyright (c) 2017

========================================================================== /*/

#include <iostream>
#include <vector>

struct nodo
{
    std::string info;
    nodo *pai;
    std::vector<nodo*> filho;
};
nodo* raiz=nullptr;

//===================================ALOCAR RAIZ===========================================
bool alocarRaiz( nodo* &raiz, std::string valor)
{
    raiz=new(std::nothrow) nodo;
    raiz->pai=nullptr;
    raiz->info=valor;
    return true;
}

//====================================LOCALIZAR============================================
nodo *localizar(std::string rotulo, nodo*end)
{
    nodo *achou;
    if(end->info==rotulo)return end;
    for(auto z : end->filho)
    {
        achou=localizar(rotulo, &*z );
        if(achou!=nullptr)return achou;
    }
    return(nullptr);
}

//====================================INSERIR FILHO============================================
bool inserirfilho(nodo*raiz, std::string valor,std::string valorpai)
{
    nodo *pai=localizar(valorpai, raiz);
    if(localizar(valor,raiz)!=nullptr)return false;
    nodo *novo= new(std::nothrow) nodo;
    novo->info=valor;
    novo->pai=pai;
    pai->filho.push_back(&*novo);
    return true;
}

//=======================================MOSTRA=============================================
void mostra( nodo *end )
{
    static int cont;
    if ( end == raiz )
        cont = 0;
    for(int i = 0 ; i < cont ; i++)
        std::cout << "  ";
    std::cout<<end->info;
    for(int i = 0 ; i < 21-(cont*2+end->info.size()) ; i++)
        std::cout<<".";
    std::cout<<std::endl;
    for(auto z : end->filho)
    {
        cont++;
        mostra(&*z);
        cont--;
    }
}
