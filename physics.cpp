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

void Physics::bounce_off_the_ground()
{
    check_if_ball_has_hit_the_ground();
    if(ballOnTheGround)
    {
        velocityInMetersPerSecond[2] = -coefficientOfRestitution*velocityInMetersPerSecond[2];
        ballOnTheGround = false;
    }
    else
    {
    }
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
