#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct local{
	char nome[50];
	int status;
}TLocal;

typedef struct rotaAerea{
	int origem, destino;
	float custo;
	struct rotaAerea *prox;
}rotaA;

void inicializaGrafo(float cidades[][100], TLocal aeroportos[], rotaA *rotasAereas, TLocal nomeCidades[]){
	int i, j;
	
	for(i=0; i<100; i++){
		for(j=0; j<100; j++){
			cidades[i][j]=0;
		}
	}
	
	for(i=0; i<100; i++){
		aeroportos[i].status=0;
	}
	
	for(i=0; i<100; i++){
		nomeCidades[i].status=0;
	}
	
	rotasAereas->custo=0;
	rotasAereas->origem=-1;
	rotasAereas->destino=-1;
	rotasAereas->prox=NULL;
}

int verificaCidade(TLocal nomeCidades[], char nome[]){
	int i;
	
	for(i=0; i<100; i++){
		if(strcmp(nome, nomeCidades[i].nome)==0){
			return i;
		}
	}
	return -1;
}

void insereCidade(TLocal nomeCidades[], char nome[]){	
	int i;
	
	if(verificaCidade(nomeCidades, nome)!=-1){
		printf("\n\nEssa cidade já foi inserida!\n");
		system("pause");
		return;
	}
	
	for(i=0; i<100; i++){
		if(nomeCidades[i].status==0){
			strcpy(nomeCidades[i].nome, nome);
			nomeCidades[i].status=1;
			break;
		}
	}
	
	printf("\n\nCidade inserida!\n");
	system("pause");
}

int verificaAero(TLocal aeroportos[], char nome[]){
	int i;
	
	for(i=0; i<100; i++){
		if(strcmp(nome, aeroportos[i].nome)==0){
			return i;
		}
	}
	return -1;
}

void insereAeroporto(TLocal aeroportos[], char nome[]){
	int i;
	
	if(verificaAero(aeroportos, nome)!=-1){
		printf("\n\nEsse aeroporto já foi inserido!\n");
		system("pause");
		return;
	}
	
	for(i=0; i<100; i++){
		if(aeroportos[i].status==0){
			strcpy(aeroportos[i].nome, nome);
			aeroportos[i].status=1;
			break;
		}
	}
	
	printf("\n\nAeroporto inserido!\n");
	system("pause");
}

void insereRotaTerrestre(float cidades[][100], TLocal nomeCidades[], int p1, int p2, float dist){
	char nome1[50], nome2[50];
	int op;
	
	if(p1==-1){
		printf("\n\nA cidade de origem não existe!\n");
		system("pause");
		return;
	}
	
	if(p2==-1){
		printf("\n\nA cidade de destino não existe!\n");
		system("pause");
		return;
	}
	
	if(p1>p2){
		if(cidades[p1][p2]!=0){
			printf("\nEssa rota já existe, digite qualquer coisa para atualizar ou 0 para não atualizar: ");
			scanf("%d", &op);
			if(op==0){
				return;
			}
		}	
		cidades[p1][p2]=dist;
	}
	
	if(p2>p1){
		if(cidades[p2][p1]!=0){
			printf("\nEssa rota já existe, digite qualquer coisa para atualizar ou 0 para não atualizar: ");
			scanf("%d", &op);
			if(op==0){
				return;
			}
		}	
		cidades[p2][p1]=dist;
	}
	
	if(p1==p2){
		printf("\nCidades de origem e destino são iguais!");
		return;
	}
	
	printf("\n\nRota inserida!\n");
	system("pause");
}

rotaA* rotaLivre(rotaA *rotasAereas){
	rotaA *aux=rotasAereas;
	
	do{
		if(aux->prox==NULL){
			return aux;
		}
		aux=aux->prox;
	}while(aux!=NULL);
}

rotaA* verificaRota(rotaA *rotasAereas, int p1, int p2){
	rotaA *aux=rotasAereas;
	
	while(aux!=NULL){
		if((aux->origem==p1)&&(aux->destino==p2)){
			return aux;
		}
		aux=aux->prox;
	}
	
	return NULL;
}

void insereRotaAerea(TLocal aeroportos[], rotaA *rotasAereas, int p1, int p2, float custo){
	int op;
	rotaA *aux;
	
	if(p1==-1){
		printf("\n\nEsse aeroporto não existe!\n");
		system("pause");
		return;
	}
	
	if(p2==-1){
		printf("\n\nEsse aeroporto não existe!\n");
		system("pause");
		return;
	}
	
	if(verificaRota(rotasAereas, p1, p2)!=NULL){
		printf("\nEssa rota já existe, digite qualquer coisa para atualizar ou 0 para não atualizar: ");
		scanf("%d", &op);
		if(op==0){
			return;
		}
	}
	
	aux=rotaLivre(rotasAereas);
	
	aux->prox=(rotaA*)malloc(sizeof(rotaA));
	
	aux->prox->origem=p1;
	aux->prox->destino=p2;
	aux->prox->custo=custo;
	aux->prox->prox=NULL;
	
	printf("\n\nRota inserida!\n");
	system("pause");
}

void listaCidadesVizinhas(float cidades[][100], TLocal nomeCidades[], char nome[]){
	int p, i, x;
	
	p=verificaCidade(nomeCidades, nome);
	
	if(p==-1){
		printf("Essa cidade não existe!");
		system("pause");
		return;
	}
	
	x=1;
	
	for(i=0; i<100; i++){
		if(cidades[p][i]!=0){
			printf("%d - %s (Distância: %f)\n", x, nomeCidades[i].nome, cidades[p][i]);
			x++;
		}
	}
	
	for(i=0; i<100; i++){
		if(cidades[i][p]!=0){
			printf("%d - %s (Distância: %f)\n", x, nomeCidades[i].nome, cidades[i][p]);
			x++;
		}
	}
	
	system("pause");
}

void listaAeroportosDestino(TLocal aeroportos[], rotaA *rotasAereas, char nome[]){
	int p, x;
	rotaA *aux;
	
	p=verificaAero(aeroportos, nome);
	
	if(p==-1){
		printf("Esse aeroporto não existe!");
		system("pause");
		return;
	}
	
	aux=rotasAereas;
	
	x=1;
	
	while(aux!=NULL){
		if(aux->origem==p){
			printf("%d - %s (Custo: %f)\n", x, aeroportos[aux->destino].nome, aux->custo);
			x++;
		}
		aux=aux->prox;
	}
	
	system("pause");
}

void listaAeroportosOrigem(TLocal aeroportos[], rotaA *rotasAereas, char nome[]){
	int p, x;
	rotaA *aux;
	
	p=verificaAero(aeroportos, nome);
	
	if(p==-1){
		printf("Esse aeroporto não existe!");
		system("pause");
		return;
	}
	
	aux=rotasAereas;
	
	x=1;
	
	while(aux!=NULL){
		if(aux->destino==p){
			printf("%d - %s (Custo: %f)\n", x, aeroportos[aux->origem].nome, aux->custo);
			x++;
		}
		aux=aux->prox;
	}
	
	system("pause");
}

void atualizaRotaTerrestre(float cidades[][100], TLocal nomeCidades[]){
	char nome1[50], nome2[50];
	int op, p1, p2;
	float dist;
	
	printf("\nDigite o nome da cidade de origem: ");
	fflush(stdin);
	gets(nome1);
	
	p1=verificaCidade(nomeCidades, nome1);
	
	if(p1==-1){
		printf("\n\nEssa cidade não existe! Digite qualquer coisa para inserir ou 0 para não inserir: \n");
		scanf("%d", &op);
		if(op==0){
			return;
		}
		insereCidade(nomeCidades, nome1);
	}
	
	printf("\nDigite o nome da cidade de destino: ");
	fflush(stdin);
	gets(nome2);
	
	p2=verificaCidade(nomeCidades, nome2);
	
	if(p2==-1){
		printf("\n\nEssa cidade não existe! Digite qualquer coisa para inserir ou 0 para não inserir: \n");
		scanf("%d", &op);
		if(op==0){
			return;
		}
		insereCidade(nomeCidades, nome2);
	}
	
	
	if(p1>p2){
		if(cidades[p1][p2]==0){
			printf("\nEssa rota não existe, digite qualquer coisa para inserir ou 0 para não inserir: ");
			scanf("%d", &op);
			if(op==0){
				return;
			}
		}
		printf("\nDigite a distância da rota: ");
		scanf("%f", &dist);	
		cidades[p1][p2]=dist;
	}
	
	if(p2>p1){
		if(cidades[p2][p1]==0){
			printf("\nEssa rota não existe, digite qualquer coisa para inserir ou 0 para não inserir: ");
			scanf("%d", &op);
			if(op==0){
				return;
			}
		}
		printf("\nDigite a distância da rota: ");
		scanf("%f", &dist);
		cidades[p2][p1]=dist;
	}
	
	if(p1==p2){
		printf("\nCidades de origem e destino são iguais!");
		return;
	}
	
	printf("\n\nRota atualizada!\n");
	system("pause");
}

void atualizaRotaAerea(TLocal aeroportos[], rotaA *rotasAereas){
	char nome1[50], nome2[50];
	int op, p1, p2;
	float custo;
	rotaA *aux;
	
	printf("\nDigite o nome do aeroporto de origem: ");
	fflush(stdin);
	gets(nome1);
	
	p1=verificaAero(aeroportos, nome1);
	
	if(p1==-1){
		printf("\n\nEsse aeroporto não existe! Digite qualquer coisa para inserir ou 0 para não inserir: \n");
		scanf("%d", &op);
		if(op==0){
			return;
		}
		insereAeroporto(aeroportos, nome1);
	}
	
	printf("\nDigite o nome do aeroporto de destino: ");
	fflush(stdin);
	gets(nome2);
	
	p2=verificaAero(aeroportos, nome2);
	
	if(p2==-1){
		printf("\n\nEsse aeroporto não existe! Digite qualquer coisa para inserir ou 0 para não inserir: \n");
		scanf("%d", &op);
		if(op==0){
			return;
		}
		insereAeroporto(aeroportos, nome2);
	}
	
	aux=verificaRota(rotasAereas, p1, p2);
	
	if(aux==NULL){
		printf("\nEssa rota não existe, digite qualquer coisa para inserir ou 0 para não inserir: ");
		scanf("%d", &op);
		if(op==0){
			return;
		}
		printf("\nDigite o custo da rota: ");
		scanf("%f", &custo);
		aux=rotaLivre(rotasAereas);
		aux->prox=(rotaA*)malloc(sizeof(rotaA));
		aux->prox->origem=p1;
		aux->prox->destino=p2;
		aux->prox->custo=custo;
		aux->prox->prox=NULL;
	}
	
	printf("\nDigite o custo da rota: ");
	scanf("%f", &custo);
	
	aux->custo=custo;
	
	printf("\n\nRota atualizada!\n");
	system("pause");
}

void removeAeroporto(TLocal aeroportos[], rotaA *rotasAereas, char nome[]){
	int p;
	rotaA *aux1, *aux2;
	
	p=verificaAero(aeroportos, nome);
	
	if(p==-1){
		printf("\nEsse aeroporto não existe!");
		return;
	}
	
	strcpy(aeroportos[p].nome, " ");
	aeroportos[p].status=0;
	
	aux1=rotasAereas;
	
	do{
		if((aux1->prox->destino==p)||(aux1->prox->origem==p)){
			aux2=aux1->prox;
			aux1->prox=aux2->prox;
			free(aux2);
		}else{
			aux1=aux1->prox;
		}
	}while(aux1->prox!=NULL);
	
	printf("\n\nAeroporto removido!\n");
	system("pause");
}

void removeRotaAerea(TLocal aeroportos[], rotaA *rotasAereas, char nome1[], char nome2[]){
	int p1, p2;
	rotaA *aux1, *aux2;
	
	p1=verificaAero(aeroportos, nome1);
	
	if(p1==-1){
		printf("\nEsse aeroporto não existe!");
		return;
	}
	
	p2=verificaAero(aeroportos, nome2);
	
	if(p2==-1){
		printf("\nEsse aeroporto não existe!");
		return;
	}
	
	aux1=rotasAereas;
	
	do{
		if((aux1->prox->origem==p1)&&(aux1->prox->destino==p2)){
			aux2=aux1->prox;
			aux1->prox=aux2->prox;
			free(aux2);
			break;
		}
		aux1=aux1->prox;
	}while(aux1!=NULL);
	
	printf("\n\nRota aérea removida!\n");
	system("pause");
}

void calculaDistTerrestres(float cidades[][100]){
	int i, j;
	float soma=0;
	
	for(i=0; i<100; i++){
		for(j=0; j<100; j++){
			soma+=cidades[i][j];
		}
	}
	
	printf("\nA soma de todas as distâncias das rotas terrestres é igual a %f.", soma);
	system("pause");
}

void calculaDistAereas(rotaA *rotasAereas){
	rotaA *aux;
	float soma=0;
	
	aux=rotasAereas;
	
	while(aux!=NULL){
		soma+=aux->custo;
		aux=aux->prox;
	}
	
	printf("\nA soma de todas as distâncias das rotas aéreas é igual a %f.", soma);
	system("pause");
}

void mostraAeroportos(TLocal aeroportos[]){
	int i;
	
	for(i=0; i<100; i++){
		if(aeroportos[i].status==1) printf("%d - %s\n", i, aeroportos[i].nome);
	}
}

void mostraCidades(TLocal nomeCidades[]){
	int i;
	
	for(i=0; i<100; i++){
		if(nomeCidades[i].status==1) printf("%d - %s\n", i, nomeCidades[i].nome);
	}
}

void menu1(float cidades[][100], TLocal aeroportos[], TLocal nomeCidades[], rotaA *rotasAereas){
	int op, p1, p2;
	char nome[50], nome1[50], nome2[50];
	float dist, custo;

	system("cls");

	printf("ROTAS - INSERIR\n\n");
	printf("1. Cidade\n");
	printf("2. Aeroporto\n");
	printf("3. Rota Terrestre\n");
	printf("4. Rota Aérea\n");
	printf("0. Voltar\n\n");

	printf("Digite o número da opção que você deseja: ");
	scanf("%d", &op);

	switch(op){
		case 0:
			break;
		case 1:
			printf("\nDigite o nome da cidade a ser inserida: ");
			fflush(stdin);
			gets(nome);
			insereCidade(nomeCidades, nome);
			break;
		case 2:
			printf("\nDigite o nome do aeroporto a ser inserido: ");
			fflush(stdin);
			gets(nome);
			insereAeroporto(aeroportos, nome);
			break;
		case 3:
			system("cls");
			printf("ROTAS - INSERIR ROTA TERRESTRE\n\n");
			mostraCidades(nomeCidades);
			printf("\nDigite o nome da cidade de origem: ");
			fflush(stdin);
			gets(nome1);
			p1=verificaCidade(nomeCidades, nome1);
			printf("\nDigite o nome da cidade de destino: ");
			fflush(stdin);
			gets(nome2);
			p2=verificaCidade(nomeCidades, nome2);
			printf("\nDigite a distância da rota: ");
			scanf("%f", &dist);
			insereRotaTerrestre(cidades, nomeCidades, p1, p2, dist);
			break;
		case 4:
			system("cls");
			printf("ROTAS - INSERIR ROTA AÉREA\n\n");
			mostraAeroportos(aeroportos);
			printf("\nDigite o nome do aeroporto de origem: ");
			fflush(stdin);
			gets(nome1);
			p1=verificaAero(aeroportos, nome1);
			printf("\nDigite o nome do aeroporto de destino: ");
			fflush(stdin);
			gets(nome2);
			p2=verificaAero(aeroportos, nome2);
			printf("\nDigite o custo da rota: ");
			scanf("%f", &custo);
			insereRotaAerea(aeroportos, rotasAereas, p1, p2, custo);
			break;
		default:
			menu1(cidades, aeroportos, nomeCidades, rotasAereas);
			break;
	}
}

void menu2(float cidades[][100], TLocal aeroportos[], rotaA *rotasAereas, TLocal nomeCidades[]){
	int op;

	system("cls");

	printf("ROTAS - ATUALIZAR\n\n");
	printf("1. Rota Terrestre\n");
	printf("2. Rota Aérea\n");
	printf("0. Voltar\n\n");

	printf("Digite o número da opção que você deseja: ");
	scanf("%d", &op);

	switch(op){
		case 0:
			break;
		case 1:
			system("cls");
			printf("ROTAS - ATUALIZAR ROTA TERRESTRE\n\n");
			mostraCidades(nomeCidades);
			atualizaRotaTerrestre(cidades, nomeCidades);
			break;
		case 2:
			system("cls");
			printf("ROTAS - ATUALIZAR ROTA TERRESTRE\n\n");
			mostraAeroportos(aeroportos);
			atualizaRotaAerea(aeroportos, rotasAereas);
			break;
		default:
			menu2(cidades, aeroportos, rotasAereas, nomeCidades);
			break;
	}
}

void menu3(float cidades[][100], TLocal aeroportos[], rotaA *rotasAereas){
	int op;
	char nome[50], nome1[50], nome2[50];

	system("cls");

	printf("ROTAS - REMOVER\n\n");
	printf("1. Aeroporto\n");
	printf("2. Rota Aérea\n");
	printf("0. Voltar\n\n");

	printf("Digite o número da opção que você deseja: ");
	scanf("%d", &op);

	switch(op){
		case 0:
			break;
		case 1:
			printf("\nDigite o nome do aeroporto que desejar remover: ");
			fflush(stdin);
			gets(nome);
			removeAeroporto(aeroportos, rotasAereas, nome);
			break;
		case 2:
			printf("\nDigite o nome do aeroporto de origem: ");
			fflush(stdin);
			gets(nome1);
			printf("\nDigite o nome do aeroporto de destino: ");
			fflush(stdin);
			gets(nome2);
			removeRotaAerea(aeroportos, rotasAereas, nome1, nome2);
			break;
		default:
			menu3(cidades, aeroportos, rotasAereas);
			break;
	}
}

void menu4(float cidades[][100], TLocal aeroportos[], rotaA *rotasAereas, TLocal nomeCidades[]){
	int op;
	char nome[50];

	system("cls");

	printf("ROTAS - LISTAR\n\n");
	printf("1. Cidades vizinhas\n");
	printf("2. Aeroportos de destino\n");
	printf("3. Aeroportos de origem\n");
	printf("0. Voltar\n\n");

	printf("Digite o número da opção que você deseja: ");
	scanf("%d", &op);

	switch(op){
		case 0:
			break;
		case 1:
			printf("\nDigite o nome da cidade: ");
			fflush(stdin);
			gets(nome);
			listaCidadesVizinhas(cidades, nomeCidades, nome);
			break;
		case 2:
			printf("\nDigite o nome do aeroporto: ");
			fflush(stdin);
			gets(nome);
			listaAeroportosDestino(aeroportos, rotasAereas, nome);
			break;
		case 3:
			printf("\nDigite o nome do aeroporto: ");
			fflush(stdin);
			gets(nome);
			listaAeroportosOrigem(aeroportos, rotasAereas, nome);
			break;
		default:
			menu4(cidades, aeroportos, rotasAereas, nomeCidades);
			break;
	}
}

void menu5(float cidades[][100], TLocal aeroportos[], rotaA *rotasAereas){
	int op;

	system("cls");

	printf("ROTAS - CALCULAR DISTÂNCIAS\n\n");
	printf("1. Rotas Terrestres\n");
	printf("2. Rotas Aéreas\n");
	printf("0. Voltar\n\n");

	printf("Digite o número da opção que você deseja: ");
	scanf("%d", &op);

	switch(op){
		case 0:
			break;
		case 1:
			calculaDistTerrestres(cidades);
			break;
		case 2:
			calculaDistAereas(rotasAereas);
			break;
		default:
			menu5(cidades, aeroportos, rotasAereas);
			break;
	}
}

void menu(float cidades[][100], TLocal aeroportos[], TLocal nomeCidades[], rotaA *rotasAereas){
	int op;
	rotaA *aux=rotasAereas->prox;
	
	system("cls");

	printf("ROTAS\n\n");
	printf("1. Inserir\n");
	printf("2. Atualizar\n");
	printf("3. Remover\n");
	printf("4. Listar\n");
	printf("5. Calcular distâncias\n");
	printf("0. Sair\n\n");

	printf("Digite o número da opção que você deseja: ");
	scanf("%d", &op);

	switch(op){
		case 0:
			exit(0);
			break;
		case 1:
			menu1(cidades, aeroportos, nomeCidades, rotasAereas);
			break;
		case 2:
			menu2(cidades, aeroportos, rotasAereas, nomeCidades);
			break;
		case 3:
			menu3(cidades, aeroportos, rotasAereas);
			break;
		case 4:
			menu4(cidades, aeroportos, rotasAereas, nomeCidades);
			break;
		case 5:
			menu5(cidades, aeroportos, rotasAereas);
			break;
	}

	menu(cidades, aeroportos, nomeCidades, rotasAereas);
}

void premenu(){
	float cidades[100][100];
	TLocal nomeCidades[100], aeroportos[100];
	rotaA rotasAereas;

	inicializaGrafo(cidades, aeroportos, &rotasAereas, nomeCidades);
	
	menu(cidades, aeroportos, nomeCidades, &rotasAereas);
}

int main(){
	setlocale(LC_ALL, "");
	system("color F0");
	int jedi=0;

	premenu();

	return jedi;
}
