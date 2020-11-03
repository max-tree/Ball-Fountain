#include "Physics.h"
#include "gtest/gtest.h"


TEST(ChangeVelocityIfBallHitsTheGround, WhenBallVelocityisZeroAtTheOriginAndInContactWithTheGround_ExpectNoChange)
{
    Physics v;
    double tolerance{0.001};

    std::array <double, 3> expectedVelocity{0.0,0.0,0.0};
    std::array <double, 3> initialPosition{0.0,0.0,v.sphereRadius};
    std::array <double, 3> initialVelocity{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};

    v.setVelocity(initialVelocity);
    v.setPosition(initialPosition);
    v.change_velocity_if_ball_hits_the_ground();
    resultantVelocity = v.getVelocity();

    EXPECT_NEAR(expectedVelocity[0],resultantVelocity[0], tolerance);
    EXPECT_NEAR(expectedVelocity[1],resultantVelocity[1], tolerance);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2], tolerance);
}

TEST(ChangeVelocityIfBallHitsTheGround, WhenBallVelocityisNonzeroAtTheOriginAndInContactWithTheGround_ExpectChangeInVelocityInTheZDirection)
{   
    Physics v;
    double tolerance{0.001};

    std::array <double, 3> expectedVelocity{0.0,0.0,9.0};
    std::array <double, 3> initialPosition{0.0,0.0,v.sphereRadius-v.correctionForVisualAccuracy};
    std::array <double, 3> initialVelocity{0.0,0.0,-10.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};

    v.setVelocity(initialVelocity);
    v.setPosition(initialPosition);
    v.change_velocity_if_ball_hits_the_ground();
    resultantVelocity = v.getVelocity();

    EXPECT_NEAR(expectedVelocity[0],resultantVelocity[0], tolerance);
    EXPECT_NEAR(expectedVelocity[1],resultantVelocity[1], tolerance);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2], tolerance);
}
