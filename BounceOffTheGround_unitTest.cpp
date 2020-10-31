#include "Physics.h"
#include "gtest/gtest.h"


TEST(BounceOffTheGround, WhenBallVelocityisZeroAtTheOriginAndInContactWithTheGround_ExpectNoChange)
{
    std::array <double, 3> expectedVelocity{0.0,0.0,0.0};
    std::array <double, 3> initialPosition{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};

    Physics v;
    double tolerance{0.001};

    v.setVelocity(initialVelocity);
    v.setPosition(initialPosition);
    v.check_if_ball_has_hit_the_ground();
    v.bounce_off_the_ground();
    resultantVelocity = v.getVelocity();

    EXPECT_NEAR(expectedVelocity[0],resultantVelocity[0], tolerance);
    EXPECT_NEAR(expectedVelocity[1],resultantVelocity[1], tolerance);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2], tolerance);
}

TEST(BounceOffTheGround, WhenBallVelocityisNonzeroAtTheOriginAndInContactWithTheGround_ExpectChangeInVelocityInTheZDirection)
{
    std::array <double, 3> expectedVelocity{0.0,0.0,9.0};
    std::array <double, 3> initialPosition{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity{0.0,0.0,-10.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};

    Physics v;
    double tolerance{0.001};

    v.setVelocity(initialVelocity);
    v.setPosition(initialPosition);
    v.check_if_ball_has_hit_the_ground();
    v.bounce_off_the_ground();
    resultantVelocity = v.getVelocity();

    EXPECT_NEAR(expectedVelocity[0],resultantVelocity[0], tolerance);
    EXPECT_NEAR(expectedVelocity[1],resultantVelocity[1], tolerance);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2], tolerance);
}
