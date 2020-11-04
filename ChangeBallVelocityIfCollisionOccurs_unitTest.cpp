#include "Physics.h"
#include "gtest/gtest.h"
#include <iostream>

void test_both_vectors_to_see_if_correct_result_is_output(std::array <double, 3>expectedVelocity1, std::array <double, 3>resultantVelocity1, double tolerance,
                                                          std::array <double, 3>expectedVelocity2, std::array <double, 3>resultantVelocity2)
{
    EXPECT_NEAR(expectedVelocity1[0],resultantVelocity1[0], tolerance);
    EXPECT_NEAR(expectedVelocity1[1],resultantVelocity1[1], tolerance);
    EXPECT_NEAR(expectedVelocity1[2],resultantVelocity1[2], tolerance);
    EXPECT_NEAR(expectedVelocity2[0],resultantVelocity2[0], tolerance);
    EXPECT_NEAR(expectedVelocity2[1],resultantVelocity2[1], tolerance);
    EXPECT_NEAR(expectedVelocity2[2],resultantVelocity2[2], tolerance);
}

void set_position_and_velocity(Physics *&v1, Physics *&v2, int testNumber)
{
    std::array <double, 3> initialPosition1{0.0,0.0,0.0};
    std::array <double, 3> initialPosition2{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity1{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity2{0.0,0.0,0.0};
    if(testNumber == 1)
    {
        initialPosition1 = {10.0,10.0,10.0};
        initialPosition2 = {0.0,0.0,0.0};
        initialVelocity1 = {0.0,0.0,-10.0};
        initialVelocity2 = {0.0,0.0,10.0};
    }
    else
    {
       initialPosition1 = {10.0,10.0,10.0};
       initialPosition2 = {10.0,10.0,8.0};
       initialVelocity1 = {0.0,0.0,-10.0};
       initialVelocity2 = {0.0,0.0,10.0};
    }
    v1->setPosition(initialPosition1);
    v2->setPosition(initialPosition2);
    v1->setVelocity(initialVelocity1);
    v2->setVelocity(initialVelocity2);
}


TEST(ChangeBallVelocityIfCollisionOccurs, WhenThereIsNoBallNearTheBallInQuestion_ExpectNoChange)
{
    int testNumber{1};

    std::array <double, 3> resultantVelocity1{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity2{0.0,0.0,0.0};

    std::array <double, 3> expectedVelocity1{0.0,0.0,-10.0};
    std::array <double, 3> expectedVelocity2{0.0,0.0,10.0};


    Physics *v1 = new Physics;
    Physics *v2 = new Physics;
    double tolerance{0.001};

    set_position_and_velocity(v1, v2, testNumber);

    change_ball_velocity_if_collision_occurs(v1,v2);
    resultantVelocity1 = v1->getVelocity();
    resultantVelocity2 = v2->getVelocity();

    test_both_vectors_to_see_if_correct_result_is_output(expectedVelocity1, resultantVelocity1, tolerance,
                                                         expectedVelocity2, resultantVelocity2);

    delete v1;
    delete v2;
}

TEST(ChangeBallVelocityIfCollisionOccurs, WhenTwoBallsCollideAndAreOnlyMovingInTheZDirection_ExpectCorrectVelocitiesInThezDirection)
{
    std::array <double, 3> resultantVelocity1{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity2{0.0,0.0,0.0};

    std::array <double, 3> expectedVelocity1{0.0,0.0,10.0};
    std::array <double, 3> expectedVelocity2{0.0,0.0,-10.0};

    int testNumber{2};
    Physics *v1 = new Physics;
    Physics *v2 = new Physics;
    double tolerance{0.001};

    set_position_and_velocity(v1, v2, testNumber);

    change_ball_velocity_if_collision_occurs(v1,v2);
    resultantVelocity1 = v1->getVelocity();
    resultantVelocity2 = v2->getVelocity();

    test_both_vectors_to_see_if_correct_result_is_output(expectedVelocity1, resultantVelocity1, tolerance,
                                                         expectedVelocity2, resultantVelocity2);

    delete v1;
    delete v2;
}
