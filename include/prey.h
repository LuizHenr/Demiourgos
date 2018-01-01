#ifndef CLASSES_H
#define CLASSES_H

//#include <math.h>
//#include <pthread.h>
//#include <funcoes.h>
//#include <stdlib.h>
#include <creature.h>

class Presa : public Criatura{
private:
	int cod_ameaca;
	Presa *prox_c;

public:
	void nascer(int c, bool s, Presa mae, Presa pai);
	Presa* getProx_c();
	int getCod_ameaca();

	void setProx_c(Presa *p);
	void setCod_ameaca(int c);


};




#endif
