#ifndef PHYSICS_H
#define PHYSICS_H
#include <array>
#include "mainwindow.h"

class physics
{
private:
    double gravitationalConstantMetric{9.81};
    std::array <double, 3> velocityInMetersPerSecond{2.0,0.0,10.0};
    std::array <double, 3> positionInMeters{0.0,0.0,0.0};
    double deltaTimeInSeconds{1.0/30.0};
public:
    physics();
    physics* node{nullptr};

    std::array <double, 3> getVelocity();
    std::array <double, 3> getPosition();

    void change_velocity_due_to_gravity();
    void change_position();
    void setVelocity(std::array <double, 3> velocityVector);
    void setPosition(std::array <double, 3> positionVector);
};

#endif // PHYSICS_H
