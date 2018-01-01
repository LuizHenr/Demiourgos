#ifndef LAKE_H
#define LAKE_H

#include <funcoes.h>

class Lago{
private:
	int codigo;
	corRGB cor;
	posXY posicao;  //do superior esquedo
	int tamanho;  // raio (em px)  
	int tamanho_atual;  // porcentagem do raio original
	Lago *prox_l;

public:
	void setCodigo(int c);
	int getCodigo();

	void setCor(corRGB c);
	corRGB getCor();

	void setPosicao(posXY p);
	posXY getPosicao();

	void setTamanho_atual(int t);
	int getTamanho_atual();
	void setTamanho(int t);
	int getTamanho();

	void setProx_l(Lago *l);
	Lago* getProx_l();


	void inicializa(int cod, corRGB c, posXY p, int t);

};


#endif
