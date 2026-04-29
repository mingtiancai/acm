#include <gtest/gtest.h>
#include "ants.h"

TEST(AntsTest, BasicTest) {
    Ants ants(3, 10, {2, 6, 7});
    Ants::Result result = ants.Execute();

    EXPECT_EQ(result.min_value, 4);
    EXPECT_EQ(result.max_value, 8);
}
