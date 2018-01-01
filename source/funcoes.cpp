#include <funcoes.h>

/*
typedef struct coresRGB{
int r, g, b;
} corRGB;  

typedef struct posicao{
	int x, y;    //valor a coluna e valor da linha
} posXY;

typedef struct dimensao{  //qt de pixels
	int x, y;  //qt de colunas e linhas    
} dimXY;
*/


//Calcula a distancia entre dois pontos passados por paramentos
int calcula_distancia(posXY p1, posXY p2){
	int dist_col, dist_lin; //distancia entre os pontos

	dist_col = abs(p1.x - p2.x);
	dist_lin = abs(p1.y - p2.y);

	return (int)floor(sqrt(pow((double)dist_col, 2) + pow((double)dist_lin, 2)));  //retorna o valor da hipotenusa arredondado    h^2= lin^2 +  col^2	
	// return (int) floor(sqrt(pow(abs(p1.x-p2.x),2)+pow(abs(p1.y-p2.y),2)));  //retorna o valor da hipotenusa arredondado    h^2= lin^2 +  col^2	
}

int diferenca_cor(corRGB c1, corRGB c2, corRGB *difCores){
	int dif = 0;

	dif += abs(c1.r - c2.r);  //diferenca de R
	dif += abs(c1.g - c2.g);  // mais diferenca de G
	dif += abs(c1.b - c2.b);  // mais diferenca de B

	difCores->r = abs(c1.r - c2.r);
	difCores->g = abs(c1.g - c2.g);
	difCores->b = abs(c1.b - c2.b);

	return dif;  //varia entre 0 e 765
}

