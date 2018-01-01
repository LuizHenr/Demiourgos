#include <creature.h>





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

void Criatura::kill(){
	Criatura::posicao.x = -1;
	Criatura::posicao.y = -1;
}

int Criatura::isAlive(){
	if (Criatura::posicao.x == -1 || Criatura::posicao.y == -1)
		return 0;
	return 1;
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

