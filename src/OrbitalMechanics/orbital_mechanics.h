#ifndef OMAACS_ORBITAL_MECHANICS_H
#define OMAACS_ORBITAL_MECHANICS_H

#include "../../libs/OMAACS_NUM/OMAACS_NUM/src/vector.h"

#include "math.h"

#define GAMMA 6.67430e-11

typedef struct Body
{
  vector_3 position;
  long double mass;
} Body;

static Body Earth = {.mass = 5.973e24};

typedef struct KeplerianElements
{
  double a; // semi-major axis
  double e; // eccentricity
  double i; // inclination
  double Omega; // longitude of the ascending node
  double omega; // argument of periapsis
  double nu; // true anomaly
} KeplerianElements;
  
typedef struct CartesianElements
{
  vector_3 r;
  vector_3 v;
} CartesianElements;

KeplerianElements keplerian_elements_from_cartesian_elements(CartesianElements state, Body* orbiting_body)
{
  printf("Calculate Keplarian Elemenets from catesian state\n");
  printf("position: (%Lf, %Lf, %Lf)\n", state.r.x, state.r.y, state.r.z);
  printf("velocity: (%Lf, %Lf, %Lf)\n", state.v.x, state.v.y, state.v.z);
  printf("calculate angular momentum\n");
  vector_3 specific_angular_momentum = vector_3_cross(state.r, state.v);
  printf("specific angular momentum: (%Lf, %Lf, %Lf)\n", specific_angular_momentum.x,\
    specific_angular_momentum.y,\
    specific_angular_momentum.z);

  long double gamma = GAMMA * orbiting_body->mass;

  printf("calculating specific energy\n");

  long double specific_energy = ((vector_3_dot(state.v, state.v))/2) - (gamma/vector_3_mag(state.r));

  printf("specific energy: %Lf\n", specific_energy);

  printf("calculating semi major axis\n");

  long double semi_major_axis = -gamma/(2*specific_energy);

  printf("semi major axis: %Lf\n", semi_major_axis);

  printf("calculating trayectory parameter\n");

  long double trayectory_parameter = pow(vector_3_mag(specific_angular_momentum), 2.0)/gamma;

  printf("trayectory parameter: %Lf\n", trayectory_parameter);

  printf("calculating excentricity\n");

  long double excentricity = sqrt(1 -  (pow(vector_3_mag(specific_angular_momentum), 2)/(gamma * semi_major_axis)));

  printf("excentricity: %Lf\n", excentricity);

  printf("calculating peri- and apoapsis\n");

  long double periapsis = semi_major_axis * (1 - excentricity);
  long double apoapsis = semi_major_axis * (1 + excentricity);

  printf("orbit from %Lf to %Lf\n", periapsis, apoapsis);

  printf("calculating periode\n");

  long double periode = 2 * M_PI * sqrt(pow(semi_major_axis, 3)/gamma);

  printf("periode: %Lf\n", periode/60);
  

  printf("calculating inclination\n");

  long double inclination = acos(specific_angular_momentum.z/vector_3_mag(specific_angular_momentum));

  printf("inclination: %Lf\n", inclination);

  printf("calculating longitude of the ascending node\n");

  vector_3 K = {.x = 0, .y = 0, .z = 1};
  vector_3 I = {.x = 1, .y = 0, .z = 0};

  long double longitude_of_the_ascending_node = acos(vector_3_dot(vector_3_cross(K, specific_angular_momentum), I)/vector_3_mag(vector_3_cross(K, specific_angular_momentum)));

  printf("longitude of the ascending node: %Lf\n", longitude_of_the_ascending_node);

  printf("eccentricity vector\n");
  
  vector_3 excentricity_vector = vector_3_sub(vector_3_scale(vector_3_cross(state.v, specific_angular_momentum), 1/gamma), vector_3_scale(state.r, 1/vector_3_mag(state.r)));

  printf("eccentricity vector: (%Lf, %Lf, %Lf)\n", excentricity_vector.x, excentricity_vector.y, excentricity_vector.z);

  printf("calculating argument of periapsis\n");

  long double argument_of_periapsis = acos(vector_3_dot(vector_3_cross(K, specific_angular_momentum), excentricity_vector)/(vector_3_mag(vector_3_cross(K, specific_angular_momentum))* vector_3_mag(excentricity_vector)));

  printf("argument of periapsis: %Lf\n", argument_of_periapsis);

  long double true_anomaly = acos(vector_3_dot(state.r, excentricity_vector)/(vector_3_mag(state.r) * vector_3_mag(excentricity_vector)));

  printf("true anomaly: %Lf\n", true_anomaly);
}

#endif