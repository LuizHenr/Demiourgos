#ifndef GRID_H
#define GRID_H

#include <funcoes.h>

#define MAX_DIMENSAO_X 1920 // 1900px
#define MAX_DIMENSAO_Y 1080 // 1050px

class Campo{
private:
	corRGB cor;
	int mes_atual, ano_atual;
	dimXY dimensao;
	char mapa_obj[MAX_DIMENSAO_X][MAX_DIMENSAO_Y];  //

public:

	void setCor(corRGB c);
	corRGB getCor();
	void inicializa(corRGB c);
	char getMapa_obj(posXY p);
};


#endif
