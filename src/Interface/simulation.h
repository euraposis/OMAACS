#ifndef OMAACS_SIMULATION_INTERFACE_H
#define OMAACS_SIMULATION_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double initial_time;
    double final_time;
    double step_size;
    double initial_value;
} OMAACS_Simulation_Parameters;

void save_simulation_parameters(char *filename, OMAACS_Simulation_Parameters *parameters){
    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "%lf\n", parameters->initial_time);
    fprintf(file, "%lf\n", parameters->final_time);
    fprintf(file, "%lf\n", parameters->step_size);
    fprintf(file, "%lf\n", parameters->initial_value);
    fclose(file);
}

OMAACS_Simulation_Parameters read_simulaion_parameters(char *filename){
    OMAACS_Simulation_Parameters parameters;
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    fscanf(file, "%lf", &parameters.initial_time);
    fscanf(file, "%lf", &parameters.final_time);
    fscanf(file, "%lf", &parameters.step_size);
    fscanf(file, "%lf", &parameters.initial_value);
    fclose(file);
    return parameters;
}





#endif