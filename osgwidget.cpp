#include "osgwidget.h"
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

class SphereUpdateCallback: public osg::NodeCallback //Note to self: every class needs to have its own .cpp file. MOVE THIS
{//I will have to make one of these for the physics equations. This is the secret. Do exactly what this does but add a physics world into the mix.
public:
    SphereUpdateCallback(){}

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
//        if(mUp)
//            mCount++;
//        else
//            mCount--;

        physicsSphere->change_position();

        currentPosition = physicsSphere->getPosition();
        osg::Vec3d position(currentPosition[0], currentPosition[1], currentPosition[2]);
        osg::Vec3d scaleFactor(0.25, 0.25, 0.25);
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *> (node);
        pat->setPosition(position);
        pat->setScale(scaleFactor);
        traverse(node, nv);


//        if(mCount==300 || mCount==0)
//            mUp=!mUp;
    }
public:
    bool mUp{true};
    unsigned int mCount{0};
    double mScaleStep{1.0/30.0};
    std::array <double, 3> currentPosition{0.0,0.0,0.0};
    physics* physicsSphere = new physics;
};

int  button_Clicked(int change)
{
    static int buttonClicked{1};

    if(change)
    {
    if(buttonClicked)
        buttonClicked--;
    else
        buttonClicked++;
    }

    return buttonClicked;
}


class SphereColorUpdateCallback: public osg::NodeCallback //Note to self: every class needs to have its own .cpp file. MOVE THIS
{//I will have to make one of these for the physics equations. This is the secret. Do exactly what this does but add a physics world into the mix.
public:
    SphereColorUpdateCallback(){}

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

    //Note to self: Make a build camera function from here to first myView
    float aspectRatio = static_cast<float>( this->width() ) / static_cast<float>( this->height() );
    auto pixelRatio   = this->devicePixelRatio();

    //Note to self: "this" always points to the parent class
    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width() * pixelRatio, this->height() * pixelRatio );

    camera->setClearColor( osg::Vec4( 0.f, 0.f, .5, 1.f ) );
    camera->setProjectionMatrixAsPerspective( 45.f, aspectRatio, 1.f, 1000.f );
    camera->setGraphicsContext( mGraphicsWindow );
    mView->setCamera( camera );


    mView->setSceneData( mRoot.get() );
    mView->addEventHandler( new osgViewer::StatsHandler );
//Make buildManipulator fcn
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow( false );
    manipulator->setHomePosition(osg::Vec3d(0.0,-20.0,3.0),osg::Vec3d(0,0,0),osg::Vec3d(0,0,1));    //Note to self: The eye is the camera position (never the origin)
    //end fcn
    mView->setCameraManipulator( manipulator );


    mViewer->addView( mView );
    mViewer->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
    mViewer->realize();
    mView->home();
    //Note to self: This is where you can edit the sphere that is produced. Create create sphere fcn and createGeo fcn

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

//    physics *physicsSphere = new physics;

    osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform;
    transform->setPosition(osg::Vec3( 0.f, 0.f, 0.f ));
    transform->setUpdateCallback(new SphereUpdateCallback());
    transform->addChild(geode);

    mRoot->addChild(transform);

    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );
    this->setMouseTracking( true );

    this->update();

    double framesPerSecond{30};//try changing this to see its limits
    double timeStep{1.0/framesPerSecond};
    double timerDurationInMilliSeconds{timeStep * 1000};
    mTimerId=startTimer(timerDurationInMilliSeconds);

}

OSGWidget::~OSGWidget()
{
    killTimer(mTimerId);
}

void OSGWidget::timerEvent(QTimerEvent *)
{
    update();
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


