#include "mainwindow.h"
//#include <osgwidget.h>
#include "ui_mainwindowform.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mMainWindowUI{new Ui::MainWindowForm}
{
    mMainWindowUI->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete mMainWindowUI;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_ChangeColor_clicked()
{
button_Clicked(1);

}
