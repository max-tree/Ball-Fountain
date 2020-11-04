#include "SphereColorUpdateCallback.h"

void SphereColorUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    osg::ShapeDrawable *pat =  dynamic_cast<osg::ShapeDrawable *> (node);

    if(push_button_clicked(0))
        pat->setColor(black);
    else
        pat->setColor(pink);
    traverse(node, nv);
}
