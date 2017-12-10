#ifndef CLASSES_H
#define CLASSES_H

#include <math.h>
#include <pthread.h>
#include <funcoes.h>
#include <stdlib.h>



#define MAX_DIMENSAO_X 1920 // 1900px
#define MAX_DIMENSAO_Y 1080 // 1050px



//class Criatura;
//class Planta;
//class Lago;


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




class Criatura{
protected:
	int codigo;
	int cod_mae;
	int cod_parceiro;  //codigo do ultimo parceiro visto (criatura do mesmo sexo + proximo)
	int cod_alvo_fome;
	int cod_alvo_sede;

	int categoria;
	corRGB cor;  //cores RGB
	bool sexo;  //1 - femea     0 - macho
	posXY posicao;//int lin,col; //linha e coluna (posicao) da presa
	int velocidade;
	int tamanho;  //raio
	int fome;
	int sede;
	bool doenca;
	bool mutacao;
	bool camuflado;

	//     bool fertil;   //se TRUE  indica q a criat  esta fertil     (categorias 2 ou 3) 
	int idade;//int ciclos;  //idade
	int idade_max;  //idade maxima em segundos
	int resguardo;  //qt de ciclos em reguardo       -  periodo em que as presas femininas passam sem procriar
	//        int meses_ferteis[3];
	// bool gestante;  //1- sim   0-nao             enquanto gestante.. nao estar disponivel p procriar
	int gestacao;  //meses q a femea fica com o filhote na barriga
	int experiencia;
	int sentidos;
	int visao_reproducao;
	int visao_reproducao_max;
	int area_interesse;
	pthread_t move_td;  //thread de movimento


public:

	void gestacao_mm();
	void resguardo_mm();
	void idade_pp();
	void fome_mm();
	void sede_mm();

	void mover(posXY posicao2, dimXY dim_campo);

	posXY aproximar(posXY posicao2);

	posXY afastar(posXY posicao2);
	int getCodigo();
	posXY getPosicao();
	corRGB getCor();
	bool getSexo();
	pthread_t getMove_td();
	int getVelocidade();
	int getIdade_max();
	int getVisao_reproducao_max();
	int getArea_interesse();
	int getTamanho();
	int getCategoria();
	int getSentidos();
	int getVisao_reproducao();
	int getCod_mae();
	int getCod_parceiro();
	bool getFertil();
	int getResguardo();
	int getGestacao();
	int getIdade();
	int getFome();
	int getSede();
	int getCod_alvo_fome();
	int getCod_alvo_sede();
	bool getDoenca();
	bool getMutacao();
	bool getCamuflado();

	void setCor(corRGB c);

	void setCod_parceiro(int c);
	void setCod_mae(int c);
	void setVelocidade(int v);
	void setTamanho(int t);
	void setPosicao(posXY p);
	void setCategoria(int c);
	void setMove_td(pthread_t m);
	void setIdade_max(int ida, int var);
	void setVisao_reproducao_max(int v);
	void setArea_interesse(int a);
	void setSentidos(int s);
	void setVisao_reproducao(int v);
	void setResguardo(int r);
	void setGestacao(int g);
	void setIdade(int i);
	void setFome(int f);
	void setSede(int s);
	void setCod_alvo_fome(int c);
	void setCod_alvo_sede(int c);
	void setDoenca(bool d);
	void setMutacao(bool m);
	void setCamuflado(bool c);

};


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


class Predador : public Criatura{
private:
	Predador *prox_c;

public:
	void nascer(int c, bool s, Predador mae, Predador pai);

	Predador* getProx_c();

	void setProx_c(Predador *p);

};



class Planta{
private:
	int codigo;
	corRGB cor;
	posXY posicao;  //do superior esquedo
	int tamanho;  // 1-pequeno   2-grande
	bool estado; // 0-morto  1-vivo
	int morte;  //tempo que a planta est� morta
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




//extern class Lago;
//extern class Criatura;
//extern class Presa;
//extern class Predador;
//extern class Planta;





#endif
