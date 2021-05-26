/*/ =======================================================================
    Algoritmo de Floyd-Warshall em C++
    Descrição: Com os valores obtidos pelos arquivos Trains.txt e Stations.txt desenvolve o algoritmo de Floyd-Warshall
    Autores: João da Silva Muniz Neto 
             Mateus Monteiro Santos
             Engenharia de Computação - UFAL
             Copyright (c) 2021   
========================================================================== /*/

// COMEÇO DO CÓDIGO
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <iomanip>

#define infi 99                 // CONSTANTE PARA DEFINIÇÃO DE INFINITO PARA O PROGRAMA

using namespace std;

class Graph{

	int estado;                	// VERTICES
	int rota;                  	// ARESTAS
	int peso;                 	// GRAFOS COM PESOS
	int **minhaMatrix; 		// ARRAY DE DUAS DIMENSÕES (2D) PARA "IF"
	int **floydMatrix;  		// ARRAY DE DUAS DIMENSÕES (2D) PARA PARA O CAMINHO MAIS CURTO
	int **reconstructMatrix;	// ARRAY DE DUAS DIMENSÕES (2D) PARA RECONSTRUÇÃO DE CAMINHOS
	string *estadocors;  	// ARRAY PARA NOMES DAS CORES

	vector<int> trainCaminho;		// UM VETOR PARA IMPRIMIR O CAMINHO RECONSTRUÍDO (NA FUNÇÃO printCaminho())

	public:

	//CONSTRUCTOR
	Graph(int estados, int rotas);

	void printMatrix();
	void addrota(int from, int to, int peso);
	bool isrota(int from, int to);                 
	void deleteMatrix();				// APAGA TODOS ARRAYS ALOCADOS DA CLASSE
	void calcShortestrotas();                      // EXECUTA O ALGORITMO F-W
	int shortestrota(string src, string dst);	// RETORNA O CAMINHO MAIS CURTO DA MATRIS F-W
	bool checkcors(string src); 			// VERIFICA SE AS CORES SÃO VERIDICAS
	void printCaminho(string src, string dst);         // IMPRIME CAMINHO DA MATRIZ DE RECONSTRUÇÃO

	//GETTERS AND SETTERS
	int getestadoId(string cor);                 // PASSE NA COR PARA OBTER A IDENTIFICAÇÃO
	string getestadocors(int id);                // OBTER A COR DA ESTAÇÃO DO ARRAY
	void setestadocors(int id, string cor);    // DEFINE A COR DA ESTAÇÃO PARA A MATRIZ

};

Graph::Graph(int estados, int rotas){

	//ARRAY FOR THE estado NAMES (DYNAMICALLY SIZED) 
	estadocors = new string[estados]; 

	estado = estados;
	rota = rotas; 

	minhaMatrix = new int* [estado];

	for(int i = 0; i<estado; i++)
	{
		minhaMatrix[i] = new int[estado];

		for(int j = 0; j < estado; j++)
		{
			minhaMatrix[i][j] = 0;  
		}						
	}

	/* INICIALIZA UMA SEGUNDA MATRIZ PARA F-W, ESTÁ É UMA CÓPIA PARA EXECUTAR O ALGORITMO, 
	E PERITA QUE A PRIMEIRA MATRIZ RETENHA SUAS INFORMAÇÕES */
	floydMatrix = new int* [estado];

	for(int i = 0; i<estado; i++)
	{
		floydMatrix[i] = new int[estado];

		for(int j = 0; j < estado; j++)
		{
			floydMatrix[i][j] = infi; //VARIAVEL INFI = 99
		}
	}  

	// INICIALIZA UMA TERCEIRA MATRIZ PARA SER USADA PARA RECONSTRUÇÃO DO CAMINHO
	reconstructMatrix = new int* [estado];

	for(int i = 0; i<estado; i++)
	{
		reconstructMatrix[i] = new int[estado];

		for(int j = 0; j < estado; j++)
		{
			reconstructMatrix[i][j] = -1; 
		}
	}  


}

void Graph::printMatrix(){

	cout << "-----Adjacency Matrix-----" << endl;

	for(int i = 0; i < estado; i++)
	{
		for(int j = 0; j < estado; j++)
		{	
			cout << setw(2) << minhaMatrix[i][j] << "  ";
		}
		cout << endl;
	}

	cout << "-----Floyd-Warshall Matrix-----" << endl;

	for(int i = 0; i < estado; i++)
	{
		for(int j = 0; j < estado; j++)
		{	
			cout << setw(2) << floydMatrix[i][j] << "  ";
		}
		cout << endl;
	}

	cout << "-----Reconstruction Matrix-----" << endl;

	for(int i = 0; i < estado; i++)
	{
		for(int j = 0; j < estado; j++)
		{	
			cout << setw(2) << reconstructMatrix[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl; 
}

// ADICIONA AS ROTAS PARA A MATRIZ DE ADJACÊNCIA E A MATRI DE F-W 
void Graph::addrota(int from, int to, int peso){

	minhaMatrix[from][to] = peso; 

	floydMatrix[from][to] = peso;

	reconstructMatrix[from][to] = to;  
}

bool Graph::isrota(int from, int to)  
{
	bool isCaminho = false;
	bool visitado[estado]; // DECLARANDO DINAMICAMENTE COM VARIÁVEL DE PROGRAMA
	queue<int> vertices;

	//INICIALIZANDO  visitado[ ]
	for(int i = 0; i < estado ; i++){
		visitado[i] = false;
	}

	visitado[from] = true;  // MARCANDO O INDEX INICIAL VISITADO
	vertices.push(from);   // ADICIONE ADD START INDEX TO QUEUE TO ENTER LOOP

	while(!vertices.empty() && isCaminho == false )
	{
		int currentInQueue;

		currentInQueue = vertices.front();                  
		vertices.pop();										

		cout << "Checando " << currentInQueue << endl;				

		for(int temp = 0; temp < estado ; temp++)
		{			

			if(minhaMatrix[currentInQueue][temp] != 0){       
															  
				if(temp == to)
				{
					isCaminho = true;
					break;
				}
		
				if(visitado[temp] == false){ 				  

					//MARCANDO COMO VISITADA
					visitado[temp] = true;				    
					//ADICIONANDO NA QUEUE
					vertices.push(temp);                    
				}
			}
		}
	}
	return isCaminho;
}

void Graph::calcShortestrotas(){ 

	int i,j,k;

	for(k = 0; k < estado; k++){

		for(i = 0; i < estado; i++){

			for(j = 0; j < estado; j++){
				
				if(floydMatrix[i][j] > floydMatrix[i][k] + floydMatrix[k][j]){

					floydMatrix[i][j] = floydMatrix[i][k] + floydMatrix[k][j];
					reconstructMatrix[i][j] = reconstructMatrix[i][k];  //RECONSTRUCTION MATRIX

				}
			}
		}
	}
}

int Graph::shortestrota(string src, string dst)
{
	int a = getestadoId(src);
	int b = getestadoId(dst);

	return floydMatrix[a][b];  
}

bool Graph::checkcors(string src)
{
	for( int i = 0; i < estado; i++ ){ 

		if(estadocors[i] == src ){
			return true;
		}
	}
	return false;
}

void Graph::printCaminho(string src, string dst)
{
	// ESTAMOS PASSANDO STRINGS QUE PRECISAM SER CONVERTIDOS PARA INTEIROS. A FUNCAO getestadoId() FAZ ISSO.
	int a = getestadoId(src);
	int b = getestadoId(dst);

	// O VETOR DO CAMINHO E INICIALIZADO COM 1 
	trainCaminho = vector<int>(1,0); 

	if(reconstructMatrix[a][b] == -1)
	{
		return; 
	}

	trainCaminho[0] = a; // INICIALIZANDO PRIMEIRO NO

	while( a != b ){
		
		a = reconstructMatrix[a][b];
		trainCaminho.push_back(a);
	}

	cout << "Seu caminho deve ser ";

	for( int i = 0 ; i < trainCaminho.size() ; i++ ){

		cout << getestadocors( trainCaminho[i] );

		 // NAO PRINTAR A FLECA CASO SEJA UMA FOLHA
		 if( i < trainCaminho.size() - 1){

		 		cout << "->" ;  
		 }		 	
	}
	cout << endl;
}

int Graph::getestadoId(string cor)
{
	int id = 0; //ID COMECA EM 0 PARA INDEX[0] NO ARRAY

	for( int i = 0; i < estado; i++ ){  

		if(estadocors[i] == cor){
			return id;
		}
		//INCRIMENTA SOMENTE SE NAO ESTA FORA DO TAMANHO DO ARRAY 
		if(id < estado)
		{
			id++; 
		}
	}
}

string Graph::getestadocors(int id){

	return estadocors[id];
}

void Graph::setestadocors(int id, string cor){

	estadocors[id] = cor;
}

//DELETANDO MEMORIA ALOCADA DINAMICAMENTE
void Graph::deleteMatrix()
{
	for( int i=0 ; i < estado ; i++ ){
		delete minhaMatrix[i];
	}

	delete minhaMatrix;

	for( int i=0 ; i < estado ; i++ ){
		delete floydMatrix[i];
	}

	delete floydMatrix;

	for( int i=0 ; i < estado ; i++ ){
		delete reconstructMatrix[i];
	}
	delete reconstructMatrix;

	delete[] estadocors;
	estadocors = NULL;

}

//MAIN
int Floyd()
{
	//ABRINDO O ARQUIVO COM OS TRAINS
	ifstream file;
	file.open("Testes/Floyd/trains.txt"); // CAMINHO trains PARA ALGORITMO
	
	if(!file.is_open()){
		cout << "File Error";
		return -1;
	}

	int afile;
	int bfile;
	int cfile;

	file >> afile >> bfile;

	Graph mainMtrx = Graph(afile,bfile);

	while (file >> afile >> bfile >> cfile ){

		mainMtrx.addrota(afile, bfile, cfile );

	}

	//ABRINDO ARQUIVO COM OS ESTADOS 
	ifstream file2;
	file2.open("Testes/Floyd/estados.txt"); // CAMINHHO estados PARA ALGORITMO

	if(!file2.is_open()){
		cout << "File Error";
		return -1;
	}

	int num;
	string cor;
	
	while ( file2 >> num >> cor ){

		mainMtrx.setestadocors(num,cor);

	}

	/*	UMA VEZ O GRAFO SENDO USADO PARA O ALGORITMO FLOYD-WARSHALL
		FOI INICIALIZADO AS NECESSIDADES DO ALGORITMO
		PARA SER EXECUTADO PARA PRODUZIR INFORMAÇÕES CORRETAS 
    */
	mainMtrx.calcShortestrotas();

	int escolha = 1; //VARIAVEL PARA A INICIALIZACAO DO LOOP DO PROGRAMA

	while(escolha == 1)
	{
		cout << "-- Menu Floyd-Warshall --" << endl;
		cout << "     1 -> Menu Print" << endl;
		cout << "     2 -> Checar se o caminho existe" << endl;
		cout << "     0 -> Retornar ao menu com os outros algoritmos" << endl;	
		cout << "     Entrada: ";

		cin >> escolha;

		if(escolha == 0)
		{
			break;
		}

		if(escolha == 2)
		{
			string fonte;
			string destino;

			cout << "\nDe que estado voce este saindo: Red , Green , Blue , Purple, Yellow ?\n";
			cin >> fonte;

			//CHECANDO A ENTRADA DO USUARIO DIANTE DA RAIZ
			while(mainMtrx.checkcors(fonte) == false){
				cout << fonte << " Entrada invalida - por favor repita a entrada: ";
				cin >> fonte;
			}

			cout << "\nPara qual estado voce quer caminhar: Red, Green, Blue Purple, Yellow ?\n";
			cin >> destino;

			//CHECANDO A ENTRADA DO USUARIO DIANTE DO DESTINO
			while(mainMtrx.checkcors(destino) == false){
				cout << destino << " Entrada invalida - por favor repita a entrada: ";
				cin >> destino;
			}
			

			//INTEIROS PARA ARMAZENAR A RAIZ E O DESTINO DO GRAFO 
			int a = mainMtrx.getestadoId(fonte);
			int b = mainMtrx.getestadoId(destino);

			//SE EXISTIR UMA ROTA
			if( mainMtrx.isrota(a,b) ){

				//MENOR ROTA
				int minrota = mainMtrx.shortestrota(fonte, destino);

				mainMtrx.printMatrix();
				cout << "Tem uma rota entre " << fonte << " e " << destino << " com a minima distancia de " << minrota << " milhas." << endl;
				mainMtrx.printCaminho(fonte, destino);
				cout << endl;
				escolha = 1;
			}
			else{

				mainMtrx.printMatrix();
				cout << "Nao ha rota entre " << fonte << " e " << destino << endl;
				cout << endl;
				escolha = 1;
			}
		}
	}

	mainMtrx.deleteMatrix();

	file.close();
	file2.close();

	return 0;
}



