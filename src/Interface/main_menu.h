#ifndef OMAACS_MAIN_MENU_H
#define OMAACS_MAIN_MENU_H

#include <stdio.h>
#include <stdlib.h>

#include "configurator.h"
#include "orbital.h"
#include "state.h"
#include "timeseries.h"

#include <unistd.h>


void printoptions(){
    printf("1 Edit Init State\n");
    printf("2 Edit Simulation settings\n");
    printf("3 Edit Output settings\n");
    printf("3 Run Simulator\n");
    printf("4 Do Keplerian Analysis\n");
    printf("5 Plot Results\n");
    printf("E END\n");
    return;
}

void main_menu(char *project_path){
    printf("OMAACS Main Menu\n");

    // checl if there is a project file

    OMAACS_CONFIGURATION config;


    strcpy(config.project_path, project_path);

    char config_filename[100];
    sprintf(config_filename, "%s/project.conf", project_path);    
    if (access(config_filename, F_OK) != -1){
        printf("Found Config\n");
        OMAACS_read_config_file(config_filename, &config);

        printf("Project %s\n\n\n", config.project_name);
    } else {
        printf("could not find config file\n\n Do you want to create a new project? (y/n)\n");
        char answer;
        scanf("%c", &answer);
        if (answer == 'y'){
            printf("Creating new project\n");
            input_config(&config);
        } else {
            printf("Exiting\n");
            exit(0);
        }
    }

    print_config(&config);

    printoptions();
    char option[10];
    scanf("%s", option);
    while (option[0] != 'E'){
        switch ((int)option[0]){
            case '1':
                {
                    if (strcmp(config.init_state_file_name, "NULL") == 0){
                        printf("No Init State File\n");
                        printf("do you want to create one? (y/n)\n");
                        char answer[100];
                        scanf("%s", answer);
                        if (answer[0] == 'y'){
                            printf("Creating new init state file\n");
                            char init_state_filename[50];
                            printf("input init state file name\n");
                            scanf("%s", init_state_filename);
                            CartesianElements state = input_state();
                            char inti_state_path[100];
                            sprintf(inti_state_path, "%s/%s", project_path, init_state_filename);
                            save_state(init_state_filename, &state, 0);
                            strcpy(config.init_state_file_name, init_state_filename);
                        } else {
                            printf("Exiting\n");
                            return;
                        }
                        break;
                    } else {
                      edit_state(config.init_state_file_name);
                    }
                    
                }
                break;
              case '4':
                {
                  if (strcmp(config.init_state_file_name, "NULL") == 0){
                    printf("No Init State File\n");
                    break;
                  }
                  CartesianElements state = read_state(config.init_state_file_name);
                  KeplerianElements kepler = ORBITLA_calculate_kepler_from_cartesian(&state, &Earth);
                  ORBITLA_save_kepler(&kepler, &config);
                }
                break;
              default:
                printf("Invalid Option\n");
                break;
          
        }
        printoptions();
        printf("\n");
        scanf("%s", option);
        printf("option: %i\n", (int)option[0]);
    }
  
    safe_config(config_filename, &config);
    return;


}


#endif // OMAACS_MAIN_MENU_H