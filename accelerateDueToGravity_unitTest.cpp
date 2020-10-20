#include "physics.h"
#include "gtest/gtest.h"


TEST(AccelerationDueToGravityTest, WhenVelocityIsZeroInitiallyInTheHorizontal_ExpectNoChangeInTheHorizontal)
{
    std::vector <double> expectedVelocity{0.0,0.0,0.0};
    physics v;
    v.accelerate_due_to_gravity(0.0,0.0,0.0);
    std::vector <double> resultantVelocity{0.0,0.0,0.0};
    resultantVelocity = v.getVelocity();
    EXPECT_EQ(expectedVelocity[0],resultantVelocity[0]);
    EXPECT_EQ(expectedVelocity[1],resultantVelocity[1]);

}

TEST(AccelerationDueToGravityTest, WhenVelocityIsNonzeroInTheHorizontal_ExpectNoChangeInTheHorizontal)
{
    std::vector <double> expectedVelocity{1.0,1.0,0.0};
    physics v;
    v.accelerate_due_to_gravity(1.0,1.0,0.0);
    std::vector <double> resultantVelocity{0.0,0.0,0.0};
    resultantVelocity = v.getVelocity();
    EXPECT_EQ(expectedVelocity[0],resultantVelocity[0]);
    EXPECT_EQ(expectedVelocity[1],resultantVelocity[1]);
}

TEST(AccelerationDueToGravityTest, WhenVelocityIsZeroInitiallyInTheVertical_ExpectCorrectResult)
{
    std::vector <double> expectedVelocity{0.0,0.0,-0.981};
    physics v;
    v.accelerate_due_to_gravity(0.0,0.0,0.0);
    std::vector <double> resultantVelocity{0.0,0.0,0.0};
    double tolerance{0.001};
    resultantVelocity = v.getVelocity();
    EXPECT_EQ(expectedVelocity[0],resultantVelocity[0]);
    EXPECT_EQ(expectedVelocity[1],resultantVelocity[1]);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2],tolerance);
}
