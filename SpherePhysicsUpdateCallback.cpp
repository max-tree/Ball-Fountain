#include "SpherePhysicsUpdateCallback.h"

void SpherePhysicsUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    physicsSphere->change_position();
    physicsSphere->change_velocity_if_ball_hits_the_ground();

    currentPosition = physicsSphere->getPosition();
    osg::Vec3d position(currentPosition[0], currentPosition[1], currentPosition[2]);
    osg::Vec3d scaleFactor(0.25, 0.25, 0.25);
    osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *> (node);

    pat->setPosition(position);
    pat->setScale(scaleFactor);
    traverse(node, nv);
}

void SpherePhysicsUpdateCallback::decide_direction_of_new_sphere()
{
    if(radio_button_clicked(0, 1) == 0)
    {
        std::array <double,3> initialVelocity{-2.0,0.0,10};
        physicsSphere->setVelocity(initialVelocity);
    }
    else if(radio_button_clicked(0,1) == 1)
    {
        std::array <double,3> initialVelocity{0.0,0.0,10};
        physicsSphere->setVelocity(initialVelocity);
    }
    else if(radio_button_clicked(0,1) == 2)
    {
        std::array <double,3> initialVelocity{2.0,0.0,10};
        physicsSphere->setVelocity(initialVelocity);
    }
    else
    {}
}
