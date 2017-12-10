#include <funcoes.h>
#include <classes.h>

#include <graphics.h>
#include <cstdlib>
//#include <iostream>
//#include <pthread.h>
//#include <time.h>


#include <direct.h>  
#include <iostream>
#include <pthread.h>


#define M_PI       3.14159265358979323846




       //   PRESAS 1.6.8     em processo

using namespace std;


                /*  Variáveis Globais*/
    Campo cp;    
    Presa *ps1;
    Predador *pd1;
    Planta *pl1;
    Lago *lg1;
    pthread_mutex_t p_key;      //Cria um objeto Pthread_mutex_t para pausar a execucao das threads (semáforo) 
    
    pthread_t ps_, pd_;

    bool pausa = false;   
    long int tempo = 0;  

    int cps_m, cps_f;
    int cpd_m, cpd_f;   
    
    
    
    int pd_sel=0;
    
    
     int mod_mutacao_cor;
     int mod_doenca;
     int mod_sede;
     int mod_lago;
     int mod_fome_presa;
     int mod_planta;
     int mod_fuga_presa;
     int mod_mudanca_cor_ambiente;
     int mod_predador_camuflagem;
    
     bool borda=true;
    
    
    
                /*  Declaração das funções*/            
Presa* criar_presa(int,bool,Presa,Presa);
Predador* criar_predador(int,bool,Predador,Predador);
Planta* criar_planta(int, corRGB, posXY, int, bool); 
Lago* criar_lago(int,corRGB,posXY,int);

void matar_presa(int);
void matar_predador(int);

void *movimentar_presa(void *);
void *movimentar_predador(void *);

posXY sorteia_posicao(posXY,int,int);   

Presa* getPresa (int);
Predador* getPredador (int);
Planta* getPlanta (int);
Lago* getLago(int);

bool atacar(Predador*, Presa*,int,int);  
bool fugir(Predador*, Presa*,int,int);  



void divide_campo(dimXY dimensao,int qt_areas,int cont_areas,int *cols,int cont_cols,int *lins,int cont_lins){
    int i,p; 
    float dimx,dimy,c_cols,c_lins;
    dimx = dimensao.x;
	dimy = dimensao.y;
	c_cols = cont_cols;
	c_lins = cont_lins;
    
    if(cont_areas < qt_areas){
	    //printf("ainda preciso dividir :P  \n"); 
	    if((cont_cols < cont_lins) || (dimensao.x >= dimensao.y && cont_cols == cont_lins)){
			//printf("cont_lins > cont_cols...  \n"); 
	        p=cont_cols;
	        for(i=1;i<(cont_cols+1)*2;i+=2){
	            //printf("i=%d",i);
			    cols[p] = (dimx / ((c_cols+1)*2))*i;
			    p++;
			} 
			//printf("saiu do for com o i=%d",i);
			cont_cols=i-2;
			cont_areas = cont_areas*2;
	    }
	    else{
			//printf("cont_cols > cont_lins...  \n"); 
			p=cont_lins;
			 for(i=1;i<(cont_lins+1)*2;i+=2){
	            //printf("i=%d",i);
			    lins[p] = (dimy / ((c_lins+1)*2))*i;
			    p++;
			} 
			//printf("saiu do for com o i=%d",i);
			cont_lins=i-2;
			cont_areas = cont_areas*2;
		}
	    
	    //printf("indo para o proximo com %d cols e %d lins\n\n",cont_cols,cont_lins); 
	    //for(int c=0;c<100;c++)
		//	if(cols[c]!=0)
		//	   printf("width %d\n",cols[c]);
		
	    //for(int c=0;c<100;c++)
		//	if(lins[c]!=0)
		//		printf("height %d\n",lins[c]);
			
	
	    //printf("\ncont areas = %d\n",cont_areas);
	    //printf("\n");
	    divide_campo(dimensao, qt_areas,cont_areas,cols,cont_cols,lins, cont_lins);
    } 
}


/*
void divide_campo(posXY inicio,dimXY dimensao,int qt_areas,int *cont_areas,int *cols,int *cont_cols,int *lins,int *cont_lins){
    printf("cheguei  \n");
	int aux=0;
	
	//if(cont_areas<qt_areas){  //o ambiente ainda precisa ser dividido
		printf("o ambiente ainda precisa ser dividido   \n ");
		if(dimensao.x >= dimensao.y){  //existem mais colunas do que linhas, entao, divida verticalmente no centro 
		  for(int i = 0 ;i < 10;i++){
			if(floor(inicio.x + (dimensao.x / 2) == cols[i])){
				aux=1;
			}
		  }
		  
		  if((*cont_areas + (*cont_lins+1) <=qt_areas) || (aux==1)){
				
			if(aux==0){
		
				printf("cols %d >=  %d lins     \n",dimensao.x,dimensao.y);
				//cols = (int*) malloc(sizeof(int)*(cont_cols+1));
				cols[*cont_cols] = floor(inicio.x + (dimensao.x / 2)); 
				
				printf("nhac %d\n",cols[*cont_cols]);
				
				
				*cont_cols++;
				*cont_areas = *cont_areas + (*cont_lins+1);
		    }
		    else{
				printf("coluna repetida");}
			printf("cont areas = %d\n",*cont_areas);
			dimensao.x = dimensao.x/2;
			divide_campo(inicio,dimensao,qt_areas,cont_areas,cols, cont_cols, lins, cont_lins);
			
			inicio.x = cols[*cont_cols-1];
			divide_campo(inicio,dimensao,qt_areas,cont_areas,cols, cont_cols, lins, cont_lins);
		 }
		}
		else{
			for(int i = 0 ;i < 10;i++){
			  if(floor(inicio.y + (dimensao.y / 2) == lins[i])){
				aux=1;
			  }
		    }
			if((*cont_areas + (*cont_cols+1) <=qt_areas) || (aux==1)){
			
			if(aux==0){
				
				printf("cols %d <  %d lins     \n",dimensao.x,dimensao.y);
				//cols = (int*) malloc(sizeof(int)*(cont_cols+1));
				lins[*cont_lins] = floor(inicio.y + (dimensao.y / 2)); 
				
				printf("nhal %d\n",lins[*cont_lins]);
				
				
				*cont_lins++;
				*cont_areas = *cont_areas + (*cont_cols+1);
		    }
		    else{
				printf("linha repetida");
		    }
		    
			printf("cont areas = %d\n",*cont_areas);
			dimensao.y = dimensao.y/2;
			divide_campo(inicio,dimensao,qt_areas,cont_areas,cols, cont_cols, lins, cont_lins);
			
			inicio.y = lins[*cont_lins-1];
			divide_campo(inicio,dimensao,qt_areas,cont_areas,cols, cont_cols, lins, cont_lins);
		}
		}
	//}else{  printf("ja tenho areas suficientes\n");
	//	}
	
}
*/
       
void imprime_campo_descricao();
void imprime_info_presa(Presa *);
void imprime_info_predador(Predador *);
void imprime_info_planta(Planta *);
void imprime_cabecalho(char*[],int);
void limpa_descricao();

void chama_configuration(char*);



              // Funcoes de Experimentos 
     
    double var_r_ps,media_r_ps;
    double var_g_ps,media_g_ps;
    double var_b_ps,media_b_ps;
    double var_r_pd,media_r_pd;
    double var_g_pd,media_g_pd;
    double var_b_pd,media_b_pd;
    double var_visao_ps,media_visao_ps;
    double var_visao_pd,media_visao_pd;
    double var_velocidade_ps,media_velocidade_ps;
    double var_velocidade_pd,media_velocidade_pd;
    double var_visao_rep_ps,media_visao_rep_ps;
    double var_visao_rep_pd,media_visao_rep_pd;
    
    
    
    void calcula_media(){                //calcula a media das cores red, green e blue em cada criatura do tipo presa
       long int soma_r_ps,soma_g_ps,soma_b_ps;
       long int soma_r_pd,soma_g_pd,soma_b_pd;
       int cont_ps,cont_pd;
       
	   //corRGB soma_ps,soma_pd;   
       double soma_visao_ps,soma_visao_pd;
       double soma_visao_rep_ps,soma_visao_rep_pd;
       double soma_velocidade_ps,soma_velocidade_pd;
       int max_visao_ps,max_visao_pd;
       
       max_visao_ps = le_info("campo_max_visao_presa");
       max_visao_pd = le_info("campo_max_visao_predador");
       
       
       Presa *ps_aux;
	   Predador *pd_aux;
       
       soma_r_ps=soma_g_ps=soma_b_ps = 0;
       soma_r_pd=soma_g_pd=soma_b_pd = 0;
       cont_ps=cont_pd = 0; 
	   soma_visao_ps= soma_visao_pd = 0;
	   soma_visao_rep_ps= soma_visao_rep_pd = 0;
       soma_velocidade_ps= soma_velocidade_pd = 0;
       media_r_ps= media_g_ps= media_b_ps = -1;
       media_r_pd= media_g_pd= media_b_pd = -1;
       media_visao_ps = media_visao_pd = -1;
       media_visao_rep_ps = media_visao_rep_pd = -1;
       media_velocidade_ps = media_velocidade_pd = -1;
       
       
       
       
           //save preys information
       ps_aux=ps1;
       while(ps_aux!=NULL){
		   cont_ps++;	
		   if(ps_aux->getCor().r>255 ||ps_aux->getCor().g>255 ||ps_aux->getCor().b>255 || ps_aux->getCor().r<0 ||ps_aux->getCor().g<0 ||ps_aux->getCor().b<0){
	 		  soma_r_ps+=128;
              soma_g_ps+=128;
              soma_b_ps+=128;
             // printf("\n**bugs: r%d g%d b%d **\n",ps_aux->getCor().r,ps_aux->getCor().g,ps_aux->getCor().b);
              //matar_presa(ps_aux->getCodigo());
		   }
		   else{
	          soma_r_ps+=ps_aux->getCor().r;
	          soma_g_ps+=ps_aux->getCor().g;
	          soma_b_ps+=ps_aux->getCor().b;
	         // printf("cores: r%d g%d b%d ",ps_aux->getCor().r,ps_aux->getCor().g,ps_aux->getCor().b);
		   }
		   
		  if(ps_aux->getSentidos()>max_visao_ps || ps_aux->getSentidos()<0){
				soma_visao_ps+= max_visao_ps*0.75;   //entre 50-100
		  }
		  else{
	          if(ps_aux->getSentidos()>max_visao_ps*0.75)
				 soma_visao_ps+= max_visao_ps - ((max_visao_ps - ps_aux->getSentidos())*2);
			  else	 	
	        	 soma_visao_ps+= max_visao_ps/2.0 + ((ps_aux->getSentidos() - max_visao_ps/2.0) * 2);
		  }
		  
		  if(ps_aux->getVisao_reproducao_max()>0){
			  soma_visao_rep_ps+= ps_aux->getVisao_reproducao_max();   
		  }
		  else{
		  	  soma_visao_rep_ps+= le_info("campo_max_visao_rep_presa");
		  }
		  
		  if(ps_aux->getVelocidade()>9 || ps_aux->getVelocidade()<0){
              soma_velocidade_ps+= 4.5;
		  }
		  else{	  
			  if(ps_aux->getVelocidade()>=5)
				 soma_velocidade_ps+= 9 - ((9-ps_aux->getVelocidade())*2.25);
			  else	 	
	        	 soma_velocidade_ps+= ps_aux->getVelocidade()*2.25;
	         }  
		  ps_aux= ps_aux->getProx_c();
		  }
            //save predators information
       pd_aux=pd1;
       while(pd_aux!=NULL){
			cont_pd++;
		  if(pd_aux->getCor().r>255 ||pd_aux->getCor().g>255 ||pd_aux->getCor().b>255 || pd_aux->getCor().r<0 ||pd_aux->getCor().g<0 ||pd_aux->getCor().b<0){
			 soma_r_pd+=128;
             soma_g_pd+=128;
             soma_b_pd+=128;
           // printf("\n**bugs: r%d g%d b%d **\n",ps_aux->getCor().r,ps_aux->getCor().g,ps_aux->getCor().b);
          //matar_presa(ps_aux->getCodigo());
		  }
		  else{
	          soma_r_pd+=pd_aux->getCor().r;
	          soma_g_pd+=pd_aux->getCor().g;
	          soma_b_pd+=pd_aux->getCor().b;
	         // printf("cores: r%d g%d b%d ",ps_aux->getCor().r,ps_aux->getCor().g,ps_aux->getCor().b);
		  }
          //soma_r_pd+=pd_aux->getCor().r;
          //soma_g_pd+=pd_aux->getCor().g;
          //soma_b_pd+=pd_aux->getCor().b;
          
          if(pd_aux->getSentidos()>max_visao_pd || pd_aux->getSentidos()<0){
			  soma_visao_pd+= max_visao_pd*0.75;   //entre 50-100 
		  }
		  else{
	          if(pd_aux->getSentidos()>max_visao_pd*0.75)
				 soma_visao_pd+= max_visao_pd - ((max_visao_pd - pd_aux->getSentidos())*2);
			  else	 	
	        	 soma_visao_pd+= max_visao_pd/2.0 + ((pd_aux->getSentidos() - max_visao_pd/2.0) * 2);
		  }
		  
		  if(pd_aux->getVisao_reproducao_max()>0){
			  soma_visao_rep_pd+= pd_aux->getVisao_reproducao_max();   
		  }
		  else{
		  	  soma_visao_rep_pd+= le_info("campo_max_visao_rep_predador");
		  }
		  
		  if(pd_aux->getVelocidade()>9 || pd_aux->getVelocidade()<0){
              soma_velocidade_pd+= 4.5;
		  }
		  else{	  
			  if(pd_aux->getVelocidade()>=5)
				 soma_velocidade_pd+=  9 - ((9-pd_aux->getVelocidade())*2.25);
			  else	 	
	        	 soma_velocidade_pd+=  pd_aux->getVelocidade()*2.25;
		  }
		  
          pd_aux= pd_aux->getProx_c();
         }  
         
       if(cont_ps > 0){
		 // printf("\nsoma R %d / %d = media %f\n",soma_r_ps,(cps_m + cps_f),((float)soma_r_ps) / (cps_m + cps_f));
		  //printf("soma G %d / %d = media %f\n",soma_g_ps,(cps_m + cps_f),((float)soma_g_ps) / (cps_m + cps_f));
		  //printf("soma B %d / %d = media %f\n",soma_b_ps,(cps_m + cps_f),((float)soma_b_ps) / (cps_m + cps_f));
		  
          media_r_ps = (double)soma_r_ps / (double)(cont_ps);
          media_g_ps = (double)soma_g_ps / (double)(cont_ps);
          media_b_ps = (double)soma_b_ps / (double)(cont_ps);
          media_visao_ps = (double)soma_visao_ps / (double)(cont_ps);
          media_velocidade_ps = (double)soma_velocidade_ps / (double)(cont_ps);
          media_visao_rep_ps = (double)soma_visao_rep_ps / (double)(cont_ps);
         }         
	   if(cont_pd > 0){
          media_r_pd = (double)soma_r_pd / (double)(cont_pd);
          media_g_pd = (double)soma_g_pd / (double)(cont_pd);
          media_b_pd = (double)soma_b_pd / (double)(cont_pd);
          media_visao_pd = (double)soma_visao_pd / (double)(cont_pd);
          media_velocidade_pd = (double)soma_velocidade_pd / (double)(cont_pd);
          media_visao_rep_pd = (double)soma_visao_rep_pd / (double)(cont_pd);
         }         
      }

    void calcula_var(){             //calcula a variacao de Red, green e blue nas cores de todas as presas
       corRGB somat_ps,somat_pd;
       long int somat_visao_ps,somat_visao_pd;
       long int somat_visao_rep_ps,somat_visao_rep_pd;
       long int somat_velocidade_ps,somat_velocidade_pd;
       long int max_visao_ps,max_visao_pd;
       long int max_visao_rep_ps,max_visao_rep_pd;
       
       int cont_ps,cont_pd;
       Presa *ps_aux;
       Predador *pd_aux;
       
       
       max_visao_ps = le_info("campo_max_visao_presa");
       max_visao_pd = le_info("campo_max_visao_predador");
       max_visao_rep_ps = le_info("campo_max_visao_rep_presa");;
       max_visao_rep_pd = le_info("campo_max_visao_rep_predador");
       
       
       calcula_media();
       
       somat_ps.r=somat_ps.g=somat_ps.b=0;
       somat_ps.r=somat_ps.g=somat_ps.b=0;
       somat_pd.r=somat_pd.g=somat_pd.b=0;
       somat_visao_ps= somat_visao_pd = 0;
       somat_visao_rep_ps= somat_visao_rep_pd = 0;
       cont_ps = cont_pd =0;
       somat_velocidade_ps= somat_velocidade_pd = 0;
	   var_r_ps=var_g_ps=var_b_ps=-1;
       var_r_pd=var_g_pd=var_b_pd=-1;
       var_visao_rep_ps = var_visao_rep_pd = -1;
       var_velocidade_ps = var_velocidade_pd = -1;
       
       
            //preys information
       ps_aux=ps1;
       while(ps_aux!=NULL){
		  cont_ps++;	
		  if(ps_aux->getCor().r>255 ||ps_aux->getCor().g>255 ||ps_aux->getCor().b>255 || ps_aux->getCor().r<0 ||ps_aux->getCor().g<0 ||ps_aux->getCor().b<0){
		      somat_ps.r+= pow(128 - media_r_ps, 2);
	          somat_ps.g+= pow(128 - media_g_ps, 2);
	          somat_ps.b+= pow(128 - media_b_ps, 2);
		  }
		  else{
			  somat_ps.r+= pow(ps_aux->getCor().r - media_r_ps, 2);
	          somat_ps.g+= pow(ps_aux->getCor().g - media_g_ps, 2);
	          somat_ps.b+= pow(ps_aux->getCor().b - media_b_ps, 2);      
		  }
		  
		  if(ps_aux->getSentidos()>max_visao_ps || ps_aux->getSentidos()<0){
			  somat_visao_ps+= pow((max_visao_ps*0.75) - media_visao_ps,2);
		  }
		  else{
			  if(ps_aux->getSentidos()>max_visao_ps*0.75)
				 somat_visao_ps+= pow((max_visao_ps - ((max_visao_ps - ps_aux->getSentidos())*2)) - media_visao_ps,2);
			  else	 	
	        	 somat_visao_ps+= pow((max_visao_ps/2 + ((ps_aux->getSentidos() - max_visao_ps/2) * 2)) - media_visao_ps,2); 
			  
		  }
		  
		  if(ps_aux->getVisao_reproducao_max()>0){
			  somat_visao_rep_ps+= pow(max_visao_rep_ps - media_visao_rep_ps,2);
		  }
		  else{
			  somat_visao_rep_ps+= pow(ps_aux->getVisao_reproducao_max() - media_visao_rep_ps,2);
		  }
		  
		  if(ps_aux->getVelocidade()>9 || ps_aux->getVelocidade()<0){
			  somat_velocidade_ps+= pow(4.5 -  media_velocidade_ps,2);	
		  }
		  else{
			  if(ps_aux->getVelocidade()>=5)
				 somat_velocidade_ps+= pow((9 - ((9-ps_aux->getVelocidade())*2.25)) -  media_velocidade_ps,2);
			  else	 	
	        	 somat_velocidade_ps+= pow((ps_aux->getVelocidade()*2.25) -  media_velocidade_ps,2);
		  }
          ps_aux=ps_aux->getProx_c();           
         }
       
                   //predator information
       pd_aux=pd1;
       while(pd_aux!=NULL){
		  cont_pd++;	
          if(pd_aux->getCor().r>255 ||pd_aux->getCor().g>255 ||pd_aux->getCor().b>255 || pd_aux->getCor().r<0 ||pd_aux->getCor().g<0 ||pd_aux->getCor().b<0){
		      somat_pd.r+= pow(128 - media_r_pd, 2);
	          somat_pd.g+= pow(128 - media_g_pd, 2);
	          somat_pd.b+= pow(128 - media_b_pd, 2);  
		  }
		  else{
			  somat_pd.r+= pow(pd_aux->getCor().r - media_r_pd, 2);
	          somat_pd.g+= pow(pd_aux->getCor().g - media_g_pd, 2);
	          somat_pd.b+= pow(pd_aux->getCor().b - media_b_pd, 2);   
		  }   
		  
		  
		  if(pd_aux->getSentidos()>max_visao_pd || pd_aux->getSentidos()<0){
			  somat_visao_pd+= pow((max_visao_pd*0.75) - media_visao_pd,2);
		  }
		  else{
			  if(pd_aux->getSentidos()>max_visao_pd*0.75)
				 somat_visao_pd+= pow((max_visao_pd - ((max_visao_pd - pd_aux->getSentidos())*2)) - media_visao_pd,2);
			  else	 	
	        	 somat_visao_pd+= pow((max_visao_pd/2 + ((pd_aux->getSentidos() - max_visao_pd/2) * 2)) - media_visao_pd,2); 
			  
		  }
		  
		  if(pd_aux->getVisao_reproducao_max()>0){
			  somat_visao_rep_pd+= pow(max_visao_rep_pd - media_visao_rep_pd,2);
		  }
		  else{
			  somat_visao_rep_pd+= pow(pd_aux->getVisao_reproducao_max() - media_visao_rep_pd,2);
		  }
		  
		  if(pd_aux->getVelocidade()>9 || pd_aux->getVelocidade()<0){
			  somat_velocidade_pd+= pow(4.5 -  media_velocidade_pd,2);	
		  }
		  else{
			  if(pd_aux->getVelocidade()>=5)
				 somat_velocidade_pd+= pow((9 - ((9-pd_aux->getVelocidade())*2.25)) -  media_velocidade_pd,2);
			  else	 	
	        	 somat_velocidade_pd+= pow((pd_aux->getVelocidade()*2.25) -  media_velocidade_pd,2);
		  }
          pd_aux=pd_aux->getProx_c(); 
       }
       
	     
       
       if(media_r_ps!=-1 && cont_ps>1){   //se algumas das cores R G ou B for  -1   significa q a media eh nula (inexistente)
          var_r_ps= sqrt(somat_ps.r/(cont_ps - 1)); 
          var_g_ps= sqrt(somat_ps.g/(cont_ps - 1));
          var_b_ps= sqrt(somat_ps.b/(cont_ps - 1));
         }
       if(media_r_pd!=-1 && cont_pd>1){   //se algumas das cores R G ou B for  -1   significa q a media eh nula (inexistente)
          var_r_pd= sqrt(somat_pd.r/(cont_pd - 1)); 
          var_g_pd= sqrt(somat_pd.g/(cont_pd - 1));
          var_b_pd= sqrt(somat_pd.b/(cont_pd - 1));
         }
         
       if(media_visao_ps!=-1 && cont_ps>1){   
          var_visao_ps= sqrt(somat_visao_ps/(cont_ps - 1));
         }
       if(media_visao_pd!=-1 && cont_pd>1){   
          var_visao_pd= sqrt(somat_visao_pd/(cont_pd - 1));
         }
       
	   if(media_visao_rep_ps!=-1 && cont_ps>1){   
          var_visao_rep_ps= sqrt(somat_visao_rep_ps/(cont_ps - 1));
         }
       if(media_visao_rep_pd!=-1 && cont_pd>1){   
          var_visao_rep_pd= sqrt(somat_visao_rep_pd/(cont_pd - 1));
         }  

       if(media_velocidade_ps!=-1 && cont_ps>1){   
          var_velocidade_ps= sqrt(somat_ps.b/(cont_ps - 1));
         }
       if(media_velocidade_pd!=-1 && cont_pd>1){   
          var_velocidade_pd= sqrt(somat_pd.b/(cont_pd - 1));
         }
         
      }


/*******************************************************************************/

  







        //Programa principal

int main( int argc, char *argv[])
{
	
	pausa=true;
	
//	printf("Lalal\n");
    char nome_relatorio[50];
    strcpy(nome_relatorio, "Report_Regular");  // strcpy(*nome_relatorio, "Relatorio_Comum");  
    char local_relatorio_visual[500];
    FILE *arq, *f;
    int n_relatorio;
    char string[200];  //vetor de char  p auxiliar nas conversoes de itoa p guardar no relatorio
    int i=0,j=0;
    char c;   
    
    
    //                   Tratamento Arquivo de Relatorio
    //()()()()()()()()()()()(()()()()()()()()()()()()()()()()()()()()()()()()()()()
        //*******************  ARQUIVO INFO_R  ********************
//	printf("LAlaa2\n"); 
	 char local_relatorio[500]; //n_relatorio2 pra conversao do n_relatorio pra string 
     char fim='\0';

	for(i=0;i<500;i++)
		local_relatorio[i]='\0';
             //gera o endereco p relatorio
	 strcpy(local_relatorio,*argv);
	 //printf("local relatorio:%s\n",local_relatorio);
	 for(i= strlen(local_relatorio)-1; i>=0; i--){
		 if(local_relatorio[i] == '\\')
		    break;
		 local_relatorio[i]= '\0';	 	
		}
    strcat(local_relatorio,"Reports\\");  //strcat(local_relatorio,"Relatorios\\");
	 for(i=0;i<strlen(local_relatorio);i++)
	    if(local_relatorio[i]== '\\')
	       local_relatorio[i] = '/';
	 //printf("local relatorio2:%s\n",local_relatorio);
	 f=fopen("info_r","r");
	     if(f!=NULL){
			//printf("controuu\n");	
			fscanf(f,"%d\n",&n_relatorio);
		     for(i=0;i<200;i++){
	            fscanf(f,"%c",&c);
	            if(c=='\n')
	               break; 
	           }
	
	         fscanf(f,"%c",&fim);
	         fclose(f);
	     }
	     else{
			printf("Error: \"info_r\" file was not found.\n");	
	     }
		 
	 
	 
	 if(fim != '#'){
       printf("\a\n WARNING: End of file INFO_R was not confirmed    (end= %c)\n\n ",fim);   //printf("\a\n ATENCAO: Nao foi confirmado o fim do arq INFO_R    (fim= %c)\n\n ",fim);
       delay(1100);
      }
     //printf("LAlaa3\n"); 
     //getchar();
     itoa(n_relatorio,string,10);//pega o num n_relatorio e converte pra string
   	 sprintf(local_relatorio,"%s%s_%s.m",local_relatorio,nome_relatorio,string);
	
	 f=fopen("info_r","w");     //***********************************************************************
	     fprintf(f,"%d\n",n_relatorio+1);
	     fprintf(f,"%s\n",local_relatorio);

         fprintf(f,"#");
         
     fclose(f);

     //cria diretorio do relatorio visual
    // C:/Users/Luiz/Desktop/Projeto Presas/PRESAS Beta 1.5/Relatorios/Relatorio_Comum_24.txt
   strcpy(local_relatorio_visual, local_relatorio);
/*
	 for(i=0;i<strlen(local_relatorio);i++){
	    if(local_relatorio_visual[i]== '/')
	       local_relatorio_visual[i] = '\\';
        else
           local_relatorio_visual[i] = local_relatorio[i];
     }
*/	       
   	 for(i= strlen(local_relatorio_visual)-1; i>=0; i--){
		 if(local_relatorio_visual[i] == '/')
		    break;
		 local_relatorio_visual[i]= '\0';	 	
		}
  //  printf("local copia: %s \n",local_relatorio_visual);  
  //       getchar();
   //strcat(local_relatorio,visual,relatorio_visual); //C:/Users/Luiz/Desktop/Projeto Presas/PRESAS Beta 1.5/Relatorios/Relatorio_Comum_4.txt
   //C:\\Users\\Luiz\\Desktop\\Projeto\ Presas\\PRESAS\ Beta\ 1.5\\Relatorios\\");  
   strcat(local_relatorio_visual, "Report_Visual_");   //strcat(local_relatorio_visual, "Relatorio_Visual_");
   strcat(local_relatorio_visual,string);
   
   //printf("path: %s \n",local_relatorio_visual);   //printf("local: %s \n",local_relatorio_visual); 
   if(mkdir(local_relatorio_visual)!=0){
	   printf("Error: Could not create the visual report directory.\n");
   }
   //system(local_relatorio_visual);  //cria diretorio do relatorio visual
      //   printf("local: %s \n",local_relatorio_visual);  
      //   getchar();
   
   strcat(local_relatorio_visual,"/");
   strcat(local_relatorio_visual,"0.bmp");
   
//   printf("local: %s \n",*nome_relatorio);  
     
	 
   arq = fopen(local_relatorio,"w");  //cria o relatorio
   
   
       
   // printf("criou a bagaca");
    escreve_relatorio("%%\t Simulation v1.6.9\t",arq);
    escreve_relatorio(__TIME__,arq);
    escreve_relatorio(" - ",arq);
    escreve_relatorio(__DATE__,arq);
    escreve_relatorio("\n%%\t^^^^^^^^^^^^^^^^^^^\n\n",arq);
      
    
    srand(time(NULL));
    pthread_mutex_init(&p_key,NULL);   // inicializa o objeto pthread_mutex_t  para ser utilizado
    
            /*Declação de variaveis*/
    int qt_col = le_info("qt_col_campo"); 
    int qt_lin = le_info("qt_lin_campo");
    int pop_ini_ps = le_info("qt_presa_m") + le_info("qt_presa_f");
	int pop_ini_pd = le_info("qt_predador_m") + le_info("qt_predador_f");

    
    long int tmp_paus=0;

    Presa *ps_aux;
    Predador *pd_aux;
    Planta *pl_aux;
    Lago *lg_aux;
    
    corRGB cor_aux;         
    posXY pos_aux;
    
    Presa *ps_pais;    //presa que ontem as informacoes aleatorias dos pais cujos as presas iniciais herdarao as caracteristicas
    Predador *pd_pais; 
    
    imprime_cabecalho(argv,n_relatorio);
    
            //setting module variables
     mod_mutacao_cor = le_info("mod_mutacao_cor");
     mod_doenca = le_info("mod_doenca");
     mod_sede = le_info("mod_sede");
     mod_lago = le_info("mod_lago");  //
     mod_fome_presa = le_info("mod_fome_presa");
     mod_planta = le_info("mod_planta");
     mod_fuga_presa = le_info("mod_fuga_presa");
     mod_mudanca_cor_ambiente = le_info("mod_mudanca_cor_ambiente");
     mod_predador_camuflagem = le_info("mod_predador_camuflagem");
     
	 //printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",mod_mutacao_cor,mod_doenca,mod_sede,mod_lago,mod_fome_presa,mod_planta,mod_fuga_presa,mod_mudanca_cor_ambiente); 
     printf("\n\n # Modules:\n");
     printf("%s - Color Mutation\n",mod_mutacao_cor?" YES":" NO ");
	 printf("%s - Illness\n",mod_doenca?" YES":" NO ");
	 printf("%s - Thirst\n",mod_sede?" YES":" NO ");
	 printf("%s - Lakes\n",mod_lago?" YES":" NO ");
	 printf("%s - Prey Hunger\n",mod_fome_presa?" YES":" NO ");
	 printf("%s - Plants\n",mod_planta?" YES":" NO ");
	 printf("%s - Prey Escape\n",mod_fuga_presa?" YES":" NO ");
	 printf("%s - Environment Color Change\n",mod_mudanca_cor_ambiente?" YES":" NO ");
	 printf("%s - Predator Camouflage\n\n",mod_predador_camuflagem?" YES":" NO ");
	 
	 //write information in file
	 sprintf(string, "%%          # Modules:\n");                                                       escreve_relatorio(string,arq);
     sprintf(string, "%% %s - Color Mutation\n",mod_mutacao_cor?" YES":" NO ");							escreve_relatorio(string,arq);
	 sprintf(string, "%% %s - Illness\n",mod_doenca?" YES":" NO ");										escreve_relatorio(string,arq);	
	 sprintf(string, "%% %s - Thirst\n",mod_sede?" YES":" NO ");										escreve_relatorio(string,arq);
	 sprintf(string, "%% %s - Lakes\n",mod_lago?" YES":" NO ");											escreve_relatorio(string,arq);
	 sprintf(string, "%% %s - Prey Hunger\n",mod_fome_presa?" YES":" NO ");								escreve_relatorio(string,arq);
	 sprintf(string, "%% %s - Plants\n",mod_planta?" YES":" NO ");										escreve_relatorio(string,arq);
	 sprintf(string, "%% %s - Prey Escape\n",mod_fuga_presa?" YES":" NO ");								escreve_relatorio(string,arq);	
	 sprintf(string, "%% %s - Environment Color Change\n",mod_mudanca_cor_ambiente?" YES":" NO ");		escreve_relatorio(string,arq);	
	 sprintf(string, "%% %s - Predator Camouflage\n\n",mod_predador_camuflagem?" YES":" NO ");			escreve_relatorio(string,arq);
	 
	 sprintf(string, "CampoCor = [%d %d %d]\n\n",le_info("cor_r_campo"),le_info("cor_g_campo"),le_info("cor_b_campo"));	    escreve_relatorio(string,arq);
	 sprintf(string, "Dados = [\n");	escreve_relatorio(string,arq);
	 
	 //printf("variacao rep ps e pd %d %d\n",le_info("var_campo_max_visao_rep_presa"),le_info("var_campo_max_visao_rep_predador"));
	 
              //***********************    Inicio da parte gráfica ************************************
    initwindow(qt_col+170, qt_lin, "Simulator");     //abre a janela com espaco para os campos
     

    cor_aux.r= le_info("cor_r_campo");
    cor_aux.g= le_info("cor_g_campo");
    cor_aux.b= le_info("cor_b_campo");
    
   
       
    cp.inicializa(cor_aux);
    
    setfillstyle(1,COLOR(cp.getCor().r, cp.getCor().g, cp.getCor().b));
    bar(0,0,qt_col,qt_lin);    
    imprime_campo_descricao();
    

    
    
    posXY inicio;
	dimXY dimensao;
	int qt_areas;
	int cont_areas;
	int cols[100];
	int cont_cols;
	int lins[100];
	int cont_lins;
	
	inicio.x = 0;
	inicio.y = 0;
	dimensao.x = qt_col;
	dimensao.y = qt_lin;
	qt_areas=256;  //4096 max    
	cont_areas=1;
	cont_cols=0;
	cont_lins=0;
	
	for(int c=0;c<100;c++){
	    cols[c] = 0;
	    lins[c] = 0;
	}
    
    divide_campo(dimensao,qt_areas,cont_areas,cols,cont_cols,lins,cont_lins);
    
    //    imprime as divisoes do campo
	/*   /
	for(int c=0;c<100;c++){
		if(cols[c]!=0){
		   line(cols[c],0,cols[c],qt_lin);
        }
	}
    for(int c=0;c<100;c++){
		if(lins[c]!=0){
			line(0,lins[c],qt_col,lins[c]);
	    }
    }
    getch();
    /**/
    
    
    
      
    
    //    printf("\a");
 
    
    cor_aux.r=-1;
    cor_aux.g=-1;
    cor_aux.b=-1;
    
    pos_aux.x=-1;
    pos_aux.y=-1;
    
	cps_m=0; cps_f=0;
	cpd_m=0; cpd_f=0;
	
	ps1=NULL;
	pd1=NULL;
	pl1=NULL;
      
	
//	printf("sddsasssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss");

	//ps_aux->setCor(cor_aux);
	//ps_aux->setPosicao(pos_aux);
	//ps_aux->setVelocidade(-1);
	//ps_aux->setCategoria(2);
    //ps_pais = ps_aux;
    
    ps_pais = (Presa*) malloc(sizeof(class Presa));   
    ps_pais->setCor(cor_aux);
    ps_pais->setPosicao(pos_aux);
    ps_pais->setVelocidade(-1);
    ps_pais->setCategoria(2);
    ps_pais->setSentidos(-1);
    ps_pais->setVisao_reproducao_max(-1);
    
    pd_pais = (Predador*) malloc(sizeof(class Predador));   
    pd_pais->setCor(cor_aux);
    pd_pais->setPosicao(pos_aux);
    pd_pais->setVelocidade(-1);
    pd_pais->setCategoria(2);
    pd_pais->setSentidos(-1);
    pd_pais->setVisao_reproducao_max(-1);
    
    
    

//printf("\t\tEh pá criar %d psmacho e %d psfema, %d pdm e %d pdfema\n",le_info("qt_presa_m"),le_info("qt_presa_f"),le_info("qt_predador_m"),le_info("qt_predador_m"));
//getch();
	
	            /*Criando os lagos*/
	            
  if(mod_lago){   
	cor_aux.r= le_info("cor_r_lago");
	cor_aux.g= le_info("cor_g_lago");
	cor_aux.b= le_info("cor_b_lago");
	
	    if(le_info("qt_lago") > 0){ 
	       lg1= criar_lago(1, cor_aux, pos_aux, -1);    
	       
	       //printf("\t\tcriou O LG1 :D cor %d %d %d\n",cor_aux.r,cor_aux.g,cor_aux.b);
	       
	       lg_aux= lg1;
	        
	       if(le_info("qt_lago")>0)   i=1;   else   i=0; 
	    
	       //printf("\t\t *= qt plantas P %d  G %d  \\o/\n",le_info("qt_planta_p"),le_info("qt_planta_g"));
	       //getchar();
	           
	       for(i=i;i<le_info("qt_lago");i++){
	          lg_aux->setProx_l(criar_lago(i+1,cor_aux,pos_aux, -1));    
	          lg_aux=lg_aux->getProx_l();    
	         }
	    
	      }
	    else{
	       lg1=NULL;   
	      }  
	    //printf("Criou os lagin \n");
	
   }
	
	
	
	
             /*Criando as plantas*/
  if(mod_planta){                
	cor_aux.r= le_info("cor_r_planta");
	cor_aux.g= le_info("cor_g_planta");
	cor_aux.b= le_info("cor_b_planta");             
	    if(le_info("qt_planta_p") > 0 || le_info("qt_planta_g") > 0){ 
	       if(le_info("qt_planta_p")>0)
	          pl1= criar_planta(1, cor_aux, pos_aux, 1,1);  
	       else
	          pl1= criar_planta(1, cor_aux, pos_aux, 2,1);    
	       
	       //printf("\t\tcriou a pl1 :D   cor %d %d %d\n",cor_aux.r,cor_aux.g,cor_aux.b);
	       
	       pl_aux= pl1;
	        
	       if(le_info("qt_planta_p")>0)   i=1;   else   i=0; 
	    
	       //printf("\t\t *= qt plantas P %d  G %d  \\o/\n",le_info("qt_planta_p"),le_info("qt_planta_g"));
	       //getchar();
	           
	       for(i=i;i<le_info("qt_planta_p");i++){              
	          pl_aux->setProx_p(criar_planta(i+1,cor_aux,pos_aux, 1, 1));    
	          pl_aux=pl_aux->getProx_p();    
	         }
	    
	       if(le_info("qt_planta_p")==0)  i=1;   else   i=0;   
	                   
	       for(i=i;i<le_info("qt_planta_g");i++){      
	          pl_aux->setProx_p(criar_planta(le_info("qt_planta_p")+i+1,cor_aux, pos_aux, 2, 1));
	          pl_aux=pl_aux->getProx_p();     
	         }
	      }
	    else{
	       pl1=NULL;   
	      }  
  // printf("Criou os matin \n");
   
   
 //  printf("Man, as parada foi criada\n");    
  // getch();
   
  // printf("cor MATIN %d %d %d\n\n",pl1->getCor().r,pl1->getCor().g,pl1->getCor().b);
	
  }
	
	
	
	//printf("Nao me sacaneie Presas, sou seu criador!\n");
              /*Criando as presas*/
    if(le_info("qt_presa_m") > 0 || le_info("qt_presa_f") > 0){ 
       if(le_info("qt_presa_m")>0)
          ps1= criar_presa(1, false, *ps_pais, *ps_pais);  
       else
          ps1= criar_presa(1, true, *ps_pais, *ps_pais);   
       
       //printf("\t\tcriou a ps1 :D\n");
       
       ps_aux= ps1;
       ps_ = ps_aux->getMove_td();
       pthread_create(&ps_, NULL, movimentar_presa, ps_aux); 
        
       if(le_info("qt_presa_m")>0)   i=1;   else   i=0; 

	  // printf("\t\tPS1 em movimento! \\o/");
	  // getchar();
           
       for(i=i;i<le_info("qt_presa_m");i++){    
           
          ps_aux->setProx_c(criar_presa(i+1,false,*ps_pais, *ps_pais));    
          ps_aux=ps_aux->getProx_c();    
          ps_=ps_aux->getMove_td();
          pthread_create(&ps_, NULL, movimentar_presa, ps_aux);  
             
         }
    
       if(le_info("qt_presa_m")==0)  i=1;   else   i=0;   
                   
       for(i=i;i<le_info("qt_presa_f");i++){      
          ps_aux->setProx_c(criar_presa(le_info("qt_presa_m")+i+1,true,*ps_pais, *ps_pais));
          ps_aux=ps_aux->getProx_c();    
		  ps_ = ps_aux->getMove_td(); 
          pthread_create(&ps_, NULL, movimentar_presa, ps_aux);        
         }
     
      }
    else{
       ps1=NULL;   
      }  
    
   // printf("criou as pss iniciais \n");  

     
                 /*Criando os predadores*/
    if(le_info("qt_predador_m") > 0 || le_info("qt_predador_f") > 0){ 
       if(le_info("qt_predador_m")>0)
          pd1= criar_predador(1, false, *pd_pais, *pd_pais);     
       else
          pd1= criar_predador(1, true,  *pd_pais, *pd_pais);   
   
       pd_aux= pd1;
       pd_ = pd_aux->getMove_td();
       pthread_create(&pd_, NULL, movimentar_predador, pd_aux); 
       
       if(le_info("qt_predador_m")>0)   i=1;   else   i=0; 
       
       for(i=i;i<le_info("qt_predador_m");i++){    
          pd_aux->setProx_c(criar_predador(i+1,false, *pd_pais, *pd_pais));  
          pd_aux=pd_aux->getProx_c();  
		  pd_ = pd_aux->getMove_td();   
          pthread_create(&pd_, NULL, movimentar_predador, pd_aux);  
         }
       
       if(le_info("qt_predador_m")==0)  i=1;   else   i=0; 
       
       for(i=i;i<le_info("qt_predador_f");i++){     
          pd_aux->setProx_c(criar_predador(le_info("qt_predador_m")+i+1,true, *pd_pais, *pd_pais));  
          pd_aux=pd_aux->getProx_c();
		  pd_=pd_aux->getMove_td();   
          pthread_create(&pd_, NULL, movimentar_predador, pd_aux);  
         }
       
      }
    else{
       pd1=NULL;    
      }
 
  // printf("Criou as initial population \n");
   
   /*
   cor_aux.r = le_info("cor_r_planta");
   cor_aux.g = le_info("cor_g_planta");
   cor_aux.b = le_info("cor_b_planta");
   */
   
   //printf("%d %d\n\n", le_info("intensidade_doenca_presa"), le_info("intensidade_doenca_predador"));
   //getchar();
 
               /*Inicia as idades e velocidades randomicas*/

   ps_aux=ps1;
   while(ps_aux!=NULL){

      ps_aux->setIdade(rand()%ps_aux->getIdade_max()+1);
      ps_aux->setFome(5+rand()%le_info("tempo_fome"));   
      ps_aux->setVelocidade(-1);
      
      ps_aux = ps_aux->getProx_c();                 
     }
   
   pd_aux=pd1;
   while(pd_aux!=NULL){
      pd_aux->setIdade(rand()%pd_aux->getIdade_max()+1);                  
      pd_aux->setFome(5+rand()%le_info("tempo_fome"));      
      pd_aux->setVelocidade(-1);            
      pd_aux = pd_aux->getProx_c(); 
            
     }
     
  
  // printf("Setou as caract iniciais das initial population \n");
 
 
 
 /*   Imprime as caracteristicas de plantas   */
 
/*    // teste GETPLANTA   ok    =) 
 int x = 1;
 
 while(getPlanta(x) != NULL){
     
     printf(" -> Planta %d  de size %d na pos %d,%d e a cor? %d %d %d\n",getPlanta(x)->getCodigo(),getPlanta(x)->getTamanho(), getPlanta(x)->getPosicao().x,getPlanta(x)->getPosicao().y,getPlanta(x)->getCor().r,getPlanta(x)->getCor().g,getPlanta(x)->getCor().b);   
         
     x++;    
 }
 */
 
 
 
 
 
 
 
    
    
              ///////////////////////////////////////////////////////////////////////////////////////////////////////// 
              //////////////////////////       Fim da criacao da populacao inicial      ///////////////////////////////
              /////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    int variacao_cor_campo = le_info("variacao_cor_campo");
    int tempo_variar = le_info("tempo_variacao_cor_campo");
    int tempo_variacao_cor_campo = le_info("tempo_variacao_cor_campo");
    int tempo_oscilacao_lago = le_info("tempo_oscilacao_lago");
    int cor_r_campo_min = le_info("cor_r_campo_min");
    int cor_r_campo_max = le_info("cor_r_campo_max"); 
    int cor_g_campo_min = le_info("cor_g_campo_min");
    int cor_g_campo_max = le_info("cor_g_campo_max");
    int cor_b_campo_min = le_info("cor_b_campo_min");
    int cor_b_campo_max = le_info("cor_b_campo_max");
    corRGB cor_campo, cor_objetivo;
    cor_objetivo.r = cor_campo.r = le_info("cor_r_campo");
    cor_objetivo.g = cor_campo.g = le_info("cor_g_campo");
    cor_objetivo.b = cor_campo.b = le_info("cor_b_campo");
    
    corRGB cor_campo_init;
    cor_campo_init.r = le_info("cor_r_campo");
    cor_campo_init.g = le_info("cor_g_campo");
    cor_campo_init.b = le_info("cor_b_campo");
    
       //verifica se as variacoes de cor do campo ultrapassararão os limites de 0 - 255    "poda" os limites
    if(cor_campo.r - cor_r_campo_min < 0)
       cor_r_campo_min = cor_campo.r;
    if(cor_campo.r + cor_r_campo_max > 255)
       cor_r_campo_max = 255 - cor_campo.r;
    if(cor_campo.g - cor_g_campo_min < 0)
       cor_g_campo_min = cor_campo.g;
    if(cor_campo.g + cor_g_campo_max > 255)
       cor_g_campo_max = 255 - cor_campo.g;
    if(cor_campo.b - cor_b_campo_min < 0)
       cor_b_campo_min = cor_campo.b;
    if(cor_campo.b + cor_b_campo_max > 255)
       cor_b_campo_max = 255 - cor_campo.b;
       
       
    
    
  
    int cod_ps=-1, cod_pd=-1, cod_pl=-1;
    posXY pos_ps, pos_pd, pos_pl;
    int visao_ps=-1, visao_pd=-1;  
    
    int tmp_rel=1;
    int segundo=0;   /**/
    
    //cont das imagens     //relatório visual   ;)
    int cont_img=0;
    
    
    
    
    while (true){
		
		
        
        if(mod_mudanca_cor_ambiente){
        
	        if(tempo/1000 >= tempo_variar){  //tempo de variar o fundo?
	         
	         // printf("infos:");
	         // printf("%d %d\t%d %d\t%d %d",cor_campo.r,cor_objetivo.r,cor_campo.g,cor_objetivo.g,cor_campo.b,cor_objetivo.b);
	        
	           if(cor_campo.r == cor_objetivo.r){   //se a cor do campo atingiu o objetivo, logo, sera sorteada outra cor objetivo
	              cor_objetivo.r = cor_campo_init.r - cor_r_campo_min + rand()%(cor_r_campo_min + cor_r_campo_max);  
	             }
	           if(cor_campo.g == cor_objetivo.g){   //se a cor do campo atingiu o objetivo, logo, sera sorteada outra cor objetivo
	              cor_objetivo.g = cor_campo_init.g - cor_g_campo_min + rand()%(cor_g_campo_min + cor_g_campo_max);          
	             }
	           if(cor_campo.b == cor_objetivo.b){   //se a cor do campo atingiu o objetivo, logo, sera sorteada outra cor objetivo
	              cor_objetivo.b = cor_campo_init.b - cor_b_campo_min + rand()%(cor_b_campo_min + cor_b_campo_max); 
	             }
	             
	           if(cor_campo.r - cor_objetivo.r > 0 ){   //Se a cor do campo atual foi maior que a cor objetivo
	              cor_campo.r -= variacao_cor_campo;
	             }
	           else{
	              cor_campo.r += variacao_cor_campo;      
	             }
	           
	           if(cor_campo.g - cor_objetivo.g > 0 ){   //Se a cor do campo atual foi maior que a cor objetivo
	              cor_campo.g -= variacao_cor_campo;
	             }
	           else{
	              cor_campo.g += variacao_cor_campo;      
	             }
	           
	           if(cor_campo.b - cor_objetivo.b > 0 ){   //Se a cor do campo atual foi maior que a cor objetivo
	              cor_campo.b -= variacao_cor_campo;
	             }
	           else{
	              cor_campo.b += variacao_cor_campo;      
	             }  
	           
	           if(abs(cor_campo.r - cor_objetivo.r) < variacao_cor_campo)  // se estiver bem proximo do objetivo, arredonda   (resolve problema de numeros nao multiplos e bla bla bla)  
	              cor_campo.r = cor_objetivo.r; 
	           if(abs(cor_campo.g - cor_objetivo.g) < variacao_cor_campo)  // se estiver bem proximo do objetivo, arredonda   (resolve problema de numeros nao multiplos e bla bla bla)  
	              cor_campo.g = cor_objetivo.g; 
	           if(abs(cor_campo.b - cor_objetivo.b) < variacao_cor_campo)  // se estiver bem proximo do objetivo, arredonda   (resolve problema de numeros nao multiplos e bla bla bla)  
	              cor_campo.b = cor_objetivo.b; 
	                        
	
	           tempo_variar += tempo_variacao_cor_campo;   
	           
	           cp.setCor(cor_campo);
	           
	           pthread_mutex_lock(&p_key);
	               setfillstyle(1,COLOR(cp.getCor().r, cp.getCor().g, cp.getCor().b));
	               bar(0,0,qt_col,qt_lin);
	           pthread_mutex_unlock(&p_key);
	           printf(" *** variou *** Atual: %d %d %d\n",cor_campo.r,cor_campo.g,cor_campo.b);
	           
	           setcolor(COLOR(255,193,37));
	           settextstyle(0, 0, 0);
	           bgiout<<cp.getCor().r<<","<<cp.getCor().g<<","<<cp.getCor().b<<"  \n"<<cor_objetivo.r<<","<<cor_objetivo.g<<","<<cor_objetivo.b<<" ";
	           outstreamxy(qt_col+25,450);
	           
	        }  
	    }
        
        
          
        
        
        
          
              
        if(tempo/1000 >= tmp_rel){    // de 5 em 5 segundos, o relatório é atualizado
           char string[10]; 
            
           pthread_mutex_lock(&p_key);  
        
        		
               //printf("hey..\n");
               //calcula_media();
               calcula_var();
               
			   //printf("Media visao ps %.1f   pd %.1f\t",media_visao_ps,media_visao_pd);
			   
			   //printf("Media speed ps %.1f   pd %.1f\n",media_velocidade_ps,media_velocidade_pd);
			   
               for(i=0;i<sizeof(string);i++){
			      string[i]='\0';
               }
               sprintf(string,"%d %d %d %d %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n",
			           cps_f,cps_m,cpd_f,cpd_m,media_r_ps,media_g_ps,media_b_ps,media_r_pd,media_g_pd,media_b_pd,media_visao_ps,media_visao_pd,media_visao_rep_ps,media_visao_rep_pd,media_velocidade_ps,media_velocidade_pd,
					   var_r_ps,var_g_ps,var_b_ps,var_r_pd,var_g_pd,var_b_pd,var_visao_ps,var_visao_pd,var_visao_rep_ps,var_visao_rep_pd,var_velocidade_ps,var_velocidade_pd); 

               escreve_relatorio(string,arq);    
			   
			//	printf("ps %.3f     pd %.3f\n",media_velocidade_ps,media_velocidade_pd);
           pthread_mutex_unlock(&p_key);   
             
                            
           if((tmp_rel<5)||(tempo/1000 > 1790 || cps_f+cps_m+cpd_f+cpd_m==0) || (cps_f+cps_m > 2*pop_ini_ps && cpd_f+cpd_m==0) || (cpd_f+cpd_m > 2*pop_ini_pd && cps_f+cps_m==0)){
				pausa=true;
	           // de 5 em 5s tira um print
	           for(i= strlen(local_relatorio_visual)-1; i>=0; i--){
	              if(local_relatorio_visual[i] == '/')
			         break;
		          local_relatorio_visual[i]= '\0';	 	
	   	         } 
	           itoa(cont_img,string,10);//pega o num n_relatorio e converte pra string
	           strcat(local_relatorio_visual,string);
	           strcat(local_relatorio_visual,".bmp");
	           if(tempo/1000 > 1790)
	     		   delay(3000);
	     	   else
				   delay(500);   
	           if(cont_img<=2)
			       writeimagefile(local_relatorio_visual,0, 0, getmaxx(), getmaxy());
	           cont_img++;
	           delay(500);
	           pausa=false;
		   }
           
           if((tempo/1000 > 1850 || cps_f+cps_m+cpd_f+cpd_m==0)||(cps_f+cps_m > 2*pop_ini_ps && cpd_f+cpd_m==0) || (cpd_f+cpd_m > 2*pop_ini_pd && cps_f+cps_m==0)){
			  sprintf(string,"];");    escreve_relatorio(string,arq);
			  fclose(arq);
			  printf("\a");
			  delay(1000);
			  printf("\a\a\a");
			  delay(1500);
			  printf("\a\a");
			  if(cont_img>1)
     			  exit(0);
           }
           
           tmp_rel+=5;
           
          }
        
       
       if(abs(tempo-segundo) > 750 || segundo == 0){      /**/
           segundo = tempo; 
           
            pl_aux = pl1;
            while(pl_aux != NULL){
               if(!pl_aux->getEstado()){    
                                      
                   if(pl_aux->getMorte() > 0){
                      pl_aux->morte_mm();
                     }
                   else{
                      pl_aux->setEstado(true); 
                     }
                  
                 }
               pl_aux = pl_aux->getProx_p(); 
            }
			
			//modificar o tamanho dos lagos
			//printf("tamanho lagin = %.6f\n", sin(2*M_PI*(1/100)*tempo));
			float variacao = 0.7;
			int t = (tempo/1000)%tempo_oscilacao_lago;  //0-100
			double y;
			lg_aux = lg1;
            while(lg_aux != NULL){  
				 y = sin(2*M_PI*(1.0/100)*t); 
				lg_aux->setTamanho_atual(lg_aux->getTamanho()+(y*variacao*100)); 
				
			   //if(lg_aux == lg1)
			   	//	printf("nvl lg %d porcentagi dos lagin lg1 %d com o seno de %.2f\n",t, lg_aux->getTamanho_atual(),y*variacao*100); 
               lg_aux = lg_aux->getProx_l(); 
               //printf("imprimindo os lagoo1!"); 
              }
			/*
			*/
			//
            
            pthread_mutex_lock(&p_key);   
            
			//printf("cp.getCor().r %d",cor_campo.r);
				
				    //apaga as bordas dos lagos
				setfillstyle(1,COLOR(cor_campo.r, cor_campo.g, cor_campo.b));
				setlinestyle(0,0,3);
				setcolor(COLOR(cor_campo.r, cor_campo.g, cor_campo.b));
				lg_aux = lg1;
	            while(lg_aux != NULL){
				   fillellipse(lg_aux->getPosicao().x,lg_aux->getPosicao().y,lg_aux->getTamanho()*lg_aux->getTamanho_atual()/100+5,lg_aux->getTamanho()*lg_aux->getTamanho_atual()/100 + 5);
				   lg_aux = lg_aux->getProx_l(); 
	              }
				    //imprime os lagos
	            
				lg_aux = lg1;
	            while(lg_aux != NULL){
				   setfillstyle(1,COLOR(lg_aux->getCor().r, lg_aux->getCor().g, lg_aux->getCor().b));
	 		       setlinestyle(0,0,1);
			       setcolor(COLOR(lg_aux->getCor().r, lg_aux->getCor().g, lg_aux->getCor().b));
				   fillellipse(lg_aux->getPosicao().x,lg_aux->getPosicao().y,lg_aux->getTamanho()*lg_aux->getTamanho_atual()/100,lg_aux->getTamanho()*lg_aux->getTamanho_atual()/100);
	               lg_aux = lg_aux->getProx_l(); 
	               //printf("imprimindo os lagoo1!");
	              }
	              
///////////////////////////////////////////////////////////////////////
  			    //imprime_campo_descricao();
				if(getPresa(cod_ps)!=NULL){
                   imprime_info_presa(getPresa(cod_ps));
                  } 
                if(getPredador(cod_pd)!=NULL){
                   imprime_info_predador(getPredador(cod_pd));
                  }  
				if(getPlanta(cod_pl)!=NULL){
 				   imprime_info_planta(getPlanta(cod_pl));
				}
				
				   // imprime as plantas
	            pl_aux = pl1;
	            while(pl_aux != NULL){
	               if(pl_aux->getEstado()){  
     				  setfillstyle(1,COLOR(pl_aux->getCor().r, pl_aux->getCor().g, pl_aux->getCor().b));
	                  if(pl_aux->getTamanho()==1)
	                     bar(pl_aux->getPosicao().x,pl_aux->getPosicao().y,pl_aux->getPosicao().x+2,pl_aux->getPosicao().y+2);
	                  else
	                     bar(pl_aux->getPosicao().x,pl_aux->getPosicao().y,pl_aux->getPosicao().x+4,pl_aux->getPosicao().y+4);     
	                 }
	               pl_aux = pl_aux->getProx_p(); 
	               //printf("imprimindo os mato1!");
	              }
				       
    
        	pthread_mutex_unlock(&p_key); 
           
          }
        
		   
             //imprime o tempo e a quantidade de agentes
        pthread_mutex_lock(&p_key);   
                 
            setcolor(WHITE); 
            settextstyle(11,0,1);
            bgiout<<tempo/1000<<" ";
            outstreamxy(getmaxx()-60,343);  
            bgiout<<cps_m<<"  ";
            outstreamxy(getmaxx()-107,399);  
            bgiout<<cps_f<<"  ";
            outstreamxy(getmaxx()-57,399);  
            bgiout<<cpd_m<<"  ";
            outstreamxy(getmaxx()-107,431);  
            bgiout<<cpd_f<<"  ";
            outstreamxy(getmaxx()-57,431);  
    
        pthread_mutex_unlock(&p_key);   
        
           
               /* tecla pressionada */
        if(kbhit()){
           char tecla= getch();          
           
           pthread_mutex_lock(&p_key);    
            
               if(tecla == 32){   //espaço
                  pausa= pausa==true? false : true;
                  
                  if(pausa){       
                      setlinestyle(1,0,1);
                      setcolor(COLOR(255,193,37));
                      
                      if(getPresa(cod_ps)!=NULL){
                         pos_ps= getPresa(cod_ps)->getPosicao();
                         visao_ps=getPresa(cod_ps)->getSentidos();
                         circle(pos_ps.x, pos_ps.y, visao_ps); 
                         imprime_campo_descricao(); 
                         imprime_info_presa(getPresa(cod_ps));
                        }
                      if(getPredador(cod_pd)!=NULL){
                         pos_pd= getPredador(cod_pd)->getPosicao();
                         visao_pd=getPredador(cod_pd)->getSentidos();
                         circle(pos_pd.x, pos_pd.y, visao_pd); 
                         imprime_campo_descricao(); 
                         imprime_info_predador(getPredador(cod_pd));                           
                        }
					  if(getPlanta(cod_pl)!=NULL){
						 setlinestyle(0,0,1);
                         pos_pl= getPlanta(cod_pl)->getPosicao();
                         if(getPlanta(cod_pl)->getTamanho()==1){
		                    rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+3,pos_pl.y+3);
					   	 }
						 else{
						    rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+5,pos_pl.y+5); 
						 }
		                 imprime_campo_descricao(); 
                         imprime_info_planta(getPlanta(cod_pl));                           
                        }
                      
                     }
                   else{   
                      setlinestyle(0,0,2);
                      setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));
        			  if(visao_ps!=-1)  //se existir algum campo de visao
                         circle(pos_ps.x, pos_ps.y,visao_ps);
                      if(visao_pd!=-1)  //se existir algum campo de visao
                         circle(pos_pd.x, pos_pd.y,visao_pd);
                      if(cod_pl!=-1 && getPlanta(cod_pl)!=NULL){
						 setlinestyle(0,0,1);
					     pos_pl = getPlanta(cod_pl)->getPosicao();
						 if(getPlanta(cod_pl)->getTamanho()==1){
		                    rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+3,pos_pl.y+3);
					     }
						 else{
						    rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+5,pos_pl.y+5); 
						}   
					  }   
  /////////////////////////////////////////////////////                    
                      imprime_campo_descricao();  
                      
                           //se houver algum agente ou planta selecionado, imprime suas info
                      if(getPresa(cod_ps)!=NULL){
                         imprime_info_presa(getPresa(cod_ps));
                        } 
                      if(getPredador(cod_pd)!=NULL){ 
                         imprime_info_predador(getPredador(cod_pd));    
                        } 
					  if(getPlanta(cod_pl)!=NULL){ 
                         imprime_info_planta(getPlanta(cod_pl));    
                        } 
						 
                     }
                
                 }  
                 
           pthread_mutex_unlock(&p_key);  
           
                 //     Switch case da tecla   /  mouse   em uma função separada           CODIGO  MUITO  BAGUNÇADO !!!
           
           if(pausa){
               if(tecla == 27){  //ESC
                  sprintf(string,"];");    escreve_relatorio(string,arq);
				  fclose(arq);
				  	printf("\a");
			  		delay(1000);
			  		printf("\a\a\a");
			  		delay(1500);
			  		printf("\a\a");
			  		break;  
                 }
               if(tecla == 99){ //c
                  calcula_var();
                  printf("\n\n -> Command: C    Vizualize the mean and variance of agents' color\n\n");
                  printf("Preys: \nMean R = %.3f\tG = %.3f\tB = %.3f\n",media_r_ps,media_g_ps,media_b_ps);
                  printf("Variance  R = %.3f \tG = %.3f\tB = %.3f\n\n",var_r_ps,var_g_ps,var_b_ps);
				  printf("Predators: \nMean R = %.3f\tG = %.3f\tB = %.3f\n",media_r_pd,media_g_pd,media_b_pd);
                  printf("Variance  R = %.3f \tG = %.3f\tB = %.3f\n\n",var_r_pd,var_g_pd,var_b_pd);
				      
                 }
               if(tecla == 120){  //x
                  printf("\n\n -> Command: X    Vizualize information about all preys\n\n");
                  int cont=0;
                  ps_aux=ps1;
                  while(ps_aux!=NULL){
                     cont++;
                     if(cont==5){
                        printf("\t\tPress ENTER to vizualize more preys...\n\n");
                        getch();
                        cont=0;
                       }               
                     printf(" *  Prey %d partner %d category %d gender %d speed %d position %d %d\n",ps_aux->getCodigo(),ps_aux->getCod_parceiro(),ps_aux->getCategoria(),ps_aux->getSexo(),ps_aux->getVelocidade(), ps_aux->getPosicao().x, ps_aux->getPosicao().y);                 
                     printf("Age %d AgeMax %d Pregnant %d Resg %d Senses %d AreaOfInterest %d Illness %d\n\n",ps_aux->getIdade(),ps_aux->getIdade_max(),ps_aux->getGestacao(),ps_aux->getResguardo(),ps_aux->getSentidos(), ps_aux->getArea_interesse(),ps_aux->getDoenca());                 
                     ps_aux= ps_aux->getProx_c(); 
                    }
                  printf("\n   > All preys vizualized < \n\n");     
                 }  
               if(tecla == 'h'){    //h
                  printf("\n\n -> Command: H    Select a predator\n\n");
                  cout<<" * Enter the code= ";
                  scanf("%d",&pd_sel);  
                 }
               if(tecla == 122){    //z
                  printf("\n\n -> Commando: Z    Vizualize information about all predators\n\n");
                  int cont=0;
                  pd_aux=pd1;
                  while(pd_aux!=NULL){
                     cont++;
                     if(cont==5){
                        printf("\t\tPress ENTER to vizualize more predators...\n\n");
                        getch();
                        cont=0;
                       }
                     printf(" *  Predator %d partner %d category %d gender %d speed %d position %d %d\n",pd_aux->getCodigo(),pd_aux->getCod_parceiro(),pd_aux->getCategoria(),pd_aux->getSexo(),pd_aux->getVelocidade(), pd_aux->getPosicao().x, pd_aux->getPosicao().y);                 
                     printf("Age %d AgeMax %d Pregnant %d Resg %d Senses %d AreaOfInterest %d Hunger %d Illness %d\n\n",pd_aux->getIdade(),pd_aux->getIdade_max(),pd_aux->getGestacao(),pd_aux->getResguardo(),pd_aux->getSentidos(), pd_aux->getArea_interesse(),pd_aux->getFome(),pd_aux->getDoenca());                         
                     pd_aux= pd_aux->getProx_c(); 
                    }
                  printf("\n   > All predators vizualized < \n\n");   
                 }
               if(tecla==118){   //v
                  printf("\n\n -> Commando: V    Vizualize environment information\n\n");
                  printf(" *  Environment: Color %d %d %d   Dimension: %d %d \n\n",cp.getCor().r,cp.getCor().g,cp.getCor().b,le_info("qt_col_campo"),le_info("qt_lin_campo"));
                 }    
               if(tecla=='a'){   //a
                  printf("\n\n -> Command: A    Create a new predator with random attributes\n\n");
                  
                  pthread_mutex_lock(&p_key);  

                      if(pd1==NULL){
                         pd1= criar_predador(1,rand()%2,*pd_pais,*pd_pais);  
                         pd_aux= pd1;
                        }  
                      else{
                         pd_aux=pd1;
                         while(pd_aux->getProx_c() != NULL){
                            pd_aux= pd_aux->getProx_c();
                           }
                         pd_aux->setProx_c(criar_predador(pd_aux->getCodigo()+1,rand()%2,*pd_pais, *pd_pais));  
                         pd_aux= pd_aux->getProx_c();
                        }               
                      pd_aux->setFome(le_info("tempo_fome"));
                      pd_aux->setSede(le_info("tempo_sede"));
                      pd_ = pd_aux->getMove_td();
                      pthread_create(&pd_, NULL, movimentar_predador, pd_aux); 
                      
                      setlinestyle(0,0,2);
                      setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));
        			  if(visao_ps!=-1)  //se existir algum campo de visao
                         circle(pos_ps.x, pos_ps.y,visao_ps);
                      if(visao_pd!=-1)  //se existir algum campo de visao
                         circle(pos_pd.x, pos_pd.y,visao_pd);
  
                      cod_ps=-1;
                      cod_pl=-1;
                      cod_pd=pd_aux->getCodigo();       
                      pos_pd=pd_aux->getPosicao();
                      visao_pd=pd_aux->getSentidos();
                      setlinestyle(1,0,1);
                      setcolor(COLOR(255,193,37));
                      circle(pos_pd.x, pos_pd.y,visao_pd);
                      
                      imprime_campo_descricao();
                      imprime_info_predador(pd_aux);
                      
            
                  pthread_mutex_unlock(&p_key);    
                  
                  printf("   > New predator created successfully < \n");   
            
                 }
               if(tecla=='s'){   //s
                  printf("\n\n -> Command: S    Create a new prey with random attributes\n\n");
                  
                  pthread_mutex_lock(&p_key);  

                      if(ps1==NULL){
                         ps1= criar_presa(1,rand()%2,*ps_pais, *ps_pais);  
                         ps_aux= ps1;
                        }  
                      else{
                         ps_aux=ps1;
                         while(ps_aux->getProx_c() != NULL){
                            ps_aux= ps_aux->getProx_c();
                           }
                         ps_aux->setProx_c(criar_presa(ps_aux->getCodigo()+1,rand()%2,*ps_pais, *ps_pais));  
                         ps_aux= ps_aux->getProx_c();
                         //printf("\t\t\tcriou mais uma  %d\n", ps_aux->getCodigo());
                        }  
                      ps_aux->setFome(le_info("tempo_fome"));  
					  ps_aux->setSede(le_info("tempo_sede"));    
					  ps_ = ps_aux->getMove_td();           
                      pthread_create(&ps_, NULL, movimentar_presa, ps_aux); 
                      
                      setlinestyle(0,0,2);
                      setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));
        			  if(visao_ps!=-1)  //se existir algum campo de visao
                         circle(pos_ps.x, pos_ps.y,visao_ps);
                      if(visao_pd!=-1)  //se existir algum campo de visao
                         circle(pos_pd.x, pos_pd.y,visao_pd);
  
  
                      cod_pd=-1;
                      cod_pl=-1;
                      cod_ps=ps_aux->getCodigo();       
                      pos_ps=ps_aux->getPosicao();
                      visao_ps=ps_aux->getSentidos();
                      setlinestyle(1,0,1);
                      setcolor(COLOR(255,193,37));
                      circle(pos_ps.x, pos_ps.y,visao_ps);
                      
                     // printf("impremiu o sentido da plesa %d\t\n",ps_aux->getCodigo());
                      
                      imprime_campo_descricao();
                      imprime_info_presa(ps_aux);
                      
                  pthread_mutex_unlock(&p_key);    
                  
                  printf("   > New prey created successfully <\n");   
            
                 }               
   
               if(tecla=='d'){   //d
                  printf("\n\n -> Command: D    Vizualize detailed information about a predator\n\n");
                  int cod;
                  cout<<" * Enter the code= ";
                  scanf("%d",&cod);  
                  pd_aux=NULL;
                  pd_aux= getPredador(cod);
                  
                  if(pd_aux!=NULL){
                       cout<<"\n§§§     Predator     §§§\n\n";
                       cout<<"Code ID= "<<pd_aux->getCodigo();
                       cout<<endl<<"Code Mother= "<<pd_aux->getCod_mae();
                       cout<<endl<<"Code Partner= "<<pd_aux->getCod_parceiro();
                       cout<<endl<<"Code Target (Hunger)= "<<pd_aux->getCod_alvo_fome();
                       cout<<endl<<"Category= "<<pd_aux->getCategoria();
                       cout<<endl<<"Color    R= "<<pd_aux->getCor().r<<"   G= "<<pd_aux->getCor().g<<"   B= "<<pd_aux->getCor().b;
                       cout<<endl<<"Gender= "<< pd_aux->getSexo();
                       cout<<endl<<"Position   X= "<<pd_aux->getPosicao().x<<"    Y= "<<pd_aux->getPosicao().y;
                       cout<<endl<<"Speed= "<<pd_aux->getVelocidade();
                       cout<<endl<<"Size= "<<pd_aux->getTamanho();
                       cout<<endl<<"Fertile?= "<<pd_aux->getFertil();
                       cout<<endl<<"Age= "<<pd_aux->getIdade();
                       cout<<endl<<"Age_Max= "<<pd_aux->getIdade_max();
                       cout<<endl<<"Pregnant= "<<pd_aux->getGestacao();
                       cout<<endl<<"Resg= "<<pd_aux->getResguardo();
                       cout<<endl<<"Senses= "<<pd_aux->getSentidos();
                       cout<<endl<<"Area of interest= "<<pd_aux->getArea_interesse();
                       cout<<endl<<"Hunger= "<<pd_aux->getFome();
                       cout<<endl<<"Thrist= "<<pd_aux->getSede()<<endl<<endl;
                    }
                  else{
                       cout<<endl<<"\nPredator code ID \""<<cod<<"\" was not found"<<endl<<endl;
                       
                    }    
                       
   
                 }
                 
               if(tecla=='f'){   //f
                  printf("\n\n -> Command: F    Visualize detailed information about a prey\n\n");
                  int cod;
                  cout<<" * Enter the code= ";
                  scanf("%d",&cod); 
                  ps_aux=NULL;
                  ps_aux= getPresa(cod);
                  
                  if(ps_aux!=NULL){
                       diferenca_cor(ps_aux->getCor(), cp.getCor(), &cor_aux);
                       cout<<"\n§§§     Prey     §§§\n\n";
                       cout<<"Code ID= "<<ps_aux->getCodigo();
                       cout<<endl<<"Code Mother= "<<ps_aux->getCod_mae();
                       cout<<endl<<"Code Partner= "<<ps_aux->getCod_parceiro();
                       cout<<endl<<"Code Target (Hunger)= "<<ps_aux->getCod_alvo_fome();
                       cout<<endl<<"Code Threat= "<<ps_aux->getCod_ameaca();
                       cout<<endl<<"Category= "<<ps_aux->getCategoria();
                       cout<<endl<<"Color    R= "<<ps_aux->getCor().r<<"   G= "<<ps_aux->getCor().g<<"   B= "<<ps_aux->getCor().b;
                       cout<<endl<<"Difference between Color Prey/Environment     R= "<<cor_aux.r<<"   G= "<<cor_aux.g<<"   B= "<<cor_aux.b;
                       cout<<endl<<"Gender= "<< ps_aux->getSexo();
                       cout<<endl<<"Position   X= "<<ps_aux->getPosicao().x<<"    Y= "<<ps_aux->getPosicao().y;
                       cout<<endl<<"Speed= "<<ps_aux->getVelocidade();
                       cout<<endl<<"Size= "<<ps_aux->getTamanho();
                       cout<<endl<<"Fertile?= "<<ps_aux->getFertil();
                       cout<<endl<<"Age= "<<ps_aux->getIdade();
                       cout<<endl<<"Age_Max= "<<ps_aux->getIdade_max();
                       cout<<endl<<"Pregnant= "<<ps_aux->getGestacao();
                       cout<<endl<<"Resg= "<<ps_aux->getResguardo();
                       cout<<endl<<"Senses= "<<ps_aux->getSentidos();
                       cout<<endl<<"Area of interest= "<<ps_aux->getArea_interesse();
                       cout<<endl<<"Hunger= "<<ps_aux->getFome();
                       cout<<endl<<"Thrist= "<<ps_aux->getSede()<<endl<<endl;
                       cor_aux.r= cor_aux.g = cor_aux.b = -1;
                       
                    }
                  else{
                       cout<<endl<<"\nPrey code ID \""<<cod<<"\" was not found"<<endl<<endl;
                       
                    }    
                       
                 }
              
              
              if(tecla=='g'){   //g
                  printf("\n\n -> Command: G    Vizualize datailed information about a plant\n\n");
                  int cod;
                  cout<<" * Enter the code= ";
                  scanf("%d",&cod); 
                  pl_aux=NULL;
                  pl_aux= getPlanta(cod);
                  
                  if(pl_aux!=NULL){
                       cout<<"\n§§§     Plant     §§§\n\n";
                       cout<<"Code ID= "<<pl_aux->getCodigo();
                       cout<<endl<<"Color    R= "<<pl_aux->getCor().r<<"   G= "<<pl_aux->getCor().g<<"   B= "<<pl_aux->getCor().b;
                       cout<<endl<<"Position   X= "<<pl_aux->getPosicao().x<<"    Y= "<<pl_aux->getPosicao().y;
                       cout<<endl<<"Size= "<<pl_aux->getTamanho();
                       cout<<endl<<"Status= "<<pl_aux->getEstado()<<endl;                      
                    }
                  else{
                       cout<<endl<<"\nPlant code ID \""<<cod<<"\" was not found"<<endl<<endl;
                    }    
                       
                 }
              
              if(tecla=='q'){   //q
                   cout<<"Exitting program...";
                   system("Taskkill /IM ProjetoPresas.exe");   //  add   /F dps do nome para forçar a saída
                       
                 }
              
              if(tecla=='b'){
				
				setfillstyle(1,COLOR(cp.getCor().r, cp.getCor().g, cp.getCor().b));
			    bar(0,0,qt_col,qt_lin);    
			    //imprime_campo_descricao();
                      
				  setlinestyle(1,0,1);
                  setcolor(COLOR(255,193,37));
                  
                  if(getPresa(cod_ps)!=NULL){
                     pos_ps= getPresa(cod_ps)->getPosicao();
                     visao_ps=getPresa(cod_ps)->getSentidos();
                     circle(pos_ps.x, pos_ps.y, visao_ps); 
                     imprime_campo_descricao(); 
                     imprime_info_presa(getPresa(cod_ps));
                    }
                  if(getPredador(cod_pd)!=NULL){
                     pos_pd= getPredador(cod_pd)->getPosicao();
                     visao_pd=getPredador(cod_pd)->getSentidos();
                     circle(pos_pd.x, pos_pd.y, visao_pd); 
                     imprime_campo_descricao(); 
                     imprime_info_predador(getPredador(cod_pd));                           
                    }  
				
					
			     if(borda){
			        ps_aux = ps1;
			        while(ps_aux != NULL){
		               setlinestyle(0,0,1); 
				       setfillstyle(1, COLOR(ps_aux->getCor().r,ps_aux->getCor().g,ps_aux->getCor().b));
					   setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));	   
				       fillellipse(ps_aux->getPosicao().x,ps_aux->getPosicao().y,ps_aux->getTamanho()+1,ps_aux->getTamanho()+1); 
				       ps_aux = ps_aux->getProx_c();
				    }
			        pd_aux = pd1;
			        while(pd_aux != NULL){
  					   setlinestyle(0,0,2); 
				       setfillstyle(1, COLOR(pd_aux->getCor().r,pd_aux->getCor().g,pd_aux->getCor().b));
			           setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));	
				       fillellipse(pd_aux->getPosicao().x,pd_aux->getPosicao().y,pd_aux->getTamanho()+1,pd_aux->getTamanho()+1); 
				       pd_aux = pd_aux->getProx_c();
					}	
				    borda = false;
				 }
				 else{
					ps_aux = ps1;
			        while(ps_aux != NULL){
    				   setlinestyle(0,0,1); 
				       setfillstyle(1, COLOR(ps_aux->getCor().r,ps_aux->getCor().g,ps_aux->getCor().b));	
			           if(ps_aux->getSexo())
				          setcolor(COLOR(255,0,0)); 
				       else
					      setcolor(COLOR(50,80,250)); 
				       fillellipse(ps_aux->getPosicao().x,ps_aux->getPosicao().y,ps_aux->getTamanho(),ps_aux->getTamanho()); 
				       ps_aux = ps_aux->getProx_c();
				    }
			        pd_aux = pd1;
			        while(pd_aux != NULL){
 					   setlinestyle(0,0,2); 
				       setfillstyle(1, COLOR(pd_aux->getCor().r,pd_aux->getCor().g,pd_aux->getCor().b));
			           if(pd_aux->getSexo())
				          setcolor(COLOR(255,200,0)); 
				       else
					      setcolor(COLOR(10,200,50)); 
				       fillellipse(pd_aux->getPosicao().x,pd_aux->getPosicao().y,pd_aux->getTamanho(),pd_aux->getTamanho()); 
				       pd_aux = pd_aux->getProx_c();
					}
					borda = true;
				 }
				    
				     
              }  //tecla b
              
              if(tecla == 72){ //Cima  // verificar se tem alguma velocidade ou campo de visão fora do limite
              
                 int max_visao = le_info("campo_max_visao_presa");
                 
                 ps_aux = ps1;
                 
                 while(ps_aux!=NULL){
				    
					if(ps_aux->getVelocidade() < 0 || ps_aux->getVelocidade() > 9 || ps_aux->getSentidos() < max_visao*0.5 || ps_aux->getSentidos() > max_visao){
						printf("\n Visao ou Campo de visao BUGADOS:\n\n");
						
						diferenca_cor(ps_aux->getCor(), cp.getCor(), &cor_aux);
                       cout<<"\n§§§     Prey     §§§\n\n";
                       cout<<"Code ID= "<<ps_aux->getCodigo();
                       //cout<<endl<<"Code Mother= "<<ps_aux->getCod_mae();
                       //cout<<endl<<"Code Partner= "<<ps_aux->getCod_parceiro();
                       //cout<<endl<<"Code Target (Hunger)= "<<ps_aux->getCod_alvo_fome();
                       //cout<<endl<<"Code Threat= "<<ps_aux->getCod_ameaca();
                       cout<<endl<<"Category= "<<ps_aux->getCategoria();
                       cout<<endl<<"Color    R= "<<ps_aux->getCor().r<<"   G= "<<ps_aux->getCor().g<<"   B= "<<ps_aux->getCor().b;
                       cout<<endl<<"Difference between Color Prey/Environment     R= "<<cor_aux.r<<"   G= "<<cor_aux.g<<"   B= "<<cor_aux.b;
                       cout<<endl<<"Gender= "<< ps_aux->getSexo();
                       cout<<endl<<"Position   X= "<<ps_aux->getPosicao().x<<"    Y= "<<ps_aux->getPosicao().y;
                       cout<<endl<<"Speed= "<<ps_aux->getVelocidade();
                       //cout<<endl<<"Size= "<<ps_aux->getTamanho();
                       //cout<<endl<<"Fertile?= "<<ps_aux->getFertil();
                       //cout<<endl<<"Age= "<<ps_aux->getIdade();
                       //cout<<endl<<"Age_Max= "<<ps_aux->getIdade_max();
                       //cout<<endl<<"Pregnant= "<<ps_aux->getGestacao();
                       //cout<<endl<<"Resg= "<<ps_aux->getResguardo();
                       cout<<endl<<"Senses= "<<ps_aux->getSentidos();
                       //cout<<endl<<"Area of interest= "<<ps_aux->getArea_interesse();
                       //cout<<endl<<"Hunger= "<<ps_aux->getFome();
                       //cout<<endl<<"Thrist= "<<ps_aux->getSede()<<endl<<endl;
                       cor_aux.r= cor_aux.g = cor_aux.b = -1;
                       
					   getch(); 	
						
					}	
						
				    ps_aux = ps_aux->getProx_c();
                 }
                 
              
                
                 pd_aux = pd1;
                 
                 while(pd_aux!=NULL){
				    
					if(pd_aux->getVelocidade() < 0 || pd_aux->getVelocidade() > 9 || pd_aux->getSentidos() < max_visao*0.5 || pd_aux->getSentidos() > max_visao){
						printf("\n Visao ou Campo de visao BUGADOS:\n\n");
						
						cout<<"\n§§§     Predator     §§§\n\n";
                       cout<<"Code ID= "<<pd_aux->getCodigo();
                       //cout<<endl<<"Code Mother= "<<pd_aux->getCod_mae();
                       //cout<<endl<<"Code Partner= "<<pd_aux->getCod_parceiro();
                       //cout<<endl<<"Code Target (Hunger)= "<<pd_aux->getCod_alvo_fome();
                       cout<<endl<<"Category= "<<pd_aux->getCategoria();
                       cout<<endl<<"Color    R= "<<pd_aux->getCor().r<<"   G= "<<pd_aux->getCor().g<<"   B= "<<pd_aux->getCor().b;
                       cout<<endl<<"Gender= "<< pd_aux->getSexo();
                       cout<<endl<<"Position   X= "<<pd_aux->getPosicao().x<<"    Y= "<<pd_aux->getPosicao().y;
                       cout<<endl<<"Speed= "<<pd_aux->getVelocidade();
                       //cout<<endl<<"Size= "<<pd_aux->getTamanho();
                       //cout<<endl<<"Fertile?= "<<pd_aux->getFertil();
                       //cout<<endl<<"Age= "<<pd_aux->getIdade();
                       //cout<<endl<<"Age_Max= "<<pd_aux->getIdade_max();
                       //cout<<endl<<"Pregnant= "<<pd_aux->getGestacao();
                       //cout<<endl<<"Resg= "<<pd_aux->getResguardo();
                       cout<<endl<<"Senses= "<<pd_aux->getSentidos();
                       //cout<<endl<<"Area of interest= "<<pd_aux->getArea_interesse();
                       //cout<<endl<<"Hunger= "<<pd_aux->getFome();
                       //cout<<endl<<"Thrist= "<<pd_aux->getSede()<<endl<<endl;
                       
					   getch(); 	
						
					}	
						
				    pd_aux = pd_aux->getProx_c();		
                 }
                
			  }
			  if(tecla == 77){ //direita
			         //apaga o campo de visao do agente selecionado
   			     setlinestyle(0,0,2);
                 setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));
    			 if(visao_ps!=-1)  
                    circle(pos_ps.x, pos_ps.y,visao_ps);
                 if(visao_pd!=-1)  
                    circle(pos_pd.x, pos_pd.y,visao_pd);
                 if(cod_pl!=-1 && getPlanta(cod_pl)!=NULL){
					  setlinestyle(0,0,1);
				      pos_pl = getPlanta(cod_pl)->getPosicao();
					  if(getPlanta(cod_pl)->getTamanho()==1){
	                     rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+3,pos_pl.y+3);
				      }
					  else{
					     rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+5,pos_pl.y+5); 
					  }   
				   }
			     
				 if(cod_ps!=-1){
					ps_aux = getPresa(cod_ps)->getProx_c(); 
				    if(ps_aux==NULL)
				       ps_aux = ps1;
					if(ps_aux!=NULL){
						cod_ps = ps_aux->getCodigo(); 
						pos_ps = ps_aux->getPosicao();
						visao_ps = ps_aux->getSentidos();
				    }
			        setlinestyle(1,0,1);
                    setcolor(COLOR(255,193,37));
                    circle(pos_ps.x, pos_ps.y,visao_ps);
                    imprime_campo_descricao();
        		    imprime_info_presa(ps_aux);
			     }
			     if(cod_pd!=-1){
					pd_aux = getPredador(cod_pd)->getProx_c();
					if(pd_aux==NULL)
					   pd_aux = pd1; 
				    if(pd_aux!=NULL){
						cod_pd = pd_aux->getCodigo(); 
						pos_pd = pd_aux->getPosicao();
						visao_pd = pd_aux->getSentidos();
				    }
				    setlinestyle(1,0,1);
                    setcolor(COLOR(255,193,37));
                    circle(pos_pd.x, pos_pd.y,visao_pd);
                    imprime_campo_descricao();
            		imprime_info_predador(pd_aux);
			     }
			     if(cod_pl!=-1){
					pl_aux = getPlanta(cod_pl)->getProx_p();
					if(pl_aux==NULL)
					   pl_aux = pl1; 
				    if(pl_aux!=NULL){
						cod_pl = pl_aux->getCodigo(); 
						pos_pl = pl_aux->getPosicao();
				    }
				    
					setlinestyle(0,0,1);
				    setcolor(COLOR(255,193,37));
                    if(pl_aux->getTamanho()==1){
	                   rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+3,pos_pl.y+3);
				    }
					else{
					   rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+5,pos_pl.y+5); 
					}  
                    
                    imprime_campo_descricao();
            		imprime_info_planta(pl_aux);
			     }
			     
			  }
			  if(tecla == 80){ //baixo
			  }
			  if(tecla == 75){ //esquerda
			  }
              
              
              
              
            }
             
             
          }   
        
        
        
             /* CLIQUE IDENTIFICADO */
        if(ismouseclick(WM_LBUTTONDOWN)){  
            posXY clique_pos;
            
            getmouseclick(WM_LBUTTONDOWN, clique_pos.x, clique_pos.y);   
   		    
            pthread_mutex_lock(&p_key);
            
                setcolor(COLOR(255,193,37));
            	settextstyle(8,0,1);		
                bgiout << clique_pos.x<<"     \n";
                bgiout << clique_pos.y<<"     ";  
                outstreamxy(qt_col+70,296);   
    	              
       		    if(pausa){ 
                   setlinestyle(0,0,2);
                   setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));
    			   if(visao_ps!=-1)  
                      circle(pos_ps.x, pos_ps.y,visao_ps);
                   if(visao_pd!=-1)  
                      circle(pos_pd.x, pos_pd.y,visao_pd);
                   if(cod_pl!=-1 && getPlanta(cod_pl)!=NULL){
					  setlinestyle(0,0,1);
				      pos_pl = getPlanta(cod_pl)->getPosicao();
					  if(getPlanta(cod_pl)->getTamanho()==1){
	                     rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+3,pos_pl.y+3);
				      }
					  else{
					     rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+5,pos_pl.y+5); 
					  }   
				   }
                }
                imprime_campo_descricao();    
                   
                cod_ps=-1;
                visao_ps=-1;
                ps_aux= ps1;
                while(ps_aux != NULL){
                   if(clique_pos.x > (ps_aux->getPosicao().x - ps_aux->getTamanho()) && clique_pos.x < (ps_aux->getPosicao().x + ps_aux->getTamanho())){
                      if(clique_pos.y > (ps_aux->getPosicao().y - ps_aux->getTamanho()) && clique_pos.y < (ps_aux->getPosicao().y + ps_aux->getTamanho())){
                         cod_ps=ps_aux->getCodigo();
                         pos_ps=ps_aux->getPosicao();
                         visao_ps=ps_aux->getSentidos();
                         if(pausa){  
                            setlinestyle(1,0,1);
                            setcolor(COLOR(255,193,37));
                            circle(pos_ps.x, pos_ps.y,visao_ps);
                           }
                         imprime_campo_descricao();
        				 imprime_info_presa(ps_aux);
    
                         break;   
                        }
                     }  
                   ps_aux=ps_aux->getProx_c();           
                  }
           
                cod_pd=-1;
                visao_pd=-1;
                if(cod_ps== -1){     
                    pd_aux= pd1;
                    while(pd_aux != NULL){
                       if(clique_pos.x > (pd_aux->getPosicao().x - pd_aux->getTamanho()) && clique_pos.x < (pd_aux->getPosicao().x + pd_aux->getTamanho())){
                          if(clique_pos.y > (pd_aux->getPosicao().y - pd_aux->getTamanho()) && clique_pos.y < (pd_aux->getPosicao().y + pd_aux->getTamanho())){
                             cod_pd=pd_aux->getCodigo();
                             pos_pd=pd_aux->getPosicao();
                             visao_pd=pd_aux->getSentidos();
                             if(pausa){
                                setlinestyle(1,0,1);
                                setcolor(COLOR(255,193,37));
                                circle(pos_pd.x, pos_pd.y,visao_pd);
                               }
                             imprime_campo_descricao();
            				 imprime_info_predador(pd_aux);
        
                             break; 
                            }
                         }  
                       pd_aux=pd_aux->getProx_c();           
                      }
                   } 
                
                cod_pl=-1;
                if(cod_ps== -1 && cod_pd== -1){   
					pl_aux= pl1;
                    while(pl_aux != NULL){
					   if(clique_pos.x >= (pl_aux->getPosicao().x) && clique_pos.x < (pl_aux->getPosicao().x + 4)){
						  if(clique_pos.y >= (pl_aux->getPosicao().y) && clique_pos.y < (pl_aux->getPosicao().y + 4)){
                             cod_pl=pl_aux->getCodigo();
                             pos_pl=pl_aux->getPosicao();
                             ///////////////////////////////////////////////////////////
							 if(pausa){
                                setlinestyle(0,0,1);
                                setcolor(COLOR(255,193,37));
                                if(pl_aux->getTamanho()==1){
				                    rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+3,pos_pl.y+3);
							   	 }
								 else{
								    rectangle(pos_pl.x-2,pos_pl.y-2,pos_pl.x+5,pos_pl.y+5); 
								 }
                               }
                             imprime_campo_descricao();
            				 imprime_info_planta(pl_aux);
        
                             break; 
                            }
                        }  
                       pl_aux=pl_aux->getProx_p();           
                    }
                } 
                
                
            pthread_mutex_unlock(&p_key);
                        
			    //clicked on config button
			     
			if(clique_pos.x >= qt_col+151 && clique_pos.x <= qt_col+167 && clique_pos.y >= 2 && clique_pos.y <= 19){
				pausa=true;
				chama_configuration(*argv);
				//read conf again
			}							

          }    
    
    
                 
        if(kbhit())  
           continue;
        
        delay(500);    
        
        if(pausa){
           tmp_paus = clock() - tempo;
          }  
        else{
           tempo = clock() - tmp_paus;  
          }  
 

    }

    closegraph(); 

    return 0;
}






//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Presa* getPresa (int cod){
   Presa *ps_aux;
   int i;
   
   ps_aux=ps1;
   if(cod!= -1 && ps_aux != NULL){        
       while(ps_aux->getCodigo() < cod){
          if(ps_aux->getProx_c()!= NULL)   
             ps_aux=ps_aux->getProx_c();
          else
             break;               
         }
       if(ps_aux->getCodigo() == cod)
          return ps_aux;
      }
   //printf(">> Prey %d not found\n\ a",cod);      
   return NULL;   
   
  }
  
  
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
Predador* getPredador (int cod){
   Predador *pd_aux;
   int i;
   
   pd_aux=pd1;
   if(cod !=-1 && pd_aux != NULL){
       while(pd_aux->getCodigo() < cod){
          if(pd_aux->getProx_c()!= NULL)   
             pd_aux=pd_aux->getProx_c();
          else
             break;               
         }
       if(pd_aux->getCodigo() == cod)
          return pd_aux;
      }
   //printf(">> Predator %d not found\n\ a",cod);   
   return NULL;   
   
  }
  
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
Planta* getPlanta (int cod){  /**/
   Planta *pl_aux;
   int i;
   
   pl_aux=pl1;
   if(cod !=-1 && pl_aux != NULL){
       while(pl_aux->getCodigo() < cod){
          if(pl_aux->getProx_p()!= NULL)   
             pl_aux=pl_aux->getProx_p();
          else
             break;               
         }
       if(pl_aux->getCodigo() == cod)
          return pl_aux;
      }
  // printf(">> Planta %d não encontrada\n\ a",cod);   
   return NULL;   
  }
  
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
Lago* getLago (int cod){  /**/
   Lago *lg_aux;
   int i;
   
   lg_aux=lg1;
   if(cod !=-1 && lg_aux != NULL){
       while(lg_aux->getCodigo() < cod){
          if(lg_aux->getProx_l()!= NULL)   
             lg_aux=lg_aux->getProx_l();
          else
             break;
         }
       if(lg_aux->getCodigo() == cod)
          return lg_aux;
      }
  // printf(">> Planta %d não encontrada\n\ a",cod);
   return NULL;
  }
  

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

posXY sorteia_posicao(posXY p1,int r,int d){    
    posXY p2;
    bool aux;
	Lago* lg_aux;
    do{
       srand(clock() * (p1.x*p1.y));

       p2.x= (p1.x-r-d) + (rand()%((p1.x+r+d+1)-(p1.x-r-d)));
       p2.y= (p1.y-r-d) + (rand()%((p1.y+r+d+1)-(p1.y-r-d)));
       
       aux=0;
       lg_aux=lg1;
       while(lg_aux != NULL){
		  
		  if(calcula_distancia(p2,lg_aux->getPosicao()) < lg_aux->getTamanho() * lg_aux->getTamanho_atual() / 100){
			 aux=1;	
			 break;
		  }		  
		  lg_aux=lg_aux->getProx_l();
       }
       
           
      }while(calcula_distancia(p1,p2)<(r-d) || calcula_distancia(p1,p2)>(r+d) || aux==1);  
      
    return p2;
    
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Presa* criar_presa(int c, bool s, Presa mae, Presa pai){    
    Presa *p;//,pai_aux;    
    posXY pos;//,pos_aux;    
    //corRGB cor_aux;
    int visao_max = le_info("campo_max_visao_presa");
    int vis_rep_max = le_info("campo_max_visao_rep_presa");
    int var_vis_rep_max = le_info("var_campo_max_visao_rep_presa");
    
    

//    cor_aux.r = -1;
//	cor_aux.g = -1;
//	cor_aux.b = -1;
 //   pos_aux.x = -1;
//	pos_aux.y = -1;
    
//    pai_aux.setCor(cor_aux);
 //   pai_aux.setPosicao(pos_aux);
  //  pai_aux.setVelocidade(-1);
   // pai_aux.setCategoria(2);
   // pai_aux.setSentidos(-1);

//    if(getPresa(mae.getCodigo()) == NULL)
//       printf("mai nola");//mae = pai_aux;
//    if(getPresa(pai.getCodigo()) == NULL)
//	   printf("pae nolo");//pai = pai_aux;   
    
    p=(Presa*) malloc(sizeof(class Presa));   
    
    p->setTamanho(le_info("tamanho_presa"));
    if(mae.getPosicao().x == -1  || mae.getPosicao().y == -1){
	   Lago* lg_aux;
	   int aux; 
	   do{		      
          pos.x=p->getTamanho() + (rand()%(le_info("qt_col_campo") - p->getTamanho()*2));
          pos.y=p->getTamanho() + (rand()%(le_info("qt_lin_campo") - p->getTamanho()*2));  
		  
		  aux = 0;
		  lg_aux=lg1;
		  while(lg_aux != NULL){
			 if(calcula_distancia(pos, lg_aux->getPosicao()) < lg_aux->getTamanho() * lg_aux->getTamanho_atual() / 100){
				aux = 1;
				break;	
			 }
			 lg_aux = lg_aux->getProx_l();	
		  }
		  
		 }while(aux==1);
	   mae.setPosicao(pos);
      }
   
    p->nascer(c,s,mae,pai);   
     
    if(s){
       cps_f++;
       
       if((1+rand()%100 <= le_info("intensidade_doenca_presa"))&&(mod_doenca)){   //doenca
          p->setDoenca(true);
          p->setIdade_max(floor(le_info("idade_media_presa_f") * ((float)(le_info("vida_doenca_presa") * 0.01))), le_info("var_idade_media_presa_f"));
         }
       else{
          p->setDoenca(false); 
          p->setIdade_max(le_info("idade_media_presa_f"), le_info("var_idade_media_presa_f"));
         }
      }
    else{
       cps_m++;
       if((1+rand()%100 <= le_info("intensidade_doenca_presa"))&&(mod_doenca)){   //doenca
          p->setDoenca(true);
          p->setIdade_max(floor(le_info("idade_media_presa_m") * ((float)(le_info("vida_doenca_presa") * 0.01))), le_info("var_idade_media_presa_m"));
         }
       else{
          p->setDoenca(false); 
          p->setIdade_max(le_info("idade_media_presa_m"), le_info("var_idade_media_presa_m"));
         }
      }
    
    
    
    
		   
   if(mae.getSentidos() >= visao_max*0.75 && pai.getSentidos() >= visao_max*0.75){ //pais ferteis
	   p->setSentidos(round(((mae.getSentidos() + pai.getSentidos()) / 2.0)-visao_max*0.25));			
   }
   else{
		if(mae.getSentidos() >= visao_max*0.75){ // o pai passou p categoria 4 durante a gestacao do bebe
			p->setSentidos(round(((mae.getSentidos() + pai.getSentidos()+visao_max*0.25) / 2.0)-visao_max*0.25));
		}
		else if(pai.getSentidos() >= visao_max*0.75){   // a mae passou p categoria 4 durante a gestacao do bebe
			p->setSentidos(round(((mae.getSentidos()+visao_max*0.25 + pai.getSentidos()) / 2.0)-visao_max*0.25));
		}
		else if(mae.getSentidos() >= visao_max*0.5 && mae.getSentidos() >= visao_max*0.5){
			p->setSentidos(round(((mae.getSentidos()+visao_max*0.25 + pai.getSentidos()+visao_max*0.25) / 2.0)-visao_max*0.25));
		}
		else{
			p->setSentidos(round(visao_max*0.5 + (rand()%visao_max*0.25)));
		}
   }
   
   if(mae.getVisao_reproducao_max() >= vis_rep_max-var_vis_rep_max && pai.getVisao_reproducao_max() >= vis_rep_max-var_vis_rep_max){ //pais vivos
	   p->setVisao_reproducao_max(round(((mae.getVisao_reproducao_max() + pai.getVisao_reproducao_max()) / 2.0))); 			
//printf("presa filh. visao rep %d pais %d %d \n",p->getVisao_reproducao_max(),mae.getVisao_reproducao_max(),pai.getVisao_reproducao_max());
   }   
   else{  //sorteio
       p->setVisao_reproducao_max((vis_rep_max-(vis_rep_max*var_vis_rep_max/100)) + rand()%((vis_rep_max*var_vis_rep_max*2/100) +1)); 
//printf("presa ORFA. visao rep %d\n",p->getVisao_reproducao_max());
   }
   
    p->setArea_interesse(le_info("area_interesse_presa"));
    p->setFome(le_info("tempo_saciedade_fome")+le_info("tempo_fome")-2);
    p->setSede(le_info("tempo_saciedade_sede")+le_info("tempo_sede")-2);
    
    
    if((1+rand()%100 <= le_info("intensidade_mutacao_presa"))&&(mod_mutacao_cor)){   //mutacao
       p->setMutacao(true);
       
       corRGB cor_aux;
       cor_aux.r = rand()%256;
       cor_aux.g = rand()%256;
       cor_aux.b = rand()%256;

       p->setCor(cor_aux);
      }
    else
       p->setMutacao(false);
       
    /*
 
    cout<<"\n§§§     Presa     §§§\n\n";
   cout<<"Codigo= "<<p->getCodigo();
   cout<<endl<<"Codigo Mae= "<<p->getCod_mae();
 //  cout<<endl<<"Codigo Parceiro= "<<p->getCod_parceiro();
 //  cout<<endl<<"Codigo Ameaca= "<<p->getCod_ameaca();
 //  cout<<endl<<"Codigo Alvo= "<<p->getCod_alvo();
   cout<<endl<<"Categoria= "<<p->getCategoria();
   cout<<endl<<"Cor    R= "<<p->getCor().r<<"   G= "<<p->getCor().g<<"   B= "<<p->getCor().b;
   cout<<endl<<"CorMa  R= "<<mae.getCor().r<<"   G= "<<mae.getCor().g<<"   B= "<<mae.getCor().b;
   cout<<endl<<"CorPa  R= "<<pai.getCor().r<<"   G= "<<pai.getCor().g<<"   B= "<<pai.getCor().b;
   
 //  cout<<endl<<"Diferenca Cor Presa/campo     R= "<<cor_aux.r<<"   G= "<<cor_aux.g<<"   B= "<<cor_aux.b;
   cout<<endl<<"Sexo= "<< p->getSexo();
//   cout<<endl<<"Posicao   X= "<<p->getPosicao().x<<"    Y= "<<p->getPosicao().y;
//   cout<<endl<<"Velocidade= "<<p->getVelocidade();
 //  cout<<endl<<"Tamanho= "<<p->getTamanho();
 //  cout<<endl<<"Fertil= "<<p->getFertil();
   cout<<endl<<"Idade= "<<p->getIdade();
   cout<<endl<<"Idade_Max= "<<p->getIdade_max();
 //  cout<<endl<<"Gestacao= "<<p->getGestacao();
 //  cout<<endl<<"Resguardo= "<<p->getResguardo();
   //cout<<endl<<"Sentidos= "<<p->getSentidos();
  // cout<<endl<<"Area interesse= "<<p->getArea_interesse();
   cout<<endl<<"Doente? "<<p->getDoenca();
   cout<<endl<<"Mutante? "<<p->getMutacao();
   
   */
    
    
    if(p==NULL)
       printf("bebe nulo bugadao");
    
    
    return p;  
 
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Predador* criar_predador(int c, bool s, Predador mae, Predador pai){     
    Predador *p;//,pai_aux;
    posXY pos;//,pos_aux;    
    //corRGB cor_aux;
    int visao_max = le_info("campo_max_visao_predador");
    int vis_rep_max = le_info("campo_max_visao_rep_predador");
    int var_vis_rep_max = le_info("var_campo_max_visao_rep_predador");
//    cor_aux.r = -1;
//	cor_aux.g = -1;
//	cor_aux.b = -1;
//    pos_aux.x = -1;
//	pos_aux.y = -1;
    
//    pai_aux.setCor(cor_aux);
//    pai_aux.setPosicao(pos_aux);
//    pai_aux.setVelocidade(-1);
//    pai_aux.setCategoria(2);
//    pai_aux.setSentidos(-1);

    //if(getPredador(mae.getCodigo()) == NULL)
    //   mae = pai_aux;
    //if(getPredador(pai.getCodigo()) == NULL)
	//   pai = pai_aux;   

    p=(Predador*) malloc(sizeof(class Predador));
    


    p->setTamanho(le_info("tamanho_predador"));
    if(mae.getPosicao().x == -1  || mae.getPosicao().y == -1){
	   Lago* lg_aux;
	   int aux; 
	   do{		      
          pos.x=p->getTamanho() + (rand()%(le_info("qt_col_campo") - p->getTamanho()*2));
          pos.y=p->getTamanho() + (rand()%(le_info("qt_lin_campo") - p->getTamanho()*2));  
		  
		  aux = 0;
		  lg_aux=lg1;
		  while(lg_aux != NULL){
			 if(calcula_distancia(pos, lg_aux->getPosicao()) < lg_aux->getTamanho() * lg_aux->getTamanho_atual() / 100){
				aux = 1;
				break;	
			 }
			 lg_aux = lg_aux->getProx_l();	
		  }
		  
		 }while(aux==1);
	   mae.setPosicao(pos);
      }  
      
    
    p->nascer(c,s,mae,pai); 
    
    if(s){
       cpd_f++;
       if((1+rand()%100 <= le_info("intensidade_doenca_predador"))&&(mod_doenca)){   //doenca
          p->setDoenca(true);
          p->setIdade_max(floor(le_info("idade_media_predador_f") * ((float)(le_info("vida_doenca_predador") * 0.01))), le_info("var_idade_media_predador_f"));
         }
       else{
          p->setDoenca(false); 
          p->setIdade_max(le_info("idade_media_predador_f"), le_info("var_idade_media_predador_f"));
         }
      }
    else{
       cpd_m++;
       if((1+rand()%100 <= le_info("intensidade_doenca_predador"))&&(mod_doenca)){   //doenca
          p->setDoenca(true);
          p->setIdade_max(floor(le_info("idade_media_predador_m") * ((float)(le_info("vida_doenca_predador") * 0.01))), le_info("var_idade_media_predador_m"));
         }
       else{
          p->setDoenca(false); 
          p->setIdade_max(le_info("idade_media_predador_m"), le_info("var_idade_media_predador_m"));
         }
      }
   
   
   if(mae.getSentidos() >= visao_max*0.75 && pai.getSentidos() >= visao_max*0.75){ //pais ferteis
	   p->setSentidos(round(((mae.getSentidos() + pai.getSentidos()) / 2.0)-visao_max*0.25));			
   }
   else{
		if(mae.getSentidos() >= visao_max*0.75){ // o pai passou p categoria 4 durante a gestacao do bebe
			p->setSentidos(round(((mae.getSentidos() + pai.getSentidos()+visao_max*0.25) / 2.0)-visao_max*0.25));
		}
		else if(pai.getSentidos() >= visao_max*0.75){   // a mae passou p categoria 4 durante a gestacao do bebe
			p->setSentidos(round(((mae.getSentidos()+visao_max*0.25 + pai.getSentidos()) / 2.0)-visao_max*0.25));
		}
		else if(mae.getSentidos() >= visao_max*0.5 && mae.getSentidos() >= visao_max*0.5){
			p->setSentidos(round(((mae.getSentidos()+visao_max*0.25 + pai.getSentidos()+visao_max*0.25) / 2.0)-visao_max*0.25));
		}
		else{
			p->setSentidos(round(visao_max*0.5 + (rand()%visao_max*0.25)));
		}
   }
   
   if(mae.getVisao_reproducao_max() >= vis_rep_max-var_vis_rep_max && pai.getSentidos() >= vis_rep_max-var_vis_rep_max){ //pais vivos
	   p->setVisao_reproducao_max(round(((mae.getVisao_reproducao_max() + pai.getVisao_reproducao_max()) / 2.0))); 			
//	   printf("predador filho. visao rep %d pais %d %d \n",p->getVisao_reproducao_max(),mae.getVisao_reproducao_max(),pai.getVisao_reproducao_max());
   }   
   else{  //sorteio
       p->setVisao_reproducao_max((vis_rep_max-(vis_rep_max*var_vis_rep_max/100)) + rand()%((vis_rep_max*var_vis_rep_max*2/100) +1)); 
//   printf("predador ORFAO. visao rep %d\n",p->getVisao_reproducao_max());
   }
   
    
    p->setArea_interesse(le_info("area_interesse_predador"));
    p->setFome(le_info("tempo_saciedade_fome")+le_info("tempo_fome"));
    p->setSede(le_info("tempo_saciedade_sede")+le_info("tempo_sede"));
    
    if((1+rand()%100 <= le_info("intensidade_mutacao_predador"))&&(mod_mutacao_cor)){   //mutacao
       p->setMutacao(true);
       
       corRGB cor_aux;
       cor_aux.r = rand()%256;
       cor_aux.g = rand()%256;
       cor_aux.b = rand()%256;

       p->setCor(cor_aux);
      }
    else
       p->setMutacao(false);
    
  //     cout<<endl<<"Idade= "<<p->getIdade();
  // cout<<endl<<"Idade_Max= "<<p->getIdade_max();
 //  cout<<endl<<"Gestacao= "<<p->getGestacao();
 //  cout<<endl<<"Resguardo= "<<p->getResguardo();
   //cout<<endl<<"Sentidos= "<<p->getSentidos();
  // cout<<endl<<"Area interesse= "<<p->getArea_interesse();
   //cout<<endl<<"Doente? "<<p->getDoenca();
  // cout<<" - "<<le_info("idade_media_predador_f") * ((float)(le_info("vida_doenca_predador") * 0.01));
  // cout<<" - "<<(float)(le_info("vida_doenca_predador") * 0.01);
   
   /*
   cout<<endl<<"Cor    R= "<<p->getCor().r<<"   G= "<<p->getCor().g<<"   B= "<<p->getCor().b;
   cout<<endl<<"CorMa  R= "<<mae.getCor().r<<"   G= "<<mae.getCor().g<<"   B= "<<mae.getCor().b;
   cout<<endl<<"CorPa  R= "<<pai.getCor().r<<"   G= "<<pai.getCor().g<<"   B= "<<pai.getCor().b;
   cout<<endl<<"Doente? "<<p->getDoenca();
   cout<<endl<<"Mutante? "<<p->getMutacao();
   */
   
    
    
    return p;  
 
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Planta* criar_planta(int c, corRGB cor, posXY pos, int t, bool e){ 
    Planta *p;

    p=(Planta*) malloc(sizeof(class Planta));
    
    if(pos.x == -1  || pos.y == -1){
    
       Lago* lg_aux;
	   int aux; 
	   do{		      
          pos.x = (le_info("tamanho_presa") + 1) + (rand()%(le_info("qt_col_campo") - le_info("tamanho_presa")*2 - 3));
          pos.y = (le_info("tamanho_presa") + 1) + (rand()%(le_info("qt_lin_campo") - le_info("tamanho_presa")*2 - 3));  
		  
		  aux = 0;
		  lg_aux = lg1;
		  while(lg_aux != NULL){
			 if(calcula_distancia(pos, lg_aux->getPosicao()) < lg_aux->getTamanho() * lg_aux->getTamanho_atual() / 100){
				aux = 1;
				break;	
			 }
			 lg_aux = lg_aux->getProx_l();	
		  }
		  
		 }while(aux==1);
       
	}   
       
    
    p->inicializa(c, cor, pos, t, e);
    
    //printf("planta criada com t %d na pos %d %d", p->getTamanho(),p->getPosicao().x,p->getPosicao().y);
    
    //cout<<"** "<< ((le_info("tamanho_presa")*0.5 + 1) + rand()%le_info("qt_col_campo")) - le_info("tamanho_presa") - 1 << endl;

    return p;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Lago* criar_lago(int c, corRGB cor, posXY pos, int tam){ 
    Lago *l;

    l=(Lago*) malloc(sizeof(class Lago));
    
    if(tam==-1){
		tam = le_info("tam_min_lago") + (rand()%(le_info("tam_max_lago") - le_info("tam_min_lago")));
    }
    
    
    if(pos.x == -1)
       pos.x = 1 + (rand()%(le_info("qt_col_campo") - 1));
    if(pos.y == -1)
       pos.y = 1 + (rand()%(le_info("qt_lin_campo") - 1));
    
    l->inicializa(c, cor, pos, tam);
    
    //printf("planta criada com t %d na pos %d %d", p->getTamanho(),p->getPosicao().x,p->getPosicao().y);
    
    //cout<<"** "<< ((le_info("tamanho_presa")*0.5 + 1) + rand()%le_info("qt_col_campo")) - le_info("tamanho_presa") - 1 << endl;

    return l;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void matar_presa(int c){
    Presa *ps_aux, *ps_morta;       
    
    if(ps1==NULL){
       printf("\a\a\n *  Failed to killing prey %d! Pointer \"ps1\" is null! \n\n",c);
       return;           
      }
    
    if(ps1->getCodigo() == c){  
       ps_morta=ps1;
             
       if(ps1->getProx_c() != NULL){  
          ps1 = ps1->getProx_c();
         }
       else{  
          ps1=NULL; 
         }
          
       free(ps_morta);
       return;
      }

    ps_aux=ps1;
      
    while(ps_aux->getProx_c() != NULL){ 
       if(ps_aux->getProx_c()->getCodigo() == c){ 
          ps_morta=ps_aux->getProx_c();
          if(ps_aux->getProx_c()->getProx_c() != NULL){   
             ps_aux->setProx_c(ps_aux->getProx_c()->getProx_c());    
            }
          else{   
             ps_aux->setProx_c(NULL);     
            }   
          
          free(ps_morta);             
          return;  
         }        
       
       ps_aux= ps_aux->getProx_c();
      }

    printf("\a\a\n *  Failed to killing prey %d! Prey was not found! \n\n",c);
       
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void matar_predador(int c){
    Predador *pd_aux, *pd_morto;       
    
    if(pd1==NULL){
       printf("\a\a\n *  Failed to killing predator %d! Pointer \"pd1\" is null! \n\n",c);
       return;           
      }
       
    if(pd1->getCodigo() == c){   
       pd_morto=pd1;
             
       if(pd1->getProx_c() != NULL){ 
          pd1 = pd1->getProx_c();
         }
       else{  
          pd1=NULL; 
         }
          
       free(pd_morto);
       return;
      }

    pd_aux=pd1;
      
    while(pd_aux->getProx_c() != NULL){  
       if(pd_aux->getProx_c()->getCodigo() == c){  
          pd_morto=pd_aux->getProx_c();
          if(pd_aux->getProx_c()->getProx_c() != NULL){   
             pd_aux->setProx_c(pd_aux->getProx_c()->getProx_c());  
            }
          else{  
             pd_aux->setProx_c(NULL);       
            }   
          
          free(pd_morto);            
          return;  
         }        
       
       pd_aux= pd_aux->getProx_c();
      }

    printf("\a\a\n *  Failed to killing predator %d! Predator was not found! \n\n",c);
       
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool atacar(Predador *pd, Presa *ps,int cmp_visao, int nvl_pers){
    float dist = calcula_distancia(pd->getPosicao(),ps->getPosicao());
    corRGB difCores;
    int nivel_camuflagem = diferenca_cor(ps->getCor(),cp.getCor(), &difCores);
                    
    if((difCores.r > nvl_pers || difCores.g > nvl_pers || difCores.b > nvl_pers) && dist < cmp_visao){
       return true;                  
      }    
    else{
       return false;
      }

}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool fugir(Predador *pd, Presa *ps,int cmp_visao, int nvl_pers){
    float dist = calcula_distancia(pd->getPosicao(),ps->getPosicao());
    corRGB difCores;
    int nivel_camuflagem = diferenca_cor(pd->getCor(),cp.getCor(), &difCores);
                    
    if((difCores.r > nvl_pers || difCores.g > nvl_pers || difCores.b > nvl_pers) && dist < cmp_visao){
       return true;                  
      }    
    else{
       return false;
      }

}



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void *movimentar_presa(void *p){
     

    //  printf("\t\tps   tread started  ");
    Presa *ps= (Presa*)p;
    Presa *ps_aux;
    Predador *pd_aux;
    Planta *pl_aux;
    Lago *lg_aux;
    
   // printf("->%d  \n",ps->getCodigo()); ps->setFome(100); //******************************************************************************************************************************************************************************************

    posXY nova_posicao;
    posXY posicao_atual;
    int i;
    int fdm=le_info("fator_delay_max_presa");
    int nvl_pers = le_info("nivel_perseguicao");
    int area_int = le_info("area_interesse_presa");
    int vai = le_info("var_area_interesse_presa");/**/
    int visao_max = le_info("campo_max_visao_presa");
    int tmpl = le_info("tempo_morte_planta");
    int tgps = le_info("tempo_gest_presa");
    int trps = le_info("tempo_resg_presa");
    
    int tmp_fome;
    int tmp_sac_fome;
    int tmp_sede;
    int tmp_sac_sede;
    int tmp_rep;
    
    
    if(mod_fome_presa){
        tmp_fome = le_info ("tempo_fome"); /**/
        tmp_sac_fome = le_info ("tempo_saciedade_fome");/**/
	}
	else{
	    tmp_fome = -1; /**/
        tmp_sac_fome = 0;/**/	
        ps->setFome(-1);
	}
    if(mod_sede){
	    tmp_sede = le_info ("tempo_sede"); /**/
        tmp_sac_sede = le_info ("tempo_saciedade_sede");/**/
    }
    else{
	    tmp_sede = -1; /**/
        tmp_sac_sede = 0;/**/
        ps->setSede(-1);
    }

    //ps->setIdade_max(50,0);
    

    int ida_cat2;
    int ida_cat3;
    int ida_cat4;
    
    int segundo=clock(); 
    dimXY dim_campo;
    Presa *parceiro;
    parceiro=NULL;
    
    dim_campo.x= le_info("qt_col_campo");
    dim_campo.y= le_info("qt_lin_campo");
    
    if(ps->getSexo()){
//       ida_cat2= le_info("idade_media_presa_f")*0.10;
//       ida_cat3= le_info("idade_media_presa_f")*0.50;
//       ida_cat4= le_info("idade_media_presa_f")*0.90;
       ida_cat2= ps->getIdade_max()*0.10;
       ida_cat3= ps->getIdade_max()*0.50;
       ida_cat4= ps->getIdade_max()*0.90;

      }
    else{
       ida_cat2= ps->getIdade_max()*0.10;
       ida_cat3= ps->getIdade_max()*0.50;
       ida_cat4= ps->getIdade_max()*0.90;
      }  
      
    nova_posicao.x = ps->getPosicao().x;
	nova_posicao.y = ps->getPosicao().y;
	pd_aux = (Predador*) malloc(sizeof(Predador));
	pd_aux->setPosicao(nova_posicao);
	
	ps->setCamuflado(!atacar(pd_aux,ps,ps->getSentidos(),nvl_pers));  
      
    
    do{
       nova_posicao = sorteia_posicao(ps->getPosicao(), ps->getArea_interesse(),vai);   
	   //printf("1");                  
	   ps->setArea_interesse(ps->getArea_interesse()-1);  
	   if(ps->getArea_interesse()<0)
	     break;
      }while(nova_posicao.x <= 0+ps->getTamanho() || nova_posicao.x >= dim_campo.x-ps->getTamanho() || nova_posicao.y <= 0+ps->getTamanho() || nova_posicao.y >= dim_campo.y-ps->getTamanho()); 
    ps->setArea_interesse(area_int);
       // printf("\t\tps %d   inicio movimento\n",ps->getCodigo());
    
    /*
    ps_aux = ps1;
    while(ps_aux != NULL){
       printf("ps %d viva!\n",ps_aux->getCodigo());
       ps_aux = ps_aux->getProx_c();  
      }
    */
    
//	printf("Psa%d sede%d sac%d\n",ps->getCodigo(),ps->getSede(),tmp_sac_sede);   
 
    int nha=0;/**/
    
    
    
    
    
    
    
    while(ps->getIdade() < ps->getIdade_max()){  
		
		
		
	
		
		
		
   		   
        pthread_mutex_lock(&p_key);   
        
       // printf("ps->getFome() <= tmp_fome +++ %d %d\n",ps->getFome(),tmp_fome);
        
  	        //Verifica se o agente presa está com fome
  	        if(mod_fome_presa){
			 if(ps->getFome() <= tmp_fome){                       
                if(ps->getCod_alvo_fome() != -1){  
                    
                    if(getPlanta(ps->getCod_alvo_fome())->getEstado()){  //se a planta estiver viva
                      pl_aux = pl1;
                      while(pl_aux != NULL){ //planta mais proxima
                         
                         if(calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()) < calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo_fome())->getPosicao())){     
                              int aux=0;
                              
                              lg_aux = lg1;
		                      while(lg_aux != NULL){
		                         
		                        // printf("calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()) < calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()) +++ %d < %d\n",calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()), calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()));
		                                   
		                         if(calcula_distancia(pl_aux->getPosicao(),lg_aux->getPosicao()) <  lg_aux->getTamanho()*lg_aux->getTamanho_atual()/100){     
		                            aux=1;
                                    break;
		                           }
		                         lg_aux= lg_aux->getProx_l();   
								 //printf("4");        
		                        }
							  if(aux==0){
	                              ps->setCod_alvo_fome(pl_aux->getCodigo());   	
							  }	   

                           }
                         pl_aux= pl_aux->getProx_p(); 
						 //printf("2");          
                        }   
                    
                    }     
                    else{
						if(pl1!=NULL){  
                           ps->setCod_alvo_fome(pl1->getCodigo());
                        } 
                    }
               ///////////////////////////////////////////////////////////////
                    if(getPlanta(ps->getCod_alvo_fome()) != NULL){
	                    if(getPlanta(ps->getCod_alvo_fome())->getEstado()){  // a pranta ainda existe?
	                        if(calcula_distancia(ps->getPosicao(),getPlanta(ps->getCod_alvo_fome())->getPosicao()) < ps->getSentidos()){   //a planta esta no raio de visao da presa     
	                           nova_posicao=getPlanta(ps->getCod_alvo_fome())->getPosicao();
	                        }
					    }
	                    else{
							if(pl1!=NULL){  
		                      ps->setCod_alvo_fome(pl1->getCodigo());
		                     } 
	                    }
					} 
					else{
						if(pl1!=NULL){  
	                      ps->setCod_alvo_fome(pl1->getCodigo());
	                     } 
	                }
                    //printf("presa indo em direcao a pranta..\n");   
                  }
                else{   
                   if(pl1!=NULL){  
                      ps->setCod_alvo_fome(pl1->getCodigo());
                     }  
                  }              
               }
	        }
       
       
                     //sede coisas
           if(mod_sede){
  	         if(ps->getSede() <= tmp_sede){       
                         
             //    printf("ps->getCod_alvo() != -1\n",ps->getCod_alvo_sede());                  
                if(ps->getCod_alvo_sede() != -1){ 
					
					if(getLago(ps->getCod_alvo_sede())->getTamanho() * getLago(ps->getCod_alvo_sede())->getTamanho_atual() / 100 > 0){     //se o rio tiver agua...                    if(getPlanta(ps->getCod_alvo_fome())->getEstado()){  //se a planta estiver viva
   
                    //  printf("tem auga nu lags\n");
                      lg_aux = lg1;
                      while(lg_aux != NULL){
                         
                        // printf("calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()) < calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()) +++ %d < %d\n",calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()), calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()));
                                   
                         if(calcula_distancia(ps->getPosicao(),lg_aux->getPosicao()) < calcula_distancia(ps->getPosicao(), getLago(ps->getCod_alvo_sede())->getPosicao())){     
                            ps->setCod_alvo_sede(lg_aux->getCodigo());   
                           }
                         lg_aux= lg_aux->getProx_l();   
						 //printf("4");        
                        }   
                    
                    }     
                    else{   
	                   ps->setCod_alvo_sede(-1); 
	                }  
               
              // printf("getPlanta(ps->getCod_alvo())->getEstado() +++ %d\n",getPlanta(ps->getCod_alvo())->getEstado()?1:0);
               
                    if(getLago(ps->getCod_alvo_sede())->getTamanho() * getLago(ps->getCod_alvo_sede())->getTamanho_atual() / 100 > 0){  // o lago ainda tem agua?
                 //     if(getPresa(pd->getCod_alvo())->getIdade() < getPresa(pd->getCod_alvo())->getIdade_max()){
                ///        printf("calcula_distancia(ps->getPosicao(),getPlanta(ps->getCod_alvo())->getPosicao()) < ps->getSentidos() +++ %d < %d\n",calcula_distancia(ps->getPosicao(),getPlanta(ps->getCod_alvo())->getPosicao()), ps->getSentidos());
                         if(calcula_distancia(ps->getPosicao(),getLago(ps->getCod_alvo_sede())->getPosicao()) < ps->getSentidos()+getLago(ps->getCod_alvo_sede())->getTamanho() * getLago(ps->getCod_alvo_sede())->getTamanho_atual() / 100){      
                         //   if(atacar(pd,getPresa(pd->getCod_alvo()),pd->getSentidos(),nvl_pers)){
 //if(ps != ps1)   
   ///                           printf("a pranta está dentro do campo de visao...");   
                               nova_posicao=getLago(ps->getCod_alvo_sede())->getPosicao();
                        //      } 
                           }
                   //     }                   
                     }
                    else{   
	                   ps->setCod_alvo_sede(-1);
					     
	                }   
                    //printf("presa indo em direcao a pranta..\n");   
                  }
                else{   
                   if(lg1!=NULL){  
                      ps->setCod_alvo_sede(lg1->getCodigo());
                     }  
                  }              
               }
			}
  	 
  	 
  	 
  	 
  	 /**/
                //define a ameaca como o predador mais proximo
            if(!ps->getCamuflado() && mod_fuga_presa){
				pd_aux=pd1;
	            
	            if(pd_aux != NULL){
				    ps->setCod_ameaca(pd_aux->getCodigo());
				}
				else{
					ps->setCod_ameaca(-1);
				}
		        
		        if(ps->getCod_ameaca() != -1){      // se a presa tiver uma ameaça...
		        
		            while(pd_aux!=NULL){  //verifica qual predador é o mais proximo e o define como ameaça
		                if(calcula_distancia(pd_aux->getPosicao(),ps->getPosicao()) < calcula_distancia(getPredador(ps->getCod_ameaca())->getPosicao(),ps->getPosicao())){
							if(mod_predador_camuflagem){
						 	    if(fugir(pd_aux,ps,ps->getSentidos(),nvl_pers)){
					                ps->setCod_ameaca(pd_aux->getCodigo());
								}
							}
							else{
								ps->setCod_ameaca(pd_aux->getCodigo());
							}
							
				        }
						pd_aux=pd_aux->getProx_c(); 
		                 
		            }
		            if(calcula_distancia(getPredador(ps->getCod_ameaca())->getPosicao(), ps->getPosicao()) < ps->getSentidos()){  // se o predador ameaça estiver dentro do campo de visao da presa...
						posXY pos_aux;
						    //define a proxima posicao para ser o inverso da posicao do predador
						if(ps->getPosicao().x > getPredador(ps->getCod_ameaca())->getPosicao().x){
							pos_aux.x = ps->getPosicao().x + ps->getArea_interesse();
						}
						else{
							pos_aux.x = ps->getPosicao().x - ps->getArea_interesse();
						}
						if(ps->getPosicao().y > getPredador(ps->getCod_ameaca())->getPosicao().y){
							pos_aux.y = ps->getPosicao().y + ps->getArea_interesse();
						}
						else{
							pos_aux.y = ps->getPosicao().y - ps->getArea_interesse();
					    }
					        
						   if(pos_aux.x<=0+ps->getTamanho())
				              pos_aux.x=1+ps->getTamanho();                 
				           if(pos_aux.x>=dim_campo.x-ps->getTamanho())   //limite
				              pos_aux.x=dim_campo.x-1-ps->getTamanho();
				           if(pos_aux.y<=0+ps->getTamanho())
				              pos_aux.y=1+ps->getTamanho();                 
				           if(pos_aux.y>=dim_campo.y-ps->getTamanho())   //limite
				              pos_aux.y=dim_campo.y-1-ps->getTamanho();
				                
				        
					    //verificar se a posicao está dentro de um dos lagos
						
						nova_posicao=pos_aux;
					}
	            
	            }
		    }
       /**/
       
       
       
       
       
       
       
       
      // ps->setCod_alvo(pl1->getCodigo());
       
       /*
  	          //imported dos pred
  	       if((ps->getCod_alvo() != -1 && (nova_posicao.x != getPlanta(ps->getCod_alvo())->getPosicao().x  && nova_posicao.y != getPlanta(ps->getCod_alvo())->getPosicao().y)) || (ps->getCod_alvo() == -1)){    // se apresa tem alvo mas nao está marcada como destino..     ou se nao tem alvo..
                
               if(ps->getGestacao() == 0 && ps->getResguardo() == 0 && ps->getFertil()){   //está fertil
                  if(ps->getCod_parceiro()!= -1){    // tem parceiro
 if(ps != ps1)                                               printf("ifi\n");    
                     ps_aux=ps1;  
                     while(ps_aux != NULL){ 
                        
                        if(ps_aux->getSexo() != ps->getSexo()){  
                           if(ps_aux->getGestacao() == 0 && ps_aux->getResguardo() == 0 && ps_aux->getFertil()){  
                              if(calcula_distancia(ps->getPosicao(),ps_aux->getPosicao()) < calcula_distancia(getPresa(ps->getCod_parceiro())->getPosicao(), ps->getPosicao())){ 
                                 ps->setCod_parceiro(ps_aux->getCodigo());    
                                }
                             }
                          }    
                        ps_aux= ps_aux->getProx_c();              
                       }
                         
                     if(calcula_distancia(ps->getPosicao(),getPresa(ps->getCod_parceiro())->getPosicao()) < ps->getSentidos()){
                        if(getPresa(ps->getCod_parceiro())->getResguardo()== 0){
                           if(getPresa(ps->getCod_parceiro())->getGestacao() == 0){   
                              if(getPresa(ps->getCod_parceiro())->getFertil()) {      
                                 nova_posicao=getPresa(ps->getCod_parceiro())->getPosicao();
                                }
                             }
                          }
                       } 
               
                     }
                  else{  
 // if(ps != ps1)                          printf("eusia presa %d nao tem parceiro sexualitos\n",ps->getCodigo());
                     ps_aux=ps1;  
                     while(ps_aux!=NULL){
                     
                         
                                           
                        if(ps->getSexo() != ps_aux->getSexo()){
                           if(ps_aux->getGestacao()==0 && ps_aux->getResguardo()==0 && ps_aux->getFertil()){  
                              ps->setCod_parceiro(ps_aux->getCodigo());
                              break;
                             }
                          }
                        ps_aux=ps_aux->getProx_c();                    
                       }
                    }  
                            
                 }
                 
              }
  	       
    */        
     //->   pthread_mutex_unlock(&p_key);  




     //->   pthread_mutex_lock(&p_key);   
  	       
  	               //Verifica se a presa está fertil e apta para procriar..
           if(ps->getGestacao() == 0 && ps->getResguardo() == 0 && ps->getFertil()){  
              if(ps->getCod_parceiro()!= -1){         
                 ps_aux=ps1;
                 while(ps_aux != NULL){        //define o código da presa fertil de sexo oposto mais proxima como possivel parceiro            
                    if(ps_aux->getSexo() != ps->getSexo()){     
                       if(ps_aux->getGestacao() == 0 && ps_aux->getResguardo()==0 && ps_aux->getFertil()){   
                          if(calcula_distancia(ps->getPosicao(),ps_aux->getPosicao()) < calcula_distancia(getPresa(ps->getCod_parceiro())->getPosicao(), ps->getPosicao())){
                             ps->setCod_parceiro(ps_aux->getCodigo());
                            }
                         }
                      } 
                    ps_aux= ps_aux->getProx_c();  
					//printf("&");            
                   } 
                 
       //          if(ps->getCod_ameaca() != -1){   //Se estiver sendo ameaçada, 
		//			 if(!calcula_distancia(getPredador(ps->getCod_ameaca())->getPosicao(), ps->getPosicao()) < ps->getSentidos()){  // mas se o predador ameaça nao estiver dentro do campo de visao da presa...      
		                 if(calcula_distancia(ps->getPosicao(),getPresa(ps->getCod_parceiro())->getPosicao()) < ps->getVisao_reproducao()){   //verifica se o parceiro está no campo de visão
		                    if(getPresa(ps->getCod_parceiro())->getResguardo()== 0){
		                       if(getPresa(ps->getCod_parceiro())->getGestacao() == 0){            
		                          if(getPresa(ps->getCod_parceiro())->getFertil()){                                                         
		                             nova_posicao=getPresa(ps->getCod_parceiro())->getPosicao();
		                            }
		                         }
		                      }
		                   } 
					 //  }
				  // }

                }            
              else{   // Nao tem nenhum parceiro
                 ps_aux=ps1;
                 while(ps_aux!=NULL){    //atribui um código de parceiro...
                    if(ps->getSexo() != ps_aux->getSexo()){  
                       if(ps_aux->getGestacao()==0 && ps_aux->getResguardo()==0 && ps_aux->getFertil()){
                          ps->setCod_parceiro(ps_aux->getCodigo());
                          break;
                         }
                      } 
                    ps_aux=ps_aux->getProx_c();       
					//printf("3");            
                   }    
                } 
                         
             } 




            
        pthread_mutex_unlock(&p_key);  









//printf("ate aqui ok o alvo eh %d \n",ps->getCod_alvo());


        posicao_atual = ps->getPosicao();
        
  
//if(ps != ps1)           
  //      printf("my pos %d %d  pozalv %d %d", ps->getPosicao().x,ps->getPosicao().y, nova_posicao.x, nova_posicao.y);
        
//        bar(nova_posicao.x,nova_posicao.y,nova_posicao.x+2,nova_posicao.y+2);

/*
           setlinestyle(0,0,1); 
           setcolor(COLOR(rand()%255,rand()%255,rand()%255)); 
           setfillstyle(1, COLOR(rand()%255,rand()%255,rand()%255));
           fillellipse(nova_posicao.x,nova_posicao.y,2,2);  
*/         
           //printf("nova_posicao; %d %d\n",nova_posicao.x,nova_posicao.y);


        
        
        if((ps->getPosicao().x == nova_posicao.x) && (ps->getPosicao().y == nova_posicao.y)){   //atingiu o alvo
           int aux;
           do{
			  aux=0;	
              nova_posicao = sorteia_posicao(ps->getPosicao(), ps->getArea_interesse(),vai); 
              
              lg_aux = lg1;
              while(lg_aux != NULL){
                 
                // printf("calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()) < calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()) +++ %d < %d\n",calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()), calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()));
                           
                 if(calcula_distancia(nova_posicao,lg_aux->getPosicao()) < lg_aux->getTamanho()*lg_aux->getTamanho_atual()/100){ 
					aux=1;
					//printf("%");
					break;	    
                   }
                 lg_aux= lg_aux->getProx_l();      
				 //printf("$");    
                }  
               //printf(")");
                  
               ps->setArea_interesse(ps->getArea_interesse()-1);  
               if(ps->getArea_interesse()<0)
	              break;
			 
			 }while(nova_posicao.x <= 0+ps->getTamanho() || nova_posicao.x >= dim_campo.x-ps->getTamanho() || nova_posicao.y <= 0+ps->getTamanho() || nova_posicao.y >= dim_campo.y-ps->getTamanho() || aux==1);    
 // if(ps != ps1)            printf("new pozalv=> %d %d",nova_posicao.x,nova_posicao.y);
              if(ps->getArea_interesse()<0)
                  nova_posicao = ps->getPosicao();
              ps->setArea_interesse(area_int);

               
          }
        else{         
         //  ps->mover(ps->aproximar(nova_posicao), dim_campo);
            
			
			/* */
			
			
			pthread_mutex_lock(&p_key);  
            if(ps->getCod_ameaca() != -1 && getPredador(ps->getCod_ameaca())!=NULL){
		   
			   if(calcula_distancia(getPredador(ps->getCod_ameaca())->getPosicao(), ps->getPosicao()) < ps->getSentidos()){    // se o predador ameaca estiver no campo de visao, fugir
			       ps->mover(ps->afastar(nova_posicao), dim_campo); 
			       //printf("afastantooo...\n");
					
			   }  
	           else 
			   if(mod_fome_presa){
				  if(ps->getFome() < tmp_fome + tmp_sac_fome-2){
					  if(mod_sede){
						  if(ps->getSede() < tmp_sede + tmp_sac_sede-2){
							 ps->mover(ps->aproximar(nova_posicao), dim_campo);	
						  }	
					  }	
					  else{
						  ps->mover(ps->aproximar(nova_posicao), dim_campo);	
					  }
				  }	
			   }
			   else
			   if(mod_sede){
				  if(ps->getSede() < tmp_sede + tmp_sac_sede-2){
					 ps->mover(ps->aproximar(nova_posicao), dim_campo);	
				  }	
			   }
			   else
    			   ps->mover(ps->aproximar(nova_posicao), dim_campo);	
			   
		    }
		    else 
		    if(mod_fome_presa){
			  if(ps->getFome() < tmp_fome + tmp_sac_fome-2){
				  if(mod_sede){
					  if(ps->getSede() < tmp_sede + tmp_sac_sede-2){
						 ps->mover(ps->aproximar(nova_posicao), dim_campo);	
					  }	
				  }
				  else{
				     ps->mover(ps->aproximar(nova_posicao), dim_campo);			
				  }	
			  }	
		   }
		   else
		   if(mod_sede){
			  if(ps->getSede() < tmp_sede + tmp_sac_sede-2){
				 ps->mover(ps->aproximar(nova_posicao), dim_campo);	
			  }	
		   }
		   else
    		   ps->mover(ps->aproximar(nova_posicao), dim_campo);	
		   
		    
		    pthread_mutex_unlock(&p_key);  
		    
		    
		    
		    /**/
		    
		    
		    
		    
		    
        }
        
//if(ps != ps1)           printf("psfome %d   tmpfome %d + tmpsac %d = %d\n", ps->getFome(),tmp_fome,tmp_sac,tmp_fome+tmp_sac);  
          

        
//if(ps != ps1)           printf("*  %d  da ps %d*\n",ps->getFome(),ps->getCodigo());   
           
        pthread_mutex_lock(&p_key);    
        
        //ps->setCod_alvo(1);   //*****saporra aqui
        
//        if(pl1 == NULL)
//            printf("pl1 dus caraio tah nulo porreeesssa?\n\a");
//        else
//            printf("pl1? %d \n",pl1->getCodigo());
                 
        if(ps->getCod_alvo_fome() != -1){
                 /*       - Probably the bad guy            */
           if(ps->getFome() <= tmp_fome){ // se a presa estiver com fome
            //  printf("to ake  ps cod alvo1 =>%d \n", ps->getCod_alvo());
              
              
              if(getPlanta(ps->getCod_alvo_fome())->getEstado()){   // se a planta estiver viva...
              // printf("to ake  ps cod alvo2 =>%d \n", ps->getCod_alvo());
              
                 if((ps->getPosicao().x == getPlanta(ps->getCod_alvo_fome())->getPosicao().x) && (ps->getPosicao().y == getPlanta(ps->getCod_alvo_fome())->getPosicao().y)){     // se a presa esta na mesma posica que a planta
                    if(getPlanta(ps->getCod_alvo_fome())->getTamanho() == 1){  // se aplanta tiver tamanho 1
                       if(ps->getFome() < (tmp_sac_fome + tmp_fome)/2)
                          ps->setFome(ps->getFome()+((tmp_sac_fome + tmp_fome)/2));
                       else
                          ps->setFome(tmp_sac_fome + tmp_fome);   
                      }
                    else   // se a planta tiver tamnho 2
                       ps->setFome(tmp_sac_fome + tmp_fome);
                    
                      //matando
                    getPlanta(ps->getCod_alvo_fome())->setEstado(false);
                    getPlanta(ps->getCod_alvo_fome())->setMorte(tmpl);
                    ps->setCod_alvo_fome(-1);          
                   }
                }
                else{
					ps->setCod_alvo_fome(-1);
                }
     
              
            }   
                 
         } 
         
		
		if(ps->getCod_alvo_sede() != -1){ 
            
           if(ps->getSede() <= tmp_sede){ // se a presa estiver com sede              
              
              if(getLago(ps->getCod_alvo_sede())->getTamanho() * getLago(ps->getCod_alvo_sede())->getTamanho_atual() / 100 > 0){   // se o lago tiver agua
                 //printf("to ake  ps cod alvo sede =>%d \n", ps->getCod_alvo_sede());
              	 if(calcula_distancia(ps->getPosicao(),getLago(ps->getCod_alvo_sede())->getPosicao()) <= getLago(ps->getCod_alvo_sede())->getTamanho() * getLago(ps->getCod_alvo_sede())->getTamanho_atual() / 100){    //se a distancia entre a presa e o lago que ela esta com sede  for menor que o tamanho do raio do lago...  
                    
					do{
					   nova_posicao = sorteia_posicao(ps->getPosicao(),ps->getArea_interesse(),vai);//ps->getPosicao();        
					   //printf("5");
					   ps->setArea_interesse(ps->getArea_interesse()-1);
					   if(ps->getArea_interesse()<0)
	                       break;
					  }while(calcula_distancia(nova_posicao,getLago(ps->getCod_alvo_sede())->getPosicao()) < (getLago(ps->getCod_alvo_sede())->getTamanho()*getLago(ps->getCod_alvo_sede())->getTamanho_atual()/100)+ (ps->getTamanho()));  // se a distancia entre a nova posicao que a presa deve ir e o lago que ela esta com sede for menor que o tamanho do raio do lago + a area de interesse / 2
				    if(ps->getArea_interesse()<0)
                       nova_posicao = ps->getPosicao();
					ps->setArea_interesse(area_int);
				    ps->setSede(tmp_sac_sede + tmp_sede);
                    ps->setCod_alvo_sede(-1);  
				   
				   }
                }
                else{
					ps->setCod_alvo_sede(-1);
                }
     
              
            }   
                 
         }   
         
         

         
         
		 
		    
                 
                 // reproduction
           if(ps->getSexo()==1 && ps->getCod_parceiro()!= -1){             
               if(getPresa(ps->getCod_parceiro()) != NULL){
                  if((ps->getPosicao().x == getPresa(ps->getCod_parceiro())->getPosicao().x) && (ps->getPosicao().y == getPresa(ps->getCod_parceiro())->getPosicao().y)){   
                     if((ps->getGestacao() == 0) && (getPresa(ps->getCod_parceiro())->getGestacao() == 0)){   
                        if((ps->getResguardo() == 0) && (getPresa(ps->getCod_parceiro())->getResguardo() == 0)){  
                           if(ps->getFertil() && getPresa(ps->getCod_parceiro())->getFertil()){     
                              ps->setGestacao(tgps); 
                              parceiro=getPresa(ps->getCod_parceiro());
                 //  printf("ifi cabuloso");
                              ps_aux=ps1;
                              while(ps_aux!=NULL){
                                 if(ps_aux->getCod_parceiro() == ps->getCodigo()){
                                    ps_aux->setCod_parceiro(-1);
                                   }     
                                 ps_aux=ps_aux->getProx_c();                   
                                //printf("8");
								}
                             }     
                          }
                       }
                    } 
                 } 
             } 
             
           
//if(ps != ps1)              printf("Here we are %d\n",ps->getCodigo());  
             
             
           if(ps->getCod_parceiro()!=-1){   
              if(!getPresa(ps->getCod_parceiro())->getFertil()){   
                 ps->setCod_parceiro(-1);                                   
                }
             }
           
		   
		   
		   if(ps->getCor().r>255 ||ps->getCor().g>255 ||ps->getCor().b>255  ||  ps->getCor().r<0 ||ps->getCor().g<0 ||ps->getCor().b<0){
				printf("presa %d cor bugada %d %d %d \n",ps->getCodigo(),ps->getCor().r,ps->getCor().g,ps->getCor().b);
				pausa=true;
		   }
           if(ps->getVelocidade()<0 || ps->getVelocidade()>9){
				printf("presa %d velocidade bugada %d\n",ps->getCodigo(),ps->getVelocidade());
		       pausa=true;
		   }
           if(ps->getSentidos()<visao_max*0.5 || ps->getSentidos()>visao_max){
				printf("presa %d visao bugada %d\n",ps->getCodigo(),ps->getSentidos());
		        pausa=true;
		   }       
		   
		   
		       
               	    
           setlinestyle(0,0,2); 
           setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b)); 
           if(ps->getCor().r>255 ||ps->getCor().g>255 ||ps->getCor().b>255 || ps->getCor().r<0 ||ps->getCor().g<0 ||ps->getCor().b<0){
			  setfillstyle(1, COLOR(255,255,255));
		   }
		   else{
				setfillstyle(1, COLOR(ps->getCor().r,ps->getCor().g,ps->getCor().b));
		    }
           //setfillstyle(1, COLOR(ps->getCor().r,ps->getCor().g,ps->getCor().b));
           fillellipse(posicao_atual.x,posicao_atual.y,ps->getTamanho(),ps->getTamanho());    

           setlinestyle(0,0,1);  
           if(ps->getCor().r>255 ||ps->getCor().g>255 ||ps->getCor().b>255 || ps->getCor().r<0 ||ps->getCor().g<0 ||ps->getCor().b<0){
				 setfillstyle(1, COLOR(255,255,255));
			}
		   else{
				setfillstyle(1, COLOR(ps->getCor().r,ps->getCor().g,ps->getCor().b));
		    }
		   //setfillstyle(1, COLOR(ps->getCor().r,ps->getCor().g,ps->getCor().b));
           if(borda){
			   if(ps->getSexo())
	              setcolor(COLOR(255,0,0)); 
	           else
		          setcolor(COLOR(50,80,250)); 
	          fillellipse(ps->getPosicao().x,ps->getPosicao().y,ps->getTamanho(),ps->getTamanho()); 
		   }
		   else{
			   setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));	
    		   fillellipse(ps->getPosicao().x,ps->getPosicao().y,ps->getTamanho()+1,ps->getTamanho()+1);  

		   }
  
        pthread_mutex_unlock(&p_key);   

  //if(ps != ps1)         printf("readdy to wait %d..  \n",ps->getCodigo());
            
        if(ps->getVelocidade()>=0 && ps->getVelocidade()<10)
           delay(fdm - (ps->getVelocidade()*(10*fdm/100)));
        
        // printf("\tChegou aquiiiiii %d \n",ps->getCodigo());  
               
        while(pausa){
           delay(100);        
          }        
        
//        if(nha==1){
//			printf(".%d.",ps->getVelocidade());
  //      }
        
        if(abs(tempo-segundo) > 750){ 
           
		   segundo = tempo;
           ps->idade_pp(); 

           if(mod_fome_presa){
	           if(ps->getFome() > 0){
	              ps->fome_mm();
	             }
	           else{
	              break;  // morre de fome
	             }
		   }
		   if(mod_sede){
	           if(ps->getSede() > 0){
	              ps->sede_mm();
	             }
	           else{
	              break;  // morre de sede
	             }
		   }

           if(ps->getSexo()){
               if(ps->getResguardo() > 0){         
                  ps->resguardo_mm();
                 }
               if(ps->getGestacao() > 0){
                  ps->gestacao_mm();
                  if(ps->getGestacao() == 0){
                     pthread_mutex_lock(&p_key); 
                     
                        /*Presa *p,pai_aux;    
    posXY pos,pos_aux;    
    corRGB cor_aux;
    int visao_max = le_info("campo_max_visao_predador");

    cor_aux.r = -1;
	cor_aux.g = -1;
	cor_aux.b = -1;
    pos_aux.x = -1;
	pos_aux.y = -1;
    
    pai_aux.setCor(cor_aux);
    pai_aux.setPosicao(pos_aux);
    pai_aux.setVelocidade(-1);
    pai_aux.setCategoria(2);
    pai_aux.setSentidos(-1);
    */
                        if(getPresa(parceiro->getCodigo()) == NULL){   //maes que sao maes e pais   kkkkk   
						   //printf("Pai nulo cod ");
						   //printf("%d\n",parceiro->getCodigo());
						    parceiro = ps;
//                        pausa=true;
						}
                   /*
				        if(getPresa(ps->getCodigo()) == NULL){
							printf("Mainha nulo cod %d",parceiro->getCodigo());
                        getch();
						}
                     */   
                        ps_aux=ps1;
                        while(ps_aux->getProx_c()!=NULL){
                           ps_aux= ps_aux->getProx_c();                      
                          }   
                        ps_aux->setProx_c(criar_presa(ps_aux->getCodigo()+1,rand()%2,*ps,*parceiro));            
                        ps_aux->getProx_c()->setCod_mae(ps->getCodigo());
                        if(mod_fome_presa)
                           ps_aux->getProx_c()->setFome(tmp_fome+tmp_sac_fome-3);
                        if(mod_sede)
						   ps_aux->getProx_c()->setSede(tmp_sede+tmp_sac_sede-3);
                        
                        
                        ps_ = ps_aux->getProx_c()->getMove_td();
                        pthread_create(&ps_, NULL, movimentar_presa, ps_aux->getProx_c());   
                        ps->setResguardo(trps);
                        
                        
                        if(ps_aux->getProx_c()->getCor().r>255 ||ps_aux->getProx_c()->getCor().g>255 ||ps_aux->getProx_c()->getCor().b>255  ||  
						   ps_aux->getProx_c()->getCor().r<0 ||ps_aux->getProx_c()->getCor().g<0 ||ps_aux->getProx_c()->getCor().b<0){
		                    printf("ps cod %d cor %d %d %d   mae %d cor %d %d %d    pai %d cor %d %d %d",ps_aux->getProx_c()->getCodigo(),ps_aux->getProx_c()->getCor().r,ps_aux->getProx_c()->getCor().g,ps_aux->getProx_c()->getCor().b,     ps->getCodigo(),ps->getCor().r,ps->getCor().g,ps->getCor().b,        parceiro->getCodigo(),parceiro->getCor().r,parceiro->getCor().g,parceiro->getCor().b);
	                        pausa=true;
						}
	                    
	                    
	                    
                            
                            
						if(ps_aux->getProx_c()->getVelocidade()<0 || ps_aux->getProx_c()->getVelocidade()>9){  //pais de categoria 1..  nao pode!!
							printf("persa %d velocidade %d mae cod %d vel %d     pai cod %d vel %d\n",ps_aux->getProx_c()->getCodigo(),ps_aux->getProx_c()->getVelocidade(),ps->getCodigo(),ps->getVelocidade(),parceiro->getCodigo(),parceiro->getVelocidade());
                            
                            
							pausa=true;
						}
                    
                     pthread_mutex_unlock(&p_key); 
                    }   
                 }
              }
           
           
              
                      
           if(ps->getIdade()>ida_cat4){
              if(ps->getCategoria() != 4){ 
                 ps->setCategoria(4);                      
                 if(ps->getSentidos()>visao_max*0.75)
                    ps->setSentidos(ps->getSentidos() - visao_max*0.25);   
          
                 //ps->setSentidos((int)le_info("campo_max_visao_presa")*0.6);   
                 //ps->setVelocidade(-1); 
                 if(ps->getVelocidade()>=5)
    				 ps->setVelocidade(ps->getVelocidade()-5); 
                 
				 ps->setCod_parceiro(-1);  
                }
             }
           else if(ps->getIdade()>ida_cat3){
              if(ps->getCategoria() != 3){ 
                 ps->setCategoria(3);   
             //    ps->setSentidos(le_info("campo_max_visao_presa"));   
                 if(ps->getSentidos()<=visao_max*0.75)
                    ps->setSentidos(ps->getSentidos() + visao_max*0.25);   
                 
                 //ps->setVelocidade(-1); 
                 //ps->setVelocidade(ps->getVelocidade()); 
                 if(ps->getVelocidade()<5)
    				 ps->setVelocidade(ps->getVelocidade()+5); 
			    }
             }
           else if(ps->getIdade()>ida_cat2){ 
              if(ps->getCategoria() != 2){ 
                 ps->setCategoria(2);
                 if(ps->getSentidos()<=visao_max*0.75)
                    ps->setSentidos(ps->getSentidos() + visao_max*0.25);   
                 //ps->setVelocidade(-1);
                 //ps->setVelocidade(ps->getVelocidade()); 
                 if(ps->getVelocidade()<5)
    				 ps->setVelocidade(ps->getVelocidade()+5); 
                }                  
             }
            
			
			
			
			/*
			pthread_mutex_lock(&p_key); 
			setfillstyle(1,COLOR(cp.getCor().r, cp.getCor().g, cp.getCor().b));
		    bar(0,0,le_info("qt_col_campo"),le_info("qt_lin_campo"));  
			pthread_mutex_unlock(&p_key); 
			 */
             
	           
			   //visao reproducao	
			if(ps->getIdade()>=ida_cat2 && ps->getIdade()<=ida_cat4){
	     		tmp_rep = ps->getIdade()-ida_cat2;  //0-100 (cat2+cat3) * 2
			    ps->setVisao_reproducao(ceil(ps->getVisao_reproducao_max()*sin(2*M_PI*(1.0/(2*(ida_cat4-ida_cat2)))*tmp_rep)));
			    //printf("visao rep rat%.2f  size%.1f  tmp rep=%d\n",sin(2*M_PI*(1.0/(2*(ida_cat4-ida_cat2)))*tmp_rep), ceil(visao_rep_max*sin(2*M_PI*(1.0/(2*(ida_cat4-ida_cat2)))*tmp_rep)), tmp_rep); 
		    
		        //printf("cvrps %d   %d\n", le_info("campo_max_visao_rep_presa"),le_info("campo_max_visao_rep_predador"));
		    /*
			setlinestyle(0,0,2);
            setcolor(COLOR(255,255,255));
    		circle(ps->getPosicao().x,ps->getPosicao().y,ps->getVisao_reproducao());
            */
			}
			       
              
          
          }   
      
      
     }   //while life
    
    delay(1500);

    for(i=ps->getTamanho();i>0;i--){
       delay(500);
       pthread_mutex_lock(&p_key); 
       
          if(i==1){
             setfillstyle(1, COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));   
            }
          else{  
             setfillstyle(1, COLOR(ps->getCor().r,ps->getCor().g,ps->getCor().b));
             setlinestyle(0,0,2); 
            }
          setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));  
          fillellipse(ps->getPosicao().x,ps->getPosicao().y,i,i);    
      
       pthread_mutex_unlock(&p_key); 
      }

    pthread_mutex_lock(&p_key); 
     
       if(ps->getSexo())
          cps_f--;
       else
          cps_m--; 
           
       ps_aux=ps1;
       while(ps_aux!=NULL){
          if(ps_aux->getCod_parceiro() == ps->getCodigo()){
             ps_aux->setCod_parceiro(-1);
            }     
          ps_aux=ps_aux->getProx_c();      
         }
       
       pd_aux=pd1;
       while(pd_aux!=NULL){
          if(pd_aux->getCod_alvo_fome() == ps->getCodigo()){
             pd_aux->setCod_alvo_fome(-1);
            }     
          pd_aux=pd_aux->getProx_c();   
         }
        
       matar_presa(ps->getCodigo()); 
           
    pthread_mutex_unlock(&p_key); 
    
	return 0;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void *movimentar_predador(void *p){   
    Predador *pd= (Predador*)p;
    Predador *pd_aux;
    Presa *ps_aux;
    Lago *lg_aux;
    
    posXY nova_posicao;
    posXY posicao_atual;
    int i;
    int fdm = le_info("fator_delay_max_predador");
    int nvl_pers = le_info("nivel_perseguicao");
    int area_int = le_info("area_interesse_predador");
    int vai = le_info("var_area_interesse_predador");
    int visao_max = le_info("campo_max_visao_predador");
    //int visao_rep_max = le_info("campo_max_visao_rep_predador");
    int tgpd = le_info("tempo_gest_predador");
    int trpd = le_info("tempo_resg_predador");
    
    int tmp_fome;
    int tmp_sac_fome;
    int tmp_sede;
    int tmp_sac_sede;
    int tmp_rep;
    
    int ida_cat2;
    int ida_cat3;
    int ida_cat4;
    
    
    tmp_fome = le_info ("tempo_fome"); /**/
    tmp_sac_fome = le_info ("tempo_saciedade_fome");/**/

    if(mod_sede){
	    tmp_sede = le_info ("tempo_sede"); /**/
        tmp_sac_sede = le_info ("tempo_saciedade_sede");/**/
    }
    else{
	    tmp_sede = -1; /**/
        tmp_sac_sede = 0;/**/
        pd->setSede(-1);
    }

    
    int segundo=clock();
    dimXY dim_campo;
    Predador *parceiro;
    
    dim_campo.x= le_info("qt_col_campo");
    dim_campo.y= le_info("qt_lin_campo");
    
    if(pd->getSexo()){
       ida_cat2= pd->getIdade_max() * 0.18;
       ida_cat3= pd->getIdade_max() * 0.41;
       ida_cat4= pd->getIdade_max() * 0.65;
      }
    else{
       ida_cat2= pd->getIdade_max() * 0.18;
       ida_cat3= pd->getIdade_max() * 0.41;
       ida_cat4= pd->getIdade_max() * 0.65;
      }
    
    
	nova_posicao.x = pd->getPosicao().x;
	nova_posicao.y = pd->getPosicao().y;
	ps_aux = (Presa*) malloc(sizeof(Presa));
	ps_aux->setPosicao(nova_posicao);
	
	pd->setCamuflado(!fugir(pd,ps_aux,pd->getSentidos(),nvl_pers));  
    
	
    
    do{
       nova_posicao= sorteia_posicao(pd->getPosicao(), pd->getArea_interesse(),vai);   
      pd->setArea_interesse(pd->getArea_interesse()-1);
      //printf("6");
      if(pd->getArea_interesse()<0)
	     break;
	  }while(nova_posicao.x <= 0+pd->getTamanho() || nova_posicao.x >= dim_campo.x-pd->getTamanho() || nova_posicao.y <= 0+pd->getTamanho() || nova_posicao.y >= dim_campo.y-pd->getTamanho()); 
       pd->setArea_interesse(area_int);
   
    while(pd->getIdade() < pd->getIdade_max()){    
        
       // if(pd->getCodigo()==pd_sel && pausa)
       //    printf("inicio do while principal\n");
          
         
        pthread_mutex_lock(&p_key);   
                
            if(pd->getFome() <= tmp_fome){               
                if(pd->getCod_alvo_fome() != -1){       
                   if(getPresa(pd->getCod_alvo_fome())!= NULL){
                      ps_aux = ps1;
                      while(ps_aux != NULL){
                         if(calcula_distancia(pd->getPosicao(),ps_aux->getPosicao()) < calcula_distancia(pd->getPosicao(), getPresa(pd->getCod_alvo_fome())->getPosicao())){     

                            //if(pd->getCodigo()==pd_sel && pausa)
                              // printf("inicio do while Procurando alvo_fome mais proximo\n");

                            pd->setCod_alvo_fome(ps_aux->getCodigo());   
                           }
                         ps_aux= ps_aux->getProx_c();           
                        }   
                     // printf("7");
                    }     
               
                   if(getPresa(pd->getCod_alvo_fome())!= NULL){
                      if(getPresa(pd->getCod_alvo_fome())->getIdade() < getPresa(pd->getCod_alvo_fome())->getIdade_max()){
                         if(calcula_distancia(pd->getPosicao(),getPresa(pd->getCod_alvo_fome())->getPosicao()) < pd->getSentidos()){      
                            if(atacar(pd,getPresa(pd->getCod_alvo_fome()),pd->getSentidos(),nvl_pers)){   
                               nova_posicao=getPresa(pd->getCod_alvo_fome())->getPosicao();
                              } 
                           }
                        }                   
                     }
                  }
                else{   
                   if(ps1!=NULL){  
                      pd->setCod_alvo_fome(ps1->getCodigo());
                     }
                  }              
               }
               
           
           
           
		             //sede coisas  -- imported das presas
		   if(mod_sede){
	  	       if(pd->getSede() <= tmp_sede){       
	                         
	             //    printf("ps->getCod_alvo() != -1\n",ps->getCod_alvo_sede());                  
	                if(pd->getCod_alvo_sede() != -1){ 
	
	               //     printf("presa %d tem alvo! %d  hehe\n",ps->getCodigo(),ps->getCod_alvo());                       
	                    
	                    
	                   // printf("getPlanta(ps->getCod_alvo())->getEstado() +++ %d\n",getPlanta(ps->getCod_alvo())->getEstado()?1:0); 
	                    
						if(getLago(pd->getCod_alvo_sede())->getTamanho() * getLago(pd->getCod_alvo_sede())->getTamanho_atual() / 100 > 0){     //se o rio tiver agua...                    if(getPlanta(ps->getCod_alvo_fome())->getEstado()){  //se a planta estiver viva
	   
	                    //  printf("tem auga nu lags\n");
	                      lg_aux = lg1;
	                      while(lg_aux != NULL){
	                         
	                        // printf("calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()) < calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()) +++ %d < %d\n",calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()), calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()));
	                                   
	                         if(calcula_distancia(pd->getPosicao(),lg_aux->getPosicao()) < calcula_distancia(pd->getPosicao(), getLago(pd->getCod_alvo_sede())->getPosicao())){     
	
	                            //if(ps->getCodigo()==pd_sel && pausa)
	                            //   printf("inicio do while Procurando alvo mais proximo\n");
	
	                            pd->setCod_alvo_sede(lg_aux->getCodigo());   
	                           }
	                         lg_aux= lg_aux->getProx_l();           
	                        }   
	                     
	                     // printf("o lago alvu da ps %d eh %d \n",ps->getCodigo(), ps->getCod_alvo_sede());  
	                      
	                     // printf("definiu o cod alvo da presa..\n");  
	                    
	                    }     
	               
	              // printf("getPlanta(ps->getCod_alvo())->getEstado() +++ %d\n",getPlanta(ps->getCod_alvo())->getEstado()?1:0);
	               
	                   if(getLago(pd->getCod_alvo_sede())->getTamanho() * getLago(pd->getCod_alvo_sede())->getTamanho_atual() / 100 > 0){  // o lago ainda tem agua?
	                 //     if(getPresa(pd->getCod_alvo())->getIdade() < getPresa(pd->getCod_alvo())->getIdade_max()){
	                ///        printf("calcula_distancia(ps->getPosicao(),getPlanta(ps->getCod_alvo())->getPosicao()) < ps->getSentidos() +++ %d < %d\n",calcula_distancia(ps->getPosicao(),getPlanta(ps->getCod_alvo())->getPosicao()), ps->getSentidos());
	                         if(calcula_distancia(pd->getPosicao(),getLago(pd->getCod_alvo_sede())->getPosicao()) < pd->getSentidos()+getLago(pd->getCod_alvo_sede())->getTamanho() * getLago(pd->getCod_alvo_sede())->getTamanho_atual() / 100){      
	                         //   if(atacar(pd,getPresa(pd->getCod_alvo()),pd->getSentidos(),nvl_pers)){
	 //if(ps != ps1)   
	   ///                           printf("a pranta está dentro do campo de visao...");   
	                               nova_posicao=getLago(pd->getCod_alvo_sede())->getPosicao();
	                        //      } 
	                           }
	                   //     }                   
	                     }
	                    //printf("presa indo em direcao a pranta..\n");   
	                  }
	                else{   
	                   if(lg1!=NULL){  
	                      pd->setCod_alvo_sede(lg1->getCodigo());
	                     }  
	                  }              
	               }
			}
  	     
               
               
               
               
     
     /*
            printf("lalala od alvo pred %d",pd->getCod_alvo());
            
           printf("*%d \n", pd->getCod_alvo());
  	       printf("**%d \n", nova_posicao.x);
  	       posXY ppp = getPresa(pd->getCod_alvo())->getPosicao();
  	       getch();
  	       printf("****");
  	       printf("***%d \n", ppp.x);
  	       printf("****%d \n", nova_posicao.y);
  	       printf("*****%d \n", getPresa(pd->getCod_alvo())->getPosicao().y);
           printf("******%d \n", pd->getCod_alvo());
           
           */
          
            if((pd->getCod_alvo_fome() != -1 && (nova_posicao.x != getPresa(pd->getCod_alvo_fome())->getPosicao().x  && nova_posicao.y != getPresa(pd->getCod_alvo_fome())->getPosicao().y)) || (pd->getCod_alvo_fome() == -1)){    
               if(pd->getGestacao() == 0 && pd->getResguardo() == 0 && pd->getFertil()){   
                  if(pd->getCod_parceiro()!= -1){      
                     pd_aux=pd1;  
                     while(pd_aux != NULL){ 
                       //printf("8");
                       // if(pd->getCodigo()==pd_sel && pausa)
                       //    printf("inicio do while Procurando parceiro mais proximo\n");
                            
                        if(pd_aux->getSexo() != pd->getSexo()){  
                           if(pd_aux->getGestacao() == 0 && pd_aux->getResguardo() == 0 && pd_aux->getFertil()){  
                              if(calcula_distancia(pd->getPosicao(),pd_aux->getPosicao()) < calcula_distancia(getPredador(pd->getCod_parceiro())->getPosicao(), pd->getPosicao())){ 
                                 pd->setCod_parceiro(pd_aux->getCodigo());    
                                }
                             }
                          }    
                        pd_aux= pd_aux->getProx_c();              
                       }
                         
                     if(calcula_distancia(pd->getPosicao(),getPredador(pd->getCod_parceiro())->getPosicao()) < pd->getVisao_reproducao()){
                        if(getPredador(pd->getCod_parceiro())->getResguardo()== 0){
                           if(getPredador(pd->getCod_parceiro())->getGestacao() == 0){   
                              if(getPredador(pd->getCod_parceiro())->getFertil()) {                                                                    
                                 nova_posicao=getPredador(pd->getCod_parceiro())->getPosicao();
                                }
                             }
                          }
                       } 
               
                     }
                  else{   
                     pd_aux=pd1;  
                     while(pd_aux!=NULL){
                     
                     //   if(pd->getCodigo()==pd_sel && pausa)
                     //      printf("inicio do while Procurando 1o parceiro\n");
                                           
                        if(pd->getSexo() != pd_aux->getSexo()){
                           if(pd_aux->getGestacao()==0 && pd_aux->getResguardo()==0 && pd_aux->getFertil()){  
                              pd->setCod_parceiro(pd_aux->getCodigo());
                              break;
                             }
                          }
                        pd_aux=pd_aux->getProx_c();                    
                       }
                    }  
                            
                 }
                 
              } 
    
       pthread_mutex_unlock(&p_key); 
                
       posicao_atual = pd->getPosicao();
        
       if((pd->getPosicao().x == nova_posicao.x) && (pd->getPosicao().y == nova_posicao.y)){
          int aux;
		  do{
			 aux=0;
             nova_posicao= sorteia_posicao(pd->getPosicao(), pd->getArea_interesse(),vai);  
              //printf("9");
        
		          lg_aux = lg1;
                  while(lg_aux != NULL){
                    
                    // printf("calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()) < calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()) +++ %d < %d\n",calcula_distancia(ps->getPosicao(),pl_aux->getPosicao()), calcula_distancia(ps->getPosicao(), getPlanta(ps->getCod_alvo())->getPosicao()));
                               
                     if(calcula_distancia(nova_posicao,lg_aux->getPosicao()) < lg_aux->getTamanho()*lg_aux->getTamanho_atual()/100){ 
						aux=1;
						//printf("\a");
						break;	    
                       }
                     lg_aux= lg_aux->getProx_l();           
                    }  
              
                  pd->setArea_interesse(pd->getArea_interesse()-1);
                  if(pd->getArea_interesse()<0)
	                 break;
		             
			}while(nova_posicao.x <= 0+pd->getTamanho() || nova_posicao.x >= dim_campo.x-pd->getTamanho() || nova_posicao.y <= 0+pd->getTamanho() || nova_posicao.y >= dim_campo.y-pd->getTamanho() || aux==1);  
         
             pd->setArea_interesse(area_int);
		 
		 }
       else{
	       if(pd->getFome() < tmp_fome + tmp_sac_fome-2){
		       if(mod_sede){
			      if(pd->getSede() < tmp_sede + tmp_sac_sede-2){
				     pd->mover(pd->aproximar(nova_posicao), dim_campo);
				  }
			   }
			   else{
				  pd->mover(pd->aproximar(nova_posicao), dim_campo);	
			   }		
	         }
         }  
       
	   
         
         
         
         
         
              
       pthread_mutex_lock(&p_key); 
           
           if(pd->getFome() <= tmp_fome){ 
              if(getPresa(pd->getCod_alvo_fome())!= NULL){
                 if((pd->getPosicao().x == getPresa(pd->getCod_alvo_fome())->getPosicao().x) && (pd->getPosicao().y == getPresa(pd->getCod_alvo_fome())->getPosicao().y)){  
                    pd->setFome(tmp_sac_fome + tmp_fome);
                    getPresa(pd->getCod_alvo_fome())->setIdade(getPresa(pd->getCod_alvo_fome())->getIdade_max());
                    pd->setCod_alvo_sede(-1);          
                   }
                }
             }
             
             
          
		   if(pd->getCod_alvo_sede() != -1){ 
            
           if(pd->getSede() <= tmp_sede){ // se a presa estiver com sede              
              
              if(getLago(pd->getCod_alvo_sede())->getTamanho() * getLago(pd->getCod_alvo_sede())->getTamanho_atual() / 100 > 0){   // se o lago tiver agua
                 //printf("to ake  ps cod alvo sede =>%d \n", ps->getCod_alvo_sede());
              	 if(calcula_distancia(pd->getPosicao(),getLago(pd->getCod_alvo_sede())->getPosicao()) <= getLago(pd->getCod_alvo_sede())->getTamanho() * getLago(pd->getCod_alvo_sede())->getTamanho_atual() / 100){      
                    
					do{
					   nova_posicao = sorteia_posicao(pd->getPosicao(),pd->getArea_interesse(),vai);//ps->getPosicao();       
					  // printf("0"); 
					   pd->setArea_interesse(pd->getArea_interesse()-1);
					   if(pd->getArea_interesse()<0)
	                      break;
					  }while(calcula_distancia(nova_posicao,getLago(pd->getCod_alvo_sede())->getPosicao()) < (getLago(pd->getCod_alvo_sede())->getTamanho()*getLago(pd->getCod_alvo_sede())->getTamanho_atual()/100)+ (pd->getTamanho()));
				   // if(pd->getArea_interesse()<0){  morreu afogado    }
				    pd->setArea_interesse(area_int);
				    
				    pd->setSede(tmp_sac_sede + tmp_sede);
                    pd->setCod_alvo_sede(-1);  
				   
				   }
                }
     
              
            }   
                 
         }   
           
		     
           
           if(pd->getSexo()==1 && pd->getCod_parceiro()!= -1){  
               if(getPredador(pd->getCod_parceiro()) != NULL){           
                  if((pd->getPosicao().x == getPredador(pd->getCod_parceiro())->getPosicao().x) && (pd->getPosicao().y == getPredador(pd->getCod_parceiro())->getPosicao().y)){ 
                     if((pd->getGestacao() == 0) && (getPredador(pd->getCod_parceiro())->getGestacao() == 0)){   
                        if((pd->getResguardo() == 0) && (getPredador(pd->getCod_parceiro())->getResguardo() == 0)){
                           if(pd->getFertil() && getPredador(pd->getCod_parceiro())->getFertil()){
                              pd->setGestacao(tgpd);  
                              parceiro=getPredador(pd->getCod_parceiro());
                              pd_aux=pd1;
                              while(pd_aux!=NULL){
                                 if(pd_aux->getCod_parceiro() == pd->getCodigo()){
                                    //if(pd->getCodigo()==pd_sel && pausa)
                                     //  printf("inicio do while Desmarcando parceiros quando da a luz\n");
                       
                                    pd_aux->setCod_parceiro(-1);
                                   }     
                                 pd_aux=pd_aux->getProx_c();                   
                                }
                             }
                          }
                       }
                    }
                 }
              }          
         
           if(pd->getCod_parceiro()!=-1){ 
              if(!getPredador(pd->getCod_parceiro())->getFertil()){   
                 pd->setCod_parceiro(-1);                                        
                }
             }     
         
         
         
         
           if(pd->getCor().r>255 ||pd->getCor().g>255 ||pd->getCor().b>255  ||  pd->getCor().r<0 ||pd->getCor().g<0 ||pd->getCor().b<0){
				printf("predador %d cor bugada %d %d %d \n",pd->getCodigo(),pd->getCor().r,pd->getCor().g,pd->getCor().b);
		        pausa=true;
		   }
           if(pd->getVelocidade()<0 || pd->getVelocidade()>9){
				printf("predador %d velocidade bugada %d\n",pd->getCodigo(),pd->getVelocidade());
		        pausa=true;
		   }
           if(pd->getSentidos()<visao_max*0.5 || pd->getSentidos()>visao_max){
				printf("predador %d visao bugada %d\n",pd->getCodigo(),pd->getSentidos());
		        pausa=true;
		   }         
         
         
         

           setlinestyle(0,0,2);
           setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));  
           if(pd->getCor().r>255 ||pd->getCor().g>255 ||pd->getCor().b>255  || pd->getCor().r<0 ||pd->getCor().g<0 ||pd->getCor().b<0){
				 setfillstyle(1, COLOR(255,255,255));
			}
		   else{
				setfillstyle(1, COLOR(pd->getCor().r,pd->getCor().g,pd->getCor().b));
		    }
           //setfillstyle(1, COLOR(pd->getCor().r,pd->getCor().g,pd->getCor().b));
           fillellipse(posicao_atual.x,posicao_atual.y,pd->getTamanho(),pd->getTamanho());   
            
           setlinestyle(0,0,2);
           
           
           
           
           
           if(pd->getCor().r>255 ||pd->getCor().g>255 ||pd->getCor().b>255  ||  pd->getCor().r<0 ||pd->getCor().g<0 ||pd->getCor().b<0){
				 
				 setfillstyle(1, COLOR(255,255,255));
			}
		   else{
				setfillstyle(1, COLOR(pd->getCor().r,pd->getCor().g,pd->getCor().b));
		    }
		    
		    if(borda){
			   if(pd->getSexo())
	              setcolor(COLOR(255,200,0)); 
	           else
		          setcolor(COLOR(10,200,50)); 
	          fillellipse(pd->getPosicao().x,pd->getPosicao().y,pd->getTamanho(),pd->getTamanho()); 
		   }
		   else{
			   setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));	
    		   fillellipse(pd->getPosicao().x,pd->getPosicao().y,pd->getTamanho()+2,pd->getTamanho()+2);  

		   }
		   
		    

       pthread_mutex_unlock(&p_key);    
       
       if(pd->getVelocidade()>=0 && pd->getVelocidade()<10)
          delay(fdm - (pd->getVelocidade()*(10*fdm/100)));
     
          
       while(pausa){
        //  if(pd->getCodigo()==pd_sel && pausa)
        //     printf("inicio do while PAUSA\n");
                                 
          delay(100);        
         }
         
       if(abs(tempo-segundo) > 750){
                
           segundo = tempo;
           pd->idade_pp();
           
           if(pd->getFome() > 0){                            
              pd->fome_mm();
             }
           else{
              break;  
             }
           if(mod_sede){
	           if(pd->getSede() > 0){
	              pd->sede_mm();
	             }
	           else{
	              break;  // morre de sede
	             }  
		   }
           if(pd->getSexo()){           
               if(pd->getResguardo() > 0){
                  pd->resguardo_mm();
                 }
               if(pd->getGestacao() > 0){
                  pd->gestacao_mm();
                  if(pd->getGestacao() == 0){
                     pthread_mutex_lock(&p_key);
                     
                         pd_aux=pd1;
                         while(pd_aux->getProx_c()!=NULL){
                            pd_aux= pd_aux->getProx_c();                      
                           }   
                         pd_aux->setProx_c(criar_predador(pd_aux->getCodigo()+1,rand()%2,*pd, *parceiro));  
                         pd_aux->getProx_c()->setCod_mae(pd->getCodigo());
                         pd_aux->getProx_c()->setFome(tmp_fome+tmp_sac_fome-3);
                         if(mod_sede)
                             pd_aux->getProx_c()->setSede(tmp_sede+tmp_sac_sede-3);
                         
                         pd_ = pd_aux->getProx_c()->getMove_td();
                         pthread_create(&pd_, NULL, movimentar_predador, pd_aux->getProx_c());   
                         pd->setResguardo(trpd);
                    
                         
                        if(pd_aux->getProx_c()->getVelocidade()<0 || pd_aux->getProx_c()->getVelocidade()>9){  //pais de categoria 1..  nao pode!!
							printf("pedradô %d velocidade %d mae cod %d vel %d     pai cod %d vel %d\n",pd_aux->getProx_c()->getCodigo(),pd_aux->getProx_c()->getVelocidade(),pd->getCodigo(),pd->getVelocidade(),parceiro->getCodigo(),parceiro->getVelocidade());
                            getch();
						}
                    
                     pthread_mutex_unlock(&p_key);
                    }  
                 }
                  
              }
             
           if(pd->getIdade()>ida_cat4){
              if(pd->getCategoria() != 4){ 
                 pd->setCategoria(4);                      
                 if(pd->getSentidos()>visao_max*0.75)
                    pd->setSentidos(pd->getSentidos() - visao_max*0.25);
                 //pd->setSentidos((int)le_info("campo_max_visao_predador")*0.6);   
                 //pd->setVelocidade(-1);
                 //pd->setVelocidade(pd->getVelocidade()); 
                    if(pd->getVelocidade()>=5)
    				   pd->setVelocidade(pd->getVelocidade()-5); 
                 pd->setCod_parceiro(-1);  
                }
             }
           else if(pd->getIdade()>ida_cat3){
              if(pd->getCategoria() != 3){ 
                 pd->setCategoria(3);                      
                 if(pd->getSentidos()<visao_max*0.75)
                    pd->setSentidos(pd->getSentidos() + visao_max*0.25);   
                 //pd->setVelocidade(-1);
                 //pd->setVelocidade(pd->getVelocidade()); 
                 if(pd->getVelocidade()<5)
    				pd->setVelocidade(pd->getVelocidade()+5); 
                 //pd->setSentidos(le_info("campo_max_visao_predador"));   
                 //pd->setVelocidade(4+rand()%6); 
                }                
             }
           else if(pd->getIdade()>ida_cat2){ 
              if(pd->getCategoria() != 2){ 
                 pd->setCategoria(2);                      
                 if(pd->getSentidos()<visao_max*0.75)
                    pd->setSentidos(pd->getSentidos() + visao_max*0.25);   
                 //pd->setVelocidade(-1);
                 //pd->setVelocidade(pd->getVelocidade()); 
                 if(pd->getVelocidade()<5)
    				pd->setVelocidade(pd->getVelocidade()+5); 
                 //pd->setSentidos(le_info("campo_max_visao_predador"));   
                 //pd->setVelocidade(4+rand()%6); 
                }                  
             }    
           
           
           		   //visao reproducao	
			if(pd->getIdade()>=ida_cat2 && pd->getIdade()<=ida_cat4){
	     		tmp_rep = pd->getIdade()-ida_cat2;  //0-100 (cat2+cat3) * 2
			    pd->setVisao_reproducao(ceil(pd->getVisao_reproducao_max()*sin(2*M_PI*(1.0/(2*(ida_cat4-ida_cat2)))*tmp_rep)));
			    //printf("vs pd rep rat%.2f  size%.1f  tmp rep=%d\n",sin(2*M_PI*(1.0/(2*(ida_cat4-ida_cat2)))*tmp_rep), ceil(visao_rep_max*sin(2*M_PI*(1.0/(2*(ida_cat4-ida_cat2)))*tmp_rep)), tmp_rep); 
		    
		        //printf("cvrps %d   %d\n", le_info("campo_max_visao_rep_presa"),le_info("campo_max_visao_rep_predador"));
			    /*
				setlinestyle(0,0,2);
	            setcolor(COLOR(255,0,255));
	    		circle(pd->getPosicao().x,pd->getPosicao().y,pd->getVisao_reproducao());
                 */
			}
           
             
          }  
          
         //  getch();
      }  //while life  
    
    
    if(pd->getSexo())
       cpd_f--;
    else
       cpd_m--;     
    
    delay(2000);   

    for(i=pd->getTamanho();i>0;i--){
       pthread_mutex_lock(&p_key); 
          if(i==1){
             setfillstyle(1, COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));   
            }
          else{  
             setfillstyle(1, COLOR(pd->getCor().r,pd->getCor().g,pd->getCor().b));
             setlinestyle(0,0,2); 
            }
          setcolor(COLOR(cp.getCor().r,cp.getCor().g,cp.getCor().b));  
          fillellipse(pd->getPosicao().x,pd->getPosicao().y,i,i);    
       pthread_mutex_unlock(&p_key); 
       delay(500);
      }


    
   
    pthread_mutex_lock(&p_key); 
    
       pd_aux=pd1;
       while(pd_aux!=NULL){
          if(pd_aux->getCod_parceiro() == pd->getCodigo()){
             pd_aux->setCod_parceiro(-1);
            }     
          pd_aux=pd_aux->getProx_c();                   
         }
        
       matar_predador(pd->getCodigo());

    pthread_mutex_unlock(&p_key); 
     

	return 0;
}
     



//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/  CAMPO DESCRIÇÃO  \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\


void imprime_campo_descricao(){	
	int col = le_info("qt_col_campo");
	int lin=0;
	
    setlinestyle(0,0,1);
	setfillstyle(1,BLACK);
    setcolor(WHITE);
    bar(col+1,1,getmaxx(),getmaxy()); 
    rectangle(col,0,getmaxx(),getmaxy());

    settextstyle(8, 0, 2);  //settextstyle(6, 0, 1);
    bgiout<<"DESCRIPTION";   //bgiout<<"DESCRIÇÂO";
	outstreamxy(col+15,lin+20);  //outstreamxy(col+13,lin+20);
    
    settextstyle(0, 0, 0);
    setcolor(COLOR(125,250,0));
    bgiout<<"Type:\n";  //bgiout<<"Tipo:\n";
    bgiout<<"Code(ID):\n";  //bgiout<<"Código:\n";
    bgiout<<"Gender:\n";   //bgiout<<"Sexo:\n";
	bgiout<<"Category:\n";  //bgiout<<"Categoria:\n";
    bgiout<<"Speed:\n";   //bgiout<<"Velocidade:\n";
    bgiout<<"Age:\n";    //bgiout<<"Idade:\n";
    bgiout<<"Color:\n";   //bgiout<<"Cor:\n";
    bgiout<<"Sit.:\n";   //bgiout<<"Situação:\n";
    bgiout<<"Target:\n";   //bgiout<<"Alvo:\n";
    bgiout<<"Threat:\n";    //bgiout<<"Ameaça:\n";
    bgiout<<"Partner:\n";   //bgiout<<"Parceiro:\n";
    bgiout<<"Hunger:\n";   
    bgiout<<"Thirst:\n";   
    bgiout<<"Camouflaged:\n";   
    outstreamxy(col+10,lin+50);
    bgiout<<"/";
    outstreamxy(col+90,lin+140);   //outstreamxy(col+110,lin+140);
    bgiout<<",";
    outstreamxy(col+97,lin+158);   //outstreamxy(col+110,lin+140);
    bgiout<<",";
    outstreamxy(col+130,lin+158);   //outstreamxy(col+110,lin+140);
    
    
	//settextstyle(12, 0, 2); // problema
    setcolor(COLOR(175,185,185));
	//setcolor(WHITE);
	settextstyle(11, 0, 1);
    //bgiout<<"Mouse position:";   //bgiout<<"Posição do Mouse:";
	//outstreamxy(col+25,lin+278);
	bgiout<<"Time (s):";   //bgiout<<"Tempo (s):";
	outstreamxy(col+40,lin+343);

	bgiout<<"Preys:\n    M:             F:\nPredators:\n    M:             F:";   //  bgiout<<"Presas:\n    M:             F:\nPredadores:\n    M:             F:";
	outstreamxy(col+32,lin+383);
	  
    //settextstyle(13, 0, 0);
    //setcolor(COLOR(100,185,250));
    //bgiout<<"X:\nY:";
	//outstreamxy(col+50,lin+298);
	
	
	        //draw confg button
    settextstyle(2, 0, 7);
    setcolor(COLOR(0,0,0));
    setbkcolor(COLOR(255,255,255));
    char c  = 15;
	bgiout<<c;
	outstreamxy(col+153,lin+2);
	setcolor(COLOR(255,255,255));
	setbkcolor(COLOR(0,0,0));
    rectangle(col+151,lin+2,col+167,lin+19);  
    
       
}



void imprime_info_presa(Presa *ps){
	int col= le_info("qt_col_campo");
    int lin=0;
    
    setcolor(COLOR(255,193,37));
    setlinestyle(0,0,1);
    settextstyle(0, 0, 0);
    bgiout<<"Prey";//bgiout<<"Presa";
    outstreamxy(col+60,lin+50);
    bgiout<<ps->getCodigo();
    outstreamxy(col+100,lin+68);  //outstreamxy(col+80,lin+68);
	if(ps->getSexo())
	   bgiout<<"Female"; //  bgiout<<"Feminino";
	else
	   bgiout<<"Male";  //bgiout<<"Masculino";
	outstreamxy(col+82,lin+86);  //outstreamxy(col+60,lin+86);  
    bgiout<<ps->getCategoria();
	outstreamxy(col+100,lin+104);  //outstreamxy(col+110,lin+104);
    bgiout<<ps->getVelocidade();
	outstreamxy(col+70,lin+122);   //outstreamxy(col+120,lin+122);
    if(ps->getIdade()<10)
       bgiout<<" "; 
    if(ps->getIdade()<100)
       bgiout<<" ";   
    bgiout<<ps->getIdade();
	outstreamxy(col+55,lin+140); //outstreamxy(col+75,lin+140);
	bgiout<<ps->getIdade_max();
	outstreamxy(col+105,lin+140);  //outstreamxy(col+125,lin+140);
	if(ps->getCor().r<100)
       bgiout<<" ";  
	bgiout<<ps->getCor().r;
	outstreamxy(col+69,lin+158);
	if(ps->getCor().g<100)
       bgiout<<" ";  
	bgiout<<ps->getCor().g;
	outstreamxy(col+103,lin+158);
	bgiout<<ps->getCor().b;
	outstreamxy(col+137,lin+158);
	if(ps->getGestacao()>0)
	   bgiout<<"Pregnant";   //Gestante
	else if(ps->getResguardo()>0)
	   bgiout<<"Resg.";
	else if(ps->getFertil())
	   bgiout<<"Fertile";   //bgiout<<"Fértil";  
	else
       bgiout<<"---------";   // bgiout<<"------";  
	outstreamxy(col+65,lin+176);  //outstreamxy(col+100,lin+176);
	if(ps->getCod_alvo_fome() == -1)
       bgiout<<"-------";  //bgiout<<"-----";
    else
       bgiout<<"["<<ps->getCod_alvo_fome()<<"]";      
  
	outstreamxy(col+80,lin+194);   //outstreamxy(col+60,lin+194);
    if(ps->getCod_ameaca() == -1)
       bgiout<<"-------";
    else
       bgiout<<"["<<ps->getCod_ameaca()<<"]";   
	outstreamxy(col+80,lin+212);
	if(ps->getCod_parceiro() == -1)
       bgiout<<"------";
    else
       bgiout<<"["<<ps->getCod_parceiro()<<"]";
    outstreamxy(col+90,lin+230);  //outstreamxy(col+100,lin+230);
    if(ps->getFome() != -1){
       bgiout<<ps->getFome();
    }
    else{
	   bgiout<<"------";
    }
    outstreamxy(col+83,lin+248);  //outstreamxy(col+100,lin+230);
    if(ps->getSede() != -1){
       bgiout<<ps->getSede();
    }
    else{
	   bgiout<<"------";
    }
    outstreamxy(col+83,lin+266);  //outstreamxy(col+100,lin+230);
    if(ps->getCamuflado())
	   bgiout<<"Yes";
	else
	   bgiout<<"No";     
	outstreamxy(col+133,lin+284);  //outstreamxy(col+100,lin+230);
    

} 


void imprime_info_predador(Predador *pd){
	int col = le_info("qt_col_campo");
    int lin = 0;
    
    setcolor(COLOR(255,193,37));
    setlinestyle(0,0,1);
    settextstyle(0, 0, 0);
    bgiout<<"Predator";    //bgiout<<"Predador";  
    outstreamxy(col+60,lin+50);
    bgiout<<pd->getCodigo();
    outstreamxy(col+100,lin+68);  //outstreamxy(col+80,lin+68);
	if(pd->getSexo())
	   bgiout<<"Female";  //bgiout<<"Feminino"; 
	else
	   bgiout<<"Male";   //bgiout<<"Masculino"; 
    outstreamxy(col+82,lin+86);  //outstreamxy(col+60,lin+86);  
    bgiout<<pd->getCategoria();
	outstreamxy(col+100,lin+104);  //outstreamxy(col+110,lin+104);
    bgiout<<pd->getVelocidade();
	outstreamxy(col+70,lin+122);   //outstreamxy(col+120,lin+122);
    if(pd->getIdade()<10)
       bgiout<<" ";
    if(pd->getIdade()<100)
       bgiout<<" ";   
    bgiout<<pd->getIdade();
	outstreamxy(col+55,lin+140);  //outstreamxy(col+75,lin+140);
	bgiout<<pd->getIdade_max();
	outstreamxy(col+105,lin+140);  //outstreamxy(col+125,lin+140);
	if(pd->getCor().r<100)
       bgiout<<" ";   
    bgiout<<pd->getCor().r;
	outstreamxy(col+69,lin+158);
	if(pd->getCor().g<100)
       bgiout<<" ";   
    bgiout<<pd->getCor().g;
	outstreamxy(col+103,lin+158);
    bgiout<<pd->getCor().b;
	outstreamxy(col+137,lin+158);
	if(pd->getGestacao()>0)
	   bgiout<<"Pregnant";   //Gestante
	else if(pd->getResguardo()>0)
	   bgiout<<"Resg.";
	else if(pd->getFertil())
	   bgiout<<"Fertile";   //bgiout<<"Fértil";  
	else
       bgiout<<"---------";   // bgiout<<"------";  
	outstreamxy(col+65,lin+176);  //outstreamxy(col+100,lin+176);
	if(pd->getCod_alvo_fome() == -1)
       bgiout<<"-------";  //bgiout<<"-----";
    else
       bgiout<<"["<<pd->getCod_alvo_fome()<<"]";      
  
	outstreamxy(col+80,lin+194);   //outstreamxy(col+60,lin+194);
    bgiout<<"-------";  // ameaca
    outstreamxy(col+80,lin+212);
	if(pd->getCod_parceiro() == -1)
       bgiout<<"------";
    else
       bgiout<<"["<<pd->getCod_parceiro()<<"]";
    outstreamxy(col+90,lin+230);  //outstreamxy(col+100,lin+230);
    if(pd->getFome() != -1){
       bgiout<<pd->getFome();
    }
    else{
	   bgiout<<"------";
    }
	outstreamxy(col+83,lin+248);  //outstreamxy(col+100,lin+230);
    if(pd->getSede() != -1){
       bgiout<<pd->getSede();
    }
    else{
	   bgiout<<"------";
    }
    outstreamxy(col+83,lin+266);  //outstreamxy(col+100,lin+230);
    if(pd->getCamuflado())
	   bgiout<<"Yes";
	else
	   bgiout<<"No";     
	outstreamxy(col+133,lin+284);  //outstreamxy(col+100,lin+230);
} 




void imprime_info_planta(Planta *pl){

	int col = le_info("qt_col_campo");
    int lin = 0;
    
    setcolor(COLOR(255,193,37));
    setlinestyle(0,0,1);
    settextstyle(0, 0, 0);
    bgiout<<"Grass";    //bgiout<<"Predador";  
    outstreamxy(col+60,lin+50);
    bgiout<<pl->getCodigo();
    outstreamxy(col+100,lin+68);  //outstreamxy(col+80,lin+68);
	bgiout<<"-------";   //bgiout<<"Masculino"; 
    outstreamxy(col+82,lin+86);  //outstreamxy(col+60,lin+86);  
    bgiout<<"-----";
	outstreamxy(col+100,lin+104);  //outstreamxy(col+110,lin+104);
    bgiout<<"--------";
	outstreamxy(col+70,lin+122);   //outstreamxy(col+120,lin+122);  
    bgiout<<"---------";
	outstreamxy(col+55,lin+140);  //outstreamxy(col+75,lin+140);
	if(pl->getCor().r<100)
       bgiout<<" ";   
    bgiout<<pl->getCor().r;
	outstreamxy(col+69,lin+158);
	if(pl->getCor().g<100)
       bgiout<<" ";   
    bgiout<<pl->getCor().g;
	outstreamxy(col+103,lin+158);
    bgiout<<pl->getCor().b;
	outstreamxy(col+137,lin+158);
	if(pl->getEstado())
	   bgiout<<"Eatable";   //Gestante
	else 
	   bgiout<<"Eaten  ";
	outstreamxy(col+65,lin+176);  //outstreamxy(col+100,lin+176);
	bgiout<<"-------";  //bgiout<<"-----";
	outstreamxy(col+80,lin+194);   //outstreamxy(col+60,lin+194);
    bgiout<<"-------";  // ameaca
    outstreamxy(col+80,lin+212);
	bgiout<<"------";
    outstreamxy(col+90,lin+230);  //outstreamxy(col+100,lin+230);
    bgiout<<"-------";
    outstreamxy(col+83,lin+248);  //outstreamxy(col+100,lin+230);
    bgiout<<"-------";
    outstreamxy(col+83,lin+266);  //outstreamxy(col+100,lin+230);
    bgiout<<"---";     
	outstreamxy(col+133,lin+284);  //outstreamxy(col+100,lin+230);
} 



void limpa_descricao(){
    int col= le_info("qt_col_campo");
    int lin=0;
    
    settextstyle(0, 0, 0);
    setcolor(BLACK);
    bgiout<<"        ";
    outstreamxy(col+60,lin+50);
    bgiout<<"       ";
    outstreamxy(col+80,lin+68);
    bgiout<<"         ";
	outstreamxy(col+60,lin+86);
    bgiout<<"  ";
	outstreamxy(col+110,lin+104);
    bgiout<<"  ";
	outstreamxy(col+120,lin+122);
    bgiout<<"   ";
	outstreamxy(col+75,lin+140);
	bgiout<<"   ";
	outstreamxy(col+125,lin+140);
	bgiout<<"           ";
	outstreamxy(col+50,lin+158);
	bgiout<<"      ";   
	outstreamxy(col+100,lin+176);
	bgiout<<"       ";   
	outstreamxy(col+60,lin+194);
    bgiout<<"       ";
    outstreamxy(col+80,lin+212);
	bgiout<<"      ";
    outstreamxy(col+100,lin+230);
    
}






void imprime_cabecalho(char *argv[], int n_relatorio){
    char local_relatorio[150]; 
    int i;

	strcpy(local_relatorio,*argv);

    for(i= strlen(local_relatorio)-1; i>=0; i--){
   	   if(local_relatorio[i] == '\\')
	      break;
	   local_relatorio[i]= '\0';	 	
	  }
		
    strcat(local_relatorio,"Reports\\");   //strcat(local_relatorio,"Relatorios\\");
	for(i=0;i<strlen(local_relatorio);i++)
	   if(local_relatorio[i]== '\\')
	      local_relatorio[i] = '/';
	 
    
    /*
    printf("\t\t\t#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n\t\t\t*#*  Simulador em execucao  *#*\n\t\t\t#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n\n\t\t\t    Nao feche esta janela ! \n\n\n");
	printf("Informacoes salvas em:\n Relatorio %d\n(%sRelatorio_%d.txt)\n",n_relatorio,local_relatorio,n_relatorio);
	   
    
    
    printf("\n\n Comandos:    (podem ser acessados quando a simulacao esta pausada)\n");
    printf("\n -> A    Cria um novo predador com atributos aleatorios");
    printf("\n -> S    Cria uma nova presa com atributos aleatorios");    
    printf("\n -> D    Visualiza informacoes detalhadas sobre um predador");
    printf("\n -> F    Visualiza informacoes detalhadas sobre uma presa");
    printf("\n -> C    Visualiza as informacoes dos predadores");
    printf("\n -> X    Visualiza as informacoes das presas");
    printf("\n -> Z    Visualiza a media e a variacao das cores das presas");
    printf("\n -> ESC  Sai da simulacao\n");
	*/
    printf("\t\t\t#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n\t\t\t*#*   Simulator executing   *#*\n\t\t\t#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n\n\t\t\t   Do not close this window ! \n\n\n");
	printf("Information has been salved in:\n Report %d\n(%sReport_%d.txt)\n",n_relatorio,local_relatorio,n_relatorio);
	   
    
    
    printf("\n\n Commands:    (They can be activated when simulation is paused)\n");
    printf("\n -> A    Create a new predator with random attributes");
    printf("\n -> S    Create a new prey with random attributes");    
    printf("\n -> D    Visualize detailed information about a predator");
    printf("\n -> F    Visualize detailed information about a prey");
    printf("\n -> Z    Visualize information about all predators");
    printf("\n -> X    Visualize information about all preys");
    printf("\n -> C    Visualize the mean and variance of agents' color, speed and view field");
    printf("\n -> B    Enable/Disable agents' border view");
    printf("\n -> ESC  Exit simulation\n");
     
     
     
     
}

void chama_configuration(char *argv){
	
	int i;
	
	char path[500];
	for(i=0;i<500;i++)
		path[i]='\0';
	
	strcpy(path, argv);
	do{
		path[strlen(path)-1] = '\0';
		
	}while(path[strlen(path)-1] != '\\');

	strcat(path,"Configuration_Simulator.exe");
	for(i=strlen(path);i>0;i--){
		path[i] =  path[i-1];
    }
	path[0] = '"';
	path[strlen(path)]= '"';
	strcat(path," info.cfg");
	printf("%s %d",path,strlen(path));
	
	system(path);
	
	
}




