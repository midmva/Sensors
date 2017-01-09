#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCamera>
#include <QProgressBar>
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

public slots:
    void setSensorData(QList<qreal> *list);
    void slotGetFPS(const int count);

private:
    Ui::MainWindow *ui;

    QCamera *camera;
    CameraSurfaceWidget *viewfinder;
    qreal filtered[3];
    QList<QProgressBar*> *list;
    int counter;

private slots:
    void setCamera(const QCameraInfo &cameraInfo);
    void getFrame(const QVideoFrame& frame);

signals:
    void setFrame(const QVideoFrame& frame);

};

#endif // MAINWINDOW_H
