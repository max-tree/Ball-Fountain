cmake_minimum_required(VERSION 3.4)
project(BallFountainSleepScreen)

FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText)
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
INCLUDE_DIRECTORIES( ${OPENSCENEGRAPH_INCLUDE_DIRS} )


SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)
SET(TEST_NAME ${PROJECT_NAME}_UnitTest)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    osgwidget.cpp
    Physics.cpp
    ChangeVelocityDueToGravity_unitTest.cpp
    ChangePosition_UnitTest.cpp
    BounceOffTheGround_unitTest.cpp
    CheckIfBallHasHitTheGround_unitTest.cpp
    mainwindow.h
    osgwidget.h
    Physics.h
    SpherePhysicsUpdateCallback.h
    SphereColorUpdateCallback.h
    mainwindowform.ui

)

target_link_libraries( ${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
)

