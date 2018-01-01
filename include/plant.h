#ifndef PLANT_H
#define PLANT_H

#include <funcoes.h>

class Planta{
private:
	int codigo;
	corRGB cor;
	posXY posicao;  //do superior esquedo
	int tamanho;  // 1-pequeno   2-grande
	bool estado; // 0-morto  1-vivo
	int morte;  //tempo que a planta está morta
	Planta *prox_p;

public:
	void setCodigo(int c);
	int getCodigo();
	void setCor(corRGB c);
	corRGB getCor();
	void setPosicao(posXY p);
	posXY getPosicao();

	void setTamanho(int t);
	int getTamanho();

	void setEstado(bool e);
	bool getEstado();

	void setMorte(int m);
	int getMorte();

	void setProx_p(Planta *p);
	Planta* getProx_p();

	void inicializa(int cod, corRGB c, posXY p, int t, bool e);
	void morte_mm();

};



#endif
