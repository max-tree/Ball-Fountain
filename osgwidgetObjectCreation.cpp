#include <osgwidget.h>

#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>

#include "SpherePhysicsUpdateCallback.h"
#include "SphereColorUpdateCallback.h"

#include <vector>

void OSGWidget::create_ground()
{
    float widthX{10.0};
    float lengthY{10.0};
    float heightZ{.125};
    osg::Vec3 center{osg::Vec3( 0.f, 0.f, heightZ/2 )};
    osg::Box* box    = new osg::Box(center, widthX, lengthY, heightZ);
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
    sd->setColor( osg::Vec4( 1.f, 1.f, 0.f, 0.f ) );
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform;
    transform->addChild(geode);
    mRoot->addChild(transform);
}

void OSGWidget::create_fountain()
{
    float cubeSideLength{1.5};
    osg::Vec3 center{osg::Vec3( 0.f, 0.f, cubeSideLength/2 )};
    osg::Box* box    = new osg::Box( center, cubeSideLength );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( box );
    sd->setColor(yellow);
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform;
    transform->addChild(geode);
    mRoot->addChild(transform);
}

void OSGWidget::create_sphere()
{
    float sphereDiameter{2.0};
    osg::Vec3 center{osg::Vec3( 0.f, 0.f, sphereDiameter )};
    osg::Sphere* sphere    = new osg::Sphere(center, sphereDiameter);
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
    sd->setColor(black);
    sd->setName( "Sphere" );
    sd->setUpdateCallback(new SphereColorUpdateCallback());

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

    osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform;
    transform->setUpdateCallback(new SpherePhysicsUpdateCallback);
    transform->addChild(geode);
    mRoot->addChild(transform);
    manage_number_of_spheres(transform);
}
