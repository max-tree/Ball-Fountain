#ifndef SPHERECOLORUPDATECALLBACK_H
#define SPHERECOLORUPDATECALLBACK_H

#include "osgwidget.h"
#include <osg/ShapeDrawable>
#include "mainwindow.h"

class SphereColorUpdateCallback: public osg::NodeCallback //Note to self: every class needs to have its own .cpp file. MOVE THIS
{//I will have to make one of these for the physics equations. This is the secret. Do exactly what this does but add a physics world into the mix.
public:
    SphereColorUpdateCallback(){}
    void SphereColorUpdateCallbackDestroy(osg::Node* node) {node = NULL;}
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        osg::ShapeDrawable *pat =  dynamic_cast<osg::ShapeDrawable *> (node);
//        std::cout << "here" << '\n';

        if(button_Clicked(0))
        {
            pat->setColor( osg::Vec4( 0.f, 0.f, 0.f, 0.f ) );

        }
        else
        {
        pat->setColor( osg::Vec4( 1.f, 0.f, 1.f, 1.f ) );

        }
        traverse(node, nv);

    }

};

#endif // SPHERECOLORUPDATECALLBACK_H
