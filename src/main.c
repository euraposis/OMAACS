#include <stdio.h>
#include <string.h>
#include "Interface/configurator.h"
#include "Interface/state.h"

#include "Interface/main_menu.h"


int main(int argc, char *argv[])
{
    printf("Orbital Mechanics and Attitude Control Simulator\n");


    printf("Welcome to OMAACS!\n");
    char project_folder[100];
    if (argc == 2) {
        strcpy(project_folder, argv[1]);
        printf("Project folder: %s\n", project_folder);
    }else{
        printf("No project folder specified.\n");
        exit(1);
    }

    main_menu(project_folder);
    
    return 0;
}