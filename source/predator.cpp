#include <predator.h>


void Predador::nascer(int c, bool s, Predador mae, Predador pai){
	Predador::codigo = c;
	Predador::cod_parceiro = -1;
	Predador::cod_alvo_fome = -1;
	Predador::cod_alvo_sede = -1;
	Predador::cod_mae = -1;
	Predador::prox_c = NULL;
	Predador::categoria = 1;
	//velocidade= rand()%4;
	if (mae.getVelocidade() >= 5 && mae.isAlive() && pai.getVelocidade() >= 5 && pai.isAlive()){
		Predador::velocidade = round(((mae.getVelocidade() + pai.getVelocidade()) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade() + pai.getVelocidade()) / 2.0)-5):floor(((mae.getVelocidade() + pai.getVelocidade()) / 2.0)-5);
	}
	else{
		if (mae.getVelocidade() >= 5 && mae.isAlive()){ // o pai passou p categoria 4 durante a gestacao do bebe
			Predador::velocidade = round(((mae.getVelocidade() + pai.getVelocidade() + 5) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade() + pai.getVelocidade()+5) / 2.0)-5):floor(((mae.getVelocidade() + pai.getVelocidade()+5) / 2.0)-5);
		}
		else if (pai.getVelocidade() >= 5 && pai.isAlive()){   // a mae passou p categoria 4 durante a gestacao do bebe
			Predador::velocidade = round(((mae.getVelocidade() + 5 + pai.getVelocidade()) / 2.0) - 5);//velocidade = aux?ceil(((mae.getVelocidade()+5 + pai.getVelocidade()) / 2.0)-5):floor(((mae.getVelocidade()+5 + pai.getVelocidade()) / 2.0)-5);
		}
		else if (mae.getVelocidade() >= 0 && pai.getVelocidade() >= 0 && mae.getVelocidade() <= 9 && pai.getVelocidade() <= 9 && mae.isAlive() && pai.isAlive()){
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


