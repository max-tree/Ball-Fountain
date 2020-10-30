#ifndef SPHEREPHYSICSUPDATECALLBACK_H
#define SPHEREPHYSICSUPDATECALLBACK_H

#include "osgwidget.h" //Do I use "" or <>?
#include "mainwindow.h"
#include <osg/PositionAttitudeTransform>
#include <osgwidget.h>
#include <iostream>
#include "SphereColorUpdateCallback.h"
#include <osg/ref_ptr>

class ActiveSpheres
{
public:
    double xDirectionDeletePosition{5.0};
    double yDirectionDeletePosition{5.0};

};

class SpherePhysicsUpdateCallback: public osg::NodeCallback //Note to self: every class needs to have its own .cpp file. MOVE THIS
{//I will have to make one of these for the physics equations. This is the secret. Do exactly what this does but add a physics world into the mix.
public:
    SpherePhysicsUpdateCallback(){}
    ~SpherePhysicsUpdateCallback(){}
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        physicsSphere->change_position();
        currentPosition = physicsSphere->getPosition();
        osg::Vec3d position(currentPosition[0], currentPosition[1], currentPosition[2]);
        osg::Vec3d scaleFactor(0.25, 0.25, 0.25);
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *> (node);
        pat->setPosition(position);
        pat->setScale(scaleFactor);
        traverse(node, nv);
        if (currentPosition[2] <= zDirectionDeletePosition)
        {
//            std::cout << "HELLO \n";
//            node->unref();
        }
    }
protected:
    bool mUp{true};
    unsigned int mCount{0};
    double mScaleStep{1.0/30.0};
    std::array <double, 3> currentPosition{0.0,0.0,0.0};
    physics* physicsSphere = new physics;
    double zDirectionDeletePosition{-2.0};

};

#endif // SPHEREPHYSICSUPDATECALLBACK_H
