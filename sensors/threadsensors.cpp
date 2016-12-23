#include "threadsensors.h"

ThreadSensors::ThreadSensors()
{

}

void ThreadSensors::run(){
    sensor = new QSensor("QAccelerometer");
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    sensor->start();
    counter = 0;
    timer->start(1);
    exec();
}


void ThreadSensors::timeOut(){
    QSensorReading *reading = sensor->reading();
    x += reading->property("x").value<qreal>();
    y += reading->property("y").value<qreal>();
    z += reading->property("z").value<qreal>();
    if (counter++>40){
        data.clear();
        data.append(x/counter);
        data.append(y/counter);
        data.append(z/counter);
        emit setSensorData(&data);
        counter = x = y = z = 0;
    }

}
