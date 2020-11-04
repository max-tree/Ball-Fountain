#ifndef SPHERECOLORUPDATECALLBACK_H
#define SPHERECOLORUPDATECALLBACK_H

#include "mainwindow.h"
#include <osgwidget.h>
#include <osg/ShapeDrawable>

class SphereColorUpdateCallback: public osg::NodeCallback
{
public:
    SphereColorUpdateCallback(){}

    osg::Vec4 pink{ osg::Vec4( 1.f, 0.f, 1.f, 1.f )};
    osg::Vec4 black{osg::Vec4( 0.f, 0.f, 0.f, 0.f )};

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
};

#endif // SPHERECOLORUPDATECALLBACK_H
