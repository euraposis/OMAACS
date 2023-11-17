#ifndef OMAACS_ORBITAL_MECHANICS_H
#define OMAACS_ORBITAL_MECHANICS_H

#include "../../libs/OMAACS_NUM/OMAACS_NUM/src/vector.h"

#include "math.h"
#include <stdio.h>

#define GAMMA 6.67430e-11

#define IN_DEGREES (180/M_PI)
#define _KM * 1000

typedef struct Body
{
  vector_3 position;
  long double mass;
  long double gravitational_parameter;
} Body;

static Body Earth = {.mass = 5.973e24, .gravitational_parameter = 3.986004415e14};

typedef struct KeplerianElements
{
  long double semi_major_axis; // semi-major axis
  long double eccentricity; // eccentricity
  long double inclination; // inclination
  long double longitude_asc_node; // longitude of the ascending node
  long double arg_periapsis; // argument of periapsis
  long double true_anomaly; // true anomaly
} KeplerianElements;
  
typedef struct CartesianElements
{
  vector_3 r;
  vector_3 v;
} CartesianElements;


void print_kepler(KeplerianElements* elements, unsigned int in_deg, unsigned int in_km)
{
  
  printf("\n\n");
  printf("Keplerian Elements:\n");
  printf("====================================================\n");
  printf("semi_major_axis                 | %Lf %s\n", elements->semi_major_axis*(in_km?(long double)1/1000:1), in_km?"km":"m");
  printf("excentricity                    | %Lf\n", elements->eccentricity);
  printf("inclination                     | %Lf %s\n", elements->inclination*(in_deg?IN_DEGREES:1), in_deg?"deg":"rad" );
  printf("longitude of the ascending node | %Lf %s\n", elements->longitude_asc_node * (in_deg?IN_DEGREES:1), in_deg?"deg":"rad");
  printf("arguments of periapsis          | %Lf %s\n", elements->arg_periapsis * (in_deg?IN_DEGREES:1), in_deg?"deg":"rad");
  printf("true anomaly                    | %Lf %s\n", elements->true_anomaly * (in_deg?IN_DEGREES:1), in_deg?"deg":"rad");
  printf("====================================================\n");
}

KeplerianElements keplerian_elements_from_cartesian_elements(CartesianElements state, const Body* orbiting_body)
{
  printf("Calculate Keplarian Elemenets from catesian state\n");
  printf("position: (%Lf, %Lf, %Lf)\n", state.r.x, state.r.y, state.r.z);
  printf("velocity: (%Lf, %Lf, %Lf)\n", state.v.x, state.v.y, state.v.z);
  printf("calculate angular momentum\n");
  vector_3 specific_angular_momentum = vector_3_cross(state.r, state.v);
  printf("specific angular momentum: (%Lf, %Lf, %Lf)\n", specific_angular_momentum.x,\
    specific_angular_momentum.y,\
    specific_angular_momentum.z);

  long double gamma = orbiting_body->gravitational_parameter;

  printf("calculatin semi-major axis\n");

  long double semi_major_axis = 1/(2/vector_3_mag(state.r) - vector_3_mag(state.v)*vector_3_mag(state.v)/gamma);

  printf("semi-major axis: %Lf\n", semi_major_axis);

  printf("calculating inclination\n");

  long double inclination = acos(specific_angular_momentum.z/vector_3_mag(specific_angular_momentum));

  printf("inclination: %Lf\n", inclination);

  printf("calculating longitude of the ascending node\n");

  vector_3 K = {.x = 0, .y = 0, .z = 1};
  vector_3 I = {.x = 1, .y = 0, .z = 0};

  long double longitude_of_the_ascending_node = acos(vector_3_dot(vector_3_cross(K, specific_angular_momentum), I)/(vector_3_mag(vector_3_cross(K, specific_angular_momentum)) * vector_3_mag(I)));

  if (specific_angular_momentum.x < 0)
  {
    longitude_of_the_ascending_node = 2*M_PI - longitude_of_the_ascending_node;
  }

  printf("longitude of the ascending node: %Lf\n", longitude_of_the_ascending_node);

  printf("eccentricity vector\n");
  
  vector_3 excentricity_vector = vector_3_sub(vector_3_scale(vector_3_cross(state.v, specific_angular_momentum), 1/gamma), vector_3_scale(state.r, 1/vector_3_mag(state.r)));

  printf("eccentricity vector: (%Lf, %Lf, %Lf)\n", excentricity_vector.x, excentricity_vector.y, excentricity_vector.z);

  printf("calculating argument of periapsis\n");

  long double argument_of_periapsis = acos(vector_3_dot(vector_3_cross(K, specific_angular_momentum), excentricity_vector)/(vector_3_mag(vector_3_cross(K, specific_angular_momentum))* vector_3_mag(excentricity_vector)));

  if (excentricity_vector.z < 0)
  {
    argument_of_periapsis = 2*M_PI - argument_of_periapsis;
  }

  printf("argument of periapsis: %Lf\n", argument_of_periapsis);

  long double true_anomaly = acos(vector_3_dot(state.r, excentricity_vector)/(vector_3_mag(state.r) * vector_3_mag(excentricity_vector)));

  if (vector_3_dot(state.r, state.v) < 0)
  {
    true_anomaly = 2*M_PI - true_anomaly;
  }

  printf("true anomaly: %Lf\n", true_anomaly);

  KeplerianElements elements = {.semi_major_axis = semi_major_axis, .eccentricity = vector_3_mag(excentricity_vector), .inclination = inclination, .longitude_asc_node = longitude_of_the_ascending_node, .arg_periapsis = argument_of_periapsis, .true_anomaly = true_anomaly};

  return elements;
}

#endif