/*/ =================================================================

    Algoritmo de Prim em C++
    Descrição:  Perunta ao usuario um valor e executa o algoritmo de Prim
    Autores: João da Silva Muniz Neto 
             Mateus Monteiro Santos
             Engenharia de Computação - UFAL
             Copyright (c) 2021   

==================================================================== /*/

#include "Arvore_geradora_minima.h"
#include "Dijkstra.h"

//PROCURA ARESTA COM MENOR PESO
bool Prim_procura(Grafo &grafo, std::list<Vertice>::iterator & IT, std::list<Aresta>::iterator &FI)
{
    auto menor=INFINITO;
    std::list<Aresta>::iterator ar;
    for(auto z= IT->arestas.begin() ; z != IT->arestas.end() ; ++z)        // Percorrendo os vizinhos procurando a aresta com menor peso
    {
        if(z->custo<menor && !z->v->viszdo)                                         // Caso tenha custo menor que o atual e a aresta não foi visitado ainda
        {
            ar=z;
            menor=z->custo;
        }
    }
    if(menor<INFINITO)                                                                              // Caso encontrou algum
    {
        FI=ar;
        return true;
    }
    return false;
}

//PERCORRE OS VERTICES JA VISITADOS (PROXIMO) A PROCURA DA ARESTA DE MENOR PESO
bool Prim_Prox(Grafo &grafo,std::list<Vertice>::iterator &pai, std::list<Vertice>::iterator &filho) //Percorre os Vertices já visitados
{
    auto prox=INFINITO;
    std::list<Aresta>::iterator ar,aresta;
    for(auto it=grafo.vertices.begin() ; it != grafo.vertices.end() ; ++it )
    {
        if(it->viszdo)                            // Percorre os vertices ja visitados
            if(Prim_procura(grafo,it,ar))   // Caso algum sutente a exigência da função
                if(ar->custo<prox)              // Procura entre estas a de menor custo
                {
                    prox=ar->custo;
                    pai=it;
                    aresta=ar;
                }
    }
    if(prox<INFINITO)                           // Caso encontrou algum
    {
        procura_vertice(grafo,aresta->v->rotulo,filho);
        return true;
    }
    return false;
}

//ADICIONA AO GRAFO DE PRIM
void Prim_Adiciona(Grafo &grafo)
{
    std::list<Vertice>::iterator PAI;
    std::list<Vertice>::iterator FILHO;
    while(Prim_Prox(grafo,PAI,FILHO)) //enquanto ainda conter vertices que sustentam as exigencias acima
    {
        inserirfilho(raiz,FILHO->rotulo,PAI->rotulo);  //Inclui o vertice na arvore
        FILHO->viszdo=PAI->viszdo=true;
    }
}

//ESCOLHA AUTOMATICA AO GRAFO DE PRIM
std::list<Vertice>::iterator Prim_escolhaAuto(Grafo &grafo) //Para selecionar a menor aresta
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

//MAIN DO ALGORITMO DE PRIM
void Prim(Grafo &grafo)
{
    std::string vertice_origem;
    std::cout<<" Informe o vertice de origem da arvore (ou 'auto' para automatico): ";
    std::cin>>vertice_origem;
    std::list<Vertice>::iterator it;
    if(vertice_origem=="auto")
    {
        it=Prim_escolhaAuto(grafo);
        goto continua;
    }
    else if(procura_vertice(grafo,vertice_origem,it))
    {
        continua:
        alocarRaiz(raiz,it->rotulo);            //inserindo o valor vertice_origemiczdo como raiz
        it->viszdo=true;                          //marcando como viszdo
        Prim_Adiciona(grafo);
        mostra(raiz);
        for(auto it=grafo.vertices.begin() ; it != grafo.vertices.end() ; ++it ) //Resetando arvore e os flags alterado pelo algoritmo . . .
        {
            it->viszdo=false;
            it->dist=INFINITO;
        }
        raiz->info.clear();
        raiz=nullptr;
    }
    else
        std::cout <<"\n *** Erro no Algoritmo de Prim: vertice nao encontrado \n";
}
