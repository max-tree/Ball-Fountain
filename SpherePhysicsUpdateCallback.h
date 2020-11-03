#ifndef SPHEREPHYSICSUPDATECALLBACK_H
#define SPHEREPHYSICSUPDATECALLBACK_H

#include "osgwidget.h"
#include "mainwindow.h"
#include <osg/PositionAttitudeTransform>
#include <osgwidget.h>
#include <iostream>
#include "SphereColorUpdateCallback.h"
#include <osg/ref_ptr>

class SpherePhysicsUpdateCallback: public osg::NodeCallback
{
public:
    SpherePhysicsUpdateCallback(){
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
    ~SpherePhysicsUpdateCallback(){
        delete physicsSphere;
    }
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
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
protected:
    std::array <double, 3> currentPosition{0.0,0.0,0.0};
    Physics* physicsSphere = new Physics;
    double zDirectionDeletePosition{-2.0};
    int sphereStorageNum{0};
};

#endif // SPHEREPHYSICSUPDATECALLBACK_H
