#ifndef THREADIMAGE_H
#define THREADIMAGE_H

#include<QThread>
#include <QTimer>
#include <QVideoFrame>


class ThreadImage : public QThread
{
    Q_OBJECT
public:
    ThreadImage();
    void run();

public slots:
    void slotGetFrame(const QVideoFrame& frame);

private slots:
    QImage imageFromVideoFrame(const QVideoFrame& buffer) const;
    void timeout();

private:
    QTimer *timer;
    int counter;

signals:
    void signalSetFPS(const int count);
};

#endif // THREADIMAGE_H
