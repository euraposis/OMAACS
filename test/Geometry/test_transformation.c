
#include "../../Unity/src/unity.h"
#include "../../src/Geometry/transformation.h"


// Setup unity test
void setUp() {}

// Cleanup unity test

void tearDown() {}

// Test transformation

void test_transformation()
{
  TEST_ASSERT_MESSAGE(1, "Test transformation");
}

int main(void)
{
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_transformation);

    return UNITY_END();
}