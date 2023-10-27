
#include "../../Unity/src/unity.h"
#include "../../src/OrbitalMechanics/orbital_mechanics.h"


// Setup unity test
void setUp() {}

// Cleanup unity test

void tearDown() {}

// Test transformation

void test_structs()
{
  KeplerianElements ke;
  CartesianElements ce;
}

void test_kepler_from_state()
{
  CartesianElements state = {.r.x = 6370000 + 400000, .r.y = 0, .r.z = 0.5, .v.x = 0, .v.y = 7770 * 0.6, .v.z = 0};
  KeplerianElements elements = keplerian_elements_from_cartesian_elements(state, &Earth);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_structs);
    RUN_TEST(test_kepler_from_state);

    return UNITY_END();
}