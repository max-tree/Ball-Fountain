#ifndef MEEN_570_OSGWIDGET
#define MEEN_570_OSGWIDGET

#include <QOpenGLWidget>
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>
#include <osg/PositionAttitudeTransform>


class OSGWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  OSGWidget( QWidget* parent = 0,
             Qt::WindowFlags f = 0 );

  virtual ~OSGWidget();
  int timerCount{0};
  int sphereStorageIndex{0};
  int getSphereStorageIndex();
  void manage_number_of_spheres(osg::PositionAttitudeTransform *transform);
  osg::Vec4 black{osg::Vec4( 0.f, 0.f, 0.f, 0.f )};
  osg::Vec4 yellow{osg::Vec4( 1.f, 1.f, 0.f, 0.f )};
  osg::PositionAttitudeTransform *sphereTransform[5]{nullptr,nullptr,nullptr,nullptr,nullptr};

protected:
  virtual void paintEvent( QPaintEvent* paintEvent );
  virtual void paintGL();
  virtual void resizeGL( int width, int height );

  void timerEvent(QTimerEvent *);
  void set_camera();
  void build_manipulator();
  void create_sphere();
  void create_fountain();
  void create_ground();
  void delete_sphere(int index);
  void initiate_timer();
  void initialize_sphere_record();

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
