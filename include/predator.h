#ifndef PREDATOR_H
#define PREDATOR_H

//#include <math.h>
//#include <pthread.h>
//#include <funcoes.h>
//#include <stdlib.h>
#include <creature.h>


class Predador : public Criatura{
private:
	Predador *prox_c;

public:
	void nascer(int c, bool s, Predador mae, Predador pai);

	Predador* getProx_c();

	void setProx_c(Predador *p);

};


#endif
