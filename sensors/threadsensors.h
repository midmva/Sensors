#ifndef THREADSENSORS_H
#define THREADSENSORS_H

#include <QObject>
#include <QThread>
#include <QtSensors>
#include <QTimer>


class ThreadSensors : public QThread
{
    Q_OBJECT
public:
    ThreadSensors();
    void run();

private:
    QSensor *sensor;
    QTimer *timer;
    qreal x,y,z;
    quint8 counter;
    QList<qreal> data;

private slots:
    void timeOut();

signals:
    void setSensorData(QList<qreal> *list);
};

#endif // THREADSENSORS_H
