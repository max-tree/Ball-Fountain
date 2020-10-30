#include "physics.h"
#include <iostream>

physics::physics()
{
    if(radio_button_clicked(0, 1) == 0)
    {
        std::array <double,3> initialVelocity{-2.0,0.0,10};
        setVelocity(initialVelocity);
    }
    else if(radio_button_clicked(0,1) == 1)
    {
        std::array <double,3> initialVelocity{0.0,0.0,10};
        setVelocity(initialVelocity);
    }
    else if(radio_button_clicked(0,1) == 2)
    {
        std::array <double,3> initialVelocity{2.0,0.0,10};
        setVelocity(initialVelocity);
    }
    else
    {}
}
void physics::change_velocity_due_to_gravity()
{
    velocityInMetersPerSecond[2] = velocityInMetersPerSecond[2] - gravitationalConstantMetric*deltaTimeInSeconds;
    return;
}

void physics::change_position()
{
    change_velocity_due_to_gravity();
    positionInMeters[0] = positionInMeters[0] + velocityInMetersPerSecond[0]*deltaTimeInSeconds;
    positionInMeters[1] = positionInMeters[1] + velocityInMetersPerSecond[1]*deltaTimeInSeconds;
    positionInMeters[2] = positionInMeters[2] + velocityInMetersPerSecond[2]*deltaTimeInSeconds;
    std::cout << "here" << '\n';

    return;
}

std::array <double, 3> physics::getVelocity()
{
    std::array <double, 3> currentVelocity{velocityInMetersPerSecond};
    return currentVelocity;
}
std::array <double, 3> physics::getPosition()
{
    std::array <double, 3> currentPosition{positionInMeters};
    return currentPosition;
}


void physics::setVelocity(std::array <double, 3> velocityVector)
{
    velocityInMetersPerSecond = velocityVector;
}

void physics::setPosition(std::array <double, 3> positionVector)
{
     positionInMeters = positionVector;
}
