#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#define MAX 100
#define INICIAL 0

typedef struct{ //VÉRTICE
	int i;
}vert;

typedef struct{ //ELEMENTO DA FILA (CONTÉM UM VÉRTICE)
	vert vertices[MAX];
	int tras, frente;
}filaBFS;

typedef struct{ //ELEMENTO DA PILHA (CONTÉM UM VÉRTICE)
	vert vertices[MAX];
	int topo;
}pilhaDFS;

void filaVazia(filaBFS *fila){ //FUNÇÃO PARA ESVAZIAR FILA
	fila->frente=1;
	fila->tras=fila->frente;
}

void pilhaVazia(pilhaDFS *pilha){ //FUNÇÃO PARA ESVAZIAR PILHA
	pilha->topo=0;
}

int vaziaF(filaBFS fila){ //FUNÇÃO PARA VERIFICAR SE FILA ESTÁ VAZIA
	return (fila.frente==fila.tras);
}

int vaziaP(pilhaDFS pilha){ //FUNÇÃO PARA VERIFICAR SE PILHA ESTÁ VAZIA
	return (pilha.topo==0);
}

void enfileirar(filaBFS *fila, vert v){ //FUNÇÃO PARA ADICIONAR VÉRTICE À FILA
	if(fila->tras%MAX+1==fila->frente){
		printf("Erro! Fila cheia!");
	}else{
		fila->vertices[fila->tras-1]=v;
		fila->tras=fila->tras%MAX+1;
	}
}

void empilhar(pilhaDFS *pilha, vert v){ //FUNÇÃO PARA ADICIONAR VÉRTICE À PILHA
	if (pilha->topo==MAX){
		printf("Pilha cheia!");
	}else{
		pilha->vertices[pilha->topo]=v;
		pilha->topo++;
	}
}

void desenfileirar(filaBFS *fila, vert *v){ //FUNÇÃO PARA RETIRAR VÉRTICE DA FILA
	if (vaziaF(*fila)){
		printf("Erro! Fila vazia!");
	}else{
		*v=fila->vertices[fila->frente-1];
		fila->frente=fila->frente%MAX+1;
	}
}

void desempilhar(pilhaDFS *pilha, vert *v){ //FUNÇÃO PARA RETIRAR VÉRTICE DA PILHA
	if (vaziaP(*pilha)){
		printf("Pilha vazia!");
	}else{
		*v=pilha->vertices[pilha->topo-1];
		pilha->topo--;
	}
}

int visitado(int tam, int visitados[], int v){ //FUNÇÃO PARA VERIFICAR SE UM ÍNDICE V FOI VISITADO(1) OU NÃO (0)
	int i;
	
	for(i=0; i<tam; i++){
		if(v==visitados[i]){
			return 1;
		}
	}
	
	return 0;
}

int menor(int tam, float vet[tam], int visitados[], int tam2){ //FUNÇÃO PARA ENCONTRAR O ÍNDICE DO MENOR ELEMENTO NA LISTA DE ADJACÊNCIA (VÉRTICE NÃO VISITADO)
	int i, pmenor;
	
	for(i=0; i<tam; i++){
		if(!visitado(tam2, visitados, i)){
			pmenor=i;
			break;
		}
	}
	
	for(i=0; i<tam; i++){
		if((!visitado(tam2, visitados, i))&&(vet[i]<vet[pmenor])){
			pmenor=i;
		}
	}
	
	return pmenor;
}

int menor2(int tam, float vet[tam], int vertices[tam]){ //FUNÇÃO PARA ENCONTRAR O ÍNDICE DO MENOR ELEMENTO NA LISTA DE VÉRTICES PARA O ALGORITMO DE PRIM
	int i, pmenor;
	
	for(i=0; i<tam; i++){
		if(vertices[i]!=-1){
			pmenor=i;
			break;
		}
	}
	
	for(i=0; i<tam; i++){
		if((vet[i]<vet[pmenor])&&(vertices[i]!=-1)){
			pmenor=i;
		}
	}
	
	return pmenor;
}

int vetorVazio(int tam, int vet[tam]){ //FUNÇÃO PARA VERIFICAR SE UM VETOR POSSUI TODAS AS POSIÇÕES IGUAIS A -1
	int i;
	
	for(i=0; i<tam; i++){
		if(vet[i]!=-1){
			return 0;
		}
	}
	
	return 1;
}

void ordenar(int tam, float arestas[tam][3]){ //FUNÇÃO PARA ORDENAR ARESTAS POR ORDEM DE PESO
	int pMenor, i, j, p1Aux, p2Aux;
	float custoMenor, custoAux;
	
	for(j=0; j<tam; j++){
		custoMenor=1000;
		for(i=j; i<tam; i++){
			if(arestas[i][2]<custoMenor){
				custoMenor=arestas[i][2];
				pMenor=i;
			}
		}
		p1Aux=arestas[j][0];
		p2Aux=arestas[j][1];
		custoAux=arestas[j][2];
		arestas[j][0]=arestas[pMenor][0];
		arestas[j][1]=arestas[pMenor][1];
		arestas[j][2]=arestas[pMenor][2];
		arestas[pMenor][0]=p1Aux;
		arestas[pMenor][1]=p2Aux;
		arestas[pMenor][2]=custoAux;
	}
}

void ordenarPeso(int tam, float vet[tam]){ //FUNÇÃO PARA ORDENAR ÍNDICES POR ORDEM DE PESO
	int i, pMenor=0, aux=tam, j, cont=0;
	float menorPeso, vetAux[tam];
	
	while(aux>0){
		menorPeso=1000;
		pMenor=0;
		for(i=0; i<tam; i++){
			if((vet[i]==0)||(vet[i]==1000)){
				vet[i]=-1000;
				aux--;
			}else{
				if((vet[i]<menorPeso)&&(vet[i]>0)){
					pMenor=i;
					menorPeso=vet[i];
				}
			}
		}
		aux--;
		vet[pMenor]=-aux;
		cont++;
	}
	
	for(i=1; i<=cont; i++){
		for(j=0; j<tam; j++){
			if(vet[j]==i-cont){
				vetAux[i-1]=j;
			}
		}
	}
	
	for(i=0; i<tam; i++){
		vet[i]=vetAux[i];
		if(i>=cont){
			vet[i]=-1;
		}
	}
}

void bfsID(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO BFS POR ORDEM CRESCENTE DE ID tem algo errado
	int visitados[vTotal], i, j, tam=0;
	filaBFS fila;
	vert v;
	
	filaVazia(&fila);
	
	v.i=INICIAL;
	enfileirar(&fila, v);
	visitados[0]=INICIAL;
	tam++;
	
	while(!vaziaF(fila)){
		desenfileirar(&fila, &v);
		i=v.i;
		for(j=0; j<vTotal; j++){
			if((!visitado(tam, visitados, j))&&(grafo[i][j]!=1000)&&(grafo[i][j]!=0)){
				visitados[tam]=j;
				tam++;
				v.i=j;
				enfileirar(&fila, v);
			}
		}
	}
	
	printf("\nVértices visitados: ");
	for(i=0; i<tam; i++){
		printf("%d ", visitados[i]);
	}
	printf("\n\n");

	system("pause");
}

void dfsID(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO DFS POR ORDEM CRESCENTE DE ID
	int visitados[vTotal], i, j, tam=0, aux;
	pilhaDFS pilha;
	vert v;
	
	pilhaVazia(&pilha);
	
	v.i=INICIAL;
	empilhar(&pilha, v);
	visitados[0]=INICIAL;
	tam++;
	
	while(!vaziaP(pilha)){
		aux=0;
		i=v.i;
		for(j=0; j<vTotal; j++){
			if((!visitado(tam, visitados, j))&&(grafo[i][j]!=1000)&&(grafo[i][j]!=0)){
				visitados[tam]=j;
				tam++;
				aux++;
				v.i=j;
				empilhar(&pilha, v);
				break;
			}
		}
		if(aux==0){
			desempilhar(&pilha, &v);
		}
	}
	
	printf("\nVértices visitados: ");
	for(i=0; i<tam; i++){
		printf("%d ", visitados[i]);
	}
	printf("\n\n");

	system("pause");
}

void bfsPeso(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO BFS POR ORDEM CRESCENTE DE PESO
	int visitados[vTotal], i, j, tam=0;
	float adj[vTotal];
	filaBFS fila;
	vert v;
	
	filaVazia(&fila);
	
	v.i=INICIAL;
	enfileirar(&fila, v);
	visitados[0]=INICIAL;
	tam++;
	
	while(!vaziaF(fila)){
		desenfileirar(&fila, &v);
		i=v.i;
		for(j=0; j<vTotal; j++){
			adj[j]=grafo[i][j];
		}
		
		ordenarPeso(vTotal, adj);
	
		for(j=0; j<vTotal; j++){
			if((!visitado(tam, visitados, adj[j]))&&(adj[j]!=-1)){
				visitados[tam]=adj[j];
				tam++;
				v.i=adj[j];
				enfileirar(&fila, v);
			}
		}
	}
	
	printf("\nVértices visitados: ");
	for(i=0; i<tam; i++){
		printf("%d ", visitados[i]);
	}
	printf("\n\n");

	system("pause");
}

void dfsPeso(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO DFS POR ORDEM CRESCENTE DE PESO
	int visitados[vTotal], i, j, tam=0, aux;
	float adj[vTotal];
	pilhaDFS pilha;
	vert v;
	
	pilhaVazia(&pilha);
	
	v.i=INICIAL;
	empilhar(&pilha, v);
	visitados[0]=INICIAL;
	tam++;
	
	while(!vaziaP(pilha)){
		aux=0;
		i=v.i;
		
		for(j=0; j<vTotal; j++){
			adj[j]=grafo[i][j];
		}
		
		ordenarPeso(vTotal, adj);
		
		for(j=0; j<vTotal; j++){
			if((!visitado(tam, visitados, adj[j]))&&(adj[j]!=-1)){
				visitados[tam]=adj[j];
				tam++;
				aux++;
				v.i=adj[j];
				empilhar(&pilha, v);
				break;
			}
		}
		if(aux==0){
			desempilhar(&pilha, &v);
		}
	}
	
	printf("\nVértices visitados: ");
	for(i=0; i<tam; i++){
		printf("%d ", visitados[i]);
	}
	printf("\n\n");

	system("pause");
}

void dijkstra(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO DE DIJKSTRA
	int visitados[vTotal], i, v, tam=0, j;
	float adj[vTotal];
	
	visitados[0]=INICIAL;
	tam++;
	
	for(i=0; i<vTotal; i++){
		adj[i]=grafo[INICIAL][i];
	}
	
	for(i=0; i<vTotal-1; i++){
		v=menor(vTotal, adj, visitados, tam);
		visitados[tam]=v;
		tam++;
		for(j=0; j<vTotal; j++){
			if((!visitado(tam, visitados, j))&&(grafo[v][j]!=1000)){
				if(adj[v]+grafo[v][j]<adj[j]){
					adj[j]=adj[v]+grafo[v][j];
				}
			}
		}
	}
	
	printf("\nSaída: \n");
	
	for(i=1; i<vTotal; i++){
		printf("%d -> %d = %f\n", visitados[0], visitados[i], adj[visitados[i]]);
	}
	
	printf("\n");
	system("pause");
}

void floyd(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO DE FLOYD-WARSHALL
	float dist[vTotal][vTotal];
	int i, j, k;
	
	for(i=0; i<vTotal; i++){
		for(j=0; j<vTotal; j++){
			dist[i][j]=grafo[i][j];
		}
	}
	
	for(k=0; k<vTotal; k++){
		for(j=0; j<vTotal; j++){
			for(i=0; i<vTotal; i++){
				if(dist[i][k]+dist[k][j]<dist[i][j]){
					dist[i][j]=dist[i][k]+dist[k][j];
				}
			}
		}
	}
	
	printf("\nSaída: \n");
	
	for(i=0; i<vTotal; i++){
		for(j=0; j<vTotal; j++){
			printf("%.2f ", dist[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	system("pause");
}

void generico(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO GENÉRICO PARA ENCONTRAR MST
	int i, j, aux=0, prox[vTotal];
	float pesoAux, custo=0;
	
	for(i=0; i<vTotal; i++){
		prox[i]=-1;
	}
	
	while(aux<vTotal-1){
		for(i=0; i<vTotal-1; i++){
			pesoAux=1000;
			for(j=0; j<vTotal; j++){
				if((grafo[i][j]!=0)&&(grafo[i][j]!=1000)&&(grafo[i][j]<pesoAux)&&(prox[j]!=i)){
					pesoAux=grafo[i][j];
					if(prox[i]==-1){
						aux++;
					}
					prox[i]=j;
				}
			}
			custo+=pesoAux;
		}
	}
	
	printf("\nArestas: \n");

	for(i=0; i<vTotal-1; i++){
		printf("(%d, %d)\n", i, prox[i]);
	}
	
	printf("\nCusto: %.2f\n\n", custo);
	
	system("pause");
}

void kruskal(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO DE KRUSKAL
	int i, j, aux=0, prox[vTotal], p=0, tam=((vTotal)*(vTotal+1))/2, aresta[2];
	float custo=0, arestas[tam][3];
	
	for(i=0; i<vTotal; i++){
		prox[i]=-1;
	}
	
	for(i=0; i<vTotal; i++){
		for(j=i; j<vTotal; j++){
			arestas[p][0]=i;
			arestas[p][1]=j;
			arestas[p][2]=grafo[i][j];
			p++;
		}
	}
	
	ordenar(tam, arestas);
	p=vTotal;
	
	while(aux<vTotal-1){
		aresta[0]=arestas[p][0];
		aresta[1]=arestas[p][1];
		p++;
		if((prox[aresta[0]]==-1)&&(prox[aresta[1]]==-1)){
			prox[aresta[0]]=aresta[1];
			aux++;
		}
	}
	
	printf("\nArestas: \n");

	for(i=0; i<vTotal-1; i++){
		printf("(%d, %d)\n", i, prox[i]);
	}
	
	for(i=0; i<vTotal-1; i++){
		custo+=grafo[i][prox[i]];
	}
	
	printf("\nCusto: %.2f\n\n", custo);
	
	system("pause");
}

void prim(int vTotal, float grafo[vTotal][vTotal]){ //FUNÇÃO DO ALGORITMO DE PRIM
	float custos[vTotal], custosFinal[vTotal], custo=0;
	int i, vertices[vTotal], j, ind[vTotal];
	
	for(i=0; i<vTotal; i++){
		custos[i]=1000;
		ind[i]=-1;
		vertices[i]=i;
	}
	
	custos[INICIAL]=0;
	
	while(!vetorVazio(vTotal, vertices)){
		i=menor2(vTotal, custos, vertices);
		custosFinal[i]=custos[i];
		vertices[i]=-1;
		for(j=0; j<vTotal; j++){
			if((grafo[i][j]!=0)&&(grafo[i][j]!=1000)&&(visitado(vTotal, vertices, j))&&(custos[j]>grafo[i][j])){
				ind[j]=i;
				custos[j]=grafo[i][j];
			}
		}
	}
	
	printf("\nPredecessores: ");
	
	for(i=0; i<vTotal; i++){
		printf("%d ", ind[i]);
	}
	
	printf("\nCustos: ");
	
	for(i=0; i<vTotal; i++){
		printf("%.2f ", custosFinal[i]);
		custo+=custosFinal[i];
	}
	
	printf("= %.2f\n\n", custo);
	
	system("pause");
}

void menu2(int op1, int v, float grafo[v][v]){ //MENU PARA ESCOLHER CRITÉRIO DE ORDEM DOS ALGORITMOS BFS E DFS
	int op2;
	
	system("cls");
	
	if(op1==1){
		printf("BFS\n");
	}else{
		printf("DFS\n");
	}
	
	printf("1. Busca por ID (crescente)\n");
	printf("2. Busca por peso (crescente)\n");
	printf("0. Voltar\n");
	printf("Digite uma opção: ");
	scanf("%d", &op2);
	
	switch(op2){
		case 0:
			return;
			break;
		case 1:
			if(op1==1){
				bfsID(v, grafo);
			}else{
				dfsID(v, grafo);
			}
			menu2(op1, v, grafo);
			break;
		case 2:
			if(op1==1){
				bfsPeso(v, grafo);
			}else{
				dfsPeso(v, grafo);
			}
			menu2(op1, v, grafo);
			break;
		default:
			menu2(op1, v, grafo);
			break;
	}
}

void menu3(int v, float grafo[v][v]){ //MENU PARA ESCOLHER ENTRE ALGORITMOS QUE ENCONTRAM MST
	int op;
	
	system("cls");
	printf("Algoritmos para encontrar MST\n");
	printf("1. Genérico\n");
	printf("2. Kruskal\n");
	printf("3. Prim\n");
	printf("0. Sair\n");
	printf("Digite uma opção: ");
	scanf("%d", &op);
	
	switch(op){
		case 0:
			return;
			break;
		case 1:
			generico(v, grafo);
			menu3(v, grafo);
			break;
		case 2:
			kruskal(v, grafo);
			menu3(v, grafo);
			break;
		case 3:
			prim(v, grafo);
			menu3(v, grafo);
			break;
		default:
			menu3(v, grafo);
			break;
	}
}

void menu(){ //MENU GERAL
	int op, v, aux;
	FILE *arq;
	
	arq=fopen("grafo.pag", "r");
	fscanf(arq, "%d", &v);

	
	int v1, v2, i, j;
	float grafo[v][v], x;
	
	for(i=0; i<(v*(v+1))/2; i++){
		fscanf(arq, "%d %d %f\n", &v1, &v2, &x);
		grafo[v1][v2]=x;
		grafo[v2][v1]=x;
	}
	
	
	system("cls");
	printf("Trabalho de Teoria dos Grafos\n");
	printf("1. BFS\n");
	printf("2. DFS\n");
	printf("3. Dijkstra\n");
	printf("4. Floyd-Warshall\n");
	printf("5. Algoritmos para encontrar MST\n");
	printf("0. Sair\n");
	printf("Digite uma opção: ");
	scanf("%d", &op);
	
	switch(op){
		case 0:
			return;
			break;
		case 1:
			menu2(1, v, grafo);
			menu();
			break;
		case 2:
			menu2(2, v, grafo);
			menu();
			break;
		case 3:
			dijkstra(v, grafo);
			menu();
			break;
		case 4:
			floyd(v, grafo);
			menu();
			break;
		case 5:
			menu3(v, grafo);
			menu();
			break;
		default:
			menu();
			break;
	}
}

int main(){
	setlocale(LC_ALL, "");
	system("color F0");
	int jedi=0;
	
	menu();
	
	return jedi;
}
