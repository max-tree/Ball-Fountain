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

private:
    Ui::MainWindowForm *mMainWindowUI;
};


int  button_Clicked(int change);

#endif // MAINWINDOW_H
