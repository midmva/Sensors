#include "threadimage.h"

ThreadImage::ThreadImage()
{
    counter = 0;
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),SLOT(timeout()));
    timer->start(100);
}

void ThreadImage::run(){
    //timer->start(1000);
    exec();
}

void ThreadImage::slotGetFrame(const QVideoFrame& frame){
    if (counter++ == 2)
        QImage image = imageFromVideoFrame(frame);
    //counter++;
}


QImage ThreadImage::imageFromVideoFrame(const QVideoFrame& buffer) const
{
    QImage img;
    QVideoFrame frame(buffer);  // make a copy we can call map (non-const) on
    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(
                frame.pixelFormat());
    // BUT the frame.pixelFormat() is QVideoFrame::Format_Jpeg, and this is
    // mapped to QImage::Format_Invalid by
    // QVideoFrame::imageFormatFromPixelFormat
    if (imageFormat != QImage::Format_Invalid) {
        img = QImage(frame.bits(),
                     frame.width(),
                     frame.height(),
                     // frame.bytesPerLine(),
                     imageFormat);
    } else {
        // e.g. JPEG
        int nbytes = frame.mappedBytes();
        img = QImage::fromData(frame.bits(), nbytes);
    }
    frame.unmap();
    return img;
}


void ThreadImage::timeout(){
    emit signalSetFPS(counter);
    counter = 0;
}
