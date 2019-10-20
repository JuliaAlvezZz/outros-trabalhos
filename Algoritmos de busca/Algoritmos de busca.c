#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#define V 250000
#define N 100000
#define INTMAX 1000000

//INICIO STRUCT DOS CLIENTES
typedef struct TipoCliente{
	long int codigo;
	char nome[50];
	int conta;
	double saldo;
}TipoCliente;
//FIM STRUCT DOS CLIENTES

//INICIO FUNÇÃO QUE GERA SAIDA.TXT
void gerarSaida(int x, double tempoS, double tempoB){
	FILE *saida;
	
	saida=fopen("saida.txt", "a");
	
	switch(x){
		case 0:
			fprintf(saida, "\nAnálise: Busca Sequencial x Busca Binária + Bubble Sort:\nQuantidade de chaves buscadas: %d\nTempo Busca Sequencial: %lf s\nTempo Busca Binária: %lf s\n", V, tempoS, tempoB);
			break;
		case 1:
			fprintf(saida, "\nAnálise: Busca Sequencial x Busca Binária + Insertion Sort:\nQuantidade de chaves buscadas: %d\nTempo Busca Sequencial: %lf s\nTempo Busca Binária: %lf s\n", V, tempoS, tempoB);
			break;
		case 2:
			fprintf(saida, "\nAnálise: Busca Sequencial x Busca Binária + Selection Sort:\nQuantidade de chaves buscadas: %d\nTempo Busca Sequencial: %lf s\nTempo Busca Binária: %lf s\n", V, tempoS, tempoB);
			break;
		case 3:
			fprintf(saida, "\nAnálise: Busca Sequencial x Busca Binária + Shell Sort:\nQuantidade de chaves buscadas: %d\nTempo Busca Sequencial: %lf s\nTempo Busca Binária: %lf s\n", V, tempoS, tempoB);
			break;
		case 4:
			fprintf(saida, "\nAnálise: Busca Sequencial x Busca Binária + Merge Sort:\nQuantidade de chaves buscadas: %d\nTempo Busca Sequencial: %lf s\nTempo Busca Binária: %lf s\n", V, tempoS, tempoB);
			break;
		case 5:
			fprintf(saida, "\nAnálise: Busca Sequencial x Busca Binária + Heap Sort:\nQuantidade de chaves buscadas: %d\nTempo Busca Sequencial: %lf s\nTempo Busca Binária: %lf s\n", V, tempoS, tempoB);
			break;
		case 6:
			fprintf(saida, "\nAnálise: Busca Sequencial x Busca Binária + Quick Sort:\nQuantidade de chaves buscadas: %d\nTempo Busca Sequencial: %lf s\nTempo Busca Binária: %lf s\n", V, tempoS, tempoB);
			break;
	}
	
	fclose(saida);
}
//FIM FUNÇÃO QUE GERA SAIDA.TXT

//INICIO BUSCA BINARIA
int buscaBinaria(TipoCliente *clientes, long int chave){
	int direita=N-1, esquerda=0, meio, encontrado=0;
	
	while ((esquerda<=direita)&&(!encontrado)){
		meio=(esquerda+direita)/2;
		if (clientes[meio].codigo==chave) encontrado=1;
		else if (chave<clientes[meio].codigo) direita=meio-1;
		else esquerda=meio+1;
	}
	
	return meio;
}
//FIM BUSCA BINARIA

//INICIO FUNÇÃO QUE TROCA DUAS POSIÇÕES NO VETOR DE STRUCT
void troca(TipoCliente *clientes, int p, int q){
	long int codigoAux;
	char nomeAux[50];
	int contaAux;
	double saldoAux;
	
	codigoAux=clientes[p].codigo;
	contaAux=clientes[p].conta;
	saldoAux=clientes[p].saldo;
	strcpy(nomeAux, clientes[p].nome);
	
	clientes[p].codigo=clientes[q].codigo;
	clientes[p].conta=clientes[q].conta;
	clientes[p].saldo=clientes[q].saldo;
	strcpy(clientes[p].nome, clientes[q].nome);
	
	clientes[q].codigo=codigoAux;
	clientes[q].conta=contaAux;
	clientes[q].saldo=saldoAux;
	strcpy(clientes[q].nome, nomeAux);
}
//FIM FUNÇÃO DE TROCA

//INICIO BUBBLE SORT
void bubbleSort(TipoCliente *clientes){
	int aux, topo, bolha;
	
	for (topo=1; topo<N; topo++){
		for (bolha=N-1; bolha>=topo; bolha--){
			if (clientes[bolha].codigo<clientes[bolha-1].codigo){
				troca(clientes, bolha, bolha-1);
			}
		}
	}
}
//FIM BUBBLE SORT

//INICIO INSERTION SORT
void insertionSort(TipoCliente *clientes){
	int i, p, conta;
	long int cod;
	double saldo;
	char nome[50];
	
	for (p=1; p<N; p++){
		cod=clientes[p].codigo;
		conta=clientes[p].conta;
		saldo=clientes[p].saldo;
		strcpy(nome, clientes[p].nome);
		i=p-1;
		while (i>=0 && clientes[i].codigo>cod){
			clientes[i+1].codigo=clientes[i].codigo;
			clientes[i+1].conta=clientes[i].conta;
			clientes[i+1].saldo=clientes[i].saldo;
			strcpy(clientes[i+1].nome, clientes[i].nome);
			i--;
		}
		clientes[i+1].codigo=cod;
		clientes[i+1].conta=conta;
		clientes[i+1].saldo=saldo;
		strcpy(clientes[i+1].nome, nome);
	}
}
//FIM INSERTION SORT

//INICIO SELECTION SORT
void selectionSort(TipoCliente *clientes){
	int aux, i, p, j;
	long int menorChave;
	
	for (p=0; p<N-1; p++){
		menorChave=clientes[p].codigo;
		i=p;
		for (j=p+1; j<N; j++){
			if (clientes[j].codigo<menorChave){
				menorChave=clientes[j].codigo;
				i=j;
			}
		}
		troca(clientes, p, i);
	}
}
//FIM SELECTION SORT

//INICIO SHELL SORT
void shellSort(TipoCliente *clientes){
	int k=3, h=1, j, i, conta;
	long int cod;
	double saldo;
	char nome[50];
	
	while (h<=N) h=k*h+1;
	while (h!=1){
		h=h/k;
		for (i=h; i<N; i++){
			cod=clientes[i].codigo;
			conta=clientes[i].conta;
			saldo=clientes[i].saldo;
			strcpy(nome, clientes[i].nome);
			j=i-h;
			while (j>=0 && cod<clientes[j].codigo){
				clientes[j+h].codigo=clientes[j].codigo;
				clientes[j+h].conta=clientes[j].conta;
				clientes[j+h].saldo=clientes[j].saldo;
				strcpy(clientes[j+h].nome, clientes[j].nome);
				j=j-h;
			}
			clientes[j+h].codigo=cod;
			clientes[j+h].conta=conta;
			clientes[j+h].saldo=saldo;
			strcpy(clientes[j+h].nome, nome);
		}
	}
}
//FIM SHELL SORT

//INICIO MERGE SORT
void merge(TipoCliente *subvet, int p, int q, int r){
	int i, j, k, n1=q-p+1, n2=r-q;
	TipoCliente *E, *D;
	
	E=(TipoCliente*)malloc(sizeof(TipoCliente)*(n1+1));
	D=(TipoCliente*)malloc(sizeof(TipoCliente)*(n2+1));
	
	
	for (i=0; i<n1; i++){
		E[i].codigo=subvet[p+i].codigo;
		E[i].conta=subvet[p+i].conta;
		E[i].saldo=subvet[p+i].saldo;
		strcpy(E[i].nome, subvet[p+i].nome);
	}
	
	for (i=0; i<n2; i++){
		D[i].codigo=subvet[q+i+1].codigo;
		D[i].conta=subvet[q+i+1].conta;
		D[i].saldo=subvet[q+1+i].saldo;
		strcpy(E[i].nome, subvet[q+i+1].nome);
	}
	
	E[n1].codigo=INTMAX;
	D[n2].codigo=INTMAX;
	i=j=0;
	
	for (k=p; k<=r; k++){
		if (E[i].codigo<=D[j].codigo){
			subvet[k].codigo=E[i].codigo;
			subvet[k].conta=E[i].conta;
			subvet[k].saldo=E[i].saldo;
			strcpy(subvet[k].nome, E[i].nome);
			i++;
		}else{
			subvet[k].codigo=D[j].codigo;
			subvet[k].conta=D[j].conta;
			subvet[k].saldo=D[j].saldo;
			strcpy(subvet[k].nome, D[j].nome);
			j++;
		}
	}
}

void mergeSort(TipoCliente *clientes, int p, int r){
	int q;

	if (p<r){
		q=(p+r)/2;
		mergeSort(clientes, p, q);
		mergeSort(clientes, q+1, r);
		merge(clientes, p, q, r);
	}
}

//FIM MERGE SORT

//INICIO HEAP SORT
void criaHeap(TipoCliente *clientes, int i, int f){
	int j=i*2+1, conta;
	long int cod;
	double saldo;
	char nome[50];
	
	cod=clientes[i].codigo;
	conta=clientes[i].conta;
	saldo=clientes[i].saldo;
	strcpy(nome, clientes[i].nome);
	
	while (j<=f){
		if (j<f)
			if (clientes[j].codigo<clientes[j+1].codigo) j++;
		if (cod<clientes[j].codigo){
			clientes[i].codigo=clientes[j].codigo;
			clientes[i].conta=clientes[j].conta;
			clientes[i].saldo=clientes[j].saldo;
			strcpy(clientes[i].nome, clientes[j].nome);
			i=j;
			j=i*2+1;
		}else j=f+1;
	}
	clientes[i].codigo=cod;
	clientes[i].conta=conta;
	clientes[i].saldo=saldo;
	strcpy(clientes[i].nome, nome);
}

void heapSort(TipoCliente *clientes){
	int aux, i;
	
	for (i=(N-1)/2; i>=0; i--)
		criaHeap(clientes, i, N-1);
	for (i=N-1; i>=1; i--){
		troca(clientes, 0, i);
		criaHeap(clientes, 0, i-1);
	}
}
//FIM HEAP SORT

//INICIO QUICK SORT
int particiona(TipoCliente *clientes, int i, int f){
	int esq=i, dir=f, pivoConta=clientes[i].conta;
	long int pivoCod=clientes[i].codigo;
	double pivoSaldo=clientes[i].saldo;
	char pivoNome[50];
	
	strcpy(pivoNome, clientes[i].nome);
	
	while (esq<dir){
		while (clientes[esq].codigo<=pivoCod) esq++;
		while (clientes[dir].codigo>pivoCod) dir--;
		if (esq<dir){
			troca(clientes, esq, dir);
		}
	}
	
	clientes[i].codigo=clientes[dir].codigo;
	clientes[i].conta=clientes[dir].conta;
	clientes[i].saldo=clientes[dir].saldo;
	strcpy(clientes[i].nome, clientes[dir].nome);
	
	clientes[dir].codigo=pivoCod;
	clientes[dir].conta=pivoConta;
	clientes[dir].saldo=pivoSaldo;
	strcpy(clientes[dir].nome, pivoNome);
	
	return dir;
}

void quickSort(TipoCliente *clientes, long int i, long int f){
	long int pivo=0;
	
	if (f>i){
		pivo=particiona(clientes, i, f);
		quickSort(clientes, i, pivo-1);
		quickSort(clientes, pivo+1, f);
	}
}
//FIM QUICK SORT

//INICIO BUSCA SEQUENCIAL
int buscaSequencial(TipoCliente *clientes, long int chave){
	int i=0, encontrado=0;
	
	while ((i<N)&&(!encontrado)){
		if (clientes[i].codigo==chave) encontrado=1;
		else i++;
	}
	
	if (!encontrado){
		return -1;
	}else{
		return i;
	}
}
//FIM BUSCA SEQUENCIAL

//INICIO FUNÇÃO QUE VERIFICA REPETIÇÃO NO VETOR DE STRUCT OU BUSCA
int repeticao(long int *vet, long int chave, int x){
	int i=0, encontrado=0, t;
	long int aux;
	
	if (x==0){
		t=N;
	}else{
		t=V;
	}
	
	while ((i<t)&&(!encontrado)){
		if (vet[i]==chave) encontrado=1;
		else i++;
	}
	
	if (!encontrado){
		return -1;
	}
	
	return 0;
}
//FIM FUNÇÃO QUE VERIFICA REPETIÇÃO

//INICIO FUNÇÃO QUE GERA VETOR DE BUSCA
void gerarVetorBusca(long int *vet){
	int i, aux;
	
	srand(time(NULL));
	
	for (i=0; i<V; i++){
		aux=rand()%30000+rand()%30000+rand()%30000+1;
		while (repeticao(vet, aux, 1)!=-1){
			aux+=rand()%30000+1;
		}
		vet[i]=aux;
	}
}
//FIM FUNÇÃO QUE GERA VETOR DE BUSCA

//INICIO FUNÇÃO QUE COPIA CONTEÚDO DE UM VETOR DE STRUCT PRA OUTRO
void copiarStruct(TipoCliente *clientes, TipoCliente *aux){
	int i;
	
	for (i=0; i<N; i++){
		aux[i].codigo=clientes[i].codigo;
		aux[i].conta=clientes[i].conta;
		aux[i].saldo=clientes[i].saldo;
		strcpy(aux[i].nome, clientes[i].nome);
	}
}
//FIM FUNÇÃO DE CÓPIA

//INICIO FUNÇÃO QUE REALIZA TODAS AS BUSCAS
int buscas(TipoCliente *clientes, long int *vet, int x, double *tempoTS){
	int i;
	TipoCliente *aux;
	double tempoI, tempoF, tempoTB;
	
	aux=(TipoCliente*)malloc(sizeof(TipoCliente)*N);
	
	copiarStruct(clientes, aux);
	
	switch(x){
		case 0:
			printf("\n\nUtilizando Bubble Sort...");
			tempoI=clock();
			bubbleSort(aux);
			for (i=0; i<V; i++){
				buscaBinaria(aux, vet[i]);
			}
			tempoF=clock();
			tempoTB=(tempoF-tempoI)/CLOCKS_PER_SEC;
			gerarSaida(x, *tempoTS, tempoTB);
			system("cls");
			printf("Bubble Sort + Busca Binária pronto.");
			return 1;
			break;
		case 1:
			printf("\n\nUtilizando Insertion Sort...");
			tempoI=clock();
			insertionSort(aux);
			for (i=0; i<V; i++){
				buscaBinaria(aux, vet[i]);
			}
			tempoF=clock();
			tempoTB=(tempoF-tempoI)/CLOCKS_PER_SEC;
			system("cls");
			printf("Insertion Sort + Busca Binária pronto.");
			gerarSaida(x, *tempoTS, tempoTB);
			return 2;
			break;
		case 2:
			printf("\n\nUtilizando Selection Sort...");
			tempoI=clock();
			selectionSort(aux);
			for (i=0; i<V; i++){
				buscaBinaria(aux, vet[i]);
			}
			tempoF=clock();
			tempoTB=(tempoF-tempoI)/CLOCKS_PER_SEC;
			system("cls");
			printf("Selection Sort + Busca Binária pronto.");
			gerarSaida(x, *tempoTS, tempoTB);
			return 3;
			break;
		case 3:
			printf("\n\nUtilizando Shell Sort...");
			tempoI=clock();
			shellSort(aux);
			for (i=0; i<V; i++){
				buscaBinaria(aux, vet[i]);
			}
			tempoF=clock();
			tempoTB=(tempoF-tempoI)/CLOCKS_PER_SEC;
			system("cls");
			printf("Shell Sort + Busca Binária pronto.");
			gerarSaida(x, *tempoTS, tempoTB);
			return 4;
			break;
		case 4:
			printf("\n\nUtilizando Merge Sort...");
			tempoI=clock();
			mergeSort(aux, 0, N-1);
			for (i=0; i<V; i++){
				buscaBinaria(aux, vet[i]);
			}
			tempoF=clock();
			tempoTB=(tempoF-tempoI)/CLOCKS_PER_SEC;
			system("cls");
			printf("Merge Sort + Busca Binária pronto.");
			gerarSaida(x, *tempoTS, tempoTB);
			return 5;
			break;
		case 5:
			printf("\n\nUtilizando Heap Sort...");
			tempoI=clock();
			heapSort(aux);
			for (i=0; i<V; i++){
				buscaBinaria(aux, vet[i]);
			}
			tempoF=clock();
			tempoTB=(tempoF-tempoI)/CLOCKS_PER_SEC;
			system("cls");
			printf("Heap Sort + Busca Binária pronto.");
			gerarSaida(x, *tempoTS, tempoTB);
			printf("\n\nTerminado.");
			return -1;
			break;
		case 6:
			printf("\n\nUtilizando Quick Sort...");
			tempoI=clock();
			quickSort(aux, 0, N-1);
			for (i=0; i<V; i++){
				buscaBinaria(aux, vet[i]);
			}
			tempoF=clock();
			tempoTB=(tempoF-tempoI)/CLOCKS_PER_SEC;
			system("cls");
			printf("Quick Sort + Busca Binária pronto.");
			gerarSaida(x, *tempoTS, tempoTB);
			return -1;
			break;
		case 7:
			system("cls");
			printf("Realizando busca sequencial...");
			tempoI=clock();
			for (i=0; i<V; i++){
				buscaSequencial(clientes, vet[i]);
			}
			tempoF=clock();
			*tempoTS=(tempoF-tempoI)/CLOCKS_PER_SEC;
			system("cls");
			printf("Busca sequencial pronto.");
			return 0;
			break;
	}
}
//FIM FUNÇÃO DE BUSCAS

//INICIO FUNÇÃO QUE CRIA VETOR DE STRUCT PELO ARQUIVO
void gerarStruct(){
	FILE *entrada;
	TipoCliente *clientes;
	long int i, *vet;
	double tempoTS;
	int x;
	
	clientes=(TipoCliente*)malloc(sizeof(TipoCliente)*N);
	vet=(long int*)malloc(sizeof(long int)*V);
	
	entrada=fopen("entrada.dat", "r");
	
	if (entrada==NULL){
		printf("Erro ao abrir arquivo.");
		return;
	}
	long int p;
	for (i=0; i<N; i++){
		fscanf(entrada, "%li %li %s %d %lf\n", &p, &clientes[i].codigo, &clientes[i].nome, &clientes[i].conta, &clientes[i].saldo);
	}
	
	system("cls");
	printf("Gerando vetor de busca...");
	
	gerarVetorBusca(vet);
	
	x=buscas(clientes, vet, 7, &tempoTS);
	
	buscas(clientes, vet, 6, &tempoTS);
	
	while (x!=-1){
		x=buscas(clientes, vet, x, &tempoTS);
	}
}
//FIM FUNÇÃO QUE CRIA VETOR DE STRUCT

//INICIO CRIAR ARQUIVO COM CLIENTES
void gerarRegistro(){
	FILE *entrada;
	int conta;
	double saldo;
	char nome[50];
	long int i, aux, codigo, *vet;
	
	printf("Gerando arquivo de entrada...");
	
	vet=(long int*)malloc(sizeof(long int)*N);
	
	if (entrada=fopen("entrada.dat", "r")){
		return;
	}
	
	entrada=fopen("entrada.dat", "w");
	
	srand(time(NULL));
	
	for (i=0; i<N; i++){
		aux=rand()%30000+rand()%30000+rand()%30000+1;
		while (repeticao(vet, aux, 0)!=-1){
			aux+=rand()%30000+1;
		}
		vet[i]=aux;
		codigo=aux;
		conta=rand()%100000+1;
		saldo=rand()%20000-10000;
		sprintf(nome, "Cliente%c", rand()%26+65);
		fprintf(entrada, " %li %li %s %d %.2lf\n", i, codigo, nome, conta, saldo);
	}
}
//FIM CRIAR ARQUIVO COM CLIENTES

int main(){
	setlocale(LC_ALL, "");
	gerarRegistro();
	gerarStruct();
	return 0;
}
