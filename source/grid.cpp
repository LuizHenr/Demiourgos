#include <grid.h>

void Campo::setCor(corRGB c){
	Campo::cor = c;
}

corRGB Campo::getCor(){
	return Campo::cor;
}


void Campo::inicializa(corRGB c){
	if (c.r == -1)     cor.r = rand() % 256;      else    cor.r = c.r;
	if (c.g == -1)     cor.g = rand() % 256;      else    cor.g = c.g;
	if (c.b == -1)     cor.b = rand() % 256;      else    cor.b = c.b;

	for (int i = 0; i<MAX_DIMENSAO_X; i++)
		for (int j = 0; j<MAX_DIMENSAO_Y; j++)
			Campo::mapa_obj[i][j] = '0';

}

char Campo::getMapa_obj(posXY p){
	return Campo::mapa_obj[p.x][p.y];
}




