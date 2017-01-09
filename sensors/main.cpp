#include "mainwindow.h"
#include <QApplication>
#include <QScreen>
#include "threadsensors.h"
#include "threadimage.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ThreadSensors *sensors = new ThreadSensors();
    QObject::connect(sensors,SIGNAL(setSensorData(QList<qreal> *)),&w,SLOT(setSensorData(QList<qreal> *)));
    sensors->start(QThread::NormalPriority);
    sensors->moveToThread(sensors);

    ThreadImage *image = new ThreadImage();
    QObject::connect(&w,SIGNAL(setFrame(const QVideoFrame&)),image,SLOT(slotGetFrame(const QVideoFrame& )));
    QObject::connect(image,SIGNAL(signalSetFPS(const int)),&w,SLOT(slotGetFPS(const int)));
    image->start(QThread::HighPriority);
    image->moveToThread(image);

    return a.exec();
}
