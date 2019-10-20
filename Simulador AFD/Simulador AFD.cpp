#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

int q, n;

struct estado{
	char nome[3];
	int final, inicial;
};

struct transicao{
	char simbolo;
	int de, para;
};

void nomeEstado(estado afd[]){
	for(int i=0; i<q; i++){
		sprintf(afd[i].nome, "q%d", i);
		afd[i].final=0;
		afd[i].inicial=0;
	}
}

int procura(char aux[], estado afd[]){
	for(int i=0; i<q; i++){
		if (strcmp(aux, afd[i].nome)==0){
			return i;
		}
	}
	return -1;
}

int processaPalavra(char palavra[], estado afd[], transicao tran[]){
	int p;
	for(int i=0; i<q; i++){
		if(afd[i].final==1){
			p=i;
			break;
		}
	}
	
	for(int i=0; i<strlen(palavra); i++){
		if(palavra[i]==tran[p*n].simbolo){
			p=tran[p*n].para;
		}else{
			if(palavra[i]==tran[(p*n)+1].simbolo){
				p=tran[(p*n)+1].para;
			}
		}
	}
	
	if(afd[p].final==1){
		printf("\nPalavra aceita.\n");
	}else{
		printf("\nPalavra rejeitada.\n");
	}
}

int verificaPalavra(char palavra[], char alfabeto[]){
	int x=0;
	for(int i=0; i<strlen(palavra); i++){
		for(int j=0; j<n; j++){
			if(palavra[i]==alfabeto[j]){
				x++;
			}
		}
	}
	if(x==strlen(palavra)){
		return 1;
	}else{
		return 0;
	}
}

void menu(){
	int f, aux2, op=0;
	char aux[3], palavra[50];
	
	system("cls");
	
	printf("Digite o número de estados do AFD: ");
	scanf("%d", &q);
	
	printf("\nDigite quantos símbolos possui o alfabeto do AFD: ");
	scanf("%d", &n);
	
	char alfabeto[n];
	struct estado afd[q];
	struct transicao tran[q*n];
	
	system("cls");
	
	for(int i=0; i<n; i++){
		fflush(stdin);
		printf("Digite o %dº símbolo do alfabeto: ", i+1);
		scanf("%c", &alfabeto[i]);
	}
	
	nomeEstado(afd);
	
	system("cls");
	
	for(int i=0; i<q; i++){
		for(int j=0; j<n; j++){
			do{
				fflush(stdin);
				printf("%s, %c -> ", afd[i].nome, alfabeto[j]);
				gets(aux);
				aux2=procura(aux, afd);
				if(aux2==-1){
					printf("\nEstado inexistente. Tente novamente.\n");
					system("pause");
					printf("\n");
				}
			}while(aux2==-1);
			if (j%n==0){
				tran[i*n].de=i;
				tran[i*n].para=procura(aux, afd);
				tran[i*n].simbolo=alfabeto[j];
			}else{
				tran[(i*n)+j%n].de=i;
				tran[(i*n)+j%n].para=procura(aux, afd);
				tran[(i*n)+j%n].simbolo=alfabeto[j];
			}
		}
	}
	
	system("cls");
	
	do{
		printf("Digite o nome do estado inicial: ");
		gets(aux);
		aux2=procura(aux, afd);
		if(aux2==-1){
			printf("\nEstado inexistente. Tente novamente.\n");
			system("pause");
			printf("\n");
		}
	}while(aux2==-1);
	
	afd[aux2].inicial=1;
	
	do{
		printf("\nDigite o número de estados finais: ");
		scanf("%d", &f);
		if(f>q){
			printf("\nNúmero de estados finais não pode ser maior que número total de estados.");
		}
	}while(f>q);
	
	for(int i=0; i<f; i++){
		do{
			fflush(stdin);
			printf("\nDigite o nome do %dº estado final: ", i+1);
			gets(aux);
			aux2=procura(aux, afd);
			if(aux2==-1){
				printf("\nEstado inexistente. Tente novamente.\n");
				system("pause");
				printf("\n");
			}
		}while(aux2==-1);
		afd[aux2].final=1;
	}
	
	system("cls");
	
	printf("Alfabeto: ");
	
	for(int i=0; i<n; i++){
		printf("%c ", alfabeto[i]);
	}
	
	for(int i=0; i<q*n; i++){
		if((afd[tran[i].de].final==1)&&(afd[tran[i].de].inicial==1)){
			printf("\n*->%s, %c -> %s", afd[tran[i].de].nome, tran[i].simbolo, afd[tran[i].para].nome);
		}
		if((afd[tran[i].de].final==1)&&(afd[tran[i].de].inicial==0)){
			printf("\n  *%s, %c -> %s", afd[tran[i].de].nome, tran[i].simbolo, afd[tran[i].para].nome);
		}
		if((afd[tran[i].de].final==0)&&(afd[tran[i].de].inicial==1)){
			printf("\n ->%s, %c -> %s", afd[tran[i].de].nome, tran[i].simbolo, afd[tran[i].para].nome);
		}
		if((afd[tran[i].de].final==0)&&(afd[tran[i].de].inicial==0)){
			printf("\n   %s, %c -> %s", afd[tran[i].de].nome, tran[i].simbolo, afd[tran[i].para].nome);
		}
	}
	
	while(op==0){
		do{
			fflush(stdin);
			printf("\n\nDigite uma palavra utilizando o alfabeto do AFD (max=50): ");
			gets(palavra);
			aux2=verificaPalavra(palavra, alfabeto);
			if(aux2==0){
				printf("\nPalavra inválida. Tente novamente.\n");
				system("pause");
				printf("\n");
			}
		}while(aux2==0);
		processaPalavra(palavra, afd, tran);
		printf("\nDigite 0 para tentar outra palavra ou 1 para criar outro afd: ");
		scanf("%d", &op);
	}
	
	if(op==1){
		menu();
	}
}

int main(){
	setlocale(LC_ALL, "");
	system("color F0");
	
	int jedi=0;
	
	menu();
	
	return jedi;
}
