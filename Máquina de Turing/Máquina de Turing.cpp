#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

int q, n;

struct transicao{ //struct para cada transição
	char ler, escrever, dir;
	int de, para;
};

struct estado{ //struct para cada estado, contendo a transição a partir de cada um
	char nome[4];
	int final, inicial, qtdT;
	struct transicao tran[10]; //número de transições é n+3 pq além dos símbolos do alfabeto tem #, * e _
};

struct fitaMT{ //struct para cada posição da fita
	char simbolo;
	int cab;
};

void nomeEstado(estado mt[]){ //dar nome para estados (q0, q1...)
	for(int i=0; i<q; i++){
		sprintf(mt[i].nome, "q%d", i);
		mt[i].final=0;
		mt[i].inicial=0;
	}
}

int procura(char aux[], estado mt[]){ //retorna a posição de um estado e caso não exista retorna -1
	for(int i=0; i<q; i++){
		if (strcmp(aux, mt[i].nome)==0){
			return i;
		}
	}
	return -1;
}

void processaPalavra(fitaMT fita[], estado mt[]){ //realiza o reconhecimento da palavra
	int p=50, est, fin;
	
	system("cls");
	
	for (int i=0; i<q; i++){ //pega o estado inicial
		if (mt[i].inicial==1){
			est=i;
			break;
		}
	}
	
	while (fin!=-1){
		if (mt[est].qtdT==0){ //se o estado não tiver transição a execução só é feita mais uma vez
			fin=-1;
		}
		fita[p].cab=1;
		printf("\n");
		for (int i=40; i<80; i++){
			printf("%c", fita[i].simbolo);
		}
		printf("\n");
		for (int i=40; i<80; i++){
			if (i==p){
				printf("%c", '^');
			}else{
				printf(" ");
			}
		}
		for (int i=0; i<mt[est].qtdT; i++){
			if (mt[est].tran[i].ler==fita[p].simbolo){
				fita[p].simbolo=mt[est].tran[i].escrever;
				fita[p].cab=0;
				if (mt[est].tran[i].dir=='>'){
					p++;
				}else{
					p--;
				}
				est=mt[est].tran[i].para;
				break;
			}
		}
	}
	printf("\n");
	system("pause");
}

int verificaPalavra(char palavra[], char alfabeto[]){ //verifica se a palavra contém caracteres do alfabeto, começa com # e termina com *
	int x=0;
	for(int i=0; i<strlen(palavra); i++){
		for(int j=0; j<n+3; j++){
			if(palavra[i]==alfabeto[j]){
				x++;
			}
		}
	}
	if(x==strlen(palavra)&&palavra[0]=='#'&&palavra[strlen(palavra)-1]=='*'){
		return 1;
	}else{
		return 0;
	}
}

void mostraAlgoritmo(estado mt[]){ //mostra transições do algoritmo
	system("cls");
	printf("--- MÁQUINA DE TURING ---\n\n");
	for (int i=0; i<q; i++){
		for (int j=0; j<mt[i].qtdT; j++){
			if (mt[i].inicial==0 && mt[i].final==0){
				printf("   %s, %c, %c, %c -> %s\n", mt[i].nome, mt[i].tran[j].ler, mt[i].tran[j].escrever, mt[i].tran[j].dir, mt[mt[i].tran[j].para].nome, mt[i].qtdT);
			}
			if (mt[i].inicial==1 && mt[i].final==0){
				printf(" ->%s, %c, %c, %c -> %s\n", mt[i].nome, mt[i].tran[j].ler, mt[i].tran[j].escrever, mt[i].tran[j].dir, mt[mt[i].tran[j].para].nome, mt[i].qtdT);
			}
			if (mt[i].inicial==0 && mt[i].final==1){
				printf("  *%s, %c, %c, %c -> %s\n", mt[i].nome, mt[i].tran[j].ler, mt[i].tran[j].escrever, mt[i].tran[j].dir, mt[mt[i].tran[j].para].nome, mt[i].qtdT);
			}
			if (mt[i].inicial==1 && mt[i].final==1){
				printf("*->%s, %c, %c, %c -> %s\n", mt[i].nome, mt[i].tran[j].ler, mt[i].tran[j].escrever, mt[i].tran[j].dir, mt[mt[i].tran[j].para].nome, mt[i].qtdT);
			}
		}
	}
}

void menu(){
	struct fitaMT fita[150];
	char fitaAux[150], palavra[50], aux[4], input[]="input.txt", de[4], para[4];
	int x;
	FILE *arq;
	
	arq=fopen(input, "r");
	
	system("cls");
	
	printf("--- MÁQUINA DE TURING ---\n\n");
	
	fscanf(arq, "%d\n", &q);
	fscanf(arq, "%d\n", &n);
	
	struct estado mt[q];
	char alfabeto[n+3];
	
	nomeEstado(mt);
	
	alfabeto[0]='#';
	alfabeto[1]='*';
	alfabeto[2]='_';
	
	for (int i=0; i<n; i++){
		fscanf(arq, "%c\n", &alfabeto[i+3]);
	}
	
	for (int i=0; i<q; i++){
		if (i<q-1) fscanf(arq, "%d ", &mt[i].qtdT);
		else fscanf(arq, "%d\n", &mt[i].qtdT);
	}
	
	for (int i=0; i<q; i++){
		for (int j=0; j<mt[i].qtdT; j++){
			fscanf(arq, "%s %c %c %c %s\n", &de, &mt[i].tran[j].ler, &mt[i].tran[j].escrever, &mt[i].tran[j].dir, &para);
			mt[i].tran[j].de=procura(de, mt);
			mt[i].tran[j].para=procura(para, mt);
			printf("%s %c %c %c %s\n", mt[i].nome, mt[i].tran[j].ler, mt[i].tran[j].escrever, mt[i].tran[j].dir, mt[mt[i].tran[j].para].nome);
		}
	}
	
	fscanf(arq, "%s\n", &aux);
	x=procura(aux, mt);
	
	mt[x].inicial=1;
	
	fscanf(arq, "%d", &x);
	
	for (int i=0; i<x; i++){
		fscanf(arq, "%s", &aux);
		int y=procura(aux, mt);
		mt[y].final=1;
	}
	
	mostraAlgoritmo(mt);
	
	do{
		fflush(stdin);
		printf("\nDigite uma palavra (iniciando com # e terminando com *): ");
		gets(palavra);
	}while (verificaPalavra(palavra, alfabeto)==0);
	
	for (int i=0; i<100; i++){
		if ((i<50) || (i>=50+strlen(palavra))) fitaAux[i]='_';
		else fitaAux[i]=palavra[i-50];
	}
	
	for (int i=0; i<150; i++){
		fita[i].simbolo=fitaAux[i];
		fita[i].cab=0;
	}
	
	processaPalavra(fita, mt);
	
	while (x!=2){
		printf("\n\nDigite 1 para dar uma entrada, 2 para alterar a máquina ou 0 para sair: ");
		scanf("%d", &x);
		if (x==1){
			do{
				fflush(stdin);
				printf("\nDigite uma palavra (iniciando com # e terminando com *): ");
				gets(fitaAux);
			}while (verificaPalavra(fitaAux, alfabeto)==0);
			
			for (int i=strlen(fitaAux); i<100; i++){
				fitaAux[i]='_';
			}
			
			for (int i=0; i<100; i++){
				fita[i].simbolo=fitaAux[i];
				fita[i].cab=0;
			}
			
			processaPalavra(fita, mt);
		}
		if (x==2){
			break;
		}
		if (x==0){
			exit(0);
		}
	}
	
	menu();
}

int main(){
	setlocale(LC_ALL, "");
	system("color F0");
	
	int jedi=0;
	
	menu();
	
	return jedi;
}
