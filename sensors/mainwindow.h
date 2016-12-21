#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSensors>
#include <QTimer>
#include <QCamera>
#include <QCameraImageCapture>
#include <camerasurfacewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSensor *sensor;
    QTimer *timer;
    QCamera *camera;
    CameraSurfaceWidget *viewfinder;

private slots:
    void setCamera(const QCameraInfo &cameraInfo);
    void timeOut();
};

#endif // MAINWINDOW_H
