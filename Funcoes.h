#include <time.h>
#include <stdlib.h>
#include "Structs.h"
#include "Chamadas.h"


void fluxo_maximo(TNO * s){

	int fluxo=0;
	while (s!=NULL){
		fluxo+=s->fluxo;
		s=s->prox;
	} 
	printf("Fluxo Maximo: %i\n\n", fluxo);

}
void zerar(TNO2 * residual[], TNO2 * caminhos[][100], int * qtd_caminho ){

	int i,j;

	for (i = 0; i < MAX_CAMINHO; i++){
		residual[i]=NULL;
		for (j = 0; j < MAX_CAMINHO; j++){
			caminhos[i][j]=NULL;
		}
	}
	*qtd_caminho=0;
}
void carregar_arquivo(FILE ** arq){

	char nome[100]; 
	while(1){

		printf("\n Informe o nome do arquivo (com .txt): ");
		scanf("%s",nome);
		*arq = fopen(nome , "r + b" );

		if(*arq == NULL)
			printf("Erro na Abertura do Arquivo\n\n"); 
		else{
			printf("\n Arquivo Aberto com Sucesso\n\n");
			temporizador(1);
			printf(" Calculando");
			temporizador(1);
			printf(".");
			temporizador(1);
			printf(".");
			temporizador(1);
			printf(".");
			system("cls");
			return;
		}

	}



}
int converter(char c){
	return c-'0';
}
void inserir(TNO *vet[], int pos, int fluxo, int capacidade, int vertice){

	TNO * novo, *aux;

	if(vet[pos]==NULL)
		vet[pos]=criar_no(&novo,fluxo,capacidade,vertice);
	else{
		aux=vet[pos];
		while (aux->prox!=NULL){
			aux=aux->prox;
		}
		aux->prox=criar_no(&novo,fluxo,capacidade,vertice);
	}
}
TNO * criar_no(TNO ** novo, int fluxo, int capacidade, int vertice){

	(*novo)=(TNO*)malloc(sizeof(TNO));
	(*novo)->capacidade=capacidade;
	(*novo)->fluxo=fluxo;
	(*novo)->vertice=vertice; 
	(*novo)->prox=NULL;
	return (*novo);
}
void exibir(TNO * vet[], int qtd_vertice){

	int i=0;
	TNO * aux=vet[0];
	printf("\nLista Adjacente: \n\n");
	while( i < qtd_vertice){
		if(i==0)
			printf("S ");
		else if(i==qtd_vertice-1)
			printf("T -> ");
		else
			printf("V%i ",i);
		while(aux!=NULL){
			printf("-> ");
			printf("(V%i ", aux->vertice);
			printf("%i ", aux->capacidade);
			printf("%i) ", aux->fluxo);
			aux=aux->prox;
		}
		i++;
		aux=vet[i];
		printf("\n\n");
	}
}
void abrirArq(TNO *vet[],int * qtd_vertices, FILE ** arq){


	char letra,valor[100];
	int status, i=0, cont=0, fluxo,capacidade,vertice,  d=8;

	carregar_arquivo(arq);

	calcular_vertice(*arq,valor,qtd_vertices);

	while (1) {
		status = fread (&letra, sizeof (char), 1, *arq);
		if (status != 1) {
			if (!feof(*arq)) 
				printf ("Erro de leitura \n");
			break;
		}
		else {
			if(letra=='-'){
				deslocamento(*arq);
				i++;
			}
			if(isdigit(letra) || letra=='t'){
				cont++;
				if(cont==1){
					vertice=converter(letra);
					if(vertice==68)
						vertice=*qtd_vertices-1;

				}else if(cont==2){

					capacidade=checar_numero(*arq,letra,valor);
					valor[0]='\0';
				}else{
					fluxo=checar_numero(*arq,letra,valor);
					valor[0]='\0';
					cont=0; 
					inserir(vet,i,fluxo,capacidade,vertice);
				}
			}
		}//fim da leitura
	}
}
FILE * abrir(char nomearq[]){

	FILE * arq;

	arq = fopen(nomearq,"rb");

	if(arq!=NULL)
		printf("Leitura Bem Sucedida!!!\n");
	else{
		printf("Erro de Leitura!!!\n"); 
	}
	return arq;
}
void calcular_vertice(FILE * arq, char valor[], int * qtd_vertices){

	char letra;

	fread (&letra, sizeof (char), 1, arq);
	*qtd_vertices=checar_numero(arq,letra,valor);
	fseek (arq, 8*sizeof(char), 1);
	fread (&letra, sizeof (char), 1, arq); 

}
void deslocamento(FILE * arq){
	fseek (arq, 7*sizeof(char), 1);
}
int checar_numero(FILE * arq, char letra, char valor[]){


	int i=0, v=-1;

	while (letra!=' '){
		if(isdigit(letra)){
			valor[i]=letra;
			i++;
		}

		fread (&letra, sizeof (char), 1, arq);

	}
	valor[i]='\0';
	fseek (arq, v*sizeof(char), 1);

	return atoi(valor);
}
void rede_residual(TNO * vet[], TNO2 * residual[], int qtd_vertice){

	int i;
	TNO * aux;

	for (i = 0; i < qtd_vertice-1; i++){
		aux=vet[i]; 
		while (aux!=NULL){
			if((aux->capacidade)-(aux->fluxo)!=0){
				inserir_residual(residual,i,(aux->capacidade)-(aux->fluxo),aux->vertice,DIRETO);
			}
			if(aux->fluxo!=0){ 
				inserir_residual(residual,aux->vertice,aux->fluxo,i,INVERSO); 
			}
			aux=aux->prox;
		}
	}
}
void inserir_residual(TNO2 * residual[],int pos,int valor,int vertice, int direcao){
	TNO2 * novo, *aux;

	if(residual[pos]==NULL){
		residual[pos]=criar_no_residual(&novo,valor,vertice,direcao,pos);
	}else{
		aux=residual[pos];
		while (aux->prox!=NULL){
			aux=aux->prox;
		}
		aux->prox=criar_no_residual(&novo,valor,vertice,direcao,pos); 
	}


}
TNO2 * criar_no_residual(TNO2 ** novo, int valor, int vertice, int direcao, int pos){

	(*novo)=(TNO2*)malloc(sizeof(TNO2));
	(*novo)->valor=valor;
	(*novo)->vertice=vertice; 
	(*novo)->direcao=direcao;
	(*novo)->origem = pos;
	(*novo)->prox=NULL;
	return (*novo);
}
void exibir_rede_residual(TNO2 * residual[], int qtd_vertices){

	int i=0;
	TNO2 * aux=residual[0];
	printf("\nRede Residual: \n\n");
	while( i < qtd_vertices){
		if(i==0)
			printf("S -> ");
		else if(i==qtd_vertices-1)
			printf("T -> ");
		else
			printf("V%i -> ",i);
		while(aux!=NULL){
			printf("%i ", aux->valor); 
			printf("%i ", aux->vertice);
			if(aux->direcao==0)
				printf(">> ", aux->direcao);
			else
				printf("<< ", aux->direcao);
			aux=aux->prox;
		}
		i++;
		aux=residual[i];
		printf("\n\n");
	}
}
void percorrer(TNO2 * residual[], TNO2 * caminhos[][100], int * qtd_caminho, int qtd_v){
	int i=0,qtd_vertice=0;
	TNO2 * aux=residual[i],* ante[MAX_CAMINHO]={{NULL}}; 

	while(1){
		do{
			if(aux==NULL){ 
				qtd_vertice--;
				aux=ante[qtd_vertice];
				aux=aux->prox;
				if(qtd_vertice==0 && aux==NULL) 
					return ; 
			}
		} while (aux==NULL);
		if(buscar(ante,qtd_vertice,aux)==0){
			if(aux->vertice==qtd_v-1){//(salvar) 
				ante[qtd_vertice]=aux;
				qtd_vertice++; 
				copiar(ante,caminhos,qtd_vertice,qtd_caminho);
				qtd_vertice--;
				(*qtd_caminho)++; 
				aux=aux->prox; 
			}else{//proxima posição
				ante[qtd_vertice]=aux; 
				qtd_vertice++;
				aux=residual[aux->vertice];
			}
		}else{
			aux=aux->prox; 
		}
	} 
}
int buscar(TNO2 * ante[],int qtd_vertice,TNO2 * no){

	int i=0;

	if(no->vertice==0)
		return 1;

	for (i = 0; i < qtd_vertice; i++){
		if(ante[i]==NULL)
			return 0;
		else if(ante[i]->vertice==no->vertice){
			return 1;
		}
	}
	return 0;
}
void copiar(TNO2 * ante[], TNO2 * caminhos[][100], int qtd_vertice, int * qtd_caminho){

	int i;
	for ( i = 0; i < qtd_vertice; i++){
		caminhos[i][*qtd_caminho]=ante[i];
		//printf("v%i -> ",caminhos[i][*qtd_caminho]->vertice);
	}
	//caminho(caminhos,*qtd_caminho);
	//printf("\n");
}
void exibir_caminhos(TNO2 * caminhos[][100], int  qtd_caminhos, int qtd_vertice){

	int i,j=0;

	for (i = 0; i < qtd_caminhos; i++){

		while(j<qtd_vertice){
			if(j==0)
				printf("S -");
			if(caminhos[j][i]!=NULL){
				if (caminhos[j][i]->vertice==qtd_vertice-1){
					printf("(%i)-> T",caminhos[j][i]->valor);
				}else{
					printf("(%i)-> V%i -",caminhos[j][i]->valor,caminhos[j][i]->vertice); 
				}
			}
			j++;
		} 
		j=0;
		printf("\n");
	}
}
void exibir_caminho(TNO2 * caminhos[][100], int pos){

	int i=0;
	TNO2 * aux=caminhos[i][pos];
	printf("\n");
	if(aux!=NULL)
		printf("S -");
	while (aux!=NULL){
		if(caminhos[i+1][pos]!=NULL){
			printf("(%i)-> V%i", aux->valor, aux->vertice); 
		}else{
			printf("(%i)-> T", aux->valor);
		}i++;
		aux=caminhos[i][pos]; 
		if(aux!=NULL)
			printf(" -");
	}
	printf("\n");
}
void f_menor(TNO2 * caminhos[][100],int qtd_caminhos , int menor[100][2], int qtd_vertices){
	int flag=MAX_CAMINHO;
	int i, j=0, f=0;

	for (i = 0; i < qtd_caminhos; i++){
		while(j<qtd_vertices){ 
			if(caminhos[j][i]!=NULL && j<qtd_vertices){
				//printf("Valor: %i\n", caminhos[j][i]->valor);
				if(caminhos[j][i]->valor!=0){
					if(flag>caminhos[j][i]->valor){
						flag=caminhos[j][i]->valor;
						menor[i][0]=flag;
					}
				}
			}
			j++;
		} 
		menor[i][1]=i; 
		flag=MAX_CAMINHO; 
		j=0; 
	}
}
int f_maior(int menor[100][2], int qtd_caminhos, int * caminho){

	int i=0, maior=0, pos=0;
	for (i = 0; i < qtd_caminhos; i++){
		if(maior<menor[i][0]){
			maior=menor[i][0];
			*caminho=i; 
		}
	}
	return maior;
}
void altera_caminho(TNO *vet[], TNO2 * caminhos[][100], int caminho, int f){

	int i=0;
	TNO *aux=vet[i]; 
	while (caminhos[i][caminho]!=NULL){ 
		if(caminhos[i][caminho]->direcao==DIRETO){
			aux=buscaLista(vet[caminhos[i][caminho]->origem],caminhos[i][caminho]->vertice);
			aux->fluxo=aux->fluxo+f;
		}else{
			aux=buscaLista(vet[caminhos[i][caminho]->vertice],caminhos[i][caminho]->origem);
			aux->fluxo=aux->fluxo-f; 
		} 
		i++;
	} 
}
TNO *buscaLista(TNO *vet, int valor){
	TNO *aux = vet;

	if(aux==NULL)
		return NULL;
	else{
		while(aux!=NULL){
			if(aux->vertice==valor)
				return aux;
			aux=aux->prox;
		}
	}
	return NULL;
}
void apresentacao()
{
	printf("----------------------------------------------------------------\n");
	printf("\t\tUniversidade Catolica de Pernambuco\n");
	printf("\t\tCurso de Ciência da computação\n");
	printf("\t\tProjeto O PROBLEMA DO FLUXO MAXIMO\n");
	printf("\t\tDisciplina: Grafos\n");
	printf("\t\tProfessor: Robson Lins\n");
	printf("\t\tEquipe: Pedro Henrique\n");
	printf("\t\t        Jesimiel Rufino\n");
	printf("\t\t        Glauber Santana\n");
	printf("----------------------------------------------------------------\n");
	temporizador(0.1);
	printf("Carregando");
	temporizador(0.1);
	printf(".");
	temporizador(0.1);
	printf(".");
	temporizador(0.1);
	printf(".");
	temporizador(0.1);
	system("cls");
}
void temporizador(double delay1)
{
	double inst1=0, inst2=0;
	if (delay1<0.001)
		return; 
	inst1 = (double)clock()/(double)CLOCKS_PER_SEC;
	while (inst2-inst1<delay1)
		inst2 = (double)clock()/(double)CLOCKS_PER_SEC;
	return;
}