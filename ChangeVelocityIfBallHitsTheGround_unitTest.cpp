#include "Physics.h"
#include "gtest/gtest.h"

std::array <double,3> get_new_velocity(Physics v, std::array <double,3> initialVelocity, std::array <double,3> initialPosition)
{
    v.setVelocity(initialVelocity);
    v.setPosition(initialPosition);
    v.change_velocity_if_ball_hits_the_ground();
    return v.getVelocity();
}

void test_velocity_vector_to_see_if_the_correct_result_is_output(std::array <double, 3> expectedVelocity, std::array <double, 3> resultantVelocity, double tolerance)
{
    EXPECT_NEAR(expectedVelocity[0],resultantVelocity[0], tolerance);
    EXPECT_NEAR(expectedVelocity[1],resultantVelocity[1], tolerance);
    EXPECT_NEAR(expectedVelocity[2],resultantVelocity[2], tolerance);
}

TEST(ChangeVelocityIfBallHitsTheGround, WhenBallVelocityisZeroAtTheOriginAndInContactWithTheGround_ExpectNoChange)
{
    Physics v;
    double tolerance{0.001};

    std::array <double, 3> expectedVelocity{0.0,0.0,0.0};
    std::array <double, 3> initialPosition{0.0,0.0,v.sphereRadius};
    std::array <double, 3> initialVelocity{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};

    resultantVelocity = get_new_velocity(v, initialVelocity, initialPosition);

    test_velocity_vector_to_see_if_the_correct_result_is_output(expectedVelocity, resultantVelocity, tolerance);
}

TEST(ChangeVelocityIfBallHitsTheGround, WhenBallVelocityisNonzeroAtTheOriginAndInContactWithTheGround_ExpectChangeInVelocityInTheZDirection)
{   
    Physics v;
    double tolerance{0.001};

    std::array <double, 3> expectedVelocity{0.0,0.0,9.0};
    std::array <double, 3> initialPosition{0.0,0.0,v.sphereRadius-v.correctionForVisualAccuracy};
    std::array <double, 3> initialVelocity{0.0,0.0,-10.0};
    std::array <double, 3> resultantVelocity{0.0,0.0,0.0};

    resultantVelocity = get_new_velocity(v, initialVelocity, initialPosition);

    test_velocity_vector_to_see_if_the_correct_result_is_output(expectedVelocity, resultantVelocity, tolerance);
}
