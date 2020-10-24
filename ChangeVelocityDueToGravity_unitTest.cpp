#include "physics.h"
#include "gtest/gtest.h"

/*Tests are based on a deltaTime of 1/30*/

TEST(ChangeVelocityDueToGravity, WhenVelocityIsZeroInitiallyInTheHorizontal_ExpectNoChangeInTheHorizontal)
{
    std::array <double, 3> expectedVelocity{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};
    physics v;

    v.setVelocity(initialVelocity);
    v.change_velocity_due_to_gravity();
    resultantVelocity = v.getVelocity();

    EXPECT_EQ(expectedVelocity[0],resultantVelocity[0]);
    EXPECT_EQ(expectedVelocity[1],resultantVelocity[1]);

}

TEST(AccelerationDueToGravityTest, WhenVelocityIsNonzeroInTheHorizontal_ExpectNoChangeInTheHorizontal)
{
    std::array <double, 3> expectedVelocity{1.0,1.0,0.0};
    std::array <double, 3> initialVelocity{1.0,1.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};
    physics v;

    v.setVelocity(initialVelocity);
    v.change_velocity_due_to_gravity();
    resultantVelocity = v.getVelocity();

    EXPECT_EQ(expectedVelocity[0],resultantVelocity[0]);
    EXPECT_EQ(expectedVelocity[1],resultantVelocity[1]);
}

TEST(AccelerationDueToGravityTest, WhenVelocityIsZeroInitiallyInTheVertical_ExpectCorrectResult)
{
    std::array <double, 3> expectedVelocity{0.0,0.0,-0.327};//.981 comes from the time step being .1s
    std::array <double, 3> initialVelocity{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};
    physics v;
    double tolerance{0.001};

    v.setVelocity(initialVelocity);
    v.change_velocity_due_to_gravity();
    resultantVelocity = v.getVelocity();

    EXPECT_EQ(expectedVelocity[0],resultantVelocity[0]);
    EXPECT_EQ(expectedVelocity[1],resultantVelocity[1]);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2],tolerance);
}

TEST(AccelerationDueToGravityTest, WhenVelocityIsInitiallyInTheVertical_ExpectCorrectResult)
{
    std::array <double, 3> expectedVelocity{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity{0.0,0.0,0.327};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};
    physics v;
    double tolerance{0.001};

    v.setVelocity(initialVelocity);
    v.change_velocity_due_to_gravity();
    resultantVelocity = v.getVelocity();

    EXPECT_EQ(expectedVelocity[0],resultantVelocity[0]);
    EXPECT_EQ(expectedVelocity[1],resultantVelocity[1]);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2],tolerance);
}
