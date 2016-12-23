#include "mainwindow.h"
#include <QApplication>
#include <QScreen>
#include "threadsensors.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ThreadSensors *thread = new ThreadSensors();
    QObject::connect(thread,SIGNAL(setSensorData(QList<qreal> *)),&w,SLOT(setSensorData(QList<qreal> *)));
    thread->start(QThread::HighPriority);
    thread->moveToThread(thread);



    return a.exec();
}
