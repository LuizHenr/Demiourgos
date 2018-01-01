#include <plant.h>




void Planta::setCodigo(int c){
	Planta::codigo = c;
}
int Planta::getCodigo(){
	return Planta::codigo;
}

void Planta::setCor(corRGB c){
	Planta::cor = c;
}
corRGB Planta::getCor(){
	return Planta::cor;
}

void Planta::setPosicao(posXY p){
	Planta::posicao = p;
}
posXY Planta::getPosicao(){
	return Planta::posicao;
}

void Planta::setTamanho(int t){
	Planta::tamanho = t;
}
int Planta::getTamanho(){
	return Planta::tamanho;
}

void Planta::setEstado(bool e){
	Planta::estado = e;
}
bool Planta::getEstado(){
	return Planta::estado;
}

void Planta::setMorte(int m){
	Planta::morte = m;
}
int Planta::getMorte(){
	return Planta::morte;
}

void Planta::setProx_p(Planta *p){
	Planta::prox_p = p;
}
Planta* Planta::getProx_p(){
	return Planta::prox_p;
}


void Planta::inicializa(int cod, corRGB c, posXY p, int t, bool e){
	if (c.r == -1)     Planta::cor.r = 0;      else    Planta::cor.r = c.r;
	if (c.g == -1)     Planta::cor.g = 200;    else    Planta::cor.g = c.g;
	if (c.b == -1)     Planta::cor.b = 0;      else    Planta::cor.b = c.b;

	Planta::codigo = cod;
	Planta::posicao = p;
	Planta::tamanho = t;
	Planta::estado = e;
	Planta::morte = 0;
	Planta::prox_p = NULL;
}


void Planta::morte_mm(){
	Planta::morte--;
}



