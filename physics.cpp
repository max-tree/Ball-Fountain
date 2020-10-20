#include "physics.h"

physics::physics()
{

}
void physics::accelerate_due_to_gravity(double vx, double vy, double vz)
{
    velocityInMetersPerSecond[0] = vx;
    velocityInMetersPerSecond[1] = vy;
    velocityInMetersPerSecond[2] = vz - gravitationalConstantMetric*deltaTimeInSeconds;
    return;
}

std::vector <double> physics::getVelocity()
{
    std::vector <double> readVelocity{velocityInMetersPerSecond[0],velocityInMetersPerSecond[1],velocityInMetersPerSecond[2]};
    return readVelocity;
}
