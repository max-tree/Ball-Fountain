//Create a class that holds the position of each of the balls created in OSGWidget.
//Or translate the manage ball function into spherecallback to be able to keep track of each balls position.

#include "Physics.h"
#include "gtest/gtest.h"


std::array <double, 3> subtract_two_vectors(std::array <double, 3> vector1, std::array <double, 3> vector2)
{
    std::array <double, 3> result{vector1[0]-vector2[0],vector1[1]-vector2[1],vector1[2]-vector2[2]};
    return result;
}

std::array <double, 3> multiply_a_vector_by_a_constant(std::array <double, 3> vector, double constant)
{
    std::array <double, 3> result{vector[0]*constant, vector[1]*constant, vector[2]*constant};
    return result;
}

void change_ball_velocity_if_collision_occurs(Physics* &sphere1, Physics* &sphere2)
{
    std::array <double,3> placeholder{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity1{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity2{0.0,0.0,0.0};

    if(calculate_distance_between_two_vectors(sphere1->getPosition(), sphere2->getPosition()) < 2.0001)
    {
        std::array <double, 3> differenceInVelocities{subtract_two_vectors(sphere1->getVelocity(), sphere2->getVelocity())};
        std::array <double, 3> differenceInPositions{subtract_two_vectors(sphere1->getPosition(), sphere2->getPosition())};
        double constant{dot_product_of_two_vectors(differenceInVelocities,differenceInPositions)/pow(calculate_distance_between_two_vectors(sphere1->getPosition(),sphere2->getPosition()),2)};
        placeholder = (subtract_two_vectors(sphere1->getVelocity(), multiply_a_vector_by_a_constant(differenceInPositions, constant)));
        resultantVelocity1 = sphere1->getVelocity();
        std::cout<<"\n resultant velocity z-dir " << resultantVelocity1[2] << '\n';

        differenceInVelocities = subtract_two_vectors(sphere2->getVelocity(), sphere1->getVelocity());
        differenceInPositions = subtract_two_vectors(sphere2->getPosition(), sphere1->getPosition());
        constant = dot_product_of_two_vectors(differenceInVelocities,differenceInPositions)/pow(calculate_distance_between_two_vectors(sphere2->getPosition(),sphere1->getPosition()),2);
        sphere2->setVelocity(subtract_two_vectors(sphere2->getVelocity(), multiply_a_vector_by_a_constant(differenceInPositions, constant)));
        resultantVelocity2 = sphere2->getVelocity();
        std::cout<<"\n difference in velocities " << differenceInVelocities[2] << '\n';
        std::cout<<"\n difference in positions " << differenceInPositions[2] << '\n';
        sphere1->setVelocity(placeholder);
        std::cout<<"\n resultant velocity z-dir " << resultantVelocity2[2] << '\n';
    }
    else
    {}
}

TEST(ChangeBallVelocityIfCollisionOccurs, WhenThereIsNoBallNearTheBallInQuestion_ExpectNoChange)
{
    std::array <double, 3> initialPosition1{10.0,10.0,10.0};
    std::array <double, 3> initialPosition2{0.0,0.0,0.0};
    std::array <double, 3> initialVelocity1{0.0,0.0,-10.0};
    std::array <double, 3> initialVelocity2{0.0,0.0,10.0};

    std::array <double, 3> resultantVelocity1{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity2{0.0,0.0,0.0};

    std::array <double, 3> expectedVelocity1{0.0,0.0,-10.0};
    std::array <double, 3> expectedVelocity2{0.0,0.0,10.0};


    Physics *v1 = new Physics;
    Physics *v2 = new Physics;
    double tolerance{0.001};

    v1->setPosition(initialPosition1);
    v2->setPosition(initialPosition2);
    v1->setVelocity(initialVelocity1);
    v2->setVelocity(initialVelocity2);
    change_ball_velocity_if_collision_occurs(v1,v2);
    resultantVelocity1 = v1->getVelocity();
    resultantVelocity2 = v2->getVelocity();

    EXPECT_NEAR(expectedVelocity1[0],resultantVelocity1[0], tolerance);
    EXPECT_NEAR(expectedVelocity1[1],resultantVelocity1[1], tolerance);
    EXPECT_NEAR(expectedVelocity1[2],resultantVelocity1[2], tolerance);
    EXPECT_NEAR(expectedVelocity2[0],resultantVelocity2[0], tolerance);
    EXPECT_NEAR(expectedVelocity2[1],resultantVelocity2[1], tolerance);
    EXPECT_NEAR(expectedVelocity2[2],resultantVelocity2[2], tolerance);

    delete v1;
    delete v2;
}

TEST(ChangeBallVelocityIfCollisionOccurs, WhenTwoBallsCollideAndAreOnlyMovingInTheZDirection_ExpectCorrectVelocitiesInThezDirection)
{
    std::array <double, 3> initialPosition1{10.0,10.0,10.0};
    std::array <double, 3> initialPosition2{10.0,10.0,8.0};
    std::array <double, 3> initialVelocity1{0.0,0.0,-10.0};
    std::array <double, 3> initialVelocity2{0.0,0.0,10.0};

    std::array <double, 3> resultantVelocity1{0.0,0.0,0.0};
    std::array <double, 3> resultantVelocity2{0.0,0.0,0.0};

    std::array <double, 3> expectedVelocity1{0.0,0.0,10.0};
    std::array <double, 3> expectedVelocity2{0.0,0.0,-10.0};


    Physics *v1 = new Physics;
    Physics *v2 = new Physics;
    double tolerance{0.001};

    v1->setPosition(initialPosition1);
    v2->setPosition(initialPosition2);
    v1->setVelocity(initialVelocity1);
    v2->setVelocity(initialVelocity2);
    change_ball_velocity_if_collision_occurs(v1,v2);
    resultantVelocity1 = v1->getVelocity();
    resultantVelocity2 = v2->getVelocity();

    EXPECT_NEAR(expectedVelocity1[0],resultantVelocity1[0], tolerance);
    EXPECT_NEAR(expectedVelocity1[1],resultantVelocity1[1], tolerance);
    EXPECT_NEAR(expectedVelocity1[2],resultantVelocity1[2], tolerance);
    EXPECT_NEAR(expectedVelocity2[0],resultantVelocity2[0], tolerance);
    EXPECT_NEAR(expectedVelocity2[1],resultantVelocity2[1], tolerance);
    EXPECT_NEAR(expectedVelocity2[2],resultantVelocity2[2], tolerance);

    delete v1;
    delete v2;
}
