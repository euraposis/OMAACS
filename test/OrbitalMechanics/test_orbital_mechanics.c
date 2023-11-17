
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
  CartesianElements state = {.r.x = 6524832,\
                             .r.y = 6862875,\
                             .r.z = 6448296,\
                             .v.x = 4901.327,\
                             .v.y = 5533.756,\
                             .v.z = -1976.341};
  KeplerianElements elements = keplerian_elements_from_cartesian_elements(state, &Earth);
  print_kepler(&elements, 0, 0);
  KeplerianElements expected_elements = {.semi_major_axis = 36127.52746746103 _KM,\
                                         .eccentricity = 0.8328541780636955,\
                                         .inclination = 87.86913563256209 / IN_DEGREES,\
                                         .longitude_asc_node = 227.8982628888632 / IN_DEGREES,\
                                         .arg_periapsis = 53.38500337126987 / IN_DEGREES,\
                                         .true_anomaly = 92.33508036613732 / IN_DEGREES};
  TEST_ASSERT_DOUBLE_WITHIN(1000, expected_elements.semi_major_axis, elements.semi_major_axis);
  TEST_ASSERT_DOUBLE_WITHIN(0.1, expected_elements.eccentricity, elements.eccentricity);
  TEST_ASSERT_DOUBLE_WITHIN(0.1, expected_elements.inclination, elements.inclination);
  TEST_ASSERT_DOUBLE_WITHIN(0.1, expected_elements.longitude_asc_node, elements.longitude_asc_node);
  TEST_ASSERT_DOUBLE_WITHIN(0.1, expected_elements.arg_periapsis, elements.arg_periapsis);
  TEST_ASSERT_DOUBLE_WITHIN(0.1, expected_elements.true_anomaly, elements.true_anomaly);

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_structs);
    RUN_TEST(test_kepler_from_state);

    return UNITY_END();
}