//
// Created by Matthew on 12/13/21.
//

#include "../include/Vectored/vectored.h"
#include <gtest/gtest.h>

TEST(Constructor, Constructor)  {
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    EXPECT_TRUE(acceleration.x() = 1);
    EXPECT_TRUE(acceleration.y() = 2);
    EXPECT_TRUE(acceleration.z() = 3);
}

TEST(Constructor, Cast) {
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    Velocity velocity(acceleration);
    EXPECT_TRUE(velocity.x() = 1);
    EXPECT_TRUE(velocity.y() = 2);
    EXPECT_TRUE(velocity.z() = 3);
}

TEST(Normal, Norm ) {
    using namespace Vectored;
    int answer = 1;
    Acceleration acceleration(1, 2, 3);
    auto result = acceleration.normalized().norm();
    ASSERT_EQ(result, answer);
}

TEST(Operator, Addition) {
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    Velocity velocity(2,5,6);
    Acceleration result = acceleration + velocity;
    Acceleration answer(3,7, 9);
    EXPECT_EQ(result, answer);
}

TEST(Operator, Subtraction) {
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    Velocity velocity(2,5,6);
    Acceleration result = acceleration - velocity;
    Acceleration answer(-1,-3, -3);
    EXPECT_EQ(result, answer);
}
