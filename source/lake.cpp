#include <lake.h>

void Lago::setCodigo(int c){
	Lago::codigo = c;
}
int Lago::getCodigo(){
	return Lago::codigo;
}

void Lago::setCor(corRGB c){
	Lago::cor = c;
}
corRGB Lago::getCor(){
	return Lago::cor;
}

void Lago::setPosicao(posXY p){
	Lago::posicao = p;
}
posXY Lago::getPosicao(){
	return Lago::posicao;
}

void Lago::setTamanho_atual(int t){
	Lago::tamanho_atual = t;
}
int Lago::getTamanho_atual(){
	return Lago::tamanho_atual;
}

void Lago::setTamanho(int t){
	Lago::tamanho = t;
}
int Lago::getTamanho(){
	return Lago::tamanho;
}

void Lago::setProx_l(Lago *l){
	Lago::prox_l = l;
}
Lago* Lago::getProx_l(){
	return Lago::prox_l;
}

void Lago::inicializa(int cod, corRGB c, posXY p, int t){
	if (c.r == -1)     Lago::cor.r = 100;      else    Lago::cor.r = c.r;
	if (c.g == -1)     Lago::cor.g = 180;      else    Lago::cor.g = c.g;
	if (c.b == -1)     Lago::cor.b = 250;    else    Lago::cor.b = c.b;

	Lago::codigo = cod;
	Lago::posicao = p;
	Lago::tamanho = t;
	Lago::prox_l = NULL;
	Lago::tamanho_atual = 100;  //porcentagem
}

