#ifndef OMAACS_CONFIGURATOR_H
#define OMAACS_CONFIGURATOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char project_name[50];
  char project_path[100];
  char init_state_file_name[50];
  char kepler_file_name[50];
} OMAACS_CONFIGURATION;

void OMAACS_read_config_file(char* config_file_name, OMAACS_CONFIGURATION* config){
  FILE* config_file = fopen(config_file_name, "r");
  if(config_file == NULL){
    printf("Error opening config file: %s\n", config_file_name);
    exit(1);
  }
  fscanf(config_file, "project: %s\n", config->project_name);
  fscanf(config_file, "init_state: %s\n", config->init_state_file_name);
  fscanf(config_file, "kepler: %s", config->kepler_file_name);
  fclose(config_file);
}

int safe_config(char* config_file_name, OMAACS_CONFIGURATION* config){
  FILE* config_file = fopen(config_file_name, "w");
  if(config_file == NULL){
    printf("Error opening config file: %s\n", config_file_name);
    return 1;
  }
  fprintf(config_file, "project: %s\n", config->project_name);
  fprintf(config_file, "init_state: %s\n", config->init_state_file_name);
  fprintf(config_file, "kepler: %s", config->kepler_file_name);
  fclose(config_file);
  return 0;
}

void print_config(OMAACS_CONFIGURATION* config){
  printf("project: %s\n", config->project_name);
  printf("init_state: %s\n", config->init_state_file_name);
  
}

void input_config(OMAACS_CONFIGURATION* config){
  printf("Enter project name: ");
  scanf("%s", config->project_name);
  printf("Enter initial state file name (NULL if not specifyed):");
  scanf("%s", config->init_state_file_name);
  printf("Enter kepler file name: (NULL if not specifyed)");
  scanf("%s", config->kepler_file_name);
}





#endif