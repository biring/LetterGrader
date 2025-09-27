#include "unity.h"

// Forward declarations
void test_always_pass(void);

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_always_pass);
    
    return UNITY_END();
}
