#ifndef PHYSICS_H
#define PHYSICS_H
#include <array>
#include <math.h>
#include "mainwindow.h"

class Physics
{
public:
    Physics(){}
    ~Physics(){}
    bool ballOnTheGround = false;
    double coefficientOfRestitution{.9};
    double sphereRadius{1.0};
    double groundradius{5.0};
    double correctionForVisualAccuracy{0.5};
    double sphereMass{10.0};
//    Physics *sphere{nullptr};

    std::array <double, 3> getVelocity();
    std::array <double, 3> getPosition();

    void change_velocity_due_to_gravity();
    void change_position();
    void setVelocity(std::array <double, 3> velocityVector);
    void setPosition(std::array <double, 3> positionVector);
    void check_if_ball_has_hit_the_ground();
    void change_velocity_if_ball_hits_the_ground();

private:
    double gravitationalConstantMetric{9.81};
    std::array <double, 3> velocityInMetersPerSecond{0.0,0.0,0.0};
    std::array <double, 3> positionInMeters{0.0,0.0,sphereRadius};
    double deltaTimeInSeconds{1.0/30.0};
};

void change_ball_velocity_if_collision_occurs(Physics* &sphere1, Physics* &sphere2);
double calculate_distance_between_two_vectors(std::array <double, 3> vector1, std::array <double, 3> vector2);
double dot_product_of_two_vectors(std::array <double, 3> vector1, std::array <double, 3> vector2);


#endif // PHYSICS_H
