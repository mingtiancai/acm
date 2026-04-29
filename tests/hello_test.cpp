#include "hello.h"

#ifdef ACM_USE_GTEST
#include <gtest/gtest.h>

TEST(HelloTest, ReturnsCorrectGreeting) {
    EXPECT_EQ(get_greeting(), "Hello, World!");
}

#else
#include <iostream>

int main() {
    if (get_greeting() != "Hello, World!") {
        std::cerr << "hello_test failed: unexpected greeting" << std::endl;
        return 1;
    }

    std::cout << "hello_test passed" << std::endl;
    return 0;
}
#endif
