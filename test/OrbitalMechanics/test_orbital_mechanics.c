
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

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_structs);

    return UNITY_END();
}