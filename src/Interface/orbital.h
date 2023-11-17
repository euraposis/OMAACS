#ifndef INTERFACE_ORBITAL_H
#define INTERFACE_ORBITAL_H

#include <stdio.h>
#include <stdlib.h>

#include "configurator.h"

#include "../OrbitalMechanics/orbital_mechanics.h"

KeplerianElements ORBITLA_calculate_kepler_from_cartesian(const CartesianElements *state, const Body *orbiting_body){
    KeplerianElements kepler = keplerian_elements_from_cartesian_elements(*state, orbiting_body);
    print_kepler(&kepler, 1, 1);
    return kepler;
}

void ORBITLA_save_kepler(KeplerianElements *state, OMAACS_CONFIGURATION *config){
    char filename[50];
    printf("Enter filename: ");
    scanf("%s", filename);
    strcpy(config->kepler_file_name, filename);

    char filepath[100];
    sprintf(filepath, "%s/%s", config->project_path, filename);
    
    FILE* outputf = fopen(filepath, "w");


    fprintf(outputf, "semi_major_axis: %Lf\n", state->semi_major_axis);
    fprintf(outputf, "eccentricity: %Lf\n", state->eccentricity);
    fprintf(outputf, "inclination: %Lf\n", state->inclination);
    fprintf(outputf, "longitude_asc_node: %Lf\n", state->longitude_asc_node);
    fprintf(outputf, "arg_periapsis: %Lf\n", state->arg_periapsis);
    fprintf(outputf, "true_anomaly: %Lf\n", state->true_anomaly);

    fclose(outputf);
}

#endif // INTERFACE_ORBITAL_H