#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QScreen>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->gridLayout);
    //ui->verticalLayout->setParent(this);
    sensor = new QSensor("QAccelerometer");
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    sensor->start();
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeOut(){
    QSensorReading *reading = sensor->reading();
    qreal x = reading->property("x").value<qreal>();
    if(x<0){
        ui->x_l->setValue(ui->x_l->minimum()-x*10);
        ui->x_r->setValue(ui->x_r->minimum());
    }
    else{
        ui->x_r->setValue(x*10);
        ui->x_l->setValue(ui->x_l->minimum());
    }
    qreal y = reading->property("y").value<qreal>();
    if(y<0){
        ui->y_l->setValue(ui->y_l->minimum()-y*10);
        ui->y_r->setValue(ui->y_r->minimum());
    }
    else{
        ui->y_r->setValue(y*10);
        ui->y_l->setValue(ui->y_l->minimum());
    }
    qreal z = reading->property("z").value<qreal>();
    if(z<0){
        ui->z_l->setValue(ui->z_l->minimum() - z*10);
        ui->z_r->setValue(ui->z_r->minimum());
    }
    else{
        ui->z_r->setValue(z*10);
        ui->z_l->setValue(ui->z_l->minimum());
    }
}
