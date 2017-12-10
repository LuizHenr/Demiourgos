#include <classes.h>



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






//int qt_col=le_info("qt_col_campo"),qt_lin= le_info("qt_lin_campo");

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






void Criatura::gestacao_mm(){
	Criatura::gestacao--;
}

void Criatura::resguardo_mm(){
	Criatura::resguardo--;
}

void Criatura::idade_pp(){
	Criatura::idade++;
}

void Criatura::fome_mm(){
	Criatura::fome--;
}
void Criatura::sede_mm(){
	Criatura::sede--;
}

void Criatura::mover(posXY posicao2, dimXY dim_campo){   //recebe a posicao p se mover	

	if (posicao2.x <= 0 + Criatura::tamanho)
		posicao2.x = 1 + Criatura::tamanho;
	if (posicao2.x >= dim_campo.x - Criatura::tamanho)   //limite
		posicao2.x = dim_campo.x - 1 - Criatura::tamanho;
	if (posicao2.y <= 0 + Criatura::tamanho)
		posicao2.y = 1 + Criatura::tamanho;
	if (posicao2.y >= dim_campo.y - Criatura::tamanho)   //limite
		posicao2.y = dim_campo.y - 1 - Criatura::tamanho;

	Criatura::posicao = posicao2;
}


posXY Criatura::aproximar(posXY posicao2){ //linha e coluna (posicao média) da presa mais proximo     //--refazer usando a funcao calcula_distamcia
	int distancia; //distancia entre a presa e o predador mais proximo
	int nova_distancia; //distancia entre a presa e o predador mais proximo
	posXY nova_posicao; //lin_aux,col_aux;//

	//var de distancia recebem o valor absoluto da distancia entre os pontos
	distancia = calcula_distancia(posicao, posicao2);

	do{
		/*sorteado a posicao
		-coluna-        -linha-
		0 1 2          0 0 0
		0 1 2          1 1 1
		0 1 2          2 2 2
		*/
		nova_posicao.y = (posicao.y - 1) + rand() % 3;//
		nova_posicao.x = (posicao.x - 1) + rand() % 3;//

		//var de distancia aux recebem a nova distancia entre a presa e o predador mais proximo
		nova_distancia = calcula_distancia(nova_posicao, posicao2);

	} while (nova_distancia >= distancia);

	return nova_posicao;
}


posXY Criatura::afastar(posXY posicao2){ //linha e coluna (posicao média) da presa mais proximo     //--refazer usando a funcao calcula_distamcia
	int distancia; //distancia entre a presa e o predador mais proximo
	int nova_distancia; //distancia entre a presa e o predador mais proximo
	posXY nova_posicao; //lin_aux,col_aux;//

	//var de distancia recebem o valor absoluto da distancia entre os pontos
	distancia = calcula_distancia(posicao, posicao2);



	do{
		/*sorteado a posicao
		-coluna-        -linha-
		0 1 2          0 0 0
		0 1 2          1 1 1
		0 1 2          2 2 2
		*/
		nova_posicao.y = (posicao.y - 1) + rand() % 3;//
		nova_posicao.x = (posicao.x - 1) + rand() % 3;//

		//var de distancia aux recebem a nova distancia entre a presa e o predador mais proximo
		nova_distancia = calcula_distancia(nova_posicao, posicao2);



	} while (nova_distancia >= distancia);

	return nova_posicao;
}




int Criatura::getCodigo(){
	return Criatura::codigo;
}
posXY Criatura::getPosicao(){
	return Criatura::posicao;
}
corRGB Criatura::getCor(){
	return Criatura::cor;
}
bool Criatura::getSexo(){
	return Criatura::sexo;
}
pthread_t Criatura::getMove_td(){
	return Criatura::move_td;
}
int Criatura::getVelocidade(){
	if (Criatura::velocidade == -1){
		if (Criatura::categoria == 1 || Criatura::categoria == 4)
			Criatura::velocidade = rand() % 5;
		else
			Criatura::velocidade = 5 + rand() % 5;
	}

	return Criatura::velocidade;
}
int Criatura::getIdade_max(){
	return Criatura::idade_max;
}
int Criatura::getVisao_reproducao_max(){
	return Criatura::visao_reproducao_max;
}
int Criatura::getArea_interesse(){
	return Criatura::area_interesse;
}
int Criatura::getTamanho(){
	return Criatura::tamanho;
}
int Criatura::getCategoria(){
	return Criatura::categoria;
}
int Criatura::getSentidos(){
	return Criatura::sentidos;
}
int Criatura::getVisao_reproducao(){
	return Criatura::visao_reproducao;
}
int Criatura::getCod_mae(){
	return Criatura::cod_mae;
}
int Criatura::getCod_parceiro(){
	return Criatura::cod_parceiro;
}
bool Criatura::getFertil(){
	if (Criatura::categoria == 2 || Criatura::categoria == 3)
		return true;
	else
		return false;
}

int Criatura::getResguardo(){
	return Criatura::resguardo;
}
int Criatura::getGestacao(){
	return Criatura::gestacao;
}
int Criatura::getIdade(){
	return Criatura::idade;
}
int Criatura::getFome(){
	return Criatura::fome;
}
int Criatura::getSede(){
	return Criatura::sede;
}
int Criatura::getCod_alvo_fome(){
	return Criatura::cod_alvo_fome;
}
int Criatura::getCod_alvo_sede(){
	return Criatura::cod_alvo_sede;
}
bool Criatura::getDoenca(){
	return Criatura::doenca;
}
bool Criatura::getMutacao(){
	return Criatura::mutacao;
}
bool Criatura::getCamuflado(){
	return Criatura::camuflado;
}

void Criatura::setCor(corRGB c){
	Criatura::cor = c;
}

void Criatura::setCod_parceiro(int c){
	Criatura::cod_parceiro = c;
}
void Criatura::setCod_mae(int c){
	Criatura::cod_mae = c;
}
//    void setFertil(bool f){
//       fertil=f;     }
void Criatura::setVelocidade(int v){
	Criatura::velocidade = v;
}
void Criatura::setTamanho(int t){
	Criatura::tamanho = t;
}
void Criatura::setPosicao(posXY p){
	Criatura::posicao = p;
}
void Criatura::setCategoria(int c){
	Criatura::categoria = c;
}
void Criatura::setMove_td(pthread_t m){
	Criatura::move_td = m;
}
void Criatura::setIdade_max(int ida, int var){
	Criatura::idade_max = (ida - (ida*var / 100)) + rand() % ((ida*var * 2 / 100) + 1);
}
void Criatura::setVisao_reproducao_max(int v){
	Criatura::visao_reproducao_max = v;
}
void Criatura::setArea_interesse(int a){
	Criatura::area_interesse = a;
}
void Criatura::setSentidos(int s){
	Criatura::sentidos = s;
}
void Criatura::setVisao_reproducao(int v){
	Criatura::visao_reproducao = v;
}
void Criatura::setResguardo(int r){
	Criatura::resguardo = r;
}
void Criatura::setGestacao(int g){
	Criatura::gestacao = g;
}
void Criatura::setIdade(int i){
	Criatura::idade = i;
}
void Criatura::setFome(int f){
	Criatura::fome = f;
}
void Criatura::setSede(int s){
	Criatura::sede = s;
}
void Criatura::setCod_alvo_fome(int c){
	Criatura::cod_alvo_fome = c;
}
void Criatura::setCod_alvo_sede(int c){
	Criatura::cod_alvo_sede = c;
}
void Criatura::setDoenca(bool d){
	Criatura::doenca = d;
}
void Criatura::setMutacao(bool m){
	Criatura::mutacao = m;
}
void Criatura::setCamuflado(bool c){
	Criatura::camuflado = c;
}




void Presa::nascer(int c, bool s, Presa mae, Presa pai){
	Presa::codigo = c;
	Presa::cod_ameaca = -1;
	Presa::cod_parceiro = -1;
	Presa::cod_alvo_fome = -1;
	Presa::cod_alvo_sede = -1;
	Presa::cod_mae = -1;
	Presa::prox_c = NULL;
	Presa::categoria = 1;

	if (mae.getVelocidade() >= 5 && pai.getVelocidade() >= 5){
		Presa::velocidade = round(((mae.getVelocidade() + pai.getVelocidade()) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade() + pai.getVelocidade()) / 2.0)-5):floor(((mae.getVelocidade() + pai.getVelocidade()) / 2.0)-5);
	}
	else{
		if (mae.getVelocidade() >= 5 && pai.getVelocidade() < 5){ // o pai passou p categoria 4 durante a gestacao do bebe
			Presa::velocidade = round(((mae.getVelocidade() + pai.getVelocidade() + 5) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade() + pai.getVelocidade()+5) / 2.0)-5):floor(((mae.getVelocidade() + pai.getVelocidade()+5) / 2.0)-5);
		}
		else if (pai.getVelocidade() >= 5 && mae.getVelocidade() < 5){   // a mae passou p categoria 4 durante a gestacao do bebe
			Presa::velocidade = round(((mae.getVelocidade() + 5 + pai.getVelocidade()) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade()+5 + pai.getVelocidade()) / 2.0)-5):floor(((mae.getVelocidade()+5 + pai.getVelocidade()) / 2.0)-5);
		}
		else if (mae.getVelocidade() >= 0 && pai.getVelocidade() >= 0 && mae.getVelocidade() <= 9 && pai.getVelocidade() <= 9){
			Presa::velocidade = round(((mae.getVelocidade() + 5 + pai.getVelocidade() + 5) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade()+5 + pai.getVelocidade()+5) / 2.0)-5):floor(((mae.getVelocidade()+5 + pai.getVelocidade()+5) / 2.0)-5);
		}
		else{
			Presa::velocidade = -1;
		}
	}




	if (mae.getCor().r >= 0 && mae.getCor().r <= 255 &&
		mae.getCor().g >= 0 && mae.getCor().g <= 255 &&
		mae.getCor().b >= 0 && mae.getCor().b <= 255 &&
		pai.getCor().r >= 0 && pai.getCor().r <= 255 &&
		pai.getCor().g >= 0 && pai.getCor().g <= 255 &&
		pai.getCor().b >= 0 && pai.getCor().b <= 255){   //cores dos pais válidas

		Presa::cor.r = (((mae.getCor().r + pai.getCor().r) / 2) - 5) + rand() % 11;
		Presa::cor.g = (((mae.getCor().g + pai.getCor().g) / 2) - 5) + rand() % 11;
		Presa::cor.b = (((mae.getCor().b + pai.getCor().b) / 2) - 5) + rand() % 11;
	}
	else{
		if (mae.getCor().r >= 0 && mae.getCor().r <= 255 &&
			mae.getCor().g >= 0 && mae.getCor().g <= 255 &&
			mae.getCor().b >= 0 && mae.getCor().b <= 255){     //mae ok
			Presa::cor.r = (mae.getCor().r - 5) + rand() % 11;
			Presa::cor.g = (mae.getCor().g - 5) + rand() % 11;
			Presa::cor.b = (mae.getCor().b - 5) + rand() % 11;
		}
		else if (pai.getCor().r >= 0 && pai.getCor().r <= 255 &&
			pai.getCor().g >= 0 && pai.getCor().g <= 255 &&
			pai.getCor().b >= 0 && pai.getCor().b <= 255){     //pai ok
			Presa::cor.r = (pai.getCor().r - 5) + rand() % 11;
			Presa::cor.g = (pai.getCor().g - 5) + rand() % 11;
			Presa::cor.b = (pai.getCor().b - 5) + rand() % 11;
		}
		else{
			Presa::cor.r = rand() % 256;
			Presa::cor.g = rand() % 256;
			Presa::cor.b = rand() % 256;
		}

	}

	if (Presa::cor.r<0)    Presa::cor.r = 0;
	if (Presa::cor.r>255)  Presa::cor.r = 255;
	if (Presa::cor.g<0)    Presa::cor.g = 0;
	if (Presa::cor.g>255)  Presa::cor.g = 255;
	if (Presa::cor.b<0)    Presa::cor.b = 0;
	if (Presa::cor.b>255)  Presa::cor.b = 255;



	//printf(" *%d*  corPresa = %d %d %d\n",c,cor.r,cor.g,cor.b);
	Presa::sexo = s;
	Presa::idade = 0;
	Presa::posicao.x = mae.getPosicao().x;
	Presa::posicao.y = mae.getPosicao().y;
	Presa::experiencia = 0;
	// gestante=false;
	Presa::gestacao = 0;
	Presa::resguardo = 0;

}

Presa* Presa::getProx_c(){
	return Presa::prox_c;
}
int Presa::getCod_ameaca(){
	return Presa::cod_ameaca;
}

void Presa::setProx_c(Presa *p){
	Presa::prox_c = p;
}
void Presa::setCod_ameaca(int c){
	Presa::cod_ameaca = c;
}



void Predador::nascer(int c, bool s, Predador mae, Predador pai){
	Predador::codigo = c;
	Predador::cod_parceiro = -1;
	Predador::cod_alvo_fome = -1;
	Predador::cod_alvo_sede = -1;
	Predador::cod_mae = -1;
	Predador::prox_c = NULL;
	Predador::categoria = 1;
	//velocidade= rand()%4;
	if (mae.getVelocidade() >= 5 && pai.getVelocidade() >= 5){
		Predador::velocidade = round(((mae.getVelocidade() + pai.getVelocidade()) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade() + pai.getVelocidade()) / 2.0)-5):floor(((mae.getVelocidade() + pai.getVelocidade()) / 2.0)-5);
	}
	else{
		if (mae.getVelocidade() >= 5){ // o pai passou p categoria 4 durante a gestacao do bebe
			Predador::velocidade = round(((mae.getVelocidade() + pai.getVelocidade() + 5) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade() + pai.getVelocidade()+5) / 2.0)-5):floor(((mae.getVelocidade() + pai.getVelocidade()+5) / 2.0)-5);
		}
		else if (pai.getVelocidade() >= 5){   // a mae passou p categoria 4 durante a gestacao do bebe
			Predador::velocidade = round(((mae.getVelocidade() + 5 + pai.getVelocidade()) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade()+5 + pai.getVelocidade()) / 2.0)-5):floor(((mae.getVelocidade()+5 + pai.getVelocidade()) / 2.0)-5);
		}
		else if (mae.getVelocidade() >= 0 && pai.getVelocidade() >= 0 && mae.getVelocidade() <= 9 && pai.getVelocidade() <= 9){
			Predador::velocidade = round(((mae.getVelocidade() + 5 + pai.getVelocidade() + 5) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade()+5 + pai.getVelocidade()+5) / 2.0)-5):floor(((mae.getVelocidade()+5 + pai.getVelocidade()+5) / 2.0)-5);
		}
		else{
			Predador::velocidade = -1;
		}
	}


	if (mae.getCor().r >= 0 && mae.getCor().r <= 255 &&
		mae.getCor().g >= 0 && mae.getCor().g <= 255 &&
		mae.getCor().b >= 0 && mae.getCor().b <= 255 &&
		pai.getCor().r >= 0 && pai.getCor().r <= 255 &&
		pai.getCor().g >= 0 && pai.getCor().g <= 255 &&
		pai.getCor().b >= 0 && pai.getCor().b <= 255){   //cores dos pais válidas

		Predador::cor.r = (((mae.getCor().r + pai.getCor().r) / 2) - 5) + rand() % 11;
		Predador::cor.g = (((mae.getCor().g + pai.getCor().g) / 2) - 5) + rand() % 11;
		Predador::cor.b = (((mae.getCor().b + pai.getCor().b) / 2) - 5) + rand() % 11;
	}
	else{
		if (mae.getCor().r >= 0 && mae.getCor().r <= 255 &&
			mae.getCor().g >= 0 && mae.getCor().g <= 255 &&
			mae.getCor().b >= 0 && mae.getCor().b <= 255){     //mae ok
			Predador::cor.r = (mae.getCor().r - 5) + rand() % 11;
			Predador::cor.g = (mae.getCor().g - 5) + rand() % 11;
			Predador::cor.b = (mae.getCor().b - 5) + rand() % 11;
		}
		else if (pai.getCor().r >= 0 && pai.getCor().r <= 255 &&
			pai.getCor().g >= 0 && pai.getCor().g <= 255 &&
			pai.getCor().b >= 0 && pai.getCor().b <= 255){     //pai ok
			Predador::cor.r = (pai.getCor().r - 5) + rand() % 11;
			Predador::cor.g = (pai.getCor().g - 5) + rand() % 11;
			Predador::cor.b = (pai.getCor().b - 5) + rand() % 11;
		}
		else{
			Predador::cor.r = rand() % 256;
			Predador::cor.g = rand() % 256;
			Predador::cor.b = rand() % 256;
		}

	}

	if (Predador::cor.r<0)    Predador::cor.r = 0;
	if (Predador::cor.r>255)  Predador::cor.r = 255;
	if (Predador::cor.g<0)    Predador::cor.g = 0;
	if (Predador::cor.g>255)  Predador::cor.g = 255;
	if (Predador::cor.b<0)    Predador::cor.b = 0;
	if (Predador::cor.b>255)  Predador::cor.b = 255;


	//if(mae.getCor().r==-1  || pai.getCor().r==-1)     cor.r= rand()%256;    else    cor.r= (((mae.getCor().r + pai.getCor().r) / 2) - 5 ) + rand()%11;
	//if(mae.getCor().g==-1  || pai.getCor().g==-1)     cor.g= rand()%256;    else    cor.g= (((mae.getCor().g + pai.getCor().g) / 2) - 5 ) + rand()%11;
	//if(mae.getCor().r==-1  || pai.getCor().r==-1)     cor.b= rand()%256;    else    cor.b= (((mae.getCor().b + pai.getCor().b) / 2) - 5 ) + rand()%11;

	Predador::sexo = s;
	Predador::idade = 0;
	Predador::posicao.x = mae.getPosicao().x;
	Predador::posicao.y = mae.getPosicao().y;
	Predador::experiencia = 0;
	//   gestante=false;
	Predador::gestacao = 0;
	Predador::resguardo = 0;

}


Predador* Predador::getProx_c(){
	return Predador::prox_c;
}

void Predador::setProx_c(Predador *p){
	Predador::prox_c = p;
}




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



