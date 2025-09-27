#include "unity.h"

// Required by Unity (even if empty)
void setUp(void) {}
void tearDown(void) {}

void test_always_pass(void) {
    TEST_ASSERT_TRUE(1); // always passes
}
