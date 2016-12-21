#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include <QCameraViewfinder>
#include <QCameraInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->centralWidget->setLayout(ui->gridLayout);




    QWidget *viewfinderPage;
    QStackedWidget *stackedWidget;
    stackedWidget = new QStackedWidget();
    stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
    stackedWidget->setSizePolicy(sizePolicy);
//    QPalette palette;
//    QBrush brush(QColor(255, 255, 255, 255));
//    brush.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Active, QPalette::Base, brush);
//    QBrush brush1(QColor(145, 145, 145, 255));
//    brush1.setStyle(Qt::SolidPattern);
//    palette.setBrush(QPalette::Active, QPalette::Window, brush1);
//    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
//    palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
//    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
//    palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
//    stackedWidget->setPalette(palette);
    stackedWidget->setContentsMargins(1,1,1,1);
    viewfinderPage = new QWidget();
    viewfinderPage->setObjectName(QStringLiteral("viewfinderPage"));
    QVBoxLayout *ver_box = new QVBoxLayout(viewfinderPage);
    ver_box->setContentsMargins(1,1,1,1);
    ver_box->setObjectName(QStringLiteral("gridLayout_5"));
    viewfinder = new CameraSurfaceWidget(viewfinderPage);
    viewfinder->setObjectName(QStringLiteral("viewfinder"));

    ver_box->addWidget(viewfinder);

    stackedWidget->addWidget(viewfinderPage);
    QVBoxLayout *hor_box = new QVBoxLayout();
    hor_box->addWidget(stackedWidget);
    hor_box->addWidget(ui->gridLayoutWidget);
    hor_box->setContentsMargins(3,3,3,3);
    ui->centralWidget->setLayout(hor_box);



    //ui->verticalLayout->setParent(this);
    setCamera(QCameraInfo::defaultCamera());



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

void MainWindow::setCamera(const QCameraInfo &cameraInfo)
{
    if (camera)
        camera->stop();
    delete camera;

    camera = new QCamera(cameraInfo);

    connect(camera, SIGNAL(error(QCamera::Error)), this, SLOT(displayCameraError()));


    camera->setViewfinder(viewfinder->surface());//! Эту строчку пришлось изменить.


//    ui->captureWidget->setTabEnabled(0, (camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
//    ui->captureWidget->setTabEnabled(1, (camera->isCaptureModeSupported(QCamera::CaptureVideo)));

    QCamera::CaptureModes captureMode = QCamera::CaptureVideo;

    if (camera->isCaptureModeSupported(captureMode))
        camera->setCaptureMode(captureMode);
    camera->start();
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
