#include "osgwidget.h"
#include "SpherePhysicsUpdateCallback.h"
#include "SphereColorUpdateCallback.h"
#include <osg/Camera>
#include <osg/DisplaySettings>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osgDB/WriteFile>
#include <osgGA/EventQueue>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osg/LineWidth>
#include <osgUtil/SmoothingVisitor>
//#include <osg/PositionAttitudeTransform>

#include <cassert>
#include <vector>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>

OSGWidget::OSGWidget( QWidget* parent, Qt::WindowFlags flags ):
    QOpenGLWidget{ parent,flags },
    mGraphicsWindow{ new osgViewer::GraphicsWindowEmbedded{ this->x(),
                                                            this->y(),
                                                            this->width(),
                                                            this->height() } }
  , mViewer{ new osgViewer::CompositeViewer }
{
    mRoot = new osg::Group;
    mView = new osgViewer::View;

   set_camera();

    mView->setSceneData( mRoot.get() );
    mView->addEventHandler( new osgViewer::StatsHandler );

    build_manipulator();

    mViewer->addView( mView );
    mViewer->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
    mViewer->realize();
    mView->home();

    create_ground();
    create_fountain();
    create_sphere();

    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );
    this->setMouseTracking( true );
    this->update();

    initiate_timer();
}

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
    transform->setUpdateCallback(new SpherePhysicsUpdateCallback());
    transform->addChild(geode);
    manage_number_of_spheres(transform);
}
OSGWidget::~OSGWidget()
{
    killTimer(mTimerId);
}

void OSGWidget::timerEvent(QTimerEvent *)
{
    update();

    if(timerCount == 30)
    {
        create_sphere();
        timerCount = 0;
    }
    timerCount++;

}

void OSGWidget::paintEvent( QPaintEvent* /* paintEvent */ )
{
    this->makeCurrent();

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );

    this->paintGL();

    painter.end();

    this->doneCurrent();
}

void OSGWidget::paintGL()
{
    mViewer->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
    this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
    mGraphicsWindow->resized( this->x(), this->y(), width, height );

    this->on_resize( width, height );
}

void OSGWidget::on_resize( int width, int height )
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras( cameras );

    auto pixelRatio = this->devicePixelRatio();

    cameras[0]->setViewport( 0, 0, width * pixelRatio, height * pixelRatio );
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if( eventQueue )
        return eventQueue;
    else
        throw std::runtime_error( "Unable to obtain valid event queue");
}

void OSGWidget::set_camera()
{
    float aspectRatio = static_cast<float>( this->width() ) / static_cast<float>( this->height() ); //make camera stuff into a function
    auto pixelRatio   = this->devicePixelRatio();

    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width() * pixelRatio, this->height() * pixelRatio );

    camera->setClearColor( osg::Vec4( 0.f, 0.f, .5, 1.f ) );
    camera->setProjectionMatrixAsPerspective( 45.f, aspectRatio, 1.f, 1000.f );
    camera->setGraphicsContext( mGraphicsWindow );
    mView->setCamera( camera );
}

void OSGWidget::build_manipulator()
{
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow( false );
    manipulator->setHomePosition(osg::Vec3d(0.0,-20.0,7.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));    //Note to self: The eye is the camera position (never the origin)
    mView->setCameraManipulator( manipulator );
}

void OSGWidget::delete_sphere(int index)
{
    mRoot->removeChild(sphereTransform[index]);
    sphereTransform[index] = nullptr;
}



void OSGWidget::manage_number_of_spheres(osg::PositionAttitudeTransform *transform)
{
    mRoot->addChild(transform);
    if(sphereStorageIndex<5)
    {
        if(sphereTransform[sphereStorageIndex] != nullptr)
        {
            delete_sphere(sphereStorageIndex);
            sphereTransform[sphereStorageIndex] = transform;
            sphereStorageIndex++;
        }
        else
        {
            sphereTransform[sphereStorageIndex] = transform;
            sphereStorageIndex++;
        }
    }
    else
    {
        sphereStorageIndex = 0;
        delete_sphere(sphereStorageIndex);
        sphereTransform[sphereStorageIndex] = transform;
        sphereStorageIndex++;
    }
}

void OSGWidget::initiate_timer()
{
    double framesPerSecond{30};
    double timeStep{1.0/framesPerSecond};
    double timerDurationInMilliSeconds{timeStep * 1000};
    mTimerId=startTimer(timerDurationInMilliSeconds);
}

int OSGWidget::getSphereStorageIndex()
{
 return sphereStorageIndex;
}

