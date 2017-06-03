#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>




TNO2 * criar_no_residual(TNO2 ** novo, int valor, int vertice, int direcao, int pos);
void exibir_rede_residual(TNO2 * residual[], int qtd_vertices);
void inserir_residual(TNO2 * residual[],int pos,int valor,int vertice, int direcao);
void rede_residual(TNO * vet[], TNO2 * residual[], int qtd_vertice);
void abrirArq(TNO *vet[],int * qtd_vertices, FILE ** arq);
int converter(char c);
void inserir(TNO *vet[], int pos, int fluxo, int capacidade, int vertice);
TNO * criar_no(TNO ** novo, int fluxo, int capacidade, int vertice);
void exibir(TNO * vet[], int qtd_vertice);
FILE * abrir(char nomearq[]);
void calcular_vertice(FILE * arq, char valor[], int * qtd_vertices);
int checar_numero(FILE * arq, char letra, char valor[]);
void deslocamento(FILE * arq);
void copiar(TNO2 * ante[], TNO2 * caminhos[][100], int qtd_vertice, int * qtd_caminho);
int buscar(TNO2 * ante[],int qtd_vertice,TNO2 * no);
void percorrer(TNO2 * residual[], TNO2 * caminhos[][100], int * qtd_caminho, int qtd_v);
void exibir_caminhos(TNO2 * caminhos[][100], int  qtd_caminhos, int qtd_vertice);
void zerar(TNO2 * residual[], TNO2 * caminhos[][100], int * qtd_caminho );
void f_menor(TNO2 * caminhos[][100],int qtd_caminhos , int menor[100][2], int qtd_vertices);
int f_maior(int menor[100][2], int qtd_caminhos, int * caminho);
void exibir_caminho(TNO2 * caminhos[][100], int pos);
void altera_caminho(TNO *vet[], TNO2 * caminhos[][100], int caminho, int f);
int f(int menor[100][2], int qtd_caminhos );
TNO *buscaLista(TNO *vet, int valor);
void carregar_arquivo(FILE ** arq);
void apresentacao();
void fluxo_maximo(TNO * s);
void temporizador(double delay1);