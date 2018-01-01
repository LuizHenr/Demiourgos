#include <prey.h>


void Presa::nascer(int c, bool s, Presa mae, Presa pai){
	Presa::codigo = c;
	Presa::cod_ameaca = -1;
	Presa::cod_parceiro = -1;
	Presa::cod_alvo_fome = -1;
	Presa::cod_alvo_sede = -1;
	Presa::cod_mae = -1;
	Presa::prox_c = NULL;
	Presa::categoria = 1;

	if (mae.getVelocidade() >= 5 && pai.getVelocidade() >= 5 && pai.isAlive() && mae.isAlive()){
		Presa::velocidade = round(((mae.getVelocidade() + pai.getVelocidade()) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade() + pai.getVelocidade()) / 2.0)-5):floor(((mae.getVelocidade() + pai.getVelocidade()) / 2.0)-5);
	}
	else{
		if (mae.getVelocidade() >= 5 && pai.getVelocidade() < 5 && pai.isAlive() && mae.isAlive()){ // o pai passou p categoria 4 durante a gestacao do bebe
			Presa::velocidade = round(((mae.getVelocidade() + pai.getVelocidade() + 5) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade() + pai.getVelocidade()+5) / 2.0)-5):floor(((mae.getVelocidade() + pai.getVelocidade()+5) / 2.0)-5);
		}
		else if (pai.getVelocidade() >= 5 && mae.getVelocidade() < 5 && pai.isAlive() && mae.isAlive()){   // a mae passou p categoria 4 durante a gestacao do bebe
			Presa::velocidade = round(((mae.getVelocidade() + 5 + pai.getVelocidade()) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade()+5 + pai.getVelocidade()) / 2.0)-5):floor(((mae.getVelocidade()+5 + pai.getVelocidade()) / 2.0)-5);
		}
		else if (mae.getVelocidade() >= 0 && pai.getVelocidade() >= 0 && mae.getVelocidade() <= 9 && pai.getVelocidade() <= 9 && pai.isAlive() && mae.isAlive()){
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


