cmake_minimum_required(VERSION 3.4)
project(BallFountainSleepScreen)

FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText)
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
INCLUDE_DIRECTORIES( ${OPENSCENEGRAPH_INCLUDE_DIRS})


SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

add_library(Physics STATIC
    Physics.cpp
    Physics.h
)

add_executable(Physics_UnitTests
    ChangeVelocityDueToGravity_unitTest.cpp
    ChangePosition_UnitTest.cpp
    ChangeVelocityIfBallHitsTheGround_unitTest.cpp
    CheckIfBallHasHitTheGround_unitTest.cpp
    ChangeBallVelocityIfCollisionOccurs_unitTest.cpp
    CalculateDistanceBetweenTwoVectors_unitTest.cpp
    DotProductOfTwoVectors_unitTest.cpp
)

target_link_libraries(Physics_UnitTests
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    Physics
)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    osgwidget.cpp
    osgwidgetObjectCreation.cpp
    SpherePhysicsUpdateCallback.cpp
    SphereColorUpdateCallback.cpp
    mainwindow.h
    osgwidget.h
    mainwindowform.ui
    SpherePhysicsUpdateCallback.h
    SphereColorUpdateCallback.h
)

target_link_libraries( ${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
    Physics
)
