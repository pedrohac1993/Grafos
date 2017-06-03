#define _CRT_SECURE_NO_WARNINGS
#include "Funcoes.h"

int main(){
	FILE * arq;
	TNO *vet[MAX_CAMINHO]={{NULL}};
	TNO2 * residual[MAX_CAMINHO], * caminhos[MAX_CAMINHO][MAX_CAMINHO]; 
	int qtd_vertices=0,qtd_caminho=0,caminho=-1;
	int menor[MAX_CAMINHO][2], melhor=0;
	setlocale(LC_ALL, "pt");

	apresentacao();
	zerar(residual,caminhos,&qtd_caminho);
	abrirArq(vet,&qtd_vertices,&arq);

	do{
		// monta a lista de adj
		exibir(vet,qtd_vertices);
		zerar(residual,caminhos,&qtd_caminho);//apaga tudo e recomeça

		rede_residual(vet,residual,qtd_vertices); // monta a rede residual 
		exibir_rede_residual(residual,qtd_vertices);

		percorrer(residual,caminhos,&qtd_caminho,qtd_vertices); //verifica todos os caminhos possiveis 

		if(qtd_caminho!=0)
			printf("\nLista de Caminhos\n\n");

		exibir_caminhos(caminhos,qtd_caminho,qtd_vertices); 

		f_menor(caminhos,qtd_caminho,menor,qtd_vertices); //verifica o menores

		melhor=f_maior(menor,qtd_caminho,&caminho); //acha o maior (melhor caminho)

		if(qtd_caminho!=0)
			printf("\nMelhor Caminho\n\n");

		exibir_caminho(caminhos,menor[caminho][1]); 

		if(qtd_caminho!=0){ 
			printf("\nF': %i\n\n", melhor); 
			printf("Nova ");
		}else
			printf("Nao existe caminho de S -> T\n");

		altera_caminho(vet,caminhos,menor[caminho][1],melhor); // altera o caminho na lista de adj
	} while (qtd_caminho!=0);
	fluxo_maximo(vet[0]);
	return 0;
}