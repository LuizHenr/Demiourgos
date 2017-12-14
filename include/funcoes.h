#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>  //fopen, fclose
#include <string.h>
#include <stdlib.h>  //itoa
#include <math.h>


struct corRGB{
	int r, g, b;
};

struct posXY{
	int x, y;    //valor a coluna e valor da linha
};

struct dimXY{  //qt de pixels
	int x, y;  //qt de colunas e linhas    
};



//Calcula a distancia entre dois pontos passados por paramentos
int calcula_distancia(posXY p1, posXY p2);

int diferenca_cor(corRGB c1, corRGB c2, corRGB *difCores);

#endif