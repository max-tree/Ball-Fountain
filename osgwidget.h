#ifndef MEEN_570_OSGWIDGET
#define MEEN_570_OSGWIDGET

#include <QOpenGLWidget>
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>
#include <Physics.h>
#include <osg/PositionAttitudeTransform>

class OSGWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  OSGWidget( QWidget* parent = 0,
             Qt::WindowFlags f = 0 );

  virtual ~OSGWidget();
  osg::PositionAttitudeTransform *sphereTransform[5]{nullptr,nullptr,nullptr,nullptr,nullptr};
  int timerCount{0};
  int sphereStorageIndex{0};
  int getSphereStorageIndex();
  void manage_number_of_spheres(osg::PositionAttitudeTransform *transform);

protected:
  virtual void paintEvent( QPaintEvent* paintEvent );//Note to self: by putting ovverride at the end of this line we can find out if this funciton is from QOpenGLWidget (the base class)
  virtual void paintGL();//Note to self: you cannot override without something being virtual first
  virtual void resizeGL( int width, int height );//Note to self: virtual prevents people overwriting these program by the children.

  void timerEvent(QTimerEvent *);//from robotics. Event driven programming. Connect a timer to a slot and the slot to signals to control what happens when the timer goes off.
  void set_camera();
  void build_manipulator();
  void create_sphere();
  void OSGWidget::delete_sphere(int index);
  void initiate_timer();

private:
  virtual void on_resize( int width, int height );
  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
  osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
  osg::ref_ptr<osgViewer::View> mView;
  osg::ref_ptr<osg::Group> mRoot;
  int mTimerId{0};
};



#endif
