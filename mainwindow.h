#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <osgwidget.h>
#include <QPushButton>
#include <physics.h>

namespace Ui {
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionExit_triggered();
private slots:
    void on_ChangeColor_clicked();

    void on_radioButtonLeft_clicked(bool checked);

    void on_radioButtonRight_clicked(bool checked);

    void on_radioButtonStraightUp_clicked(bool checked);

private:
    Ui::MainWindowForm *mMainWindowUI;
};


int  button_Clicked(int change);
int radio_button_clicked(bool change, int initialRadioButton);


#endif // MAINWINDOW_H
