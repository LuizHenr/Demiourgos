#ifndef FUNC_ARQ_H
#define FUNC_ARQ_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>


struct Configurations{
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
	int tempo_fim_simulacao;
	int populacao_fim_simulacao;
	int interface_grafica;
	int barra_descricao;
	int descricao_console;
	int captura_tela_simulacao;
	int captura_tela_fim_inicio;
	int borda;
	int contador_relatorio;
};

typedef struct Configurations Config;

void reads_configurations();
void reads_old_cfg_file();
void reads_new_cfg_file();
int valor_config(char *, char *);

int cria_relatorio(FILE *arq);  //returns number of current report
void escreve_relatorio(char s[200], FILE *arq);
void salva_relatorio(FILE *arq);

#endif