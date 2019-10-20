#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <conio.h>

#define MAXTAM 1000
typedef int TipoApontador;

typedef struct TipoItem{
	int cod;
	float valor;
	int op;
}TipoItem;

typedef struct{
	TipoApontador frente;
	TipoApontador tras;
	int tamanho;
	TipoItem item[MAXTAM];
}TipoFila;

typedef struct{
	int clientesAtendidos;
	float valorSaque;
	float valorDeposito;
	float valorPagamento;
}TipoCaixa;

void CVazio(TipoCaixa *caixa){
	caixa->clientesAtendidos=0;
	caixa->valorDeposito=0;
	caixa->valorPagamento=0;
	caixa->valorSaque=0;
}

void FVazia(TipoFila *fila){
	fila->frente=1;
	fila->tras=fila->frente;
	fila->tamanho=0;
}

int vazia(TipoFila fila){
	return (fila.frente==fila.tras);
}

int vazio(TipoCaixa caixa){
	return (caixa.clientesAtendidos==0);
}

void enfileirar(TipoFila *fila1, TipoFila *fila2, TipoFila *fila3, TipoItem item){
	if (fila1->tamanho < fila2->tamanho&&fila1->tamanho < fila3->tamanho){
		fila1->item[fila1->tras-1]=item;
		fila1->tras=fila1->tras%MAXTAM+1;
		fila1->tamanho++;
		return;
	}else{
			if (fila2->tamanho < fila1->tamanho&&fila2->tamanho < fila3->tamanho){
			fila2->item[fila2->tras-1]=item;
			fila2->tras=fila2->tras%MAXTAM+1;
			fila2->tamanho++;
			return;
		}else{
			if (fila3->tamanho < fila1->tamanho&&fila3->tamanho < fila2->tamanho){
				fila3->item[fila3->tras-1]=item;
				fila3->tras=fila3->tras%MAXTAM+1;
				fila3->tamanho++;
				return;
			}else{
				if (fila1->tamanho==fila2->tamanho&&fila1->tamanho==fila3->tamanho){
					fila1->item[fila1->tras-1]=item;
					fila1->tras=fila1->tras%MAXTAM+1;
					fila1->tamanho++;
					return;
				}else{
					if (fila1->tamanho>=fila2->tamanho&&fila2->tamanho==fila3->tamanho){
						fila2->item[fila2->tras-1]=item;
						fila2->tras=fila2->tras%MAXTAM+1;
						fila2->tamanho++;
						return;
					}else{
						if (fila2->tamanho>=fila1->tamanho&&fila1->tamanho==fila3->tamanho){
							fila1->item[fila1->tras-1]=item;
							fila1->tras=fila1->tras%MAXTAM+1;
							fila1->tamanho++;
							return;
						}else{
							if (fila3->tamanho>=fila1->tamanho&&fila1->tamanho==fila2->tamanho){
								fila1->item[fila1->tras-1]=item;
								fila1->tras=fila1->tras%MAXTAM+1;
								fila1->tamanho++;
								return;
							}
						}
					}
				}
			}
		}
	}
}

void caixa(TipoCaixa *caixa1, TipoCaixa *caixa2, TipoCaixa *caixa3, TipoItem cliente, int n){
	if (n==1){
		caixa1->clientesAtendidos++;
		if (cliente.op==0){
			caixa1->valorSaque+=cliente.valor;
		}else{
			if (cliente.op==1){
				caixa1->valorDeposito+=cliente.valor;
			}else{
				if (cliente.op==2){
					caixa1->valorPagamento+=cliente.valor;
				}
			}
		}
	}else{
		if (n==2){
			caixa2->clientesAtendidos++;
			if (cliente.op==0){
				caixa2->valorSaque+=cliente.valor;
			}else{
				if (cliente.op==1){
					caixa2->valorDeposito+=cliente.valor;
				}else{
					if (cliente.op==2){
						caixa2->valorPagamento+=cliente.valor;
					}
				}
			}
		}else{
			if (n==3){
				caixa3->clientesAtendidos++;
				if (cliente.op==0){
					caixa3->valorSaque+=cliente.valor;
				}else{
					if (cliente.op==1){
						caixa3->valorDeposito+=cliente.valor;
					}else{
						if (cliente.op==2){
							caixa3->valorPagamento+=cliente.valor;
						}
					}
				}
			}
		}
	}
}

void desenfileirar(TipoFila *fila, TipoItem *item){
	if (vazia(*fila)){
		return;
	}else{
		*item=fila->item[fila->frente-1];
		fila->frente=fila->frente%MAXTAM+1;
		fila->tamanho--;
	}
}

int main(){
	setlocale(LC_ALL, "");
	system("color F0");
	TipoCaixa caixa1, caixa2, caixa3;
	TipoFila fila1, fila2, fila3;
	TipoItem cliente;
	int cont=0, clientes=1, i, n, j=0, tempo=20; 
	
	srand(time(NULL));
	
	CVazio(&caixa1);
	CVazio(&caixa2);
	CVazio(&caixa3);
	
	FVazia(&fila1);
	FVazia(&fila2);
	FVazia(&fila3);
	
	for (i=0; i<clientes; i++){
		if (i==clientes-1){
			j=i;
		}
		cliente.cod=i+j;
		cliente.op=rand()%3;
		cliente.valor=rand()%10000+1;
		enfileirar(&fila1, &fila2, &fila3, cliente);
	}
	
	while (!vazia(fila1)||!vazia(fila2)||!vazia(fila3)){
		if (clientes==1){
			desenfileirar(&fila1, &cliente);
		}
		while (cont<tempo){	
			clientes=rand()%31;
			for (i=0; i<clientes; i++){
				if (i==clientes-1){
					j=i;
				}
				cliente.cod=i+j;
				cliente.op=rand()%3;
				cliente.valor=rand()%10000+1;
				enfileirar(&fila1, &fila2, &fila3, cliente);
			}
			if (!vazia(fila1)){
				n=1;
				desenfileirar(&fila1, &cliente);
				caixa(&caixa1, &caixa2, &caixa3, cliente, n);
			}
			if (!vazia(fila2)){
				n=2;
				desenfileirar(&fila2, &cliente);
				caixa(&caixa1, &caixa2, &caixa3, cliente, n);
			}
			if (!vazia(fila3)){
				n=3;
				desenfileirar(&fila3, &cliente);
				caixa(&caixa1, &caixa2, &caixa3, cliente, n);
			}
			cont++;
		}
		clientes=0;
		if (!vazia(fila1)||!vazia(fila2)||!vazia(fila3)){
			if (!vazia(fila1)){
				n=1;
				desenfileirar(&fila1, &cliente);
				caixa(&caixa1, &caixa2, &caixa3, cliente, n);
			}
			if (!vazia(fila2)){
				n=2;
				desenfileirar(&fila2, &cliente);
				caixa(&caixa1, &caixa2, &caixa3, cliente, n);
			}
			if (!vazia(fila3)){
				n=3;
				desenfileirar(&fila3, &cliente);
				caixa(&caixa1, &caixa2, &caixa3, cliente, n);
			}
		}
	}
	
	printf("                             ##############################################################\n");
	printf("                             ###                                                        ###\n");
	printf("                             ###                                                        ###\n");
	printf("                             ###                                                        ###\n");
	printf("                             ###                    RELATÓRIO FINAL                     ###\n");
	printf("                             ###                  DA AGÊNCIA BANCÁRIA                   ###\n");
	printf("                             ###                                                        ###\n");
	printf("                             ###                                                        ###\n");
	printf("                             ###                                                        ###\n");
	printf("                             ##############################################################\n\n\n");
	printf("                                O caixa 1 atendeu %d pessoas, contabilizando R$%.2f \n                                em Saques, R$%.2f em Depósitos e R$%.2f em \n                                Pagamentos.\n\n", caixa1.clientesAtendidos, caixa1.valorSaque, caixa1.valorDeposito, caixa1.valorPagamento);
	printf("                                O caixa 2 atendeu %d pessoas, contabilizando R$%.2f \n                                em Saques, R$%.2f em Depósitos e R$%.2f em \n                                Pagamentos.\n\n", caixa2.clientesAtendidos, caixa2.valorSaque, caixa2.valorDeposito, caixa2.valorPagamento);
	printf("                                O caixa 3 atendeu %d pessoas, contabilizando R$%.2f \n                                em Saques, R$%.2f em Depósitos e R$%.2f em \n                                Pagamentos.\n\n", caixa3.clientesAtendidos, caixa3.valorSaque, caixa3.valorDeposito, caixa3.valorPagamento);
	printf("\n\n                                                       Trabalho de Julia Rezende Alves.");
}
