#ifndef OMAACS_ORBITAL_MECHANICS_H
#define OMAACS_ORBITAL_MECHANICS_H

#include "../../libs/OMAACS_NUM/OMAACS_NUM/src/vector.h"

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

#endif