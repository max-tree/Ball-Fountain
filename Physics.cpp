#include "Physics.h"

void Physics::change_velocity_due_to_gravity()
{
    velocityInMetersPerSecond[2] = velocityInMetersPerSecond[2] - gravitationalConstantMetric*deltaTimeInSeconds;
    return;
}

void Physics::change_position()
{
    change_velocity_due_to_gravity();
    positionInMeters[0] = positionInMeters[0] + velocityInMetersPerSecond[0]*deltaTimeInSeconds;
    positionInMeters[1] = positionInMeters[1] + velocityInMetersPerSecond[1]*deltaTimeInSeconds;
    positionInMeters[2] = positionInMeters[2] + velocityInMetersPerSecond[2]*deltaTimeInSeconds;
}

void Physics::check_if_ball_has_hit_the_ground()
{
    if(positionInMeters[2] > sphereRadius-correctionForVisualAccuracy
            || positionInMeters[0] > groundradius  || positionInMeters[1] > groundradius
            || positionInMeters[0] < -groundradius || positionInMeters[1] < -groundradius)
    {
        ballOnTheGround = false;
    }
    else
    {
        ballOnTheGround = true;
    }
}

void Physics::change_velocity_if_ball_hits_the_ground()
{
    check_if_ball_has_hit_the_ground();
    if(ballOnTheGround)
    {
        velocityInMetersPerSecond[2] = -coefficientOfRestitution*velocityInMetersPerSecond[2];
        ballOnTheGround = false;
    }
    else
    {}
}

std::array <double, 3> Physics::getVelocity()
{
    std::array <double, 3> currentVelocity{velocityInMetersPerSecond};
    return currentVelocity;
}

std::array <double, 3> Physics::getPosition()
{
    std::array <double, 3> currentPosition{positionInMeters};
    return currentPosition;
}


void Physics::setVelocity(std::array <double, 3> velocityVector)
{
    velocityInMetersPerSecond = velocityVector;
}

void Physics::setPosition(std::array <double, 3> positionVector)
{
     positionInMeters = positionVector;
}

double calculate_distance_between_two_vectors(std::array <double, 3> vector1, std::array <double, 3> vector2)
{
    return sqrt(pow(vector1[0]-vector2[0],2)+pow(vector1[1]-vector2[1],2)+pow(vector1[2]-vector2[2],2));
}

double dot_product_of_two_vectors(std::array <double, 3> vector1, std::array <double, 3> vector2)
{
    double result{0.0};
    for(int index{0}; index<3; index++)
    {
        result = result + vector1[index]*vector2[index];
    }
    return result;
}

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

    if(calculate_distance_between_two_vectors(sphere1->getPosition(), sphere2->getPosition()) < 2.1)
    {
        std::array <double, 3> differenceInVelocities{subtract_two_vectors(sphere1->getVelocity(), sphere2->getVelocity())};
        std::array <double, 3> differenceInPositions{subtract_two_vectors(sphere1->getPosition(), sphere2->getPosition())};
        double constant{dot_product_of_two_vectors(differenceInVelocities,differenceInPositions)/
                    pow(calculate_distance_between_two_vectors(sphere1->getPosition(),sphere2->getPosition()),2)};
        placeholder = (subtract_two_vectors(sphere1->getVelocity(), multiply_a_vector_by_a_constant(differenceInPositions, constant)));

        differenceInVelocities = subtract_two_vectors(sphere2->getVelocity(), sphere1->getVelocity());
        differenceInPositions = subtract_two_vectors(sphere2->getPosition(), sphere1->getPosition());
        constant = dot_product_of_two_vectors(differenceInVelocities,differenceInPositions)/
                pow(calculate_distance_between_two_vectors(sphere2->getPosition(),sphere1->getPosition()),2);
        sphere2->setVelocity(subtract_two_vectors(sphere2->getVelocity(), multiply_a_vector_by_a_constant(differenceInPositions, constant)));

        sphere1->setVelocity(placeholder);
    }
    else
    {}
}
