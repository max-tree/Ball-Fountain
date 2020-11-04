#ifndef SPHEREPHYSICSUPDATECALLBACK_H
#define SPHEREPHYSICSUPDATECALLBACK_H

#include "mainwindow.h"
#include <osg/PositionAttitudeTransform>
#include <osgwidget.h>
#include <osg/ref_ptr>

class SpherePhysicsUpdateCallback: public osg::NodeCallback
{
public:
    SpherePhysicsUpdateCallback()
    {
        decide_direction_of_new_sphere();
    }
    ~SpherePhysicsUpdateCallback()
    {
        delete physicsSphere;
    }
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
    std::array <double, 3> currentPosition{0.0,0.0,0.0};
    Physics* physicsSphere = new Physics;
    double zDirectionDeletePosition{-2.0};
    int sphereStorageNum{0};

    void decide_direction_of_new_sphere();
};

#endif // SPHEREPHYSICSUPDATECALLBACK_H
