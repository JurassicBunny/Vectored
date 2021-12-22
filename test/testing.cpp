#include <gtest/gtest.h>
#include <string>

#include "../include/Vectored/vectored.hpp"

TEST(Constructor, Constructor)
{
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    Eigen::Vector3d answer(1, 2, 3);
    EXPECT_EQ(acceleration.as_vec(), answer);
}

TEST(Constructor, Cast)
{
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    Velocity velocity(acceleration);
    EXPECT_TRUE(velocity.as_vec().x() = 1);
    EXPECT_TRUE(velocity.as_vec().y() = 2);
    EXPECT_TRUE(velocity.as_vec().z() = 3);
}
TEST(Constructor, AS)
{
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    Velocity velocity(1, 2, 3);
    EXPECT_TRUE(typeid(velocity).name() == typeid(acceleration.as<Velocity>()).name());
}

TEST(Normal, Norm)
{
    using namespace Vectored;
    int answer = 1;
    Acceleration acceleration(1, 2, 3);
    auto result = acceleration.as_vec().normalized().norm();
    EXPECT_EQ(result, answer);
}

TEST(Operator, Addition)
{
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    Velocity velocity(2, 5, 6);
    Acceleration result = acceleration + velocity;
    Acceleration answer(3, 7, 9);
    EXPECT_EQ(result.as_vec(), answer.as_vec());
}

TEST(Operator, Subtraction)
{
    using namespace Vectored;
    Acceleration acceleration(1, 2, 3);
    Velocity velocity(2, 5, 6);
    Acceleration result = acceleration - velocity;
    Acceleration answer(-1, -3, -3);
    EXPECT_EQ(result.as_vec(), answer.as_vec());
}

TEST(Scalar_Vector, Mul)
{
    using namespace Vectored;
    using namespace Scalar;
    Acceleration acceleration(1, 2, 3);
    Time time(2);
    auto result = time * acceleration;
    EXPECT_EQ(typeid(result).name(), typeid(Acceleration).name());
}
TEST(Vector_Scalar, Mul)
{
    using namespace Vectored;
    using namespace Scalar;
    Acceleration acceleration(1, 2, 3);
    Time time(2);
    auto result = acceleration * time;
    EXPECT_EQ(typeid(result).name(), typeid(Acceleration).name());
}
