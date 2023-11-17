#ifndef OMAACS_STATE_H
#define OMAACS_STATE_H

#include <stdio.h>
#include <stdlib.h>

#include "../OrbitalMechanics/orbital_mechanics.h"

void save_state(char *filename, CartesianElements *state, double t){
  FILE* outputf = fopen(filename, "w");

  fprintf(outputf, "x: %Lf\n", state->r.x);
  fprintf(outputf, "y: %Lf\n", state->r.y);
  fprintf(outputf, "z: %Lf\n", state->r.z);
  fprintf(outputf, "vx: %Lf\n", state->v.x);
  fprintf(outputf, "vy: %Lf\n", state->v.y);
  fprintf(outputf, "vz: %Lf\n", state->v.z);
  fprintf(outputf, "t: %f\n", t);

  fclose(outputf);
}

CartesianElements read_state(char * filename){
  FILE* infile = fopen(filename, "r");
  CartesianElements state;
  if (infile == NULL){
    printf("Error opening file %s\n", filename);
    exit(1);
  }
  fscanf(infile, "x: %Lf\n", &state.r.x);
  fscanf(infile, "y: %Lf\n", &state.r.y);
  fscanf(infile, "z: %Lf\n", &state.r.z);
  fscanf(infile, "vx: %Lf\n", &state.v.x);
  fscanf(infile, "vy: %Lf\n", &state.v.y);
  fscanf(infile, "vz: %Lf\n", &state.v.z);

  fclose(infile);
  return state;
}

CartesianElements input_state(){
  CartesianElements state;
  printf("Enter x: ");
  scanf("%Lf", &state.r.x);
  printf("Enter y: ");
  scanf("%Lf", &state.r.y);
  printf("Enter z: ");
  scanf("%Lf", &state.r.z);
  printf("Enter vx: ");
  scanf("%Lf", &state.v.x);
  printf("Enter vy: ");
  scanf("%Lf", &state.v.y);
  printf("Enter vz: ");
  scanf("%Lf", &state.v.z);
  return state;
}

void edit_state(char * filename){
  
  CartesianElements state = read_state(filename);
  while(1){
    printf("Current state:\n");
    printf("(1) x: %Lf\n", state.r.x);
    printf("(2) y: %Lf\n", state.r.y);
    printf("(3) z: %Lf\n", state.r.z);
    printf("(4) vx: %Lf\n", state.v.x);
    printf("(5) vy: %Lf\n", state.v.y);
    printf("(6) vz: %Lf\n", state.v.z);
    printf("Enter index to edit (0 to exit):\n");
    int index;
    scanf("%d", &index);
    printf("Enter new value:\n");
    long double new_value;
    scanf("%Lf", &new_value);
    switch (index){
      case 0:
        save_state(filename, &state, 0);
        return;
      case 1:
        state.r.x = new_value;
        break;
      case 2:
        state.r.y = new_value;
        break;
      case 3:
        state.r.z = new_value;
        break;
      case 4:
        state.v.x = new_value;
        break;
      case 5:
        state.v.y = new_value;
        break;
      case 6:
        state.v.z = new_value;
        break;
      default:
        printf("Invalid index\n");
    }
  }
}

#endif // OMAACS_STATE_H