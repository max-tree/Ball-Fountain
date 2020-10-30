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
#include <osg/PositionAttitudeTransform>

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

    create_sphere();

    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );
    this->setMouseTracking( true );
    this->update();

    initiate_timer();
}

OSGWidget::~OSGWidget()
{
    killTimer(mTimerId);
}

void OSGWidget::timerEvent(QTimerEvent *)
{
    update();

    static int timerCount{0};
    if(timerCount == 30)
    {
//        std::cout << "HELLO!\n";
//        mRoot-> = 0;
        create_sphere();

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
    manipulator->setHomePosition(osg::Vec3d(0.0,-20.0,3.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));    //Note to self: The eye is the camera position (never the origin)
    mView->setCameraManipulator( manipulator );
}

void OSGWidget::create_sphere()
{
//    osg::ref_ptr<osg::Sphere> sphere;
    osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 2.0f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
    sd->setColor( osg::Vec4( 0.f, 0.f, 0.f, 0.f ) );
    sd->setName( "Sphere" );
    sd->setUpdateCallback(new SphereColorUpdateCallback());

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );

    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );     //Note to self: this one controls how the scene is built. this one is set to build from the back to the front of the scene.

    osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform;
    transform->setPosition(osg::Vec3( 0.f, 0.f, 0.f ));
    transform->setUpdateCallback(new SpherePhysicsUpdateCallback());
    transform->addChild(geode);
    mRoot->addChild(transform);
}

void OSGWidget::initiate_timer()
{
    double framesPerSecond{30};
    double timeStep{1.0/framesPerSecond};
    double timerDurationInMilliSeconds{timeStep * 1000};
    mTimerId=startTimer(timerDurationInMilliSeconds);
}
