
#ifndef FUNC_ARQ_C
#define FUNC_ARQ_C

#include <funcoes.h>  




int le_info( char atributo[]){
    
    FILE *f;
    
         //Variaveis para o armazenamento das informacoes contidas no arquivo INFO

     int qt_col_campo, qt_lin_campo;
     int cor_r_campo, cor_g_campo, cor_b_campo;
     int qt_presa_m, qt_presa_f;
     int qt_predador_m, qt_predador_f;
     int tamanho_presa, tamanho_predador;
     int idade_media_presa_m, var_idade_media_presa_m;
     int idade_media_presa_f, var_idade_media_presa_f;
     int idade_media_predador_m, var_idade_media_predador_m;
     int idade_media_predador_f, var_idade_media_predador_f;
     int area_interesse_presa, var_area_interesse_presa;
     int area_interesse_predador, var_area_interesse_predador;
     int tempo_gest_presa, tempo_gest_predador;
     int tempo_resg_presa, tempo_resg_predador;    
     int campo_max_visao_presa, campo_max_visao_predador;
     int campo_max_visao_rep_presa, var_campo_max_visao_rep_presa;
	 int campo_max_visao_rep_predador, var_campo_max_visao_rep_predador;
     int fator_delay_max_presa, fator_delay_max_predador;
     int tempo_saciedade_fome, tempo_fome;
     int tempo_saciedade_sede, tempo_sede;
     int nivel_perseguicao;
     int variacao_cor_campo;
     int tempo_variacao_cor_campo;
     int cor_r_campo_min, cor_r_campo_max; 
     int cor_g_campo_min, cor_g_campo_max;
     int cor_b_campo_min, cor_b_campo_max; 
     int cor_r_planta, cor_g_planta, cor_b_planta;
     int qt_planta_p, qt_planta_g;
     int tempo_morte_planta;
     int intensidade_doenca_presa, vida_doenca_presa;
     int intensidade_doenca_predador, vida_doenca_predador;
     int intensidade_mutacao_presa, intensidade_mutacao_predador;
     int cor_r_lago, cor_g_lago, cor_b_lago;
     int qt_lago, tam_min_lago, tam_max_lago;
     int tempo_oscilacao_lago;
     int mod_mutacao_cor;
     int mod_doenca;
     int mod_sede;
     int mod_lago;
     int mod_fome_presa;
     int mod_planta;
     int mod_fuga_presa;
     int mod_mudanca_cor_ambiente;
     int mod_predador_camuflagem;
     
    
     
     char fim='\0';
     
    
    
    f=fopen("info.cfg","r");
   	     fscanf(f,"%d\n%d\n",&qt_col_campo, &qt_lin_campo);
         fscanf(f,"%d\n%d\n%d\n",&cor_r_campo, &cor_g_campo, &cor_b_campo);
         fscanf(f,"%d\n%d\n",&qt_presa_m, &qt_presa_f);
         fscanf(f,"%d\n%d\n",&qt_predador_m, &qt_predador_f);
         fscanf(f,"%d\n%d\n",&tamanho_presa, &tamanho_predador);
         fscanf(f,"%d\n%d\n",&idade_media_presa_m, &var_idade_media_presa_m);
         fscanf(f,"%d\n%d\n",&idade_media_presa_f, &var_idade_media_presa_f);
         fscanf(f,"%d\n%d\n",&idade_media_predador_m, &var_idade_media_predador_m);
         fscanf(f,"%d\n%d\n",&idade_media_predador_f, &var_idade_media_predador_f);
         fscanf(f,"%d\n%d\n",&area_interesse_presa, &var_area_interesse_presa);
         fscanf(f,"%d\n%d\n",&area_interesse_predador, &var_area_interesse_predador);
         fscanf(f,"%d\n%d\n",&tempo_gest_presa, &tempo_gest_predador);
         fscanf(f,"%d\n%d\n",&tempo_resg_presa, &tempo_resg_predador);
         fscanf(f,"%d\n%d\n",&campo_max_visao_presa, &campo_max_visao_predador);
         fscanf(f,"%d\n%d\n",&campo_max_visao_rep_presa, &var_campo_max_visao_rep_presa);
         fscanf(f,"%d\n%d\n",&campo_max_visao_rep_predador, &var_campo_max_visao_rep_predador);
         fscanf(f,"%d\n%d\n",&fator_delay_max_presa, &fator_delay_max_predador);
         fscanf(f,"%d\n%d\n",&tempo_saciedade_fome, &tempo_fome);
         fscanf(f,"%d\n%d\n",&tempo_saciedade_sede, &tempo_sede);
         fscanf(f,"%d\n",&nivel_perseguicao);
         fscanf(f,"%d\n%d\n",&variacao_cor_campo,&tempo_variacao_cor_campo);
         fscanf(f,"%d\n%d\n",&cor_r_campo_min, &cor_r_campo_max);
         fscanf(f,"%d\n%d\n",&cor_g_campo_min, &cor_g_campo_max);
         fscanf(f,"%d\n%d\n",&cor_b_campo_min, &cor_b_campo_max);     
         fscanf(f,"%d\n%d\n%d\n",&cor_r_planta, &cor_g_planta, &cor_b_planta);
         fscanf(f,"%d\n%d\n",&qt_planta_p, &qt_planta_g);   
         fscanf(f,"%d\n",&tempo_morte_planta);   
         fscanf(f,"%d\n%d\n",&intensidade_doenca_presa, &vida_doenca_presa); 
         fscanf(f,"%d\n%d\n",&intensidade_doenca_predador, &vida_doenca_predador); 
         fscanf(f,"%d\n%d\n",&intensidade_mutacao_presa, &intensidade_mutacao_predador); 
         fscanf(f,"%d\n%d\n%d\n",&cor_r_lago, &cor_g_lago, &cor_b_lago);
         fscanf(f,"%d\n%d\n%d\n",&qt_lago, &tam_min_lago,&tam_max_lago);  
		 fscanf(f,"%d\n",&tempo_oscilacao_lago); 
		 fscanf(f,"%d\n",&mod_mutacao_cor);
	     fscanf(f,"%d\n",&mod_doenca);
	     fscanf(f,"%d\n",&mod_sede);
	     fscanf(f,"%d\n",&mod_lago);
	     fscanf(f,"%d\n",&mod_fome_presa);
	     fscanf(f,"%d\n",&mod_planta);
	     fscanf(f,"%d\n",&mod_fuga_presa);
	     fscanf(f,"%d\n",&mod_mudanca_cor_ambiente);
	     fscanf(f,"%d\n",&mod_predador_camuflagem);
	     

         fscanf(f,"%c",&fim);
    fclose(f);
    
    if(fim != '#'){
       printf("\a\n ATENCAO: Nao foi confirmado o fim do arq INFO    (fim= %c)\n\n ",fim);
       //delay(1100);
       return -1;       
      }  
      
      /*
    printf("n_relato  %d\n",n_relatorio);
    printf("local_relato  %s\n",local_relatorio);
    printf("qt_col_campoo  %d\n",qt_col_campo);
    printf("qt_lin_campoo  %d\n",qt_lin_campo);
    printf("cor_r_campo  %d\n",cor_r_campo);
    printf("cor_g_campo  %d\n",cor_g_campo);
    printf("cor_b_campo  %d\n",cor_b_campo);
  
    printf("qt_presa_m  %d\n",qt_presa_m);
    printf("idade_media_presa  %d\n",idade_media_presa);
    printf("var %d", var_idade_media_presa);
    printf("idade_media_predador  %d\n",idade_media_predador);
    printf("var %d", var_idade_media_predador);
    
    
    
    printf("campo visao  %d", campo_max_visao_presa);    
    printf("fator d m ps  %d\n", fator_delay_max_presa);    
    */
        
        
        

    if (strcmp(atributo,"qt_col_campo")==0)
	   return qt_col_campo;
    if (strcmp(atributo,"qt_lin_campo")==0)
	   return qt_lin_campo;
    if (strcmp(atributo,"cor_r_campo")==0)
	   return cor_r_campo;
    if (strcmp(atributo,"cor_g_campo")==0)
	   return cor_g_campo;
    if (strcmp(atributo,"cor_b_campo")==0)
	   return cor_b_campo;
    if (strcmp(atributo,"qt_presa_m")==0)
	   return qt_presa_m;
    if (strcmp(atributo,"qt_presa_f")==0)
	   return qt_presa_f;
    if (strcmp(atributo,"qt_predador_m")==0)
	   return qt_predador_m;
    if (strcmp(atributo,"qt_predador_f")==0)
	   return qt_predador_f;
    if (strcmp(atributo,"tamanho_presa")==0)
	   return tamanho_presa;
	if (strcmp(atributo,"tamanho_predador")==0)
	   return tamanho_predador;
    if (strcmp(atributo,"idade_media_presa_m")==0)
	   return idade_media_presa_m;
    if (strcmp(atributo,"var_idade_media_presa_m")==0)
	   return var_idade_media_presa_m;
    if (strcmp(atributo,"idade_media_presa_f")==0)
	   return idade_media_presa_f;
    if (strcmp(atributo,"var_idade_media_presa_f")==0)
	   return var_idade_media_presa_f;
    if (strcmp(atributo,"idade_media_predador_m")==0)
	   return idade_media_predador_m;
    if (strcmp(atributo,"var_idade_media_predador_m")==0)
	   return var_idade_media_predador_m;
    if (strcmp(atributo,"idade_media_predador_f")==0)
	   return idade_media_predador_f;
    if (strcmp(atributo,"var_idade_media_predador_f")==0)
	   return var_idade_media_predador_f;
    if (strcmp(atributo,"area_interesse_presa")==0)
	   return area_interesse_presa;
    if (strcmp(atributo,"var_area_interesse_presa")==0)
	   return var_area_interesse_presa;
    if (strcmp(atributo,"area_interesse_predador")==0)
	   return area_interesse_predador;
    if (strcmp(atributo,"var_area_interesse_predador")==0)
	   return var_area_interesse_predador;
    if (strcmp(atributo,"tempo_gest_presa")==0)
	   return tempo_gest_presa;
    if (strcmp(atributo,"tempo_gest_predador")==0)
	   return tempo_gest_predador;
    if (strcmp(atributo,"tempo_resg_presa")==0)
	   return tempo_resg_presa;
    if (strcmp(atributo,"tempo_resg_predador")==0)
	   return tempo_resg_predador;
    if (strcmp(atributo,"campo_max_visao_presa")==0)
	   return campo_max_visao_presa;
    if (strcmp(atributo,"campo_max_visao_predador")==0)
	   return campo_max_visao_predador;
	if (strcmp(atributo,"campo_max_visao_rep_presa")==0)
	   return campo_max_visao_rep_presa;
	if (strcmp(atributo,"var_campo_max_visao_rep_presa")==0)
	   return var_campo_max_visao_rep_presa;   
    if (strcmp(atributo,"campo_max_visao_rep_predador")==0)
	   return campo_max_visao_rep_predador;
	if (strcmp(atributo,"var_campo_max_visao_rep_predador")==0)
	   return var_campo_max_visao_rep_predador;
	if (strcmp(atributo,"fator_delay_max_presa")==0)
	   return fator_delay_max_presa;
	if (strcmp(atributo,"fator_delay_max_predador")==0)
	   return fator_delay_max_predador;
   	if (strcmp(atributo,"tempo_saciedade_fome")==0)
	   return tempo_saciedade_fome;
   	if (strcmp(atributo,"tempo_fome")==0)
	   return tempo_fome;
	if (strcmp(atributo,"tempo_saciedade_sede")==0)
	   return tempo_saciedade_sede;
   	if (strcmp(atributo,"tempo_sede")==0)
	   return tempo_sede;
   	if (strcmp(atributo,"nivel_perseguicao")==0)
	   return nivel_perseguicao;
	if (strcmp(atributo,"variacao_cor_campo")==0)
	   return variacao_cor_campo;
	if (strcmp(atributo,"tempo_variacao_cor_campo")==0)
	   return tempo_variacao_cor_campo;         
	if (strcmp(atributo,"cor_r_campo_min")==0)
	   return cor_r_campo_min;
	if (strcmp(atributo,"cor_r_campo_max")==0)
	   return cor_r_campo_max;
	if (strcmp(atributo,"cor_g_campo_min")==0)
	   return cor_g_campo_min;
	if (strcmp(atributo,"cor_g_campo_max")==0)
	   return cor_g_campo_max;	
    if (strcmp(atributo,"cor_b_campo_min")==0)
	   return cor_b_campo_min;
	if (strcmp(atributo,"cor_b_campo_max")==0)
	   return cor_b_campo_max;
    if (strcmp(atributo,"cor_r_planta")==0)
	   return cor_r_planta;
	if (strcmp(atributo,"cor_b_planta")==0)
	   return cor_b_planta;
	if (strcmp(atributo,"cor_g_planta")==0)
	   return cor_g_planta;
	if (strcmp(atributo,"qt_planta_p")==0)
	   return qt_planta_p;
	if (strcmp(atributo,"qt_planta_g")==0)
	   return qt_planta_g;
	if (strcmp(atributo,"tempo_morte_planta")==0)
	   return tempo_morte_planta;
  	if (strcmp(atributo,"intensidade_doenca_presa")==0)
	   return intensidade_doenca_presa;
	if (strcmp(atributo,"vida_doenca_presa")==0)
	   return vida_doenca_presa;
   	if (strcmp(atributo,"intensidade_doenca_predador")==0)
	   return intensidade_doenca_predador;
    if (strcmp(atributo,"vida_doenca_predador")==0)
	   return vida_doenca_predador;
   	if (strcmp(atributo,"intensidade_mutacao_presa")==0)
	   return intensidade_mutacao_presa;
   	if (strcmp(atributo,"intensidade_mutacao_predador")==0)
	   return intensidade_mutacao_predador;   
	if (strcmp(atributo,"cor_r_lago")==0)
	   return cor_r_lago;
	if (strcmp(atributo,"cor_b_lago")==0)
	   return cor_b_lago;
	if (strcmp(atributo,"cor_g_lago")==0)
	   return cor_g_lago;
	if (strcmp(atributo,"qt_lago")==0)
	   return qt_lago;
	if (strcmp(atributo,"tam_min_lago")==0)
	   return tam_min_lago;
	if (strcmp(atributo,"tam_max_lago")==0)
	   return tam_max_lago;
	if (strcmp(atributo,"tempo_oscilacao_lago")==0)
	   return tempo_oscilacao_lago;
	if (strcmp(atributo,"mod_mutacao_cor")==0)
	   return mod_mutacao_cor;
	if (strcmp(atributo,"mod_doenca")==0)
	   return mod_doenca;
	if (strcmp(atributo,"mod_sede")==0)
	   return mod_sede;
	if (strcmp(atributo,"mod_lago")==0)
	   return mod_lago;
	if (strcmp(atributo,"mod_fome_presa")==0)
	   return mod_fome_presa;
	if (strcmp(atributo,"mod_planta")==0)
	   return mod_planta;
	if (strcmp(atributo,"mod_fuga_presa")==0)
	   return mod_fuga_presa;
	if (strcmp(atributo,"mod_mudanca_cor_ambiente")==0)
	   return mod_mudanca_cor_ambiente;
	if (strcmp(atributo,"mod_predador_camuflagem")==0)
	   return mod_predador_camuflagem;


    printf("\a\n # O atributo %s nao foi encontrado no arquivo INFO! \a\n\n\n\n\n\n\n ",atributo);
    //delay(1100);
    return -1;
}
   




int cria_relatorio(char *argv[], char *nome[], FILE *arq){
     
        char string[10];  //vetor de char  p auxiliar nas conversoes de itoa p guardar no relatorio
        int i;
        char c;
    
        //*******************  ARQUIVO INFO_R  ********************
	 int n_relatorio;
	 char local_relatorio[250]; //n_relatorio2 pra conversao do n_relatorio pra string 

     char fim='\0';

             //gera o endereco p relatorio
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
	 
	 
	 FILE *f;
	 f=fopen("info_r","r");
	     fscanf(f,"%d\n",&n_relatorio);
	     for(i=0;;i++){
            fscanf(f,"%c",&c);
            if(c=='\n')
               break; 
           }

         fscanf(f,"%c",&fim);
	 fclose(f);
	 
	 if(fim != '#'){
       printf("\a\n WARNING: End of file INFO_R was not confirmed    (end= %c)\n\n ",fim);
       //delay(1100);
      }
      
     itoa(n_relatorio,string,10);//pega o num n_relatorio e converte pra string
  	 strcat(local_relatorio,*nome);
  	 strcat(local_relatorio,"_");
	 strcat(local_relatorio,string);
   	 strcat(local_relatorio,".txt");
	
	 f=fopen("info_r","w");     //***********************************************************************
	     fprintf(f,"%d\n",n_relatorio+1);
	     fprintf(f,"%s\n",local_relatorio);

         fprintf(f,"#");
         
     fclose(f);
	 
     arq = fopen(local_relatorio,"w");    
            //cria o relatorio atual e insere o comando # significando seu fim
	 //f=fopen(local_relatorio,"w");
	 //    fprintf(f,"\n#");
	 //fclose(f);
	 
	 
     return n_relatorio;
 }
 
 

	
void escreve_relatorio(char s[200],FILE *arq){
   
   //FILE *f;
   //f = arq;
   //fprintf(f,"%s",s);
   fprintf(arq,"%s",s);
   
   /*
   FILE *f1,*f2;
	char carac;
   char local_1[150],local_2[150];  //local1 do relatorio atual, local2 da pasta relatorios (arq copinadoinformacoes)
   char n_relatorio[5];  //num do relat atual
   char fim='\0';
   
           //le as informacoes do arq INFO
	f1= fopen("info_r","r");
		 fscanf(f1,"%s\n",&n_relatorio);
		 for(int i=0;;i++){
			 fscanf(f1,"%c",&carac);
			 if(carac == '\n'){ 
				 local_1[i]='\0';
			    break; }
			 local_1[i]= carac;
			 local_2[i]= carac;
			}
          fscanf(f1,"%c",&fim);
	fclose(f1);
	 
	 if(fim != '#'){
       printf("\a\n ATENCAO: Nao foi confirmado o fim do arq INFO_R    (fim= %c)\n\n ",fim);
       delay(1100);
      }    	
	
	   //arq2
	for(int i= strlen(local_2)-1; i>=0; i--){
		 if(local_2[i] == '/')
		    break;   
		 local_2[i]= '\0';	 	
		}
	strcat(local_2,"Copiando_informacoes...");
	
	
	                 //guarda as informacoes no arq auxiliar 'COpiando_informacoes...'	
   f1= fopen(local_1,"r");
		 f2= fopen(local_2,"w");
			  for(;;){
			     fscanf(f1,"%c",&carac);	
				  if (carac == '#'){
      			  fprintf(f2,"%s#",s);
					  break;
					 }	 		     	 
				  fprintf(f2,"%c",carac);   
				 }  //le um novo caractere enquanto o comando § nao for encontrado 
	    fclose(f2);	   
   fclose (f1);
   
	                    //guarda as informacoes que estavam no arq auxiliar 'Cpiando_informacoes.txt' no Relatorio	, gravando a informacao mandada
	f1= fopen(local_2,"r");
       f2= fopen(local_1,"w");
			  do{
			     fscanf(f1,"%c",&carac);		 
				  fprintf(f2,"%c",carac);   
				 }while(carac != '#');  //le um novo caractere enquanto o comando § nao for encontrado   
	    fclose(f2);	   
   fclose (f1);
	
	remove(local_2);	
	*/
}



void salva_relatorio(FILE *arq){
  
  fclose(arq); 
       
     
     

}

#endif