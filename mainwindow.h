#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <osgwidget.h>
#include <QPushButton>

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
    void on_actionToggle_toggle();
private slots:


private:
    Ui::MainWindowForm *mMainWindowUI;
};

#endif // MAINWINDOW_H
