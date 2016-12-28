#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QHBoxLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    counter(0),
    ui(new Ui::MainWindow)
{
    filtered[0] = 0;
    filtered[1] = 0;
    filtered[2] = 0;
    ui->setupUi(this);
    list = new QList<QProgressBar*>();
    list->append(ui->x_l);
    list->append(ui->x_r);
    list->append(ui->y_l);
    list->append(ui->y_r);
    list->append(ui->z_l);
    list->append(ui->z_r);
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

    stackedWidget->setContentsMargins(1,1,1,1);
    viewfinderPage = new QWidget();
    viewfinderPage->setObjectName(QStringLiteral("viewfinderPage"));
    QVBoxLayout *ver_box = new QVBoxLayout(viewfinderPage);
    ver_box->setContentsMargins(1,1,1,1);
    ver_box->setObjectName(QStringLiteral("gridLayout_5"));
    viewfinder = new CameraSurfaceWidget(viewfinderPage);
    viewfinder->setObjectName(QStringLiteral("viewfinder"));
    connect(viewfinder,SIGNAL(setFrame(const QVideoFrame&)),this, SLOT(getFrame(const QVideoFrame&)));

    ver_box->addWidget(viewfinder);

    stackedWidget->addWidget(viewfinderPage);

    QVBoxLayout *hor_box = new QVBoxLayout();
    hor_box->addWidget(stackedWidget);
    ui->centralWidget->setLayout(hor_box);
    //hor_box->addWidget(ui->gridLayoutWidget);
    QWidget *widget = new QWidget(ui->centralWidget);
    widget->setLayout(ui->gridLayout);
    widget->setFixedSize(500,500);
    widget->setStyleSheet("QWidget{background-color: rgba(0,0,0,0)}");
    widget->show();
    hor_box->setContentsMargins(3,3,3,3);


    setCamera(QCameraInfo::defaultCamera());


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

    QCamera::CaptureModes captureMode = QCamera::CaptureVideo;

    if (camera->isCaptureModeSupported(captureMode))
        camera->setCaptureMode(captureMode);
    camera->start();
}


void MainWindow::setSensorData(QList<qreal> *data){
    for(int i = 0; i<3;i++){
        qreal value = data->at(i);
        list->at(i*2)->setValue(value>0?list->at(i*2)->minimum():list->at(i*2)->minimum()-value*10);
        list->at(i*2+1)->setValue(value>0?value*10:list->at(i*2+1)->minimum());
    }
}

void MainWindow::getFrame(const QVideoFrame& frame){
    static int counter = 0;
    ui->counter->setText(QString::number(counter++));
}
