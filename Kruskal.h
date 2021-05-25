/*/ =================================================================

    Algoritmo de Kruskal em C++
    Descrição:  Perunta ao usuário um valor e executa o algoritmo de Kruskal
    Autores: João da Silva Muniz Neto 
             Mateus Monteiro Santos
             Engenharia de Computação - UFAL
             Copyright (c) 2021   
             
==================================================================== /*/

#include "Prim.h"

//CONFERE SE EXISTE CAMINHO
bool Kruskal_ConfereCaminho(Vertice*  X, Vertice*  Y,Vertice*  Z)
{
    if(X==Y)return true;    // Caso existir caminho
    for(auto z= X->arestas.begin() ; z != X->arestas.end() ; ++z)
    {
        if(z->viszdo && z->v != Z)       //  Enquanto existir arestas não viszdas
            if(Kruskal_ConfereCaminho(z->v, Y,X))
                break;
    }
}

//PROCURA DA ARESTA DE MENOR PESO
bool Kruskal_Procura(Grafo &grafo, std::list<Vertice>::iterator & IT, std::list<Aresta>::iterator &FI)
{
    auto menor=INFINITO;
    std::list<Aresta>::iterator ar;
    for(auto z= IT->arestas.begin() ; z != IT->arestas.end() ; ++z) //   percorrendo os vizinhos procurando a aresta com menor peso . . .
    {
        if(!z->viszdo && z->custo<menor && !z->v->viszdo || !z->viszdo && z->custo<menor && !Kruskal_ConfereCaminho(z->v,&*IT,z->v)) // caso tenha custo menor que o atual e a aresta n�o foi viszdo ainda ou caso n�o exista caminho entre z e IT
        {
            ar=z;
            menor=z->custo;
        }
    }
    if(menor<INFINITO)  //Caso encontrou algum  . . .
    {
        FI=ar;
        return true;
    }
    return false;
}

//CONFERE PROXIMA ARESTA 
bool Kruskal_Prox(Grafo &grafo,std::list<Vertice>::iterator &pai, std::list<Vertice>::iterator &filho) //Percorre os Vertices já viszdos
{
    auto prox=INFINITO;
    std::list<Aresta>::iterator ar,aresta;
    for(auto it=grafo.vertices.begin() ; it != grafo.vertices.end() ; ++it ) // Percorre entre todos os vertices
    {
        if(Kruskal_Procura(grafo,it,ar))
            if(ar->custo<prox)      // Dentre as todas arestas que sustentam o criterio da função acima escolhe a de menor custo
            {
                prox=ar->custo;
                pai=it;
                aresta=ar;
            }
    }
    if(prox<INFINITO)                               // Caso encontre algum
    {
        procura_vertice(grafo,aresta->v->rotulo,filho);
        std::list<Aresta>::iterator aresta2;
        procura_aresta(*filho, aresta->rotulo, aresta2);
        aresta2->viszdo=aresta->viszdo=true;
        return true;
    }
    return false;
}

//INCLUIR NO GRAFO
void Kruskal_Inclui(Grafo &grafo)
{
    std::list<Vertice>::iterator PAI;
    std::list<Vertice>::iterator FILHO;
    while(Kruskal_Prox(grafo,PAI,FILHO)) //enquanto ainda conter vertices que sustentam as exigencias acima
    {
        std::cout<<"PAI   : "<<PAI->rotulo<<std::endl;
        std::cout<<"Filho : "<<FILHO->rotulo<<std::endl;
        FILHO->viszdo=PAI->viszdo=true;
    }
}

//ESCOLHA AUTOMATICA COM MENOR ARESTA
std::list<Vertice>::iterator Kruskal_escolhaAuto(Grafo &grafo) 
{
    std::list<Vertice>::iterator it;
    std::list<Aresta>::iterator ar;
    auto prox=INFINITO;
    for(auto aut=grafo.vertices.begin() ; aut != grafo.vertices.end() ; ++aut)
    {
        if(Prim_procura(grafo,aut,ar))
            if(ar->custo<prox)
            {
                prox=ar->custo;
                it=aut;
            }
    }
    return it;
}

//INSERIR ARVORE
bool Kruskal_InserirArvore(Vertice* PAI,Vertice* ANT)
{
    for(auto z= PAI->arestas.begin() ; z != PAI->arestas.end() ; ++z)
        if(z->viszdo && z->v!= ANT)
        {
            inserirfilho(raiz,z->v->rotulo,PAI->rotulo);
            Kruskal_InserirArvore(z->v, PAI);
        }
}

//MAIN KRUSKAL
void Kruskal(Grafo &grafo)
{
    std::string vertice_origem;
    std::cout<<" Informe o vertice de origem da arvore (ou 'auto'): ";
    std::cin>>vertice_origem;
    std::list<Vertice>::iterator it;
    if(vertice_origem=="auto")
    {
        it=Kruskal_escolhaAuto(grafo);
        goto continua;
    }
    else if(procura_vertice(grafo,vertice_origem,it))
    {
continua:
        alocarRaiz(raiz,it->rotulo);            // Inserindo o valor vertice_origem como raiz
        it->viszdo=true;                          // Marcando como visitado
        Kruskal_Inclui(grafo);                  // Função principal do programa
        Kruskal_InserirArvore(&*it,&*it);
        mostra(raiz);
        for(auto it=grafo.vertices.begin() ; it != grafo.vertices.end() ; ++it ) //Resetando arvore e as flags alterado pelo algoritmo
        {
            for(auto z= it->arestas.begin() ; z != it->arestas.end() ; ++z)
                z->viszdo=false;
            it->viszdo=false;
            it->dist=INFINITO;
        }
        raiz->info.clear();
        raiz=nullptr;
    }
    else
        std::cout <<"\n *** Erro no algoritmo de Kruskal: valor nao encontrado \n";
}
