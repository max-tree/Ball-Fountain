#ifndef SPHERECOLORUPDATECALLBACK_H
#define SPHERECOLORUPDATECALLBACK_H

#include "osgwidget.h"
#include <osg/ShapeDrawable>
#include "mainwindow.h"

class SphereColorUpdateCallback: public osg::NodeCallback
{
public:
    SphereColorUpdateCallback(){}

    osg::Vec4 pink{ osg::Vec4( 1.f, 0.f, 1.f, 1.f )};
    osg::Vec4 black{osg::Vec4( 0.f, 0.f, 0.f, 0.f )};

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        osg::ShapeDrawable *pat =  dynamic_cast<osg::ShapeDrawable *> (node);

        if(button_Clicked(0))
        {
            pat->setColor(black);

        }
        else
        {
        pat->setColor(pink);

        }
        traverse(node, nv);

    }

};

#endif // SPHERECOLORUPDATECALLBACK_H
