#include "mainwindow.h"
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
    int placeholder{0};
    placeholder = button_Clicked(1);//I should change this to update a class that holds this info instead of a fcn

}

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

int radio_button_clicked(bool change, int initialRadioButton)
{
    static int radioButton{0};
    if(change)
    {
        if(initialRadioButton == 0)
        {

            radioButton = 0;
        }
        else if (initialRadioButton ==1)
        {
            radioButton = 1;
        }
        else
        {
            radioButton = 2;
        }
    }
    return radioButton;
}

void MainWindow::on_radioButtonLeft_clicked(bool checked)
{
    int placeholder{radio_button_clicked(checked, 0)};
}

void MainWindow::on_radioButtonRight_clicked(bool checked)
{
    int placeholder{radio_button_clicked(checked, 2)};
}

void MainWindow::on_radioButtonStraightUp_clicked(bool checked)
{
    int placeholder{radio_button_clicked(checked, 1)};

}
