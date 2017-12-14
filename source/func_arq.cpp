
#ifndef FUNC_ARQ_C
#define FUNC_ARQ_C

#include <func_arq.h>  

Config cfg;  //This object stores all configurations read from the file "parameters.cfg" 

void reads_configurations()  //reads all configurations from file
{
	FILE *f;
	int info = 0, demiourgos = 0; //check if the files "info.cfg" and "parameters.cfg" exist

	f = fopen("parameters.cfg", "r");
	if (f != NULL)
	{
		demiourgos = 1;
		fclose(f);
	}
	
	f = fopen("info.cfg", "r");
	if (f != NULL)
	{
		info = 1;
		fclose(f);
	}
	
	if (demiourgos == 0 && info == 0)  //No configuration file found, search for them inside bin folder
	{
		f = fopen("bin\\parameters.cfg", "r");
		if (f != NULL)
		{
			demiourgos = 1;
			fclose(f);
		}

		f = fopen("bin\\info.cfg", "r");
		if (f != NULL)
		{
			info = 1;
			fclose(f);
		}

		if (demiourgos == 0 && info == 0)  // No configuration file found inside bin folder 
		{
			printf("Error: Neither \"info.cfg\" nor \"parameters.cfg\" configuration file was found.\n");
			getchar();

			printf("The program will now terminate");
			for (int i = 0; i < 3; i++)
			{
				_sleep(1000);
				printf(".");
			}
			exit(1);
		}
		else if (demiourgos == 1 && info == 1) // Two configuration files were found inside bin folder
		{
			printf("Warning: \"bin\\info.cfg\" and \"bin\\parameters.cfg\" configuration file were found.\n");
			printf("The configurations are being read from \"bin\\parameters.cfg\" file.\n\n");
			reads_new_cfg_file();
		}
		else if (demiourgos == 1) //Only "bin\\parameters.cfg" configuration file
		{
			printf("The configurations are being read from \"bin\\parameters.cfg\" file.\n\n");
			reads_new_cfg_file();
		}
		else{  //Only "bin\\info.cfg" configuration file
			printf("The configurations are being read from \"bin\\info.cfg\" file.\n\n");
			reads_old_cfg_file();
		}

	}
	else if (demiourgos == 1 && info == 1) // Two configuration files were found
	{
		printf("Warning: \"info.cfg\" and \"parameters.cfg\" configuration file were found.\n");
		printf("The configurations are being read from \"parameters.cfg\" file.\n\n");
		reads_new_cfg_file();
	}
	else if (demiourgos == 1) //Only "parameters.cfg" configuration file
	{
		printf("The configurations are being read from \"parameters.cfg\" file.\n\n");
		reads_new_cfg_file();
	}
	else{  //Only "info.cfg" configuration file
		printf("The configurations are being read from \"info.cfg\" file.\n\n");
		reads_old_cfg_file();
	}

}

void reads_old_cfg_file()
{
	FILE *f;
	char fim;

	f = fopen("info.cfg", "r");
	if (f == NULL)
	{
		f = fopen("bin\\info.cfg", "r");
		if (f == NULL)
		{
			printf("Error:  \"info.cfg\" configuration file was not found.\n");
			getchar();

			printf("The program will now terminate");
			for (int i = 0; i < 3; i++)
			{
				_sleep(1000);
				printf(".");
			}
			exit(1);
		}
	}
	fscanf(f, "%d\n%d\n", &cfg.qt_col_campo, &cfg.qt_lin_campo);
	fscanf(f, "%d\n%d\n%d\n", &cfg.cor_r_campo, &cfg.cor_g_campo, &cfg.cor_b_campo);
	fscanf(f, "%d\n%d\n", &cfg.qt_presa_m, &cfg.qt_presa_f);
	fscanf(f, "%d\n%d\n", &cfg.qt_predador_m, &cfg.qt_predador_f);
	fscanf(f, "%d\n%d\n", &cfg.tamanho_presa, &cfg.tamanho_predador);
	fscanf(f, "%d\n%d\n", &cfg.idade_media_presa_m, &cfg.var_idade_media_presa_m);
	fscanf(f, "%d\n%d\n", &cfg.idade_media_presa_f, &cfg.var_idade_media_presa_f);
	fscanf(f, "%d\n%d\n", &cfg.idade_media_predador_m, &cfg.var_idade_media_predador_m);
	fscanf(f, "%d\n%d\n", &cfg.idade_media_predador_f, &cfg.var_idade_media_predador_f);
	fscanf(f, "%d\n%d\n", &cfg.area_interesse_presa, &cfg.var_area_interesse_presa);
	fscanf(f, "%d\n%d\n", &cfg.area_interesse_predador, &cfg.var_area_interesse_predador);
	fscanf(f, "%d\n%d\n", &cfg.tempo_gest_presa, &cfg.tempo_gest_predador);
	fscanf(f, "%d\n%d\n", &cfg.tempo_resg_presa, &cfg.tempo_resg_predador);
	fscanf(f, "%d\n%d\n", &cfg.campo_max_visao_presa, &cfg.campo_max_visao_predador);
	fscanf(f, "%d\n%d\n", &cfg.campo_max_visao_rep_presa, &cfg.var_campo_max_visao_rep_presa);
	fscanf(f, "%d\n%d\n", &cfg.campo_max_visao_rep_predador, &cfg.var_campo_max_visao_rep_predador);
	fscanf(f, "%d\n%d\n", &cfg.fator_delay_max_presa, &cfg.fator_delay_max_predador);
	fscanf(f, "%d\n%d\n", &cfg.tempo_saciedade_fome, &cfg.tempo_fome);
	fscanf(f, "%d\n%d\n", &cfg.tempo_saciedade_sede, &cfg.tempo_sede);
	fscanf(f, "%d\n", &cfg.nivel_perseguicao);
	fscanf(f, "%d\n%d\n", &cfg.variacao_cor_campo, &cfg.tempo_variacao_cor_campo);
	fscanf(f, "%d\n%d\n", &cfg.cor_r_campo_min, &cfg.cor_r_campo_max);
	fscanf(f, "%d\n%d\n", &cfg.cor_g_campo_min, &cfg.cor_g_campo_max);
	fscanf(f, "%d\n%d\n", &cfg.cor_b_campo_min, &cfg.cor_b_campo_max);
	fscanf(f, "%d\n%d\n%d\n", &cfg.cor_r_planta, &cfg.cor_g_planta, &cfg.cor_b_planta);
	fscanf(f, "%d\n%d\n", &cfg.qt_planta_p, &cfg.qt_planta_g);
	fscanf(f, "%d\n", &cfg.tempo_morte_planta);
	fscanf(f, "%d\n%d\n", &cfg.intensidade_doenca_presa, &cfg.vida_doenca_presa);
	fscanf(f, "%d\n%d\n", &cfg.intensidade_doenca_predador, &cfg.vida_doenca_predador);
	fscanf(f, "%d\n%d\n", &cfg.intensidade_mutacao_presa, &cfg.intensidade_mutacao_predador);
	fscanf(f, "%d\n%d\n%d\n", &cfg.cor_r_lago, &cfg.cor_g_lago, &cfg.cor_b_lago);
	fscanf(f, "%d\n%d\n%d\n", &cfg.qt_lago, &cfg.tam_min_lago, &cfg.tam_max_lago);
	fscanf(f, "%d\n", &cfg.tempo_oscilacao_lago);
	fscanf(f, "%d\n", &cfg.mod_mutacao_cor);
	fscanf(f, "%d\n", &cfg.mod_doenca);
	fscanf(f, "%d\n", &cfg.mod_sede);
	fscanf(f, "%d\n", &cfg.mod_lago);
	fscanf(f, "%d\n", &cfg.mod_fome_presa);
	fscanf(f, "%d\n", &cfg.mod_planta);
	fscanf(f, "%d\n", &cfg.mod_fuga_presa);
	fscanf(f, "%d\n", &cfg.mod_mudanca_cor_ambiente);
	fscanf(f, "%d\n", &cfg.mod_predador_camuflagem);


	fscanf(f, "%c", &fim);
	fclose(f);

	if (fim != '#'){
		printf("Warning: The end of \"info.cfg\" configuration file was not confirmed (final char= %c). \n",fim);
		_sleep(1100);
		//return -1;       
	}

}

void reads_new_cfg_file()
{

	FILE *f;
	char line[500];
	char com[100],value[1000];
	int i, j;

	f = fopen("parameters.cfg", "r");
	if (f == NULL)
	{
		f = fopen("bin\\parameters.cfg", "r");
		if (f == NULL)
		{
			printf("Error:  \"parameters.cfg\" configuration file was not found.\n");
			getchar();

			printf("The program will now terminate");
			for (int i = 0; i < 3; i++)
			{
				_sleep(1000);
				printf(".");
			}
			exit(1);
		}
	}


	while (!feof(f))   //while it does not reach the end of file
	{
		for (i = 0; i<500; i++)
		{
			line[i] = '\0';
		}
		fgets(line, 500, f);  // reads a line
		
		for (i = 0; i<strlen(line); i++) // remove all spaces and tabs from read line
		{
			if (line[i] == 32 || line[i] == 9)
			{
				for (j = i; j<strlen(line) - 1; j++)
				{
					line[j] = line[j + 1];
				}
				line[j] = '\0';
				i--;
			}
		}

		if (line[0] != '%' && line[0] != 13 && line[0] != 10 && line[0] != 0)  // ignore comment and empty lines
		{
			for (i = 0; i<100; i++)
			{
				com[i] = '\0';
				value[i] = '\0';
			}
			i = 0;  // 0 - command        1 - value
			
			for (j = 0; j<strlen(line); j++) // separate command and its value from line
			{
				if (line[j] == '%' || line[j] == 13) // break if a comment or end of line is reached
				{
					break;
				}
				if (line[j] == '=')
				{
					i = j +1; 
				}
				else
				{
					if (i == 0)
					{
						com[j] = line[j];
					}
					else
					{
						value[j - i] = line[j];
					}
				}
			}
			if (valor_config(com, value) == 1) //set the value to config struct 
			{
				printf("Warning: The command \"%s\" which value is \"%s\" was not recognized.\n",com,value);
				_sleep(1100);
			}
		}

	}
	fclose(f);
}

int valor_config(char *com, char *value) // Set values to configuration struct
{
	char atributo[100], valor[100];
	int i;

	for (i = 0; i < strlen(com); i++)
	{
		atributo[i] = toupper(com[i]);
	}
	atributo[i] = '\0';
	for (i = 0; i < strlen(value); i++)
	{
		valor[i] = toupper(value[i]);
	}
	valor[i] = '\0';

	// Environment configurations

	if (strcmp(atributo, "ENVIRONMENT_WIDTH") == 0)
	{
		cfg.qt_col_campo = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_HEIGHT") == 0)
	{
		cfg.qt_lin_campo = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_COLOR_VAR_LEVEL") == 0)
	{
		cfg.variacao_cor_campo = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_COLOR_VAR_TIME") == 0)
	{
		cfg.tempo_variacao_cor_campo = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_MIN_VAR_COLOR_R") == 0)
	{
		cfg.cor_r_campo_min = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_MAX_VAR_COLOR_R") == 0)
	{
		cfg.cor_r_campo_max = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_MIN_VAR_COLOR_G") == 0)
	{
		cfg.cor_g_campo_min = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_MAX_VAR_COLOR_G") == 0)
	{
		cfg.cor_g_campo_max = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_MIN_VAR_COLOR_B") == 0)
	{
		cfg.cor_b_campo_min = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "ENVIRONMENT_MAX_VAR_COLOR_B") == 0)
	{
		cfg.cor_b_campo_max = atoi(valor);
		return 0;
	}


	// Preys and Predators configurations

	if (strcmp(atributo, "PREY_SIZE") == 0)
	{
		cfg.tamanho_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_SIZE") == 0)
	{
		cfg.tamanho_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_MALE_LIFE_EXPECTANCY") == 0)
	{
		cfg.idade_media_presa_m = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_MALE_LIFE_EXPECTANCY_VAR") == 0)
	{
		cfg.var_idade_media_presa_m = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_FEMALE_LIFE_EXPECTANCY") == 0)
	{
		cfg.idade_media_presa_f = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_FEMALE_LIFE_EXPECTANCY_VAR") == 0)
	{
		cfg.var_idade_media_presa_f = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_MALE_LIFE_EXPECTANCY") == 0)
	{
		cfg.idade_media_predador_m = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_MALE_LIFE_EXPECTANCY_VAR") == 0)
	{
		cfg.var_idade_media_predador_m = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_FEMALE_LIFE_EXPECTANCY") == 0)
	{
		cfg.idade_media_predador_f = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_FEMALE_LIFE_EXPECTANCY_VAR") == 0)
	{
		cfg.var_idade_media_predador_f = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_DISPLACEMENT_AREA") == 0)
	{
		cfg.area_interesse_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_DISPLACEMENT_AREA_VAR") == 0)
	{
		cfg.var_area_interesse_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_DISPLACEMENT_AREA") == 0)
	{
		cfg.area_interesse_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_DISPLACEMENT_AREA_VAR") == 0)
	{
		cfg.var_area_interesse_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_GESTATION_PERIOD") == 0)
	{
		cfg.tempo_gest_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_GESTATION_PERIOD") == 0)
	{
		cfg.tempo_gest_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_POSTPARTUM_PERIOD") == 0)
	{
		cfg.tempo_resg_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_POSTPARTUM_PERIOD") == 0)
	{
		cfg.tempo_resg_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_MAX_VISUAL_FIELD") == 0)
	{
		cfg.campo_max_visao_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_MAX_VISUAL_FIELD") == 0)
	{
		cfg.campo_max_visao_predador = atoi(valor);
		return 0;
	}

	if (strcmp(atributo, "PREY_MAX_REPRODUCTION_VISUAL_FIELD") == 0)
	{
		cfg.campo_max_visao_rep_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_MAX_REPRODUCTION_VISUAL_FIELD_VAR") == 0)
	{
		cfg.var_campo_max_visao_rep_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_MAX_REPRODUCTION_VISUAL_FIELD") == 0)
	{
		cfg.campo_max_visao_rep_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_MAX_REPRODUCTION_VISUAL_FIELD_VAR") == 0)
	{
		cfg.var_campo_max_visao_rep_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_MAX_DELAY_FACTOR") == 0)
	{
		cfg.fator_delay_max_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_MAX_DELAY_FACTOR") == 0)
	{
		cfg.fator_delay_max_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "SATIETY_HUNGER_PERIOD") == 0)
	{
		cfg.tempo_saciedade_fome = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "HUNGER_PERIOD") == 0)
	{
		cfg.tempo_fome = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "SATIETY_THIRST_PERIOD") == 0)
	{
		cfg.tempo_saciedade_sede = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "THIRST_PERIOD") == 0)
	{
		cfg.tempo_sede = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PERSECUTION_LEVEL") == 0)
	{
		cfg.nivel_perseguicao = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_ILLNESS_INTENSITY") == 0)
	{
		cfg.intensidade_doenca_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_ILLNESS_LIFE_EXPECTANCY") == 0)
	{
		cfg.vida_doenca_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_ILLNESS_INTENSITY") == 0)
	{
		cfg.intensidade_doenca_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_ILLNESS_LIFE_EXPECTANCY") == 0)
	{
		cfg.vida_doenca_predador = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREY_MUTATION_INTENSITY") == 0)
	{
		cfg.intensidade_mutacao_presa = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PREDATOR_MUTATION_INTENSITY") == 0)
	{
		cfg.intensidade_mutacao_predador = atoi(valor);
		return 0;
	}


	// Plant configurations

	if (strcmp(atributo, "PLANT_COLOR_R") == 0)
	{
		cfg.cor_r_planta = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PLANT_COLOR_G") == 0)
	{
		cfg.cor_g_planta = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PLANT_COLOR_B") == 0)
	{
		cfg.cor_b_planta = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PLANT_NUMBER_MINOR") == 0)
	{
		cfg.qt_planta_p = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PLANT_NUMBER_MAJOR") == 0)
	{
		cfg.qt_planta_g = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "PLANT_REVIVAL_TIME") == 0)
	{
		cfg.tempo_morte_planta = atoi(valor);
		return 0;
	}


	// Lake configurations

	if (strcmp(atributo, "LAKE_COLOR_R") == 0)
	{
		cfg.cor_r_lago = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "LAKE_COLOR_G") == 0)
	{
		cfg.cor_g_lago = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "LAKE_COLOR_B") == 0)
	{
		cfg.cor_b_lago = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "LAKE_NUMBER") == 0)
	{
		cfg.qt_lago = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "LAKE_MIN_SIZE") == 0)
	{
		cfg.tam_min_lago = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "LAKE_MAX_SIZE") == 0)
	{
		cfg.tam_max_lago = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "LAKE_OSCILLATION_TIME") == 0)
	{
		cfg.tempo_oscilacao_lago = atoi(valor);
		return 0;
	}


	// Simulation Initialization

	if (strcmp(atributo, "INIT_PREY_MALE") == 0)
	{
		cfg.qt_presa_m = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "INIT_PREY_FEMALE") == 0)
	{
		cfg.qt_presa_f = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "INIT_PREDATOR_MALE") == 0)
	{
		cfg.qt_predador_m = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "INIT_PREDATOR_FEMALE") == 0)
	{
		cfg.qt_predador_f = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "INIT_ENVIRONMENT_COLOR_R") == 0)
	{
		cfg.cor_r_campo = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "INIT_ENVIRONMENT_COLOR_G") == 0)
	{
		cfg.cor_g_campo = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "INIT_ENVIRONMENT_COLOR_B") == 0)
	{
		cfg.cor_b_campo = atoi(valor);
		return 0;
	}


	// Modules configurations

	if (strcmp(atributo, "MODULE_MUTATION_COLOR") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_mutacao_cor = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_mutacao_cor = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n",valor,atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "MODULE_ILLNESS") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_doenca = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_doenca = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "MODULE_THIRST") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_sede = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_sede = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "MODULE_LAKE") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_lago = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_lago = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "MODULE_HUNGER_PREY") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_fome_presa = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_fome_presa = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "MODULE_PLANT") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_planta = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_planta = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "MODULE_ESCAPE_PREY") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_fuga_presa = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_fuga_presa = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "MODULE_VAR_COLOR_ENVIRONMENT") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_mudanca_cor_ambiente = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_mudanca_cor_ambiente = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "MODULE_CAMOUFLAGE_PREDATOR") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.mod_predador_camuflagem = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.mod_predador_camuflagem = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}


	// General configurations

	if (strcmp(atributo, "STOP_TIME") == 0)
	{
		cfg.tempo_fim_simulacao = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "STOP_POPULATION") == 0)
	{
		cfg.populacao_fim_simulacao = atoi(valor);
		return 0;
	}
	if (strcmp(atributo, "GHAPHIC_INTERFACE_ENABLED") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.interface_grafica = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.interface_grafica = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "DESCRIPTION_BAR_ENABLED") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.barra_descricao = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.barra_descricao = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "DESCRIPTION_IN_CONSOLE") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.descricao_console = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.descricao_console = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "SCREENSHOT_DURING_SIMULATION") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.captura_tela_simulacao = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.captura_tela_simulacao = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "SCREENSHOT_BEGIN_END") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.captura_tela_fim_inicio = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.captura_tela_fim_inicio = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "BORDER_ENABLED") == 0)
	{
		if (strcmp(valor, "YES") == 0)
		{
			cfg.borda = 1;
		}
		else if (strcmp(valor, "NO") == 0)
		{
			cfg.borda = 0;
		}
		else
		{
			printf("Warning: The value \"%s\" of command \"%s\" was not recognized.\n", valor, atributo);
			_sleep(1100);
		}
		return 0;
	}
	if (strcmp(atributo, "REPORT_COUNTER") == 0)
	{
		cfg.contador_relatorio = atoi(valor);
		return 0;
	}

	return 1;
}



int cria_relatorio(FILE *arq){
	FILE *f;
	char report_name[200];
	int report_counter = 0;
	struct stat info;  
	int ok = 0;  // ok = 0 Error      ok = 1 folder Reports      ok = 2 folder bin/Reports
	int report_number = 0;

	// check if Reports folder exists
	sprintf(report_name,"Reports");
	if (stat(report_name, &info) != 0) // if Reports folder does not exist
	{
		// check if bin\\Reports folder exists
		sprintf(report_name, "bin\\Reports");
		if (stat(report_name, &info) != 0) // if bin\\Reports folder does not exist, create it
		{
			printf("Warning: The \"Reports\" folder does not exist. It will be created.\n");
			_sleep(1100);
			// check if bin folder exists
			sprintf(report_name, "bin");
			if (stat(report_name, &info) != 0) // if bin folder does not exist
			{
				system("mkdir Reports");
				ok = 1;
			}
			else
			{
				system("mkdir bin\\Reports");
				ok = 2;
			}
		}
		else // if bin\\Reports folder exists
		{
			ok = 2;
		}

	}
	else // if Reports folder exists
	{
		ok = 1;
	}

	if (ok == 0)
	{
		printf("Error: Could not create Reports folder.\n");
		getchar();

		printf("The program will now terminate");
		for (int i = 0; i < 3; i++)
		{
			_sleep(1000);
			printf(".");
		}
		exit(1);
	}

	//define what is the report number
	while (true)
	{
		report_number++;
		if (ok == 1)
		{
			sprintf(report_name, "Reports\\Report_Regular_%d.m",report_number);
		}
		if (ok == 2)
		{
			sprintf(report_name, "bin\\Reports\\Report_Regular_%d.m", report_number);
		}
			
		f = fopen(report_name, "r");
		if (f == NULL) //report file does not exists
		{
			if (ok == 1)
			{
				sprintf(report_name, "Reports\\Report_Visual_%d", report_number);
			}
			if (ok == 2)
			{
				sprintf(report_name, "bin\\Reports\\Report_Visual_%d", report_number);
			}

			if (stat(report_name, &info) != 0) // Report Visual folder does not exist
			{
				// Ready for create a new report regular file and visual folder
				break;
			}
		}
		else
		{
			fclose(f);
		}

	}

	// create Report regular file
	if (ok == 1)
	{
		sprintf(report_name, "Reports\\Report_Regular_%d.m", report_number);
	}
	if (ok == 2)
	{
		sprintf(report_name, "bin\\Reports\\Report_Regular_%d.m", report_number);
	}

	f = fopen(report_name, "w");
	if (f == NULL) //report file could not be created
	{
		printf("Error: Could not create report regular file.\n");
		getchar();

		printf("The program will now terminate");
		for (int i = 0; i < 3; i++)
		{
			_sleep(1000);
			printf(".");
		}
		exit(1);
	}
	//fprintf(f, "#");  
	fclose(f);

	// create Report visual folder
	if (ok == 1)
	{
		sprintf(report_name, "mkdir Reports\\Report_Visual_%d", report_number);
	}
	if (ok == 2)
	{
		sprintf(report_name, "mkdir bin\\Reports\\Report_Visual_%d", report_number);
	}
	system(report_name);
	
	return report_number;
}




void escreve_relatorio(char s[200], FILE *arq){

	//FILE *f;
	//f = arq;
	//fprintf(f,"%s",s);
	fprintf(arq, "%s", s);

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


/*  --old fun arq file
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

	if (f == NULL)  // se nao encontrar o arquivo de config, procurar na subpasta bin  (resolve o problema de executar do explorer ou do VS)
	{
		f = fopen("bin\\info.cfg", "r");
		if (f == NULL)
		{
			printf("\a\n ERRO: Nao foi possivel encontrar o arq INFO\n\n ");
			//delay(1100);
			return -1;
		}
	}

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
    * /
        
        
        

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
	* /
}



void salva_relatorio(FILE *arq){
  
  fclose(arq); 
       
     
     

}


*/

#endif