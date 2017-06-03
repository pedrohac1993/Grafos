#define LINHA 100
#define COLUNA 100
#define DIRETO 0
#define INVERSO 1
#define MAX_CAMINHO 100

typedef struct NO{

	int capacidade;
	int fluxo;
	struct NO *prox;
	int vertice;
}TNO;
typedef struct NO2{ 
	struct NO2 *prox; 
	int vertice;
	int valor;
	int direcao;
	int origem;
}TNO2;