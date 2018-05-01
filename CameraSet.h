#ifndef CAMERASET_H
#define CAMERASET_H
#include "mythread.h"
#include <QDialog>
#include <QTcpSocket>
#include <QPixmap>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QDebug>
#include <QFileDialog>
#include <QScreen>

namespace Ui {
class CameraSet;
}

class CameraSet : public QDialog
{
    Q_OBJECT

public:
    explicit CameraSet(QWidget *parent = 0);
    QImage img;
    ~CameraSet();
    QTcpSocket* set_socket;

    MyThread *recvThread_set;

private slots:

    void on_show_clicked();

    void slotReadyRead();

    void on_save_clicked();

    void closeEvent(QCloseEvent *);//重写关闭事件

    void connectSocket();
    void on_select_clicked();

    void on_start_test_clicked();

signals:
    void close_signal();
    void init_signal();//初始化mythread线程
    void sendCMD(const QString &);

private:
    Ui::CameraSet *ui;
};

#endif // CAMERASET_H
